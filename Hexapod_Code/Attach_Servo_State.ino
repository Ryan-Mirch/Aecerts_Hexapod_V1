int AttachServoStateState = 0;

void attachServoState() {
  if(currentState != Attach)
  {
    Serial.println("Attach Servo State."); 
    AttachServoStateState = 0;
  }
  
  currentState = Attach;

  if(AttachServoStateState == 0){
    bool legsUp = true;
    //lifting legs up so the hex is sitting on the ground.
    for (int i = 0; i < 6; i++) {
      if (currentPoints[i].z < -1) {
        legsUp = false;
        float nextZ = lerp(currentPoints[i].z, 1, 0.02);
        moveToPos(i, Vector3(currentPoints[i].x, currentPoints[i].y, nextZ));
      }
    }
    if(legsUp)AttachServoStateState = 1;
  }
  

  if(AttachServoStateState == 1){
    bool targetReached = true;
    
    for (int i = 0; i < 6; i++) {
      Vector3 servoAngles = {90,150,30};
      rotateToAngle(i, servoAngles);
    }
  }
}



