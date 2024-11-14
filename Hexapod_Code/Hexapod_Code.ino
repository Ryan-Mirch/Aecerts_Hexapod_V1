#include <Arduino.h>
#include <Servo.h>
#include <math.h>
#include <EEPROM.h>

#include "vectors.h"
#include "Helpers.h"
#include "RC.h"
#include "Initializations.h"

#define UNPRESSED 0x1
#define PRESSED 0x0

enum State {
  Initialize,
  Stand,
  Car,
  Crab,
  Calibrate,
  SlamAttack,
  Sleep,
  Attach
};

enum LegState {
  Propelling,
  Lifting,
  Standing,
  Reset
};

enum Gait {
  TRI,     //0
  RIPPLE,  //1
  WAVE,    //2
  QUAD,    //3
  BI,      //4
  HOP      //5
};

bool connected = false;
bool dynamicStrideLength = true;

int totalGaits = 6;
Gait gaits[6] = { TRI, RIPPLE, WAVE, QUAD, BI, HOP };

int8_t rawOffsets[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
Vector3 baseOffset = {90,50,-10};
Vector3 offsets[6];

float points = 1000;
int cycleProgress[6];
LegState legStates[6];
int standProgress = 0;

State currentState = Initialize;
Gait currentGait = TRI;
Gait previousGait = TRI;
int currentGaitID = 0;

float standingDistanceAdjustment = 0;

float distanceFromGroundBase = -60;
float distanceFromGround = 0;
float targetDistanceFromGround = 0;

float liftHeight = 130;
float landHeight = 70;
float strideOvershoot = 10;
float distanceFromCenter = 173;

float crabTargetForwardAmount = 0;
float crabForwardAmount = 0;

Vector2 joy1TargetVector = Vector2(0, 0);
float joy1TargetMagnitude = 0;

Vector2 joy1CurrentVector = Vector2(0, 0);
float joy1CurrentMagnitude = 0;

Vector2 joy2TargetVector = Vector2(0, 0);
float joy2TargetMagnitude = 0;

Vector2 joy2CurrentVector = Vector2(0, 0);
float joy2CurrentMagnitude = 0;

unsigned long timeSinceLastInput = 0;

float landingBuffer = 15;

int attackCooldown = 0;
long elapsedTime = 0;
long loopStartTime = 0;



void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  attachServos();
  RC_Setup();
  loadRawOffsetsFromEEPROM();
  stateInitialize();
}

void loop() {
  elapsedTime = millis() - loopStartTime;
  loopStartTime = millis();

  connected = GetSendNRFData(); 

  if (!connected) {
    //attachServoState();
    sleepState();
    return;
  }

  if(currentType == RC_CONTROL_DATA) processControlData(rc_control_data);
  if(currentType == RC_SETTINGS_DATA) processSettingsData(rc_settings_data);
}

void processControlData(const RC_Control_Data_Package& data) {
  sendType = HEXAPOD_SENSOR_DATA; //when control data is being process, always send sensor data back.

  dynamicStrideLength = data.dynamic_stride_length;

  /*sleep from controller*/
  if (data.sleep == 1) {
    
    sleepState();
    return;
  }

  /*idle from controller*/
  if (data.idle == 1) {
    standingState();
    return;
  }

  double joy1x = map(data.joy1_X, 0, 254, -100, 100);
  double joy1y = map(data.joy1_Y, 0, 254, -100, 100);

  double joy2x = map(data.joy2_X, 0, 254, -100, 100);
  double joy2y = map(data.joy2_Y, 0, 254, -100, 100);

  joy1TargetVector = Vector2(joy1x, joy1y);
  joy1TargetMagnitude = constrain(calculateHypotenuse(abs(joy1x), abs(joy1y)), 0, 100);

  joy2TargetVector = Vector2(joy2x, joy2y);
  joy2TargetMagnitude = constrain(calculateHypotenuse(abs(joy2x), abs(joy2y)), 0, 100);

  targetDistanceFromGround = distanceFromGroundBase + (data.slider2 * -1.7);
  distanceFromGround = lerp(distanceFromGround, targetDistanceFromGround, 0.04);
  if(distanceFromGround >= 0) distanceFromGround = targetDistanceFromGround;

  distanceFromCenter = 170;

  joy1CurrentVector = lerp(joy1CurrentVector, joy1TargetVector, 0.08);
  joy1CurrentMagnitude = lerp(joy1CurrentMagnitude, joy1TargetMagnitude, 0.08);

  joy2CurrentVector = lerp(joy2CurrentVector, joy2TargetVector, 0.12);
  joy2CurrentMagnitude = lerp(joy2CurrentMagnitude, joy2TargetMagnitude, 0.12);

  previousGait = currentGait;
  currentGait = gaits[data.gait]; 

  /*Drive*/
  if (abs(joy1CurrentMagnitude) >= 10 || abs(joy2CurrentMagnitude) >= 10) {
    carState();
    timeSinceLastInput = millis();
    return;
  }

  /*idle from hexapod*/
  if (abs(timeSinceLastInput - millis()) > 5) {
    standingState();
    return;
  }

  /*Attack*/
  if (data.joy1_Button == PRESSED && attackCooldown == 0) {
    Serial.println("slam attack");
    resetMovementVectors();
    slamAttack();
    standingState();
    attackCooldown = 50;
    loopStartTime = millis();
    return;
  } else {
    attackCooldown = max(attackCooldown - elapsedTime, 0);
  }
}

