Vector3 SGCP0[10];
Vector3 SGCP1[10];
Vector3 SGCP2[10];
Vector3 SGCP3[10];
Vector3 SGCP4[10];
Vector3 SGCP5[10];

int SGCPAmounts[6] = {4,4,4,4,4,4};

Vector3 StraightGaitGetPoint(int leg, float t){
  switch(leg){
    case 0:
      return GetPointOnBezierCurve(SGCP0, SGCPAmounts[0], t);

    case 1:
      return GetPointOnBezierCurve(SGCP1, SGCPAmounts[1], t);

    case 2:
      return GetPointOnBezierCurve(SGCP2, SGCPAmounts[2], t);

    case 3:
      return GetPointOnBezierCurve(SGCP3, SGCPAmounts[3], t);

    case 4:
      return GetPointOnBezierCurve(SGCP4, SGCPAmounts[4], t);

    case 5:
      return GetPointOnBezierCurve(SGCP5, SGCPAmounts[5], t);

    default:
      break;
  }  
}

void StraightGaitUpdateControlPoints(float strideLengthMultiplier){
  switch(phase) {
    case 0:
      SGCP0[0] = phaseStartPoints[0];
      SGCP0[1] = phaseStartPoints[0] + Vector3(0,0,liftHeight);
      SGCP0[2] = Vector3(distanceFromCenter, -(strideLength/2 + strideOvershoot) * strideLengthMultiplier, distanceFromGround + liftHeight * landHeightOffsetMultiplier).rotate(-55, Vector2(distanceFromCenter,0));
      SGCP0[3] = Vector3(distanceFromCenter, -strideLength/2 * strideLengthMultiplier, distanceFromGround).rotate(-55, Vector2(distanceFromCenter,0));
      SGCPAmounts[0] = 4;

      SGCP1[0] = phaseStartPoints[1];
      SGCP1[1] = Vector3(distanceFromCenter, strideLength/2 * strideLengthMultiplier, distanceFromGround);
      SGCPAmounts[1] = 2;

      SGCP2[0] = phaseStartPoints[2];
      SGCP2[1] = phaseStartPoints[2] + Vector3(0,0,liftHeight);
      SGCP2[2] = Vector3(distanceFromCenter, -(strideLength/2 + strideOvershoot) * strideLengthMultiplier, distanceFromGround + liftHeight * landHeightOffsetMultiplier).rotate(55, Vector2(distanceFromCenter,0));
      SGCP2[3] = Vector3(distanceFromCenter, -strideLength/2 * strideLengthMultiplier, distanceFromGround).rotate(55, Vector2(distanceFromCenter,0));
      SGCPAmounts[2] = 4;

      SGCP3[0] = phaseStartPoints[3];
      SGCP3[1] = Vector3(distanceFromCenter, -strideLength/2 * strideLengthMultiplier, distanceFromGround).rotate(-55, Vector2(distanceFromCenter,0));
      SGCPAmounts[3] = 2;

      SGCP4[0] = phaseStartPoints[4];
      SGCP4[1] = phaseStartPoints[4] + Vector3(0,0,liftHeight);
      SGCP4[2] = Vector3(distanceFromCenter, (strideLength/2 + strideOvershoot) * strideLengthMultiplier, distanceFromGround + liftHeight * landHeightOffsetMultiplier);
      SGCP4[3] = Vector3(distanceFromCenter, strideLength/2 * strideLengthMultiplier, distanceFromGround);
      SGCPAmounts[4] = 4;

      SGCP5[0] = phaseStartPoints[5];
      SGCP5[1] = Vector3(distanceFromCenter, -strideLength/2 * strideLengthMultiplier, distanceFromGround).rotate(55, Vector2(distanceFromCenter,0));
      SGCPAmounts[5] = 2;  
      break;

    case 1:
      SGCP0[0] = phaseStartPoints[0];
      SGCP0[1] = Vector3(distanceFromCenter, strideLength/2 * strideLengthMultiplier, distanceFromGround).rotate(-55, Vector2(distanceFromCenter,0));
      SGCPAmounts[0] = 2;  

      SGCP1[0] = phaseStartPoints[1];
      SGCP1[1] = phaseStartPoints[1] + Vector3(0,0,liftHeight);
      SGCP1[2] = Vector3(distanceFromCenter, -(strideLength/2 + strideOvershoot) * strideLengthMultiplier, distanceFromGround + liftHeight * landHeightOffsetMultiplier);
      SGCP1[3] = Vector3(distanceFromCenter, -strideLength/2 * strideLengthMultiplier, distanceFromGround);
      SGCPAmounts[1] = 4;  

      SGCP2[0] = phaseStartPoints[2];
      SGCP2[1] = Vector3(distanceFromCenter, strideLength/2 * strideLengthMultiplier, distanceFromGround).rotate(55, Vector2(distanceFromCenter,0));
      SGCPAmounts[2] = 2;  

      SGCP3[0] = phaseStartPoints[3];
      SGCP3[1] = phaseStartPoints[3] + Vector3(0,0,liftHeight);
      SGCP3[2] = Vector3(distanceFromCenter, (strideLength/2 + strideOvershoot) * strideLengthMultiplier, distanceFromGround + liftHeight * landHeightOffsetMultiplier).rotate(-55, Vector2(distanceFromCenter,0));
      SGCP3[3] = Vector3(distanceFromCenter, strideLength/2 * strideLengthMultiplier, distanceFromGround).rotate(-55, Vector2(distanceFromCenter,0));
      SGCPAmounts[3] = 4;  

      SGCP4[0] = phaseStartPoints[4];
      SGCP4[1] = Vector3(distanceFromCenter, -strideLength/2 * strideLengthMultiplier, distanceFromGround);
      SGCPAmounts[4] = 2;  

      SGCP5[0] = phaseStartPoints[5];
      SGCP5[1] = phaseStartPoints[5] + Vector3(0,0,liftHeight);
      SGCP5[2] = Vector3(distanceFromCenter, (strideLength/2 + strideOvershoot) * strideLengthMultiplier, distanceFromGround + liftHeight * landHeightOffsetMultiplier).rotate(55, Vector2(distanceFromCenter,0));
      SGCP5[3] = Vector3(distanceFromCenter, strideLength/2 * strideLengthMultiplier, distanceFromGround).rotate(55, Vector2(distanceFromCenter,0));
      SGCPAmounts[5] = 4;  
      break;

    default:
      break;
  }
}




