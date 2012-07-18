void setup() {

  encoderX.write(-1);
  encoderY.write(-1);
  //attachInterrupt(5,countX,RISING);
  //attachInterrupt(4,countY,RISING);
  //attachInterrupt(0,countZ,RISING);

  pinMode(loadX, INPUT);
  pinMode(loadY, INPUT);
  pinMode(pwmX, OUTPUT);
  pinMode(pwmY, OUTPUT);
  pinMode(dirX, OUTPUT);
  pinMode(dirY, OUTPUT);
  pinMode(enableX, OUTPUT);
  pinMode(enableY, OUTPUT);
  pinMode(zSolenoid, OUTPUT);
  pinMode(atxPowerCtrl, OUTPUT);
  pinMode(atxPowerState, INPUT);
  pinMode(atxPowerLed, OUTPUT);
  pinMode(pwrSwitch, INPUT);
  digitalWrite(pwrSwitch,HIGH);
  analogWrite(pwmX,xPowerOutput);
  analogWrite(pwmY,yPowerOutput);
  Serial.begin(115200);
  lcd.begin(lcdColumns, lcdRows);
  doServoMove('X',1000);
  doServoMove('Y',1000);
  //Serial.print("x0y1z1");
}

