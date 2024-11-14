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

const float a1 = 46;  //Coxa Length
const float a2 = 108; //Femur Length
const float a3 = 200; //Tibia Length   
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

bool servosAttached = false;

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

  servosAttached = true;  
  Serial.println("Servos Attached");
}

void detachServos() {
  coxa1.detach();
  femur1.detach();
  tibia1.detach();

  coxa2.detach();
  femur2.detach();
  tibia2.detach();

  coxa3.detach();
  femur3.detach();
  tibia3.detach();

  coxa4.detach();
  femur4.detach();
  tibia4.detach();

  coxa5.detach();
  femur5.detach();
  tibia5.detach();

  coxa6.detach();
  femur6.detach();
  tibia6.detach();

  servosAttached = false;
  Serial.println("Servos Detached");
}

