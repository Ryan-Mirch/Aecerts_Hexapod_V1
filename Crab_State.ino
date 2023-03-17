//Crab Gait Control Points
Vector3 CGCP0[10];
Vector3 CGCP1[10];
Vector3 CGCP2[10];
Vector3 CGCP3[10];
Vector3 CGCP4[10];
Vector3 CGCP5[10];
 
int CGCPAmounts[6] = {4,4,4,4,4,4};

int rotateDegrees = 0;

void crabState() {

  currentState = Crab;
  
  CrabGaitUpdateControlPoints();
  if(crabForwardAmount < 5) return;

  float t = (float) phaseProgress / points;
  if(t > 1) t = 1;

  moveToPos(0, CrabGaitGetPoint(0, t));
  moveToPos(1, CrabGaitGetPoint(1, t));
  moveToPos(2, CrabGaitGetPoint(2, t));
  moveToPos(3, CrabGaitGetPoint(3, t));
  moveToPos(4, CrabGaitGetPoint(4, t));
  moveToPos(5, CrabGaitGetPoint(5, t));

  phaseProgress += crabForwardAmount;
  timeSinceLastInput = millis();
  
}

Vector3 CrabGaitGetPoint(int leg, float t){  
  switch(leg){
    case 0:
      return GetPointOnBezierCurve(CGCP0, CGCPAmounts[0], t);

    case 1:
      return GetPointOnBezierCurve(CGCP1, CGCPAmounts[1], t);

    case 2:
      return GetPointOnBezierCurve(CGCP2, CGCPAmounts[2], t);

    case 3:
      return GetPointOnBezierCurve(CGCP3, CGCPAmounts[3], t);

    case 4:
      return GetPointOnBezierCurve(CGCP4, CGCPAmounts[4], t);

    case 5:
      return GetPointOnBezierCurve(CGCP5, CGCPAmounts[5], t);

    default:
      break;
  }  
}

void CrabGaitUpdateControlPoints(int leg, ){
  Vector2 v = joy1CurrentVector;

  switch(phase) {
    case 0:
      CGCP0[0] = phaseStartPoints[0];
      CGCP0[1] = phaseStartPoints[0] + Vector3(0,0,liftHeight);
      CGCP0[2] = Vector3(-v.x + distanceFromCenter, (v.y + strideOvershoot), distanceFromGround + landHeight).rotate(-55, Vector2(distanceFromCenter,0));
      CGCP0[3] = Vector3(-v.x + distanceFromCenter, v.y, distanceFromGround).rotate(-55, Vector2(distanceFromCenter,0));
      CGCPAmounts[0] = 4;

      CGCP1[0] = phaseStartPoints[1];
      CGCP1[1] = Vector3(v.x + distanceFromCenter, -v.y, distanceFromGround);
      CGCPAmounts[1] = 2;

      CGCP2[0] = phaseStartPoints[2];
      CGCP2[1] = phaseStartPoints[2] + Vector3(0,0,liftHeight);
      CGCP2[2] = Vector3(-v.x + distanceFromCenter, (v.y + strideOvershoot), distanceFromGround + landHeight).rotate(55, Vector2(distanceFromCenter,0));
      CGCP2[3] = Vector3(-v.x + distanceFromCenter, v.y, distanceFromGround).rotate(55, Vector2(distanceFromCenter,0));
      CGCPAmounts[2] = 4;

      CGCP3[0] = phaseStartPoints[3];
      CGCP3[1] = Vector3(-v.x + distanceFromCenter, v.y, distanceFromGround).rotate(-55, Vector2(distanceFromCenter,0));
      CGCPAmounts[3] = 2;

      CGCP4[0] = phaseStartPoints[4];
      CGCP4[1] = phaseStartPoints[4] + Vector3(0,0,liftHeight);
      CGCP4[2] = Vector3(v.x + distanceFromCenter, -(v.y + strideOvershoot), distanceFromGround + landHeight);
      CGCP4[3] = Vector3(v.x + distanceFromCenter, -v.y, distanceFromGround);
      CGCPAmounts[4] = 4;

      CGCP5[0] = phaseStartPoints[5];
      CGCP5[1] = Vector3(-v.x + distanceFromCenter, v.y, distanceFromGround).rotate(55, Vector2(distanceFromCenter,0));
      CGCPAmounts[5] = 2;  
      break;

    case 1:
      CGCP0[0] = phaseStartPoints[0];
      CGCP0[1] = Vector3(v.x + distanceFromCenter, -v.y, distanceFromGround).rotate(-55, Vector2(distanceFromCenter,0));
      CGCPAmounts[0] = 2;  

      CGCP1[0] = phaseStartPoints[1];
      CGCP1[1] = phaseStartPoints[1] + Vector3(0,0,liftHeight);
      CGCP1[2] = Vector3(-v.x + distanceFromCenter, (v.y + strideOvershoot), distanceFromGround + landHeight);
      CGCP1[3] = Vector3(-v.x + distanceFromCenter, v.y, distanceFromGround);
      CGCPAmounts[1] = 4;  

      CGCP2[0] = phaseStartPoints[2];
      CGCP2[1] = Vector3(v.x + distanceFromCenter, -v.y, distanceFromGround).rotate(55, Vector2(distanceFromCenter,0));
      CGCPAmounts[2] = 2;  

      CGCP3[0] = phaseStartPoints[3];
      CGCP3[1] = phaseStartPoints[3] + Vector3(0,0,liftHeight);
      CGCP3[2] = Vector3(v.x + distanceFromCenter, -(v.y + strideOvershoot), distanceFromGround + landHeight).rotate(-55, Vector2(distanceFromCenter,0));
      CGCP3[3] = Vector3(v.x + distanceFromCenter, -v.y, distanceFromGround).rotate(-55, Vector2(distanceFromCenter,0));
      CGCPAmounts[3] = 4;  

      CGCP4[0] = phaseStartPoints[4];
      CGCP4[1] = Vector3(-v.x + distanceFromCenter, v.y, distanceFromGround);
      CGCPAmounts[4] = 2;  

      CGCP5[0] = phaseStartPoints[5];
      CGCP5[1] = phaseStartPoints[5] + Vector3(0,0,liftHeight);
      CGCP5[2] = Vector3(v.x + distanceFromCenter, -(v.y + strideOvershoot), distanceFromGround + landHeight).rotate(55, Vector2(distanceFromCenter,0));
      CGCP5[3] = Vector3(v.x + distanceFromCenter, -v.y, distanceFromGround).rotate(55, Vector2(distanceFromCenter,0));
      CGCPAmounts[5] = 4;  
      break;

    default:
      break;
  }
}




