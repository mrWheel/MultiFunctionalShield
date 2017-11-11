# MultiFunctional Shield

Demo program for the Arduino MultiFunctional Shield
<br />
<br />
You need to install the following library's:

TimerOne          - https://github.com/PaulStoffregen/TimerOne (part of the default IDE installation)
<br />
Wire              - https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire (part of the default IDE installation)
<br />
MultiFuncShield   - http://files.cohesivecomputing.co.uk/MultiFuncShield-Library.zip
<br />
<br />
After compiling and uploading to the Arduino UNO you can use the following buttons:

  Button 1:  
<br />&nbsp; &nbsp; &nbsp; short press: Start/Stop UP-counter
<br />&nbsp; &nbsp; &nbsp; long press : Zero counter  

  Button 2: 
<br />&nbsp; &nbsp; &nbsp; short press: Start/Stop DOWN-counter
<br />&nbsp; &nbsp; &nbsp; long press : Zero counter  

  Button 3: 
<br />&nbsp; &nbsp; &nbsp; short press: read Potmeter value
<br />&nbsp; &nbsp; &nbsp; long press : return to previous mode  

<br />The program does the counting, checking buttons, lighting the LED's and reading the potentiometer <b>simultaneously</b>!
<br /><br />
See the program at work in this video https://youtu.be/4BS07XFOi9w
<br /><br />
<b>Watch out!!</b>
<br />
The soldering connections on the back of the MultiFunction Shield short-out on the USB connector on the Arduino UNO. Make shure you stick some isolation material on the back of the shield!
<br />
![Alt text](https://github.com/mrWheel/MultiFunctionalShield/blob/master/IMG_3403.JPG?raw=true "Isolate LED connections")
