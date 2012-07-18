

/*
 EmcArduino version 0.04alpha, this work is public domain.
 
 This ALPHA quality sketch is used for intergrating an
 Arduino with EMC2.4/AXIS as a CNC host. 
 
 Current Features:
   Stepper Support
   Idustry compliant G-Code Host via EMC w/tons of features.
   Automatic ATX power supply control.
   LCD Support
   
 To Do List:
   Blind Closed-loop feedback control. (Arduino controlled)
   Encoder to EMC communications for fully closed loop control.
   Spindle Support
   More axies EMC can go upto 9!!!
   Support for extras like coolant pumps, fans, and more buttons (like E-Stop.)
   Physical limit switches instead of just virtual ones.
   Multi-USB & I2C Support (technically there is no reason why one arduino has to do everything.)
   Multi-Machine control, fabshop, machine chaining.
     ie. One PC, 3 machines, running simultaneously in sync as an assembly line.
   
 Hardware requirments:
   1x PC with USB port and EMC Linux and installed.
   1x Arduino, Prefferably a Mega2560 (for more pin options.)
   1x Arduino Motor Shield (or an H-Bridge of you choice.)
   2x Encoders (or servos w/encoders)
   1x Plotter solenoid. To hold a pen for testing it out with.
  
 Credits:
 Jeff Epler http://axis.unpy.net/etchcnc for inspiring Colin Kingsbury to make the following.
 Colin Kingsbury for http://ckcnc.wordpress.com/basic-arduino-emc-howto/arduino-sketch/
             and for http://ckcnc.wordpress.com/basic-arduino-emc-howto/python-emc-module/
             and for http://ckcnc.wordpress.com/basic-arduino-emc-howto/hal-file-for-simple-arduino-example/
 Dan ? of http://www.marginallyclever.com/2011/10/controlling-your-arduino-through-the-serial-monitor/
 All the folks at http://www.linuxcnc.org/ for making the very excellent and very free EMC2.4/AXIS Linux distro.
 And lastly Duane Bishop (Myself) for playing with legos and hacking up printers. :)

*/



 

