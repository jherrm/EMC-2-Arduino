/*
Please note: Although there are a LOT pin settings here.
You can get by with as few as TWO pins per Axis. (dir & step)
ie: 3 axies = 6 pins used. (minimum)
    9 axies = 18 pins or an entire UNO (using virtual limits switches only)

Note concerning switches: Be smart!
  AT LEAST use HOME switches.
  You'll find life a lot easier if you do...
  
  If you choose to build with threaded rod for lead screws but leave out the switches
  You'll have one of two possible outcomes;
    You'll get tired really quickly of resetting the machine by hand.
    Or worse, you'll forget (only once) to reset it, and upon power up
    it WILL destroy itself while you go -> WTF!? -> OMFG! -> PANIC! -> FACEPALM!

 List of axies. All 9 of them.
     AXIS_0 = X
     AXIS_1 = Y
     AXIS_2 = Z
     AXIS_3 = A
     AXIS_4 = B
     AXIS_5 = C
     AXIS_6 = U
     AXIS_7 = V
     AXIS_8 = W
*/

// You'll need this library. Get the interrupt safe version.
#include <digitalWriteFast.h> // http://code.google.com/p/digitalwritefast/

#define BAUD    (115200)
#define MAX_BUF (64)

#define stepsPerInchX 3200
#define stepsPerInchY 3200
#define stepsPerInchZ 3200
#define stepsPerInchA 3200
#define stepsPerInchB 3200
#define stepsPerInchC 3200
#define stepsPerInchU 3200
#define stepsPerInchV 3200
#define stepsPerInchW 3200

#define minStepTime 25 //delay in MICROseconds between step pulses.

// step pins (required)
#define stepPin0 41
#define stepPin1 40
#define stepPin2 35
#define stepPin3 34
#define stepPin4 -1
#define stepPin5 -1
#define stepPin6 -1
#define stepPin7 -1
#define stepPin8 -1

// dir pins (required)
#define dirPin0 43
#define dirPin1 42
#define dirPin2 33
#define dirPin3 32
#define dirPin4 -1
#define dirPin5 -1
#define dirPin6 -1
#define dirPin7 -1
#define dirPin8 -1

// microStepping pins (optional)
#define chanXms1 45
#define chanXms2 47
#define chanXms3 49
#define chanYms1 44
#define chanYms2 46
#define chanYms3 48
#define chanZms1 31
#define chanZms2 29
#define chanZms3 27
#define chanAms1 30
#define chanAms2 28
#define chanAms3 26
#define chanBms1 -1
#define chanBms2 -1
#define chanBms3 -1
#define chanCms1 -1
#define chanCms2 -1
#define chanCms3 -1
#define chanUms1 -1
#define chanUms2 -1
#define chanUms3 -1
#define chanVms1 -1
#define chanVms2 -1
#define chanVms3 -1
#define chanWms1 -1
#define chanWms2 -1
#define chanWms3 -1

#define xEnablePin 38
#define yEnablePin 39
#define zEnablePin 37
#define aEnablePin 36
#define bEnablePin -1
#define cEnablePin -1
#define uEnablePin -1
#define vEnablePin -1
#define wEnablePin -1

// Set to false if your using real switches for MIN positions.
#define useVirtualMinX true
#define useVirtualMinY true
#define useVirtualMinZ true
#define useVirtualMinA true
#define useVirtualMinB true
#define useVirtualMinC true
#define useVirtualMinU true
#define useVirtualMinV true
#define useVirtualMinW true

// Set to false if your using real switches for HOME positions.
#define useVirtualHomeX true
#define useVirtualHomeY true
#define useVirtualHomeZ true
#define useVirtualHomeA true
#define useVirtualHomeB true
#define useVirtualHomeC true
#define useVirtualHomeU true
#define useVirtualHomeV true
#define useVirtualHomeW true

// Set to false if your using real switches for MAX positions.
#define useVirtualMaxX true
#define useVirtualMaxY true
#define useVirtualMaxZ true
#define useVirtualMaxA true
#define useVirtualMaxB true
#define useVirtualMaxC true
#define useVirtualMaxU true
#define useVirtualMaxV true
#define useVirtualMaxW true

