Encoder encoderX(encoderXa,encoderXb);
Encoder encoderY(encoderYa,encoderYb);

void moveTo(char axis, long target)
{
  if(axis == 'X') {
    targetX=target;
    oldTimeX=millis();
    doServoMove('X',target);
    targetX=target;
  }

  if(axis == 'Y') {
    targetY=target;
    oldTimeY=millis();
    doServoMove('Y',target);
    targetY=target;
  }

  if(axis == 'Z') {
    targetZ=target;
    oldTimeZ=millis();
    doServoMove('Z',target);
    targetZ=target;
  }
}

long currentPos=0;
boolean doServoMove(char axis, long target)
{
  if(axis == 'X')
  {
    currentPos=encoderX.read();
    if(findDiff(target,currentPos) > xServoTolerance) // We need to move, so power up motor and move.
    {
      digitalWriteFast2(enableX,LOW);
      if(xPowerRamping)
        analogWrite(pwmX,constrain(findDiff(target,currentPos), xPowerOutput, xOverdrivePwr));
      if(target > currentPos)
      {
        digitalWriteFast2(dirX,HIGH); // Move X back
      }else{
        digitalWriteFast2(dirX,LOW); // Move X forward
      }
    }else{ // were on target, while we're here disable moter. (Don't cook the contact brushes.)
      digitalWriteFast2(enableX,HIGH);
    }
  }
  if(axis == 'Y')
  {
    currentPos=encoderY.read();
    if(findDiff(target,currentPos) > yServoTolerance)
    {
      digitalWriteFast2(enableY,LOW);
      if(yPowerRamping)
        analogWrite(pwmY,constrain(findDiff(target,currentPos), yPowerOutput, yOverdrivePwr));
      if(target > currentPos)
      {
        digitalWriteFast2(dirY,HIGH); // Move Y back
      }else{
        digitalWriteFast2(dirY,LOW); // Move Y forward
      }
    }else{
      digitalWriteFast2(enableY,HIGH);
    }
  }
  if(axis == 'Z')
  {
    if(zSolenoidInvert==true)
    {
      if(target < 0)
      {
        digitalWriteFast2(zSolenoid,HIGH);
      }else{
        digitalWriteFast2(zSolenoid,LOW);
      }
    }else{
      if(target > 0)
      {
        digitalWriteFast2(zSolenoid,HIGH);
      }else{
        digitalWriteFast2(zSolenoid,LOW);
      }
    }
  }
}

