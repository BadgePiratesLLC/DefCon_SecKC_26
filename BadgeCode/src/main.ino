#include "Chaplex.h"
#include <PinButton.h>

#define A 0 // pin 12
#define B 1 // pin 14
#define C 2 // pin 27
#define D 3 // pin 19
#define E 4 // pin 18
#define G 5 // pin 5
#define H 6 // pin 17

byte controlPins[] = {12, 14, 27, 19, 18, 5, 17};
#define numControlPins sizeof(controlPins) / sizeof(*controlPins)
Chaplex myCharlie(controlPins, numControlPins); //control instance

charlieLed indicatorLeds[9] = {
  {G,B},
  {G,H},
  {G,E}, // wifi light
  {A,H},
  {E,H},
  {B,H},
  {D,H},
  {G,B},
  {C,H}
};

charlieLed myLeds[34]  = {
  // left laurel
  {E,B}, {H,E}, {D,B}, {A,G}, {C,B}, {B,G}, {A,B}, {C,G},
  {H,A}, {G,A}, {D,G}, {E,A}, {E,G}, {D,A}, {H,G}, {C,A},
  {B,A},
  // right laurel
  {H,B}, {D,E}, {A,C}, {C,E}, {B,C}, {B,E}, {D,C}, {A,E},
  {E,C}, {H,D}, {G,C}, {H,C}, {G,D}, {A,D}, {E,D}, {B,D},
  {C,D}
};

charlieLed allLeds[42]  = {
  {A,B},  {B,C},  {C,D},  {D,E},  {E,G},  {G,H},  {H,A},
  {B,A},  {C,B},  {D,C},  {E,D},  {G,E},  {H,G},  {A,H},
  {A,C},  {B,D},  {C,E},  {D,G},  {E,H},  {G,A},  {H,B},
  {C,A},  {D,B},  {E,C},  {G,D},  {H,E},  {A,G},  {B,H},
  {A,D},  {B,E},  {C,G},  {D,H},  {E,A},  {G,B},  {H,C},
  {D,A},  {E,B},  {G,C},  {H,D},  {A,E},  {B,G},  {C,H}
};

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
int interruptCounter;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
  myCharlie.outRow();
}

hw_timer_t * timer = NULL;

void setup() {
  Serial.begin(115200);

  pinMode(13,INPUT_PULLUP);

  randomSeed(analogRead(A0));

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 100, true);
  timerAlarmEnable(timer);
}

PinButton myButton(13);
int animationState = 0;
int numUnlockedAnimations = 2;
int totalInterruptCounter;

void loop() {

  myButton.update();

  if (myButton.isSingleClick()) {
    Serial.println("single");
    // Only triggers on a single, short click (i.e. not
    // on the first click of a double-click, nor on a long click).
    if(animationState >= numUnlockedAnimations) {
      animationState = 0;
    }
    else {
      animationState++;
    }
  }

  switch(animationState) {
    case 0:
      snowfall();
      break;
    case 1:
      reverseSnowfall();
      break;
    case 2:
      defaultAnimation();
      break;
    case 3:
      flashyFlashy();
      break;
  }

  if (interruptCounter > 0) {
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
    totalInterruptCounter++;
  }
}

void getHallReading() {
  int measurement = 0;

    measurement = hallRead();

    if(measurement >= 50) {
      numUnlockedAnimations = 3;
      animationState = 3;
    }
}

void meshIndicator(bool meshStatus) {
  if(meshStatus) {
    myCharlie.ledWrite(indicatorLeds[3], 1);
  } else {
    myCharlie.ledWrite(indicatorLeds[3], 0);
  }
}

int current = 0;

int snowCurrent = 16;

void flashyFlashy(){
    unsigned long timeNow = millis();                     //
    unsigned long displayTime = 1000 + random(90);          // milliseconds to spend at each focus LED in descent
    while(millis()- timeNow < (displayTime+current*2)) {  // animation slows toward end
      for (byte i=0; i<8; i++)
        myCharlie.ledWrite(allLeds[(byte)random(0,42)], (byte)random(0,2));
    }
}