// If your using REAL switches you'll need real pins (ignored if using virtual switches).
#define xMinPin -1
#define yMinPin -1
#define zMinPin -1
#define aMinPin -1
#define bMinPin -1
#define cMinPin -1
#define uMinPin -1
#define vMinPin -1
#define wMinPin -1

#define xHomePin -1
#define yHomePin -1
#define zHomePin -1
#define aHomePin -1
#define bHomePin -1
#define cHomePin -1
#define uHomePin -1
#define vHomePin -1
#define wHomePin -1

#define xMaxPin -1
#define yMaxPin -1
#define zMaxPin -1
#define aMaxPin -1
#define bMaxPin -1
#define cMaxPin -1
#define uMaxPin -1
#define vMaxPin -1
#define wMaxPin -1

// Signal inversion for real switch users.
#define xMinPinInverted false
#define yMinPinInverted false
#define zMinPinInverted false
#define aMinPinInverted false
#define bMinPinInverted false
#define cMinPinInverted false
#define uMinPinInverted false
#define vMinPinInverted false
#define wMinPinInverted false

#define xHomePinInverted false
#define yHomePinInverted false
#define zHomePinInverted false
#define aHomePinInverted false
#define bHomePinInverted false
#define cHomePinInverted false
#define uHomePinInverted false
#define vHomePinInverted false
#define wHomePinInverted false

#define xMaxPinInverted false
#define yMaxPinInverted false
#define zMaxPinInverted false
#define aMaxPinInverted false
#define bMaxPinInverted false
#define cMaxPinInverted false
#define uMaxPinInverted false
#define vMaxPinInverted false
#define wMaxPinInverted false


// Where should the VIRTUAL Min switches be set to (ignored if using real switches).
#define xMin -5.1
#define yMin -5.1
#define zMin -5.1
#define aMin -5.1
#define bMin -5.1
#define cMin -5.1
#define uMin -5.1
#define vMin -5.1
#define wMin -5.1

// Where should the VIRTUAL home switches be set to (ignored if using real switches).
#define xHome 0
#define yHome 0
#define zHome 0
#define aHome 0
#define bHome 0
#define cHome 0
#define uHome 0
#define vHome 0
#define wHome 0

// Where should the VIRTUAL Max switches be set to (ignored if using real switches).
#define xMax 15.1
#define yMax 15.1
#define zMax 15.1
#define aMax 15.1
#define bMax 15.1
#define cMax 15.1
#define uMax 15.1
#define vMax 15.1
#define wMax 15.1

// Invert direction of movement for an axis by setting to false.
boolean dirState0=true;
boolean dirState1=true;
boolean dirState2=true;
boolean dirState3=true;
boolean dirState4=true;
boolean dirState5=true;
boolean dirState6=true;
boolean dirState7=true;
boolean dirState8=true;

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////END OF USER SETTINGS///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

char buffer[MAX_BUF];
int sofar;
 
float pos_x;
float pos_y;
float pos_z;
float pos_a;
float pos_b;
float pos_c;
float pos_u;
float pos_v;
float pos_w;

boolean stepState=LOW;
unsigned long stepTimeOld=0;
long stepper0Pos=0;
long stepper0Goto=0;
long stepper1Pos=0;
long stepper1Goto=0;
long stepper2Pos=0;
long stepper2Goto=0;
long stepper3Pos=0;
long stepper3Goto=0;
long stepper4Pos=0;
long stepper4Goto=0;
long stepper5Pos=0;
long stepper5Goto=0;
long stepper6Pos=0;
long stepper6Goto=0;
long stepper7Pos=0;
long stepper7Goto=0;
long stepper8Pos=0;
long stepper8Goto=0;
int stepModeX=-1; // don't set these here, look at stepMode() for info.
int stepModeY=-1;
int stepModeZ=-1;
int stepModeA=-1;
int stepModeB=-1;
int stepModeC=-1;
int stepModeU=-1;
int stepModeV=-1;
int stepModeW=-1;

