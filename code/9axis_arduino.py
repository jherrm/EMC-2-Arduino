#!/usr/bin/python
#    HAL userspace component to interface with Arduino board
#    by Colin Kingsbury (http://ckcnc.wordpress.com_)
#    Inspired by the earlier example from Jeff Epler
#
#    Modified by Duane Bishop for use with EMC-2-Arduino
#	(https://github.com/dewy721/EMC-2-Arduino)
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
import serial
import hal
import sys
import time

class Pins:
  SWITCH_ON         = 'switch-on'
  SWITCH_OFF        = 'switch-off'
  ESTOP             = 'eStop'
  PROBE             = 'probe'
  SPINDLE_ENABLE    = 'spindleEnable'
  SPINDLE_DIRECTION = 'spindleDirection'
  SPINDLE_AT_SPEED  = 'spindleAtSpeed'
  COOLANT_MIST      = 'coolantMist'
  COOLANT_FLOOD     = 'coolantFlood'
  START             = 'start'
  STOP              = 'stop'
  PAUSE             = 'pause'
  RESUME            = 'resume'
  STEP              = 'step'
  MACHINE_STATE     = 'machine-state'

  # All AXIS_* pins must be prefixed by the axis name (lowercase)
  AXIS_POSITION     = 'PosCmd'
  AXIS_MIN_LIMIT    = 'MinLmt'
  AXIS_MAX_LIMIT    = 'MaxLmt'
  AXIS_HOME         = 'Home'

def create_axes_pins(component, axes):
  for axis in axes:
    component.newpin(axis +  Pins.AXIS_POSITION, hal.HAL_FLOAT, hal.HAL_IN)
    component.newpin(axis + Pins.AXIS_MIN_LIMIT,   hal.HAL_BIT, hal.HAL_IN)
    component.newpin(axis + Pins.AXIS_MAX_LIMIT,   hal.HAL_BIT, hal.HAL_IN)
    component.newpin(axis +      Pins.AXIS_HOME,   hal.HAL_BIT, hal.HAL_IN)


#First we open the serial port. This should correspond to the port the Arduino
#is connected to. This can be found in the Arduino IDE in Tools->Serial Port
PORT = "/dev/ttyACM0"
ser = serial.Serial(PORT, 115200, timeout=15)

#Now we create the HAL component and its pins
c = hal.component("arduino")
c.newpin(         Pins.SWITCH_ON, hal.HAL_BIT, hal.HAL_IN)
c.newpin(        Pins.SWITCH_OFF, hal.HAL_BIT, hal.HAL_IN)
c.newpin(             Pins.ESTOP, hal.HAL_BIT, hal.HAL_IN)
c.newpin(             Pins.PROBE, hal.HAL_BIT, hal.HAL_IN)
c.newpin(    Pins.SPINDLE_ENABLE, hal.HAL_BIT, hal.HAL_IN)
c.newpin( Pins.SPINDLE_DIRECTION, hal.HAL_BIT, hal.HAL_IN)
c.newpin(  Pins.SPINDLE_AT_SPEED, hal.HAL_BIT, hal.HAL_IN)
c.newpin(      Pins.COOLANT_MIST, hal.HAL_BIT, hal.HAL_IN)
c.newpin(     Pins.COOLANT_FLOOD, hal.HAL_BIT, hal.HAL_IN)
c.newpin(             Pins.START, hal.HAL_BIT, hal.HAL_IN)
c.newpin(              Pins.STOP, hal.HAL_BIT, hal.HAL_IN)
c.newpin(             Pins.PAUSE, hal.HAL_BIT, hal.HAL_IN)
c.newpin(            Pins.RESUME, hal.HAL_BIT, hal.HAL_IN)
c.newpin(              Pins.STEP, hal.HAL_BIT, hal.HAL_IN)
c.newpin(     Pins.MACHINE_STATE, hal.HAL_BIT, hal.HAL_IN)

# axis name cannot be any of the following: [p, e, P, h, S] whic are reserved for
# [power, eStop, probe, start/stop/pause/resume/step, signal] when decoding serial commands
axes = ['x', 'y', 'z', 'a', 'b', 'c', 'u', 'v', 'w']
create_axes_pins(c, axes)

time.sleep(2)

c.ready()

#We save the machine state (i.e. whether it's off or on) so that we only
#send a message to the Arduino when it changes
machineState = c[Pins.MACHINE_STATE]
eStopState   = c[Pins.ESTOP]

#Check if the machine is on and set the LED accordingly
if(machineState != 1):
  ser.write("+P")

# store the last position of the axes to detect changes, initialize to 0
axes_pos = {}
for axis in axes:
  axes_pos[axis] = 0

coolantMistOld = 0;
coolantFloodOld = 0;
spindleEnableOld = 0;
spindleDirectionOld = 0;

jog_multiplier = 1000000 # Our HAL script won't send the six decimal place floats that EMC cranks out.
                         # A simple workaround is to multply it by 1000000 before sending it over the wire.
                         # This must be reversed in the arduino firmware via a divisor.

