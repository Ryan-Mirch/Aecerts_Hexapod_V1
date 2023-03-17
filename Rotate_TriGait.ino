


/*
void RotateGaitUpdateControlPoints(float direction) {
  int phase = 0;
  if(cycleProgress[0] < points/2)phase = 1;
  switch (phase) {
    case 0:
      RGCP0[0] = cycleStartPoints[0];
      RGCP0[1] = cycleStartPoints[0] + Vector3(0,0,liftHeight);
      RGCP0[2] = { distanceFromCenter + 40, 0, distanceFromGround + liftHeight };
      RGCP0[3] = { distanceFromCenter, (strideLength/2 + strideOvershoot) * direction, distanceFromGround + liftHeight * landHeightOffsetMultiplier };
      RGCP0[4] = { distanceFromCenter, strideLength/2 * direction, distanceFromGround};
      RGCPAmounts[0] = 5;

      RGCP1[0] = cycleStartPoints[1];
      RGCP1[1] = { distanceFromCenter + 40, 0, distanceFromGround };
      RGCP1[2] = { distanceFromCenter, -strideLength/2 * direction, distanceFromGround };
      RGCPAmounts[1] = 3;

      RGCP2[0] = cycleStartPoints[2];
      RGCP2[1] = cycleStartPoints[2] + Vector3(0,0,liftHeight);
      RGCP2[2] = { distanceFromCenter + 40, 0, distanceFromGround + liftHeight };
      RGCP2[3] = { distanceFromCenter, (strideLength/2 + strideOvershoot) * direction, distanceFromGround + liftHeight * landHeightOffsetMultiplier };
      RGCP2[4] = { distanceFromCenter, strideLength/2 * direction, distanceFromGround};
      RGCPAmounts[2] = 5;

      RGCP3[0] = cycleStartPoints[3];
      RGCP3[1] = { distanceFromCenter + 40, 0, distanceFromGround };
      RGCP3[2] = { distanceFromCenter, -strideLength/2 * direction, distanceFromGround };
      RGCPAmounts[3] = 3;

      RGCP4[0] = cycleStartPoints[4];
      RGCP4[1] = cycleStartPoints[4] + Vector3(0,0,liftHeight);
      RGCP4[2] = { distanceFromCenter + 40, 0, distanceFromGround + liftHeight };
      RGCP4[3] = { distanceFromCenter, (strideLength/2 + strideOvershoot) * direction, distanceFromGround + liftHeight * landHeightOffsetMultiplier };
      RGCP4[4] = { distanceFromCenter, strideLength/2 * direction, distanceFromGround};
      RGCPAmounts[4] = 5;

      RGCP5[0] = cycleStartPoints[5];
      RGCP5[1] = { distanceFromCenter + 40, 0, distanceFromGround };
      RGCP5[2] = { distanceFromCenter, -strideLength/2 * direction, distanceFromGround };
      RGCPAmounts[5] = 3;
      break;

    case 1:
      RGCP0[0] = cycleStartPoints[0];
      RGCP0[1] = { distanceFromCenter + 40, 0, distanceFromGround };
      RGCP0[2] = { distanceFromCenter, -strideLength/2 * direction, distanceFromGround };
      RGCPAmounts[0] = 3;

      RGCP1[0] = cycleStartPoints[1];
      RGCP1[1] = cycleStartPoints[1] + Vector3(0,0,liftHeight);
      RGCP1[2] = { distanceFromCenter + 40, 0, distanceFromGround + liftHeight };
      RGCP1[3] = { distanceFromCenter, (strideLength/2 + strideOvershoot) * direction, distanceFromGround + liftHeight * landHeightOffsetMultiplier };
      RGCP1[4] = { distanceFromCenter, strideLength/2 * direction, distanceFromGround};
      RGCPAmounts[1] = 5;

      RGCP2[0] = cycleStartPoints[2];
      RGCP2[1] = { distanceFromCenter + 40, 0, distanceFromGround };
      RGCP2[2] = { distanceFromCenter, -strideLength/2 * direction, distanceFromGround };
      RGCPAmounts[2] = 3;

      RGCP3[0] = cycleStartPoints[3];
      RGCP3[1] = cycleStartPoints[3] + Vector3(0,0,liftHeight);
      RGCP3[2] = { distanceFromCenter + 40, 0, distanceFromGround + liftHeight };
      RGCP3[3] = { distanceFromCenter, (strideLength/2 + strideOvershoot) * direction, distanceFromGround + liftHeight * landHeightOffsetMultiplier };
      RGCP3[4] = { distanceFromCenter, strideLength/2 * direction, distanceFromGround};
      RGCPAmounts[3] = 5;

      RGCP4[0] = cycleStartPoints[4];
      RGCP4[1] = { distanceFromCenter + 40, 0, distanceFromGround };
      RGCP4[2] = { distanceFromCenter, -strideLength/2 * direction, distanceFromGround };
      RGCPAmounts[4] = 3;

      RGCP5[0] = cycleStartPoints[5];
      RGCP5[1] = cycleStartPoints[5] + Vector3(0,0,liftHeight);
      RGCP5[2] = { distanceFromCenter + 40, 0, distanceFromGround + liftHeight };
      RGCP5[3] = { distanceFromCenter, (strideLength/2 + strideOvershoot) * direction, distanceFromGround + liftHeight * landHeightOffsetMultiplier };
      RGCP5[4] = { distanceFromCenter, strideLength/2 * direction, distanceFromGround};
      RGCPAmounts[5] = 5;
      break;

    default:
      break;
  }
}
*/