boolean xMinState=false;
boolean yMinState=false;
boolean zMinState=false;
boolean aMinState=false;
boolean bMinState=false;
boolean cMinState=false;
boolean uMinState=false;
boolean vMinState=false;
boolean wMinState=false;
boolean xMinStateOld=false;
boolean yMinStateOld=false;
boolean zMinStateOld=false;
boolean aMinStateOld=false;
boolean bMinStateOld=false;
boolean cMinStateOld=false;
boolean uMinStateOld=false;
boolean vMinStateOld=false;
boolean wMinStateOld=false;

boolean xHomeState=false;
boolean yHomeState=false;
boolean zHomeState=false;
boolean aHomeState=false;
boolean bHomeState=false;
boolean cHomeState=false;
boolean uHomeState=false;
boolean vHomeState=false;
boolean wHomeState=false;
boolean xHomeStateOld=false;
boolean yHomeStateOld=false;
boolean zHomeStateOld=false;
boolean aHomeStateOld=false;
boolean bHomeStateOld=false;
boolean cHomeStateOld=false;
boolean uHomeStateOld=false;
boolean vHomeStateOld=false;
boolean wHomeStateOld=false;

boolean xMaxState=false;
boolean yMaxState=false;
boolean zMaxState=false;
boolean aMaxState=false;
boolean bMaxState=false;
boolean cMaxState=false;
boolean uMaxState=false;
boolean vMaxState=false;
boolean wMaxState=false;
boolean xMaxStateOld=false;
boolean yMaxStateOld=false;
boolean zMaxStateOld=false;
boolean aMaxStateOld=false;
boolean bMaxStateOld=false;
boolean cMaxStateOld=false;
boolean uMaxStateOld=false;
boolean vMaxStateOld=false;
boolean wMaxStateOld=false;

long divisor=1000000; // input divisor. Our HAL script wont send the six decimal place floats that EMC cranks out.
                      // A simple workaround is to multply it by 1000000 before sending it over the wire.
                      // So here we have put the decimal back to get the real numbers.
                      // Used in: processCommand()

