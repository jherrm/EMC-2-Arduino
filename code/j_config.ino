// Adjust these to reflect EMC's limits *1000000
#define xMinLimit -500000
#define yMinLimit -250000
#define zMinLimit -1500000
#define xMaxLimit 11000000
#define yMaxLimit 70000000
#define zMaxLimit 15000000

#define xServoTolerance 1 // Slop allowance, too little = oscillation vs. too much = sloppy deadzone, inaccuracy.
#define yServoTolerance 2 // Ditto.

// Pin config section
#define pwrSwitch 42 // For toggling power button within the EMC application window.

#define encoderXa 20 // Your quadrature encoder pins go here.
#define encoderXb 22
#define encoderYa 21
#define encoderYb 23

  // pin config for the "Official Aruino Motor Shield"
#define loadX A0 // not used. Yet?
#define loadY A1 // not used. Yet?
#define pwmX 3
#define pwmY 11
#define xPowerOutput 150 // Aright Scotty. How fast you wanna go. Too much = noisy,fuzzy (but interesting) drawings
#define yPowerOutput 150 //  and a hot driver circuit,  Too little = weak, wobbly or no movement at all. Max.value=255
#define xOverdrivePwr 255 // Reffer to the l_variables tab. (Section: Servo options)
#define yOverdrivePwr 255
#define dirX 12
#define dirY 13
#define enableX 9
#define enableY 8
#define zSolenoid 27

  // lcd config
#define lcdColumns 8
#define lcdRows 2
#define lcdRS 53
#define lcdEN 52
#define lcdD4 50
#define lcdD5 51
#define lcdD6 48
#define lcdD7 49

  // ATX psu control
#define atxPowerCtrl A15     // Usually the PSU's green wire. (We bring this LOW to turn PSU on.)
#define atxPowerState 36     // Usually the PSU's gray wire. (Use a diode, ie. Arduino --|<|-- PSU, else lights blink when PSU sleeps.)
#define atxPowerLed 35       // Just an output led pin for visual feedback.
#define atxPowerTimeout 1000 // How long to wait before shutting down once EMC has been closed. (milliSeconds) 

//Libraries to include are as follows:
#include <LiquidCrystal.h>     // Standard issue arduino library, most likely you already have this one.
#include <digitalWriteFast.h>  // Found at http://code.google.com/p/digitalwritefast/downloads/list get the safe one.
#include <Encoder.h>           // Found at http://www.pjrc.com/teensy/td_libs_Encoder.html

