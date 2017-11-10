/*
***************************************************************************  
**  Program  : MFS_Demo
**  Copyright (c) 2017 Willem Aandewiel
**
**  TERMS OF USE: MIT License. See bottom of file.                                                            
***************************************************************************  
**
**  Button_1: short press: Start/Stop UP-counter
**            long press : Zero counter  
**
**  Button_2: short press: Start/Stop DOWN-counter
**            long press : Zero counter  
**
**  Button_3: short press: read Potmeter value
**            long press : return to previous mode  
**            
*/

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

enum ModeValues {
  COUNTING_STOPPED,
  COUNT_UP,
  COUNT_DOWN,
  READ_POT
};

byte saveMode, actualMode = COUNTING_STOPPED;
byte lastButton;
char seconds = 0;
char minutes = 0;
uint32_t  delay1Sec, delay250ms;
int walkingLed = 0;


void scrollText(String text, int speed) {
  String seg4;

  text = "   " + text + "  ";

  for (int p=0; p < text.length(); p++) {
      seg4 = text.substring(p, (p+4));
      MFS.write(seg4.c_str());
      delay(speed);
  }
  
} // scrollText();


void animateDisplay() {
  Serial.println("All LED's ON");
  MFS.writeLeds(LED_ALL, ON);
  
  scrollText("Multi Functional Shield", 500);
  
  Serial.println("All LED's OFF");
  MFS.writeLeds(LED_ALL, OFF);
  delay(100);
  Serial.println("LED 1 ON");
  MFS.writeLeds(LED_1, ON);
  delay(200);
  Serial.println("LED 2 ON");
  MFS.writeLeds(LED_2, ON);
  delay(200);
  Serial.println("LED 3 ON");
  MFS.writeLeds(LED_3, ON);
  delay(200);
  Serial.println("LED 4 ON");
  MFS.writeLeds(LED_4, ON);
  delay(200);
  Serial.println("LED 1 OFF");
  MFS.writeLeds(LED_1, OFF);
  delay(200);
  Serial.println("LED 2 OFF");
  MFS.writeLeds(LED_2, OFF);
  delay(200);
  Serial.println("LED 3 OFF");
  MFS.writeLeds(LED_3, OFF);
  delay(200);

  Serial.println("All LED's OFF");
  MFS.writeLeds(LED_ALL, OFF);
  
} // animateDisplay()


void setup() {
 // put your setup code here, to run once:
  Timer1.initialize();
  MFS.initialize(&Timer1); // initialize multi-function shield library
  MFS.write(0);

  Serial.begin(19200);
  
  animateDisplay();

  actualMode = COUNTING_STOPPED;
  saveMode   = COUNTING_STOPPED;
  
  MFS.write(0);
  delay1Sec = millis();

} // setup()


