#include "intervalTimer.h"

intervalTimer timerRed; bool redStatus=0;

#define beepOut 27
#define greenOut 32
#define yellowOut 25
#define redOut 26

void redOff() { timerRed.disable(); redStatus=0; digitalWrite(redOut,0); }
void redToggle() { redStatus=!redStatus; digitalWrite(redOut,redStatus); }
void fastOn() { redOff(); timerRed.set(250,true,0,itInfinite,redToggle); }
void slowOn() { redOff(); timerRed.set(1000,true,0,itInfinite,redToggle); }
void yellowOff() { digitalWrite(yellowOut,0); }
void yellowOn() { digitalWrite(yellowOut,1); }
void greenOff() { digitalWrite(greenOut,0); }
void greenOn() { digitalWrite(greenOut,1); }

void initLED() {
  pinMode(beepOut,OUTPUT);
  pinMode(greenOut,OUTPUT);
  pinMode(yellowOut,OUTPUT);
  pinMode(redOut,OUTPUT);
  greenOn(); yellowOn(); }

void ledWorker() { timerRed.check(); }