void jog(float x, float y, float z, float a, float b, float c, float u, float v, float w)
{
  pos_x=x;
  pos_y=y;
  pos_z=z;
  pos_a=a;
  pos_b=b;
  pos_c=c;
  pos_u=u;
  pos_v=v;
  pos_w=w;

  // Handle our limit switches.
    // Compressed to save visual space. Otherwise it would be several pages long!
    
  if(useVirtualMinX==true){if(pos_x > xMin){xMinState=true;}else{xMinState=false;}}else{xMinState=digitalReadFast2(xMinPin);if(xMinPinInverted)xMinState=!xMinState;}
  if(useVirtualMinY==true){if(pos_y > yMin){yMinState=true;}else{yMinState=false;}}else{yMinState=digitalReadFast2(yMinPin);if(yMinPinInverted)yMinState=!yMinState;}
  if(useVirtualMinZ==true){if(pos_z > zMin){zMinState=true;}else{zMinState=false;}}else{zMinState=digitalReadFast2(zMinPin);if(zMinPinInverted)zMinState=!zMinState;}
  if(useVirtualMinA==true){if(pos_a > aMin){aMinState=true;}else{aMinState=false;}}else{aMinState=digitalReadFast2(aMinPin);if(aMinPinInverted)aMinState=!aMinState;}
  if(useVirtualMinB==true){if(pos_b > bMin){bMinState=true;}else{bMinState=false;}}else{bMinState=digitalReadFast2(bMinPin);if(bMinPinInverted)bMinState=!bMinState;}
  if(useVirtualMinC==true){if(pos_c > cMin){cMinState=true;}else{cMinState=false;}}else{cMinState=digitalReadFast2(cMinPin);if(cMinPinInverted)cMinState=!cMinState;}
  if(useVirtualMinU==true){if(pos_u > uMin){uMinState=true;}else{uMinState=false;}}else{uMinState=digitalReadFast2(uMinPin);if(uMinPinInverted)uMinState=!uMinState;}
  if(useVirtualMinV==true){if(pos_v > vMin){vMinState=true;}else{vMinState=false;}}else{vMinState=digitalReadFast2(vMinPin);if(vMinPinInverted)vMinState=!vMinState;}
  if(useVirtualMinW==true){if(pos_w > wMin){wMinState=true;}else{wMinState=false;}}else{wMinState=digitalReadFast2(wMinPin);if(wMinPinInverted)wMinState=!wMinState;}

  if(useVirtualMaxX==true){if(pos_x > xMax){xMaxState=true;}else{xMaxState=false;}}else{xMaxState=digitalReadFast2(xMaxPin);if(xMaxPinInverted)xMaxState=!xMaxState;}
  if(useVirtualMaxY==true){if(pos_y > yMax){yMaxState=true;}else{yMaxState=false;}}else{yMaxState=digitalReadFast2(yMaxPin);if(yMaxPinInverted)yMaxState=!yMaxState;}
  if(useVirtualMaxZ==true){if(pos_z > zMax){zMaxState=true;}else{zMaxState=false;}}else{zMaxState=digitalReadFast2(zMaxPin);if(zMaxPinInverted)zMaxState=!zMaxState;}
  if(useVirtualMaxA==true){if(pos_a > aMax){aMaxState=true;}else{aMaxState=false;}}else{aMaxState=digitalReadFast2(aMaxPin);if(aMaxPinInverted)aMaxState=!aMaxState;}
  if(useVirtualMaxB==true){if(pos_b > bMax){bMaxState=true;}else{bMaxState=false;}}else{bMaxState=digitalReadFast2(bMaxPin);if(bMaxPinInverted)bMaxState=!bMaxState;}
  if(useVirtualMaxC==true){if(pos_c > cMax){cMaxState=true;}else{cMaxState=false;}}else{cMaxState=digitalReadFast2(cMaxPin);if(cMaxPinInverted)cMaxState=!cMaxState;}
  if(useVirtualMaxU==true){if(pos_u > uMax){uMaxState=true;}else{uMaxState=false;}}else{uMaxState=digitalReadFast2(uMaxPin);if(uMaxPinInverted)uMaxState=!uMaxState;}
  if(useVirtualMaxV==true){if(pos_v > vMax){vMaxState=true;}else{vMaxState=false;}}else{vMaxState=digitalReadFast2(vMaxPin);if(vMaxPinInverted)vMaxState=!vMaxState;}
  if(useVirtualMaxW==true){if(pos_w > wMax){wMaxState=true;}else{wMaxState=false;}}else{wMaxState=digitalReadFast2(wMaxPin);if(wMaxPinInverted)wMaxState=!wMaxState;}

  if(useVirtualHomeX==true){if(pos_x > xHome){xHomeState=true;}else{xHomeState=false;}}else{xHomeState=digitalReadFast2(xHomePin);if(xHomePinInverted)xHomeState=!xHomeState;}
  if(useVirtualHomeY==true){if(pos_y > yHome){yHomeState=true;}else{yHomeState=false;}}else{yHomeState=digitalReadFast2(yHomePin);if(yHomePinInverted)yHomeState=!yHomeState;}
  if(useVirtualHomeZ==true){if(pos_z > zHome){zHomeState=true;}else{zHomeState=false;}}else{zHomeState=digitalReadFast2(zHomePin);if(zHomePinInverted)zHomeState=!zHomeState;}
  if(useVirtualHomeA==true){if(pos_a > aHome){aHomeState=true;}else{aHomeState=false;}}else{aHomeState=digitalReadFast2(aHomePin);if(aHomePinInverted)aHomeState=!aHomeState;}
  if(useVirtualHomeB==true){if(pos_b > bHome){bHomeState=true;}else{bHomeState=false;}}else{bHomeState=digitalReadFast2(bHomePin);if(bHomePinInverted)bHomeState=!bHomeState;}
  if(useVirtualHomeC==true){if(pos_c > cHome){cHomeState=true;}else{cHomeState=false;}}else{cHomeState=digitalReadFast2(cHomePin);if(cHomePinInverted)cHomeState=!cHomeState;}
  if(useVirtualHomeU==true){if(pos_u > uHome){uHomeState=true;}else{uHomeState=false;}}else{uHomeState=digitalReadFast2(uHomePin);if(uHomePinInverted)uHomeState=!uHomeState;}
  if(useVirtualHomeV==true){if(pos_v > vHome){vHomeState=true;}else{vHomeState=false;}}else{vHomeState=digitalReadFast2(vHomePin);if(vHomePinInverted)vHomeState=!vHomeState;}
  if(useVirtualHomeW==true){if(pos_w > wHome){wHomeState=true;}else{wHomeState=false;}}else{wHomeState=digitalReadFast2(wHomePin);if(wHomePinInverted)wHomeState=!wHomeState;}

  if(xMinState != xMinStateOld){xMinStateOld=xMinState;Serial.print("x");Serial.print(xMinState);}
  if(yMinState != yMinStateOld){yMinStateOld=yMinState;Serial.print("y");Serial.print(yMinState);}
  if(zMinState != zMinStateOld){zMinStateOld=zMinState;Serial.print("z");Serial.print(zMinState);}
  if(aMinState != aMinStateOld){aMinStateOld=aMinState;Serial.print("a");Serial.print(aMinState);}
  if(bMinState != bMinStateOld){bMinStateOld=bMinState;Serial.print("b");Serial.print(bMinState);}
  if(cMinState != cMinStateOld){cMinStateOld=cMinState;Serial.print("c");Serial.print(cMinState);}
  if(uMinState != uMinStateOld){uMinStateOld=uMinState;Serial.print("u");Serial.print(uMinState);}
  if(vMinState != vMinStateOld){vMinStateOld=vMinState;Serial.print("v");Serial.print(vMinState);}
  if(wMinState != wMinStateOld){wMinStateOld=wMinState;Serial.print("w");Serial.print(wMinState);}

  if(xHomeState != xHomeStateOld){xHomeStateOld=xHomeState;Serial.print("x");Serial.print(xHomeState+4);}
  if(yHomeState != yHomeStateOld){yHomeStateOld=yHomeState;Serial.print("y");Serial.print(yHomeState+4);}
  if(zHomeState != zHomeStateOld){zHomeStateOld=zHomeState;Serial.print("z");Serial.print(zHomeState+4);}
  if(aHomeState != aHomeStateOld){aHomeStateOld=aHomeState;Serial.print("a");Serial.print(aHomeState+4);}
  if(bHomeState != bHomeStateOld){bHomeStateOld=bHomeState;Serial.print("b");Serial.print(bHomeState+4);}
  if(cHomeState != cHomeStateOld){cHomeStateOld=cHomeState;Serial.print("c");Serial.print(cHomeState+4);}
  if(uHomeState != uHomeStateOld){uHomeStateOld=uHomeState;Serial.print("u");Serial.print(uHomeState+4);}
  if(vHomeState != vHomeStateOld){vHomeStateOld=vHomeState;Serial.print("v");Serial.print(vHomeState+4);}
  if(wHomeState != wHomeStateOld){wHomeStateOld=wHomeState;Serial.print("w");Serial.print(wHomeState+4);}

  if(xMaxState != xMaxStateOld){xMaxStateOld=xMaxState;Serial.print("x");Serial.print(xMaxState+1);}
  if(yMaxState != yMaxStateOld){yMaxStateOld=yMaxState;Serial.print("y");Serial.print(yMaxState+1);}
  if(zMaxState != zMaxStateOld){zMaxStateOld=zMaxState;Serial.print("z");Serial.print(zMaxState+1);}
  if(aMaxState != aMaxStateOld){aMaxStateOld=aMaxState;Serial.print("a");Serial.print(aMaxState+1);}
  if(bMaxState != bMaxStateOld){bMaxStateOld=bMaxState;Serial.print("b");Serial.print(bMaxState+1);}
  if(cMaxState != cMaxStateOld){cMaxStateOld=cMaxState;Serial.print("c");Serial.print(cMaxState+1);}
  if(uMaxState != uMaxStateOld){uMaxStateOld=uMaxState;Serial.print("u");Serial.print(uMaxState+1);}
  if(vMaxState != vMaxStateOld){vMaxStateOld=vMaxState;Serial.print("v");Serial.print(vMaxState+1);}
  if(wMaxState != wMaxStateOld){wMaxStateOld=wMaxState;Serial.print("w");Serial.print(wMaxState+1);}

  stepper0Goto=pos_x*stepsPerInchX*2;
  stepper1Goto=pos_y*stepsPerInchY*2;
  stepper2Goto=pos_z*stepsPerInchZ*2; // we need the *2 as we're driving a flip-flop routine (in stepLight function)
  stepper3Goto=pos_a*stepsPerInchA*2;
  stepper4Goto=pos_b*stepsPerInchB*2;
  stepper5Goto=pos_c*stepsPerInchC*2;
  stepper6Goto=pos_u*stepsPerInchU*2;
  stepper7Goto=pos_v*stepsPerInchV*2;
  stepper8Goto=pos_w*stepsPerInchW*2;

}

