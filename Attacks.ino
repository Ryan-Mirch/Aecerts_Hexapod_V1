void slamAttack(){
  setCycleStartPoints();

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
  delay(200);

  for(int i = 0; i < attackSpeed*3; i++){
    float t = (float)i/attackSpeed*3;
    moveToPos(0, getLeapPathPoint(0,t));
    moveToPos(1, getLeapPathPoint(1,t));
    moveToPos(4, getLeapPathPoint(4,t));
    moveToPos(5, getLeapPathPoint(5,t));
  }

  for(int i = 0; i < attackSpeed*3; i++){
    float t = (float)i/attackSpeed*3;
    moveToPos(2, getSlamPathPoint(2,t));
    moveToPos(3, getSlamPathPoint(3,t));
  }
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

  ControlPoints[0] = cycleStartPoints[leg];
  ControlPoints[1] = Vector3(100, 0, 50).rotate(55 * rotationMultiplier[leg], Vector2(distanceFromCenter,0));
  ControlPoints[2] = Vector3(150, 0, 200).rotate(55 * rotationMultiplier[leg], Vector2(distanceFromCenter,0)); 
  ControlPoints[3] = Vector3(200, 0, 200).rotate(55 * rotationMultiplier[leg], Vector2(distanceFromCenter,0)); 
  ControlPoints[4] = Vector3(distanceFromCenter, 0, 0).rotate(55 * rotationMultiplier[leg], Vector2(distanceFromCenter,0)); 
  Vector3 point = GetPointOnBezierCurve(ControlPoints, 5, t);

  return point;
}