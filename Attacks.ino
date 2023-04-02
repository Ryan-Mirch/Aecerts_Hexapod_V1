
bool slamstarted = false;
void slamAttack(){
  setCycleStartPoints();
  currentState = Animate;
  slamstarted = false;

  int attackSpeed = map(rc_data.slider2,0,100,20,100);

  for(int i = 0; i < attackSpeed; i++){
    float t = (float)i/attackSpeed;
    moveToPos(0, getFootPlacementPathPoint(0,t));
    moveToPos(1, getFootPlacementPathPoint(1,t));
    moveToPos(2, getFootPlacementPathPoint(2,t));
    moveToPos(3, getFootPlacementPathPoint(3,t));
    moveToPos(4, getFootPlacementPathPoint(4,t));
    moveToPos(5, getFootPlacementPathPoint(5,t));
  }
  setCycleStartPoints();

  for(int i = 0; i < attackSpeed*2; i++){
    float t = (float)i/(attackSpeed*2);
    moveToPos(0, getLeapPathPoint(0,t));
    moveToPos(1, getLeapPathPoint(1,t));
    moveToPos(4, getLeapPathPoint(4,t));
    moveToPos(5, getLeapPathPoint(5,t));

    moveToPos(2, getSlamPathPoint(2,t));
    moveToPos(3, getSlamPathPoint(3,t));
    if(t >= 0.5 && slamstarted == false) {
      slamstarted = true;      
    }
  }
  
  setCycleStartPoints();
  delay(400);
}

Vector3 getFootPlacementPathPoint(int leg, float t){
  int xOffset = 0;
  int yOffset = 0;
  int zOffset = 0;

  if(leg == 1){  
    zOffset = -50;
  }
  if(leg == 4){   
    zOffset = -50;
  }

  ControlPoints[0] = cycleStartPoints[leg];
  ControlPoints[1] = Vector3(distanceFromCenter, -120 * strideMultiplier[leg], -50 + zOffset).rotate(55 * rotationMultiplier[leg], Vector2(distanceFromCenter,0)); 
  Vector3 point = GetPointOnBezierCurve(ControlPoints, 2, t);

  return point;
}

Vector3 getLeapPathPoint(int leg, float t){
  return cycleStartPoints[leg];
}

Vector3 getSlamPathPoint(int leg, float t){

  float slamPercentage = 0.75;
  //Leg Raise
  if(t < slamPercentage){
    ControlPoints[0] = cycleStartPoints[leg];
    ControlPoints[1] = Vector3(200, 0, 200).rotate(-40 * rotationMultiplier[leg], Vector2(0,0)); 
    ControlPoints[2] = Vector3(0, 0, 270).rotate(-35 * rotationMultiplier[leg], Vector2(0,0)); 
    Vector3 point = GetPointOnBezierCurve(ControlPoints, 3, mapFloat(t,0,slamPercentage,0,1));
    return point;
  }

  //Leg Slam
  if(t >= slamPercentage){
    ControlPoints[0] = Vector3(40, 0, 290).rotate(-35 * rotationMultiplier[leg], Vector2(0,0)); 
    ControlPoints[1] = Vector3(300, 0, 300).rotate(-35 * rotationMultiplier[leg], Vector2(0,0)); 
    ControlPoints[2] = Vector3(400, 0, 0).rotate(-35 * rotationMultiplier[leg], Vector2(0,0)); 
    ControlPoints[3] = Vector3(180, 0, -130).rotate(-35 * rotationMultiplier[leg], Vector2(0,0)); 
    Vector3 point = GetPointOnBezierCurve(ControlPoints, 4, mapFloat(t,slamPercentage,1,0,1));
    return point;
  }

  
}