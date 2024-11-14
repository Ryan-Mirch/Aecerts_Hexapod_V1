Vector3 targetSleepPosition = Vector3(130, 0, -46);

int sleepStateState = 1;

void sleepState() {
  if(currentState != Sleep)
  {
    Serial.println("Sleep State."); 
    sleepStateState = 1;
  }
  
  currentState = Sleep;
  if(!servosAttached)return;

/*
  if(sleepStateState == 0){
    bool legsUp = true;
    //lifting legs up so the hex is sitting on the ground.
    for (int i = 0; i < 6; i++) {
      if (currentPoints[i].z < -1) {
        legsUp = false;
        float nextZ = lerp(currentPoints[i].z, 1, 0.02);
        moveToPos(i, Vector3(currentPoints[i].x, currentPoints[i].y, nextZ));
      }
    }
    if(legsUp)sleepStateState = 1;
  }
  */
  

  if(sleepStateState == 1){
    bool targetReached = true;
    for (int i = 0; i < 6; i++) {
      Vector3 next = lerp(currentPoints[i], targetSleepPosition, 0.03);
      if(abs(currentPoints[i].x - targetSleepPosition.x) < 1) next.x = targetSleepPosition.x;
      if(abs(currentPoints[i].y - targetSleepPosition.y) < 1) next.y = targetSleepPosition.y;
      if(abs(currentPoints[i].z - targetSleepPosition.z) < 1) next.z = targetSleepPosition.z;
      moveToPos(i, next);
      if(currentPoints[i] != targetSleepPosition)targetReached = false;
    }
    if(targetReached)sleepStateState = 2;
  } 

  if(sleepStateState == 2){
    detachServos();
    sleepStateState = 3;
  }
}



