

void carState() {
  currentState = Car;
  
  //StraightGaitUpdateControlPoints(forwardAmount/125);
  float forwardAmount = joy1CurrentMagnitude;
  float turnAmount = joy2CurrentVector.x;

  CrabGaitUpdateControlPoints();
  RotateGaitUpdateControlPoints(turnAmount/100);

  float t = (float)phaseProgress / points;
  if(t > 1) t = 1;

  

  float weightSum = abs(forwardAmount) + abs(turnAmount);

  Vector3 straightPoint1 = CrabGaitGetPoint(0, t);
  Vector3 rotatePoint1 = RotateGaitGetPoint(0, t);
  Vector3 nextPoint1 = (straightPoint1*abs(forwardAmount) + rotatePoint1*abs(turnAmount))/ weightSum;

  Vector3 straightPoint2 = CrabGaitGetPoint(1, t);
  Vector3 rotatePoint2 = RotateGaitGetPoint(1, t);
  Vector3 nextPoint2 = (straightPoint2*abs(forwardAmount) + rotatePoint2*abs(turnAmount))/ weightSum;

  Vector3 straightPoint3 = CrabGaitGetPoint(2, t);
  Vector3 rotatePoint3 = RotateGaitGetPoint(2, t);
  Vector3 nextPoint3 = (straightPoint3*abs(forwardAmount) + rotatePoint3*abs(turnAmount))/ weightSum;

  Vector3 straightPoint4 = CrabGaitGetPoint(3, t);
  Vector3 rotatePoint4 = RotateGaitGetPoint(3, t);
  Vector3 nextPoint4 = (straightPoint4*abs(forwardAmount) + rotatePoint4*abs(turnAmount))/ weightSum;

  Vector3 straightPoint5 = CrabGaitGetPoint(4, t);
  Vector3 rotatePoint5 = RotateGaitGetPoint(4, t);
  Vector3 nextPoint5 = (straightPoint5*abs(forwardAmount) + rotatePoint5*abs(turnAmount))/ weightSum;

  Vector3 straightPoint6 = CrabGaitGetPoint(5, t);
  Vector3 rotatePoint6 = RotateGaitGetPoint(5, t);
  Vector3 nextPoint6 = (straightPoint6*abs(forwardAmount) + rotatePoint6*abs(turnAmount))/ weightSum;

  moveToPos(0, nextPoint1);
  moveToPos(1, nextPoint2);
  moveToPos(2, nextPoint3);
  moveToPos(3, nextPoint4);
  moveToPos(4, nextPoint5);
  moveToPos(5, nextPoint6);

  float progressChangeAmount = calculateHypotenuse(abs(forwardAmount), abs(turnAmount)) * 1.25;

  phaseProgress += progressChangeAmount;
  
}