void processCommand()
{
    float xx=pos_x;
    float yy=pos_y;
    float zz=pos_z;
    float aa=pos_a;
    float bb=pos_b;
    float cc=pos_c;
    float uu=pos_u;
    float vv=pos_v;
    float ww=pos_w;

  char *ptr=buffer;
  while(ptr && ptr<buffer+sofar) {
    ptr=strchr(ptr,' ')+1;
    switch(*ptr) {
      case 'x': case 'X': xx=atof(ptr+1); xx=xx/divisor; break;
      case 'y': case 'Y': yy=atof(ptr+1); yy=yy/divisor; break;
      case 'z': case 'Z': zz=atof(ptr+1); zz=zz/divisor; break;
      case 'a': case 'A': aa=atof(ptr+1); aa=aa/divisor; break;
      case 'b': case 'B': bb=atof(ptr+1); bb=bb/divisor; break;
      case 'c': case 'C': cc=atof(ptr+1); cc=cc/divisor; break;
      case 'u': case 'U': uu=atof(ptr+1); uu=uu/divisor; break;
      case 'v': case 'V': vv=atof(ptr+1); vv=vv/divisor; break;
      case 'w': case 'W': ww=atof(ptr+1); ww=ww/divisor; break;
    default: ptr=0; break;
    }
  }

  jog(xx,yy,zz,aa,bb,cc,uu,vv,ww);
}

