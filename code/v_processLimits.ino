int processLimits(char Axis, float Position)
{
  int limit=-1;
  if(Axis=='X')
  {
    if(Position < xMinLimit)
    {
      limit=0; // xMinLimit reached.
    }else{
      if(Position > xMaxLimit)
      {
        limit=2; // xMaxLimit reached.
      }else{
        limit=1; // niether xMinLimit nor xMaxLimit reached.
      }
    }
//    long currentTime = millis();
//    if(currentTime - limitPollingTime > limitPollingTimeOld)
    if(limit != xLimitOld)
    {
      xLimitOld=limit;
      Serial.print("x");
      Serial.print(limit);
//      limitPollingTimeOld=currentTime;
    }
  }
  if(Axis=='Y')
  {
    if(Position < yMinLimit)
    {
      limit=0; // yMinLimit reached.
    }else{
      if(Position > yMaxLimit)
      {
        limit=2; // yMaxLimit reached.
      }else{
        limit=1; // niether yMinLimit nor yMaxLimit reached.
      }
    }
//    long currentTime = millis();
//    if(currentTime - limitPollingTime > limitPollingTimeOld)
    if(limit != yLimitOld)
    {
      yLimitOld=limit;
      Serial.print("y");
      Serial.print(limit);
//      limitPollingTimeOld=currentTime;
    }
  }
  if(Axis=='Z')
  {
    if(Position < zMinLimit)
    {
      limit=0; // zMinLimit reached.
    }else{
      if(Position > zMaxLimit)
      {
        limit=2; // zMaxLimit reached.
      }else{
        limit=1; // niether zMinLimit nor xMaxLimit reached.
      }
    }
//    long currentTime = millis();
//    if(currentTime - limitPollingTime > limitPollingTimeOld)
    if(limit != zLimitOld)
    {
      zLimitOld=limit;
      Serial.print("z");
      Serial.print(limit);
//      limitPollingTimeOld=currentTime;
    }
  }
  return limit;
}