void snowfall(){
  unsigned long loopCount = 0;                          // used to determine duty cycle of each LED
  unsigned long timeNow = millis();                     //
  unsigned long displayTime = 100;          // milliseconds to spend at each focus LED in descent
  while(millis()- timeNow < (displayTime+current*2)) {  // animation slows toward end
    loopCount++;
    // the "snowflake" gets full duty cycle.  When it gets to the end, hold it at the end until the tail collapses
    myCharlie.ledWrite(myLeds[snowCurrent], 1);
    myCharlie.ledWrite(myLeds[snowCurrent + 17], 1);
    // each member of tail has reduced duty cycle, and never get to the final position
    if(!(loopCount % 3)) if(snowCurrent+1 <=16 && snowCurrent+1 > 0) myCharlie.ledWrite(myLeds[snowCurrent+1], 1);
    if(!(loopCount % 6)) if(snowCurrent+2 <=16 && snowCurrent+2 > 0) myCharlie.ledWrite(myLeds[snowCurrent+2], 1);
    if(!(loopCount % 9)) if(snowCurrent+3 <=16 && snowCurrent+3 > 0) myCharlie.ledWrite(myLeds[snowCurrent+3], 1);
    if(!(loopCount % 12)) if(snowCurrent+4 <=16 && snowCurrent+4 > 0) myCharlie.ledWrite(myLeds[snowCurrent+4], 1);

    if(!(loopCount % 3)) if(snowCurrent+1 <=16 && snowCurrent+1 > 0) myCharlie.ledWrite(myLeds[snowCurrent+17+1], 1);
    if(!(loopCount % 6)) if(snowCurrent+2 <=16 && snowCurrent+2 > 0) myCharlie.ledWrite(myLeds[snowCurrent+17+2], 1);
    if(!(loopCount % 9)) if(snowCurrent+3 <=16 && snowCurrent+3 > 0) myCharlie.ledWrite(myLeds[snowCurrent+17+3], 1);
    if(!(loopCount % 12)) if(snowCurrent+4 <=16 && snowCurrent+4 > 0) myCharlie.ledWrite(myLeds[snowCurrent+17+4], 1);
  }

  snowCurrent--;
  if(snowCurrent<=0) { // start over
    myCharlie.ledWrite(myLeds[0], 1);
    myCharlie.ledWrite(myLeds[17], 1);
    delay(500);
    clearLaurels();
    snowCurrent = 16;
  }
}

void reverseSnowfall() {
  unsigned long loopCount = 0;                          // used to determine duty cycle of each LED
  unsigned long timeNow = millis();                     //
  unsigned long displayTime = 100;          // milliseconds to spend at each focus LED in descent
  while(millis()- timeNow < (displayTime+current*2)) {  // animation slows toward end
    clearLaurels();
    loopCount++;
    // the "snowflake" gets full duty cycle.  When it gets to the end, hold it at the end until the tail collapses
    myCharlie.ledWrite(myLeds[current], 1);
    myCharlie.ledWrite(myLeds[current + 17], 1);
    // each member of tail has reduced duty cycle, and never get to the final position
    if(!(loopCount % 3)) if(current-1 >=0 && current-1 < 16) myCharlie.ledWrite(myLeds[current-1], 1);
    if(!(loopCount % 6)) if(current-2 >=0 && current-2 < 16) myCharlie.ledWrite(myLeds[current-2], 1);
    if(!(loopCount % 9)) if(current-3 >=0 && current-3 < 16) myCharlie.ledWrite(myLeds[current-3], 1);
    if(!(loopCount % 12)) if(current-4 >=0 && current-4 < 16) myCharlie.ledWrite(myLeds[current-4], 1);

    if(!(loopCount % 3)) if(current-1 >=0 && current-1 < 16) myCharlie.ledWrite(myLeds[current+17-1], 1);
    if(!(loopCount % 6)) if(current-2 >=0 && current-2 < 16) myCharlie.ledWrite(myLeds[current+17-2], 1);
    if(!(loopCount % 9)) if(current-3 >=0 && current-3 < 16) myCharlie.ledWrite(myLeds[current+17-3], 1);
    if(!(loopCount % 12)) if(current-4 >=0 && current-4 < 16) myCharlie.ledWrite(myLeds[current+17-4], 1);
  }

  current++;
  if(current>=16) { // start over
    myCharlie.ledWrite(myLeds[16], 1);
    myCharlie.ledWrite(myLeds[33], 1);
    delay(125);
    clearLaurels();
    current = 0;
  }
}

int numOfLEDsToShow = 0;
unsigned long myTime;

void defaultAnimation() {
  int frameTime = 50;
  if (numOfLEDsToShow < 17) { // less than the number of leds per laurel
    numOfLEDsToShow = numOfLEDsToShow + 1;
  } else {
    numOfLEDsToShow = 0;
  }

  myTime = millis();
  unsigned long burnTime = myTime + frameTime;
  while(myTime < burnTime) {
    myTime = millis();
    for (int i = 0; i < numOfLEDsToShow; i++) {
      myCharlie.ledWrite(myLeds[i], 1);
      myCharlie.ledWrite(myLeds[i+17], 1);
    }
  }
  clearLaurels();
}

void clearLaurels() {
  for (int i = 0; i < (sizeof(myLeds) / sizeof(myLeds[0])); i++) {
    myCharlie.ledWrite(myLeds[i], 0);
  }
}
