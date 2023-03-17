float forwardAmount;
float turnAmount;
float tArray[6];

void carState() {
  if(currentState != Car){
    cycleProgress[0] = 0;
    cycleProgress[1] = points/2;
    cycleProgress[2] = 0;
    cycleProgress[3] = points/2;
    cycleProgress[4] = 0;
    cycleProgress[5] = points/2;

    legStates[0] = Propelling;
    legStates[1] = Lifting;
    legStates[2] = Propelling;
    legStates[3] = Lifting;
    legStates[4] = Propelling;
    legStates[5] = Lifting;
  }

  currentState = Car;

  
  for(int i = 0; i < 6; i++){
    tArray[i] = (float)cycleProgress[i] / points;    
  }  

  forwardAmount = joy1CurrentMagnitude;
  turnAmount = joy2CurrentVector.x;

  moveToPos(0, getGaitPoint(0, 0.5, 0));
  moveToPos(1, getGaitPoint(1, 0.5, 0));
  moveToPos(2, getGaitPoint(2, 0.5, 0));
  moveToPos(3, getGaitPoint(3, 0.5, 0));
  moveToPos(4, getGaitPoint(4, 0.5, 0));
  moveToPos(5, getGaitPoint(5, 0.5, 0));

  
  float progressChangeAmount = (calculateHypotenuse(abs(forwardAmount), abs(turnAmount)) * 1.25) * .2;

  for(int i = 0; i < 6; i++){
    if(cycleProgress[i] >= points){
      cycleProgress[i] = 0;
    }

    cycleProgress[i] += progressChangeAmount;
    

    if(cycleProgress[i] > points){
      cycleProgress[i] = points;
    }
  } 
}



Vector3 getGaitPoint(int leg, float pushFraction, int centerOffset){
  int rotationMultiplier = 0;
  int strideMultiplier = 1; // Y direction, X direction is the opposite
  int strideRotateDirectionMultiplier = 1;
  
  Vector3 ControlPoints[10];
  Vector3 RotateControlPoints[10];

  int ControlPointsAmount = 0;
  int RotateControlPointsAmount = 0;

  float rotateStrideLength = joy2CurrentVector.x;
  Vector2 v = joy1CurrentVector;

  float weightSum = abs(forwardAmount) + abs(turnAmount);

  float t = tArray[leg];  

  switch (leg) {
    case 0:
      strideRotateDirectionMultiplier = -1;
      strideMultiplier = 1;
      rotationMultiplier = -1;
      break;
    case 1:
      strideRotateDirectionMultiplier = -1;
      strideMultiplier = 1;
      rotationMultiplier = 0;
      break;
    case 2:
      strideRotateDirectionMultiplier = -1;
      strideMultiplier = 1;
      rotationMultiplier = 1;    
      break;
    case 3:
      strideRotateDirectionMultiplier = -1;
      strideMultiplier = -1;
      rotationMultiplier = -1;    
      break;
    case 4:
      strideRotateDirectionMultiplier = -1;
      strideMultiplier = -1;
      rotationMultiplier = 0;      
      break;
    case 5:
      strideRotateDirectionMultiplier = -1;
      strideMultiplier = -1;
      rotationMultiplier = 1;      
      break;
    default:
      break;
  }

  
  
  //Propelling
  if(t < pushFraction){ 
    if(legStates[leg] != Propelling)setCycleStartPoints(leg);
    legStates[leg] = Propelling;

    ControlPoints[0] = cycleStartPoints[leg];
    ControlPoints[1] = Vector3(v.x * strideMultiplier + distanceFromCenter, -v.y * strideMultiplier, distanceFromGround).rotate(55 * rotationMultiplier, Vector2(distanceFromCenter,0));
    ControlPointsAmount = 2;    
    Vector3 straightPoint = GetPointOnBezierCurve(ControlPoints, ControlPointsAmount, mapFloat(t,0,pushFraction,0,1));

    RotateControlPoints[0] = cycleStartPoints[leg];
    RotateControlPoints[1] = { distanceFromCenter + 40, 0, distanceFromGround };
    RotateControlPoints[2] = { distanceFromCenter, -rotateStrideLength * strideRotateDirectionMultiplier, distanceFromGround };
    RotateControlPointsAmount = 3;    
    Vector3 rotatePoint = GetPointOnBezierCurve(RotateControlPoints, RotateControlPointsAmount, mapFloat(t,0,pushFraction,0,1));

    return (straightPoint*abs(forwardAmount) + rotatePoint*abs(turnAmount))/ weightSum;
  }

  //Lifting
  else{
    if(legStates[leg] != Lifting)setCycleStartPoints(leg);
    legStates[leg] = Lifting;

    ControlPoints[0] = cycleStartPoints[leg];
    ControlPoints[1] = cycleStartPoints[leg] + Vector3(0,0,liftHeight);
    ControlPoints[2] = Vector3(-v.x * strideMultiplier + distanceFromCenter, (v.y + strideOvershoot) * strideMultiplier, distanceFromGround + landHeight).rotate(55 * rotationMultiplier, Vector2(distanceFromCenter,0));
    ControlPoints[3] = Vector3(-v.x * strideMultiplier + distanceFromCenter, v.y * strideMultiplier, distanceFromGround).rotate(55 * rotationMultiplier, Vector2(distanceFromCenter,0));
    ControlPointsAmount = 4;
    Vector3 straightPoint = GetPointOnBezierCurve(ControlPoints, ControlPointsAmount, mapFloat(t,pushFraction,1,0,1));

    RotateControlPoints[0] = cycleStartPoints[leg];
    RotateControlPoints[1] = cycleStartPoints[leg] + Vector3(0,0,liftHeight);
    RotateControlPoints[2] = { distanceFromCenter + 40, 0, distanceFromGround + liftHeight };
    RotateControlPoints[3] = { distanceFromCenter, (rotateStrideLength + strideOvershoot) * strideRotateDirectionMultiplier, distanceFromGround + liftHeight * landHeightOffsetMultiplier };
    RotateControlPoints[4] = { distanceFromCenter, rotateStrideLength * strideRotateDirectionMultiplier, distanceFromGround};
    RotateControlPointsAmount = 5;
    Vector3 rotatePoint =  GetPointOnBezierCurve(RotateControlPoints, RotateControlPointsAmount, mapFloat(t,pushFraction,1,0,1));

    return (straightPoint*abs(forwardAmount) + rotatePoint*abs(turnAmount))/ weightSum;
  }  
}