void processSettingsData(const RC_Settings_Data_Package& data) {
  sendType = HEXAPOD_SETTINGS_DATA; //when settings data is being process, always send settings data back.
  if (data.calibrating == 1) {
    calibrationState();
    return;
  }  

  //finished calibrating, save offsets.
  if (currentState == Calibrate) {
    saveOffsets();
  }
  sleepState();
}

void resetMovementVectors() {
  joy1CurrentVector = Vector2(0, 0);
  joy1CurrentMagnitude = 0;

  joy2CurrentVector = Vector2(0, 0);
  joy2CurrentMagnitude = 0;
}

void setCycleStartPoints(int leg) {
  cycleStartPoints[leg] = currentPoints[leg];
}

void setCycleStartPoints() {
  for (int i = 0; i < 6; i++) {
    cycleStartPoints[i] = currentPoints[i];
  }
}

int angleToMicroseconds(double angle) {
  double val = 500.0 + (((2500.0 - 500.0) / 180.0) * angle);
  return (int)val;
}

void rotateToAngle(int leg, Vector3 targetRot) {
  if(!servosAttached) attachServos();
  
  int coxaMicroseconds = angleToMicroseconds(targetRot.x);
  int femurMicroseconds = angleToMicroseconds(targetRot.y);
  int tibiaMicroseconds = angleToMicroseconds(targetRot.z);

  switch (leg) {
    case 0:
      coxa1.writeMicroseconds(coxaMicroseconds);
      femur1.writeMicroseconds(femurMicroseconds);
      tibia1.writeMicroseconds(tibiaMicroseconds);
      break;

    case 1:
      coxa2.writeMicroseconds(coxaMicroseconds);
      femur2.writeMicroseconds(femurMicroseconds);
      tibia2.writeMicroseconds(tibiaMicroseconds);
      break;

    case 2:
      coxa3.writeMicroseconds(coxaMicroseconds);
      femur3.writeMicroseconds(femurMicroseconds);
      tibia3.writeMicroseconds(tibiaMicroseconds);
      break;

    case 3:
      coxa4.writeMicroseconds(coxaMicroseconds);
      femur4.writeMicroseconds(femurMicroseconds);
      tibia4.writeMicroseconds(tibiaMicroseconds);
      break;

    case 4:
      coxa5.writeMicroseconds(coxaMicroseconds);
      femur5.writeMicroseconds(femurMicroseconds);
      tibia5.writeMicroseconds(tibiaMicroseconds);
      break;

    case 5:
      coxa6.writeMicroseconds(coxaMicroseconds);
      femur6.writeMicroseconds(femurMicroseconds);
      tibia6.writeMicroseconds(tibiaMicroseconds);
      break;

    default:
      break;
  }
  return;
}

