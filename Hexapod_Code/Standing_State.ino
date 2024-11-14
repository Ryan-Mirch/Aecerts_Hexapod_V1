//Standing Control Points Array
Vector3 SCPA[6][10];

Vector3 standingStartPoints[6];      //the points the legs are at in the beginning of the standing state
Vector3 standingInBetweenPoints[6];  //the middle points of the bezier curves that the legs will follow to smoothly transition to the end points
Vector3 standingEndPoint;

int currentLegs[3] = { -1, -1, -1 };
int standLoops = 0;

void standingState() {
  if(currentState != Stand)Serial.println("Standing State.");

  bool moveAllAtOnce = false;
  bool highLift = false;
  setCycleStartPoints();
  standingEndPoint = Vector3(distanceFromCenter, 0, distanceFromGround + standingDistanceAdjustment);
  standLoops = 2;
  // We only set the starting, inbetween, and ending points one time, which is when we enter the standing state.
  if (currentState == Calibrate || currentState == Initialize || currentState == SlamAttack || currentState == Sleep || currentState == Attach) moveAllAtOnce = true;
  if (currentState == SlamAttack || currentState == Sleep) highLift = true;
  if (currentState != Stand) {
    
    set3HighestLeg();
    standLoops = 0;
    standProgress = 0;
    memcpy(standingStartPoints, currentPoints, sizeof(currentPoints[0]) * 6);
    currentState = Stand;

    // Calculate the inbetween and ending points
    for (int i = 0; i < 6; i++) {
      Vector3 inBetweenPoint = standingStartPoints[i];
      inBetweenPoint.x = (inBetweenPoint.x + standingEndPoint.x) / 1.5;
      inBetweenPoint.y = (inBetweenPoint.y + standingEndPoint.y) / 1.5;

      inBetweenPoint.z = ((inBetweenPoint.z + standingEndPoint.z) / 2);
      if(abs(inBetweenPoint.z - standingEndPoint.z) < 50 )inBetweenPoint.z += 70;
      if(highLift)inBetweenPoint.z += 80;

      standingInBetweenPoints[i] = inBetweenPoint;

      SCPA[i][0] = standingStartPoints[i];
      SCPA[i][1] = standingInBetweenPoints[i];
      SCPA[i][2] = standingEndPoint;
    }

    for(int i = 0; i < 6; i++){
      legStates[i] = Standing;
    } 
  }

  //update distance from ground constantly
  for (int i = 0; i < 6; i++) {
    SCPA[i][2] = standingEndPoint;
  }

  //readjusting. This takes about a second
  while(standLoops < 2){
    standProgress += 20;
    /*
    if(highLift){
      standProgress += 40 - 50 * ((float)standProgress / points);
    }
  */
    float t = (float)standProgress / points;
    if (t > 1) {
      t = 1;
    }

    if(moveAllAtOnce){
      for (int i = 0; i < 6; i++) {
        moveToPos(i, GetPointOnBezierCurve(SCPA[i], 3, t));
      }

      if (standProgress > points) {
        standProgress = 0;
        standLoops = 2;
      }
    }

    else{
      for (int i = 0; i < 3; i++) {
        if (currentLegs[i] != -1) {
          moveToPos(currentLegs[i], GetPointOnBezierCurve(SCPA[currentLegs[i]], 3, t));
        }
      }

      if (standProgress > points) {
        standProgress = 0;
        standLoops++;
        set3HighestLeg();
      }
    }
  }


  //constantly move to the standing end position
  for (int i = 0; i < 6; i++) {
    moveToPos(i, GetPointOnBezierCurve(SCPA[i], 3, 1));
  }
  return;
}

void set3HighestLeg() {

  currentLegs[0] = -1;
  currentLegs[1] = -1;
  currentLegs[2] = -1;
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 6; i++) {  //go through the legs
      //if the leg is already on the list of current legs, skip it
      if (currentLegs[0] == i || currentLegs[1] == i || currentLegs[2] == i) continue;

      //if the leg is already in position, dont add it
      if (currentPoints[i] == standingEndPoint) continue;

      //if the legs z is greater than the leg already there, add it
      if (currentLegs[j] == -1 || currentPoints[i].z > currentPoints[currentLegs[j]].z) {
        currentLegs[j] = i;
      }
    }
  }
}