try:
  while 1:
    time.sleep(.01)

    for axis in axes:
      axis_pos = c[axis + Pins.AXIS_POSITION];
      if axis_pos != axes_pos[axis]:
        axes_pos[axis] = axis_pos;
        ser.write("jog " + axis.upper());
        ser.write(repr(axis_pos * jog_multiplier))
        ser.write(";");
        ser.write("\n");


    spindleEnable = c[Pins.SPINDLE_ENABLE];
    if spindleEnable != spindleEnableOld:
      spindleEnableOld = spindleEnable;
      if spindleEnable == 1:
        ser.write("+S;");
      else:
        ser.write("-S;");

    spindleDirection = c[Pins.SPINDLE_DIRECTION];
    if spindleDirection != spindleDirectionOld:
      spindleDirectionOld = spindleDirection;
      if spindleDirection == 1:
        ser.write("+D;");
      else:
        ser.write("-D;");

    coolantMist = c[Pins.COOLANT_MIST];
    if coolantMist != coolantMistOld:
      coolantMistOld = coolantMist;
      if coolantMist == 1:
        ser.write("+M;");
      else:
        ser.write("-M;");

    coolantFlood = c[Pins.COOLANT_FLOOD];
    if coolantFlood != coolantFloodOld:
      coolantFloodOld = coolantFlood;
      if coolantFlood == 1:
        ser.write("+F;");
      else:
        ser.write("-F;");

    #Check the machine State
    if(machineState != c[Pins.MACHINE_STATE]):
      if(c[Pins.MACHINE_STATE] == 1):
        #The machine is on, so turn on the power LED
        ser.write("+P;")
      else:
        #opposite of above
        ser.write("-P;")
      #update the machine state variable
      machineState = c[Pins.MACHINE_STATE]

    #Check to see if we have a message waiting from the Arduino
    while ser.inWaiting():
      #This should be set to the length of whatever fixed-length message
      #you're sending from the arduino. It does not have to be the same length
      #as the outbound messages.
      key = ser.read(2)
      #The Arduino generates two different key events
      #One when the key is pressed down (+S) and another when it is released (-S)
      #In this case we are going to ignore the release

      # axes
      if(key[0] in axes):
        axis = key[0]
        cmd  = key[1]
        if(cmd == '0'): # e.g. "x0"
          # Set min limit triggers
          c[axis + Pins.AXIS_MIN_LIMIT] = 1
        if(cmd == '1'): # e.g. "x1"
          # Clear limit triggers
          c[axis + Pins.AXIS_MIN_LIMIT] = 0
          c[axis + Pins.AXIS_MAX_LIMIT] = 0
        if(cmd == '2'): # e.g. "x2"
          # Set max limit triggers
          c[axis + Pins.AXIS_MAX_LIMIT] = 1
        if(cmd == '4'): # e.g. "x4"
          # set home switches
          c[axis + Pins.AXIS_HOME] = 0
        if(cmd == '5'): # e.g. "x5"
          # unset home switches
          c[axis + Pins.AXIS_HOME] = 1

      #power
      if(key == "p0"):
        c[Pins.SWITCH_ON]  = 0
        c[Pins.SWITCH_OFF] = 1
      if(key == "p1"):
        c[Pins.SWITCH_ON]  = 1
        c[Pins.SWITCH_OFF] = 0
      if(key == "pt"):
        # If the machine is currently on, we turn it off, and vice-versa
        if(machineState == 1):
          c[Pins.SWITCH_ON]  = 1
          c[Pins.SWITCH_OFF] = 0
        else:
          c[Pins.SWITCH_ON]  = 0
          c[Pins.SWITCH_OFF] = 1

      #eStop
      if(key == "e0"):
        c[Pins.ESTOP] = 1
      if(key == "e1"):
        c[Pins.ESTOP] = 0

      #probe
      if(key == "P0"):
        c[Pins.PROBE] = 1
      if(key == "P1"):
        c[Pins.PROBE] = 0

      #program start
      if(key == "h0"):
        c[Pins.START] = 0
      if(key == "h1"):
        c[Pins.START] = 1

      #program stop
      if(key == "h2"):
        c[Pins.STOP] = 0
      if(key == "h3"):
        c[Pins.STOP] = 1

      #program pause
      if(key == "h4"):
        c[Pins.PAUSE] = 1
      if(key == "h5"):
        c[Pins.PAUSE] = 0

      #program resume
      if(key == "h6"):
        c[Pins.RESUME] = 1
      if(key == "h7"):
        c[Pins.RESUME] = 0

      #program step
      if(key == "h8"):
        c[Pins.STEP] = 1
      if(key == "h9"):
        c[Pins.STEP] = 0

      #spindle at speed signal
      if(key == "S1"):
        c[Pins.SPINDLE_AT_SPEED] = 1
      if(key == "S0"):
        c[Pins.SPINDLE_AT_SPEED] = 0

except KeyboardInterrupt:
    ser.write("-P;");
    raise SystemExit

