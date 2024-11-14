Vector3 targetCalibration = Vector3(a1 + 43, 0, a2 + 185);
//Vector3 targetCalibration = Vector3(a1+a3, 0, a2);
int inBetweenZ = -20;
int8_t previousOffsets[18];

void calibrationState() {
  if(currentState != Calibrate)Serial.println("Calibration State."); 

  currentState = Calibrate;

  bool legsUp = true;

  //lifting legs up so the hex is sitting on the ground.
  for (int i = 0; i < 6; i++) {
    if (currentPoints[i].z < inBetweenZ) {
      legsUp = false;
      float nextZ = lerp(currentPoints[i].z, inBetweenZ + 2, 0.03);
      moveToPos(i, Vector3(currentPoints[i].x, currentPoints[i].y, nextZ));
    }
  }

  if (legsUp) {

    //if connected to the controller, use its offsets
    setOffsetsFromControllerData();

    //move legs 
    for (int i = 0; i < 6; i++) {
      float nextX = min(currentPoints[i].x + 5, targetCalibration.x);
      float nextY = min(currentPoints[i].y + 5, targetCalibration.y);
      float nextZ = min(currentPoints[i].z + 5, targetCalibration.z);
      moveToPos(i, Vector3(nextX, nextY, nextZ));
    }
  }
}