void stepLight() // Set by jog() && Used by loop()
{
  unsigned long curTime=micros();
  if(curTime - stepTimeOld >= minStepTime)
  {
    stepState=!stepState;
    

    if(stepper0Pos != stepper0Goto){if(stepper0Pos > stepper0Goto){digitalWriteFast2(dirPin0,!dirState0);digitalWriteFast2(stepPin0,stepState);stepper0Pos--;}else{digitalWriteFast2(dirPin0, dirState0);digitalWriteFast2(stepPin0,stepState);stepper0Pos++;}}
    if(stepper1Pos != stepper1Goto){if(stepper1Pos > stepper1Goto){digitalWriteFast2(dirPin1,!dirState1);digitalWriteFast2(stepPin1,stepState);stepper1Pos--;}else{digitalWriteFast2(dirPin1, dirState1);digitalWriteFast2(stepPin1,stepState);stepper1Pos++;}}
    if(stepper2Pos != stepper2Goto){if(stepper2Pos > stepper2Goto){digitalWriteFast2(dirPin2,!dirState2);digitalWriteFast2(stepPin2,stepState);stepper2Pos--;}else{digitalWriteFast2(dirPin2, dirState2);digitalWriteFast2(stepPin2,stepState);stepper2Pos++;}}
    if(stepper3Pos != stepper3Goto){if(stepper3Pos > stepper3Goto){digitalWriteFast2(dirPin3,!dirState3);digitalWriteFast2(stepPin3,stepState);stepper3Pos--;}else{digitalWriteFast2(dirPin3, dirState3);digitalWriteFast2(stepPin3,stepState);stepper3Pos++;}}
    if(stepper4Pos != stepper4Goto){if(stepper4Pos > stepper4Goto){digitalWriteFast2(dirPin4,!dirState4);digitalWriteFast2(stepPin4,stepState);stepper4Pos--;}else{digitalWriteFast2(dirPin4, dirState4);digitalWriteFast2(stepPin4,stepState);stepper4Pos++;}}
    if(stepper5Pos != stepper5Goto){if(stepper5Pos > stepper5Goto){digitalWriteFast2(dirPin5,!dirState5);digitalWriteFast2(stepPin5,stepState);stepper5Pos--;}else{digitalWriteFast2(dirPin5, dirState5);digitalWriteFast2(stepPin5,stepState);stepper5Pos++;}}
    if(stepper6Pos != stepper6Goto){if(stepper6Pos > stepper6Goto){digitalWriteFast2(dirPin6,!dirState6);digitalWriteFast2(stepPin6,stepState);stepper6Pos--;}else{digitalWriteFast2(dirPin6, dirState6);digitalWriteFast2(stepPin6,stepState);stepper6Pos++;}}
    if(stepper7Pos != stepper7Goto){if(stepper7Pos > stepper7Goto){digitalWriteFast2(dirPin7,!dirState7);digitalWriteFast2(stepPin7,stepState);stepper7Pos--;}else{digitalWriteFast2(dirPin7, dirState7);digitalWriteFast2(stepPin7,stepState);stepper7Pos++;}}
    if(stepper8Pos != stepper8Goto){if(stepper8Pos > stepper8Goto){digitalWriteFast2(dirPin8,!dirState8);digitalWriteFast2(stepPin8,stepState);stepper8Pos--;}else{digitalWriteFast2(dirPin8, dirState8);digitalWriteFast2(stepPin8,stepState);stepper8Pos++;}}

    stepTimeOld=curTime;
  }
}