void moveToPos(int leg, Vector3 pos) {
  hex_sensor_data.foot_positions[leg].x = (int)pos.x;
  hex_sensor_data.foot_positions[leg].y = (int)pos.y;

  if(!servosAttached) attachServos();

  currentPoints[leg] = pos;

  float dis = Vector3(0, 0, 0).distanceTo(pos);
  if (dis > legLength) {
    print_value("Point impossible to reach", pos, false);
    print_value("Distance", dis, true);
    return;
  }

  float x = pos.x;
  float y = pos.y;
  float z = pos.z;

  float o1 = offsets[leg].x;
  float o2 = offsets[leg].y;
  float o3 = offsets[leg].z;

  float theta1 = atan2(y, x) * (180 / PI) + o1;  // base angle
  float l = sqrt(x * x + y * y);                 // x and y extension
  float l1 = l - a1;
  float h = sqrt(l1 * l1 + z * z);

  float phi1 = acos(constrain((pow(h, 2) + pow(a2, 2) - pow(a3, 2)) / (2 * h * a2), -1, 1));
  float phi2 = atan2(z, l1);
  float theta2 = (phi1 + phi2) * 180 / PI + o2;
  float phi3 = acos(constrain((pow(a2, 2) + pow(a3, 2) - pow(h, 2)) / (2 * a2 * a3), -1, 1));
  float theta3 = 180 - (phi3 * 180 / PI) + o3;

  targetRot = Vector3(theta1, theta2, theta3);

  int coxaMicroseconds = angleToMicroseconds(targetRot.x);
  int femurMicroseconds = angleToMicroseconds(targetRot.y);
  int tibiaMicroseconds = angleToMicroseconds(targetRot.z);

  switch (leg) {
    case 0:
      coxa1.writeMicroseconds(coxaMicroseconds);
      femur1.writeMicroseconds(femurMicroseconds);
      tibia1.writeMicroseconds(tibiaMicroseconds);
      break;

    case 1:
      coxa2.writeMicroseconds(coxaMicroseconds);
      femur2.writeMicroseconds(femurMicroseconds);
      tibia2.writeMicroseconds(tibiaMicroseconds);
      break;

    case 2:
      coxa3.writeMicroseconds(coxaMicroseconds);
      femur3.writeMicroseconds(femurMicroseconds);
      tibia3.writeMicroseconds(tibiaMicroseconds);
      break;

    case 3:
      coxa4.writeMicroseconds(coxaMicroseconds);
      femur4.writeMicroseconds(femurMicroseconds);
      tibia4.writeMicroseconds(tibiaMicroseconds);
      break;

    case 4:
      coxa5.writeMicroseconds(coxaMicroseconds);
      femur5.writeMicroseconds(femurMicroseconds);
      tibia5.writeMicroseconds(tibiaMicroseconds);
      break;

    case 5:
      coxa6.writeMicroseconds(coxaMicroseconds);
      femur6.writeMicroseconds(femurMicroseconds);
      tibia6.writeMicroseconds(tibiaMicroseconds);
      break;

    default:
      break;
  }
  return;
}

#define EEPROM_OFFSETS_ADDR 0  // 18 bytes

void saveOffsets() {  
  Serial.print("Saving rawOffsets to EEPROM. ");
  for (int i = 0; i < 18; i++) {
    EEPROM.put(EEPROM_OFFSETS_ADDR + i * sizeof(int8_t), rawOffsets[i]);
  }
  Serial.println("Done");
}

void loadRawOffsetsFromEEPROM() {
  Serial.println("Filling rawOffsets from EEPROM.");
  for (int i = 0; i < 18; i++) {
    int8_t val;
    EEPROM.get(EEPROM_OFFSETS_ADDR + i * sizeof(int8_t), val);
    rawOffsets[i] = val;
  }
  updateOffsetVariables();
  printRawOffsets();
}

void updateOffsetVariables() {  
  //updating Vector3 offsets[]
  //Serial.println("Filling offsets from rawOffsets.");
  for (int i = 0; i < 6; ++i) {
    offsets[i] = Vector3(rawOffsets[i * 3] + baseOffset.x, rawOffsets[i * 3 + 1] + baseOffset.y, rawOffsets[i * 3 + 2] + baseOffset.z);
  }

  //updating hex_data.offsets[18]
  //Serial.println("Filling hex_data.offsets from rawOffsets.");  
  for (int i = 0; i < 18; i++) {
    hex_settings_data.offsets[i] = rawOffsets[i];
  }
}

void setOffsetsFromControllerData() {    
  
  //dont set offsets data if the controller isnt connected
  if(rc_settings_data.offsets[0] == -128 || !connected){
    return;
  }

  //Serial.print("Filling rawOffsets from rc_settings_data.offsets. ");
  printRawOffsets();
  for (int i = 0; i < 18; i++) {
    rawOffsets[i] = rc_settings_data.offsets[i];
  }

  updateOffsetVariables();
  
  //Serial.println("Done");
}

void printConnectedStatus(){
  Serial.print("Connected: ");
  if(connected)Serial.println("TRUE");
  else Serial.println("FALSE");
}

void printRawOffsets() {
  return;
  Serial.print("Raw Offsets: ");
  for (int i = 0; i < 18; i++) {

    Serial.print(rawOffsets[i]);
    if (i < 17) {
      Serial.print(" ");
    }
  }
  Serial.println();

  Serial.print("Offsets: ");
    for (int i = 0; i < 6; i++) {
      Serial.print(offsets[i].toString());
      if (i < 5) {
        Serial.print(" ");
      }
    }
    Serial.println();

    Serial.print("EEPROM: ");
    for (int i = 0; i < 18; i++) {
      int8_t val;
      EEPROM.get(i * sizeof(int8_t), val);
      Serial.print(val);
      if (i < 17) {
        Serial.print(" ");
      }
    }
    Serial.println();
}
