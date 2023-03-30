Servo coxa1;
Servo femur1;
Servo tibia1;

Servo coxa2;
Servo femur2;
Servo tibia2;

Servo coxa3;
Servo femur3;
Servo tibia3;

Servo coxa4;
Servo femur4;
Servo tibia4;

Servo coxa5;
Servo femur5;
Servo tibia5;

Servo coxa6;
Servo femur6;
Servo tibia6;

const int coxa1Pin = 22;
const int femur1Pin = 23;
const int tibia1Pin = 24;

const int coxa2Pin = 25;
const int femur2Pin = 26;
const int tibia2Pin = 27;

const int coxa3Pin = 28;
const int femur3Pin = 29;
const int tibia3Pin = 30;

const int coxa4Pin = 31;
const int femur4Pin = 32;
const int tibia4Pin = 33;

const int coxa5Pin = 34;
const int femur5Pin = 35;
const int tibia5Pin = 36;

const int coxa6Pin = 37;
const int femur6Pin = 38;
const int tibia6Pin = 39;

const Vector3 offsets1 = {90,92,-18};
const Vector3 offsets2 = {93,84,-15};
const Vector3 offsets3 = {93,85,-18}; 
const Vector3 offsets4 = {87,86,-26};
const Vector3 offsets5 = {94,86,-22};
const Vector3 offsets6 = {93,93,-24};
const Vector3 offsets[6] = {offsets1, offsets2, offsets3, offsets4, offsets5, offsets6};

const Vector2 calibrationsTibia1 = {2427.5, 581.5};
const Vector2 calibrationsFemur1 = {2382.5, 552.5};
const Vector2 calibrationsCoxa1 = {2461, 569};

const Vector2 calibrationsTibia2 = {2401, 609};
const Vector2 calibrationsFemur2 = {2454.5, 572.5};
const Vector2 calibrationsCoxa2 = {2473.5, 531.5};

const Vector2 calibrationsTibia3 = {2433, 625};
const Vector2 calibrationsFemur3 = {2410.5, 552.5};
const Vector2 calibrationsCoxa3 = {2435, 547};

const Vector2 calibrationsTibia4 = {2386, 570};
const Vector2 calibrationsFemur4 = {2406, 634};
const Vector2 calibrationsCoxa4 = {2407, 547};

const Vector2 calibrationsTibia5 = {2462, 546};
const Vector2 calibrationsFemur5 = {2424, 540};
const Vector2 calibrationsCoxa5 = {2485, 589};

const Vector2 calibrationsTibia6 = {2439, 535};
const Vector2 calibrationsFemur6 = {2442, 614};
const Vector2 calibrationsCoxa6 = {2473.5, 547.5};

const Vector2 calibrations[18] = {
  calibrationsTibia1, 
  calibrationsFemur1,
  calibrationsCoxa1,

  calibrationsTibia2, 
  calibrationsFemur2,
  calibrationsCoxa2,

  calibrationsTibia3, 
  calibrationsFemur3,
  calibrationsCoxa3,

  calibrationsTibia4, 
  calibrationsFemur4,
  calibrationsCoxa4,

  calibrationsTibia5, 
  calibrationsFemur5,
  calibrationsCoxa5,

  calibrationsTibia6, 
  calibrationsFemur6,
  calibrationsCoxa6};

const float a1 = 41;  //Coxa Length
const float a2 = 116; //Femur Length
const float a3 = 183; //Tibia Length   
float legLength = a1+a2+a3;

Vector3 currentPoints[6];
Vector3 cycleStartPoints[6];

Vector3 currentRot(180, 0, 180);
Vector3 targetRot(180, 0, 180);

float strideMultiplier[6] = {1, 1, 1, -1, -1, -1};
float rotationMultiplier[6] = {-1, 0, 1, -1, 0 , 1};

Vector3 ControlPoints[10];
Vector3 RotateControlPoints[10];

Vector3 AttackControlPoints[10];


void attachServos(){
  coxa1.attach(coxa1Pin,500,2500);
  femur1.attach(femur1Pin,500,2500);
  tibia1.attach(tibia1Pin,500,2500); 

  coxa2.attach(coxa2Pin,500,2500);
  femur2.attach(femur2Pin,500,2500);
  tibia2.attach(tibia2Pin,500,2500);  

  coxa3.attach(coxa3Pin,500,2500);
  femur3.attach(femur3Pin,500,2500);
  tibia3.attach(tibia3Pin,500,2500);

  coxa4.attach(coxa4Pin,500,2500);
  femur4.attach(femur4Pin,500,2500);
  tibia4.attach(tibia4Pin,500,2500);

  coxa5.attach(coxa5Pin,500,2500);
  femur5.attach(femur5Pin,500,2500);
  tibia5.attach(tibia5Pin,500,2500);

  coxa6.attach(coxa6Pin,500,2500);
  femur6.attach(femur6Pin,500,2500);
  tibia6.attach(tibia6Pin,500,2500);  
}