void setup()
{
  pinMode(xEnablePin,OUTPUT);digitalWrite(xEnablePin,LOW);
  pinMode(yEnablePin,OUTPUT);digitalWrite(yEnablePin,LOW);
  pinMode(zEnablePin,OUTPUT);digitalWrite(zEnablePin,LOW);
  pinMode(aEnablePin,OUTPUT);digitalWrite(aEnablePin,LOW);
  pinMode(bEnablePin,OUTPUT);digitalWrite(bEnablePin,LOW);
  pinMode(cEnablePin,OUTPUT);digitalWrite(cEnablePin,LOW);
  pinMode(uEnablePin,OUTPUT);digitalWrite(uEnablePin,LOW);
  pinMode(vEnablePin,OUTPUT);digitalWrite(vEnablePin,LOW);
  pinMode(wEnablePin,OUTPUT);digitalWrite(wEnablePin,LOW);

  pinMode(stepPin0,OUTPUT);
  pinMode(stepPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT);
  pinMode(stepPin3,OUTPUT);
  pinMode(stepPin4,OUTPUT);
  pinMode(stepPin5,OUTPUT);
  pinMode(stepPin6,OUTPUT);
  pinMode(stepPin7,OUTPUT);
  pinMode(stepPin8,OUTPUT);
  
  pinMode(dirPin0,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(dirPin3,OUTPUT);
  pinMode(dirPin4,OUTPUT);
  pinMode(dirPin5,OUTPUT);
  pinMode(dirPin6,OUTPUT);
  pinMode(dirPin7,OUTPUT);
  pinMode(dirPin8,OUTPUT);

  pinMode(chanXms1,OUTPUT);pinMode(chanXms2,OUTPUT);pinMode(chanXms3,OUTPUT);
  pinMode(chanYms1,OUTPUT);pinMode(chanYms2,OUTPUT);pinMode(chanYms3,OUTPUT);
  pinMode(chanZms1,OUTPUT);pinMode(chanZms2,OUTPUT);pinMode(chanZms3,OUTPUT);
  pinMode(chanAms1,OUTPUT);pinMode(chanAms2,OUTPUT);pinMode(chanAms3,OUTPUT);
  pinMode(chanBms1,OUTPUT);pinMode(chanBms2,OUTPUT);pinMode(chanBms3,OUTPUT);
  pinMode(chanCms1,OUTPUT);pinMode(chanCms2,OUTPUT);pinMode(chanCms3,OUTPUT);
  pinMode(chanUms1,OUTPUT);pinMode(chanUms2,OUTPUT);pinMode(chanUms3,OUTPUT);
  pinMode(chanVms1,OUTPUT);pinMode(chanVms2,OUTPUT);pinMode(chanVms3,OUTPUT);
  pinMode(chanWms1,OUTPUT);pinMode(chanWms2,OUTPUT);pinMode(chanWms3,OUTPUT);

  stepMode('ALL',1);
  Serial.begin(BAUD);
  sofar=0;
}

void stepMode(char axis, int mode) // May be omitted in the future. (Undecided)
{
  // called just once during setup()
  
  // This works OPPOSITE of what you might think.
  // Mode 1 = 1/16 step.
  // Mode 2 = 1/8 step.
  // Mode 4 = 1/4 step.
  // Mode 8 = 1/2 step.
  // Mode 16 = Full step.
  // Its simular to a car's gearbox with gears from low to high as in 1,2,4,8,16

  // Originally intended for dynamic microstepping control to reduce mpu overhead and speed steppers when moving large distances.
  // Real world result: Increased overhead and slowed steppers while juggling unessessary math and pin commands.
  
  boolean ms1;
  boolean ms2;
  boolean ms3;
  int count;
  if(mode>=16){ms1=LOW;ms2=LOW;ms3=LOW;count=16;}
  if(mode>=8 && mode<=15){ms1=HIGH;ms2=LOW;ms3=LOW;count=8;}
  if(mode>=4 && mode<=7){ms1=LOW;ms2=HIGH;ms3=LOW;count=4;}
  if(mode>=2 && mode<=3){ms1=HIGH;ms2=HIGH;ms3=LOW;count=2;}
  if(mode<=1){ms1=HIGH;ms2=HIGH;ms3=HIGH;count=1;}
  if(axis == 'X' || 'ALL'){if(mode!=stepModeX){digitalWriteFast2(chanXms1,ms1);digitalWriteFast2(chanXms2,ms2);digitalWriteFast2(chanXms3,ms3);stepModeX=count;}}
  if(axis == 'Y' || 'ALL'){if(mode!=stepModeY){digitalWriteFast2(chanYms1,ms1);digitalWriteFast2(chanYms2,ms2);digitalWriteFast2(chanYms3,ms3);stepModeY=count;}}
  if(axis == 'Z' || 'ALL'){if(mode!=stepModeZ){digitalWriteFast2(chanZms1,ms1);digitalWriteFast2(chanZms2,ms2);digitalWriteFast2(chanZms3,ms3);stepModeZ=count;}}
  if(axis == 'A' || 'ALL'){if(mode!=stepModeA){digitalWriteFast2(chanAms1,ms1);digitalWriteFast2(chanAms2,ms2);digitalWriteFast2(chanAms3,ms3);stepModeA=count;}}
  if(axis == 'B' || 'ALL'){if(mode!=stepModeB){digitalWriteFast2(chanBms1,ms1);digitalWriteFast2(chanBms2,ms2);digitalWriteFast2(chanBms3,ms3);stepModeB=count;}}
  if(axis == 'C' || 'ALL'){if(mode!=stepModeC){digitalWriteFast2(chanCms1,ms1);digitalWriteFast2(chanCms2,ms2);digitalWriteFast2(chanCms3,ms3);stepModeC=count;}}
  if(axis == 'U' || 'ALL'){if(mode!=stepModeU){digitalWriteFast2(chanUms1,ms1);digitalWriteFast2(chanUms2,ms2);digitalWriteFast2(chanUms3,ms3);stepModeU=count;}}
  if(axis == 'V' || 'ALL'){if(mode!=stepModeV){digitalWriteFast2(chanVms1,ms1);digitalWriteFast2(chanVms2,ms2);digitalWriteFast2(chanVms3,ms3);stepModeV=count;}}
  if(axis == 'W' || 'ALL'){if(mode!=stepModeW){digitalWriteFast2(chanWms1,ms1);digitalWriteFast2(chanWms2,ms2);digitalWriteFast2(chanWms3,ms3);stepModeW=count;}}
}

void loop()
{
  // listen for serial commands
  while(Serial.available() > 0) {
    buffer[sofar++]=Serial.read();
    if(buffer[sofar-1]==';') break;  // in case there are multiple instructions
  }
 
  // if we hit a semi-colon, assume end of instruction.
  if(sofar>0 && buffer[sofar-1]==';') {
 
    buffer[sofar]=0;
 
    // do something with the command
    processCommand();
 
    // reset the buffer
    sofar=0;
  }
  stepLight(); // call every loop cycle.
}