void loop() {
  
  lastButton = MFS.getButton();
  
  switch (actualMode) {
    case COUNTING_STOPPED:
                if ((minutes*100 + seconds) == 0 && (millis() > delay250ms + 250)) {
                    delay250ms = millis();
                    walkingLed++;
                    if (walkingLed > 15) walkingLed = 0;
                    MFS.writeLeds(LED_ALL, OFF);
                    MFS.writeLeds(walkingLed, ON); 
                }

                if (lastButton == BUTTON_1_LONG_RELEASE || lastButton == BUTTON_2_LONG_RELEASE ||
                    lastButton == BUTTON_1_LONG_PRESSED || lastButton == BUTTON_2_LONG_PRESSED) {
                  Serial.println("BUTTON_n_LONG_RELEASE/PRESSED");
                  // reset the timer
                  seconds = 0;
                  minutes = 0;
                  MFS.write(minutes*100 + seconds);
                    /**.
                           /-------------- beep for 50 milliseconds
                           |  /----------- silent for 50 milliseconds
                           |  |  /-------- repeat above cycle 5 times
                           |  |  |  /----- loop 1 times
                           |  |  |  |  /-- wait 10 milliseconds between loop
                           |  |  |  |  |
                           |  |  |  |  |      **/
                  MFS.beep(5, 5, 5, 1, 1); 
                  actualMode = COUNTING_STOPPED;
                } else if (lastButton == BUTTON_1_SHORT_RELEASE) {
                  Serial.println("BUTTON_1_SHORT_RELEASE");
                    /**.
                           /-------------- beep for 10 milliseconds
                           |  /----------- silent for 10 milliseconds
                           |  |  /-------- repeat above cycle 1 times
                           |  |  |  /----- loop 1 times
                           |  |  |  |  /-- wait 10 milliseconds between loop
                           |  |  |  |  |
                           |  |  |  |  |      **/
                  MFS.beep(1, 1, 1, 1, 1); 
                  actualMode = COUNT_UP;
                  delay1Sec = millis();
                } else if (lastButton == BUTTON_2_SHORT_RELEASE) {
                  Serial.println("BUTTON_2_SHORT_RELEASE");
                    /**.
                           /-------------- beep for 10 milliseconds
                           |  /----------- silent for 10 milliseconds
                           |  |  /-------- repeat above cycle 1 times
                           |  |  |  /----- loop 1 times
                           |  |  |  |  /-- wait 10 milliseconds between loop
                           |  |  |  |  |
                           |  |  |  |  |      **/
                  MFS.beep(1, 1, 1, 1, 1); 
                  actualMode  = COUNT_DOWN;
                  delay1Sec  = millis();
                  delay250ms = millis();
                }
                break;

    case COUNT_UP:
                if (lastButton == BUTTON_1_SHORT_RELEASE) {
                  Serial.println("BUTTON_1_SHORT_RELEASE");
                    /**.
                           /-------------- beep for 10 milliseconds
                           |  /----------- silent for 10 milliseconds
                           |  |  /-------- repeat above cycle 1 times
                           |  |  |  /----- loop 1 times
                           |  |  |  |  /-- wait 10 milliseconds between loop
                           |  |  |  |  |
                           |  |  |  |  |      **/
                  MFS.beep(1, 1, 1, 1, 1); 
                  // stop the timer
                  actualMode = COUNTING_STOPPED;
                  MFS.writeLeds(LED_ALL, OFF);
                } else {
                  //------ walk the LED's ----------------
                  if (millis() > delay250ms + 250) {
                    delay250ms = millis();
                    walkingLed--;
                    if (walkingLed < 0) walkingLed = 3;
                    MFS.writeLeds(LED_ALL, OFF);
                    MFS.writeLeds((1 << walkingLed), ON); 
                  }
                  // continue counting
                  if (millis() > (delay1Sec + 1000)) {
                    delay1Sec = millis();
                    seconds++;
                  }

                  if (seconds > 59) {
                    seconds = 0;
                    minutes++;
                    /**.
                             /-------------- beep for 10 milliseconds
                             |  /----------- silent for 10 milliseconds
                             |  |  /-------- repeat above cycle 1 times
                             |  |  |  /----- loop 1 times
                             |  |  |  |  /-- wait 10 milliseconds between loop
                             |  |  |  |  |
                             |  |  |  |  |      **/
                    MFS.beep(1, 1, 1, 1, 1); 
                  }

                  if (minutes > 59) {
                    minutes = 0;
                    seconds = 0;
                    MFS.beep(50, 50, 3); // beep 3 times, 500 milliseconds on / 500 off
                  }

                  MFS.write(minutes*100 + seconds);

                }
                break;

    case COUNT_DOWN:
                if (lastButton == BUTTON_2_SHORT_RELEASE) {
                  Serial.println("BUTTON_2_SHORT_RELEASE");
                    /**.
                             /-------------- beep for 20 milliseconds
                             |  /----------- silent for 20 milliseconds
                             |  |  /-------- repeat above cycle 1 times
                             |  |  |  /----- loop 1 times
                             |  |  |  |  /-- wait 10 milliseconds between loop
                             |  |  |  |  |
                             |  |  |  |  |      **/
                    MFS.beep(2, 2, 1, 1, 1); 
                  // stop the timer
                  actualMode = COUNTING_STOPPED;
                } else {
                  //------ walk the LED's ----------------
                  if (millis() > delay250ms + 250) {
                    delay250ms = millis();
                    walkingLed++;
                    if (walkingLed > 3) walkingLed = 0;
                    MFS.writeLeds(LED_ALL, OFF); 
                    MFS.writeLeds((1 << walkingLed), ON); 
                  }

                  // continue counting
                  if (millis() > (delay1Sec + 1000)) {
                    delay1Sec = millis();
                    seconds--;
                  }

                  if (seconds < 0) {
                    seconds = 59;
                    minutes--;
                    // 4 short beeps, repeated 3 times.
                    /**.
                             /-------------- beep for 20 milliseconds
                             |  /----------- silent for 20 milliseconds
                             |  |  /-------- repeat above cycle 1 times
                             |  |  |  /----- loop 1 times
                             |  |  |  |  /-- wait 10 milliseconds between loop
                             |  |  |  |  |
                             |  |  |  |  |      **/
                    MFS.beep(2, 2, 1, 1, 1); 
                  }

                  if (minutes < 0) {
                    minutes = 0;
                    seconds = 0;
                    MFS.writeLeds(LED_ALL, OFF);
                    MFS.beep(25, 25, 3); // beep 3 times, 500 milliseconds on / 500 off
                    actualMode = COUNTING_STOPPED;
                  } 

                  MFS.write(minutes*100 + seconds);
                }
                break;

    case READ_POT:
                if (lastButton == BUTTON_3_LONG_PRESSED ||
                    lastButton == BUTTON_1_SHORT_RELEASE || lastButton == BUTTON_2_SHORT_RELEASE) {
                  MFS.beep(); // 200 milli seconds
                  Serial.println("BUTTON_3_LONG_RELEASE");
                  actualMode = saveMode;
                  MFS.write(minutes*100 + seconds);
                } else {                
                  MFS.write(analogRead(POT_PIN));
                  delay(50);
                  if (saveMode == COUNT_UP) {
                    //-- walk the LED's ----
                    if (millis() > delay250ms + 250) {
                      delay250ms = millis();
                      walkingLed--;
                      if (walkingLed < 0) walkingLed = 3;
                      MFS.writeLeds(LED_ALL, OFF);
                      MFS.writeLeds((1 << walkingLed), ON); 
                    }                  

                    if (millis() > (delay1Sec + 1000)) {
                      delay1Sec = millis();
                      seconds++;
                    }

                    if (seconds > 59) {
                      seconds = 0;
                      minutes++;
                      /**.
                               /-------------- beep for 10 milliseconds
                               |  /----------- silent for 10 milliseconds
                               |  |  /-------- repeat above cycle 1 times
                               |  |  |  /----- loop 1 times
                               |  |  |  |  /-- wait 10 milliseconds between loop
                               |  |  |  |  |
                               |  |  |  |  |      **/
                      MFS.beep(1, 1, 1, 1, 1); 
                    }

                    if (minutes > 59) {
                      minutes = 0;
                      seconds = 0;
                      MFS.beep(20, 20, 5); // beep 5 times, 200 milliseconds on / 200 off
                    }

                  } // COUNT_UP
                  
                  if (saveMode == COUNT_DOWN) {
                    //-- walk the LED's ----
                    if (millis() > delay250ms + 250) {
                      delay250ms = millis();
                      walkingLed++;
                      if (walkingLed > 3) walkingLed = 0;
                      MFS.writeLeds(LED_ALL, OFF); 
                      MFS.writeLeds((1 << walkingLed), ON); 
                    }                  

                    if (millis() > (delay1Sec + 1000)) {
                      delay1Sec = millis();
                      seconds--;
                    }

                    if (seconds < 0) {
                      seconds = 59;
                      minutes--;
                      /**.
                               /-------------- beep for 10 milliseconds
                               |  /----------- silent for 10 milliseconds
                               |  |  /-------- repeat above cycle 1 times
                               |  |  |  /----- loop 1 times
                               |  |  |  |  /-- wait 10 milliseconds between loop
                               |  |  |  |  |
                               |  |  |  |  |      **/
                      MFS.beep(1, 1, 1, 1, 1); 
                    }

                    if (minutes < 0) {
                      minutes = 0;
                      seconds = 0;
                      MFS.writeLeds(LED_ALL, OFF);
                      MFS.beep(50, 50, 5); // beep 5 times, 500 milliseconds on / 500 off
                      saveMode = COUNTING_STOPPED;
                    }

                  } // COUNT_DOWN
                }
                break;
                
  } // switch on mode

  
  if (actualMode != READ_POT && lastButton == BUTTON_3_PRESSED) {
    Serial.println("BUTTON_3_PRESSED");
    MFS.beep();
    if (actualMode != READ_POT) {
      saveMode   = actualMode;
    }
    actualMode = READ_POT;
  }

} // loop()


/***************************************************************************
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit
* persons to whom the Software is furnished to do so, subject to the
* following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
* OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
* THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* 
***************************************************************************/

