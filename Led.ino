
#include "led.h"

static const int PIN_LED[] = { 5, 6, 10, 11 };
unsigned long startTime;
unsigned long currentTime; 

////////////////////////////////////////////////////////////
// void InitializeLed()
// [機能]  LEDの初期設定を行う
// [引数] なし
// [戻り値]  なし

void InitializeLed() {
  int led;
  for (led = LED0; led <= LED3; led++) {
    pinMode(PIN_LED[led], OUTPUT);
  }
}

////////////////////////////////////////////////////////////
// void LedOff(int led)
// [機能] 引数で指定されたLEDを消灯する
// [引数] led LEDを表す値
//      LED0,LED1,LED2,LED3のいずれか
// [戻り値]  なし

void LedOff(int led) {
  if (led < LED0 || led > LED3) {
    return;
  }
  digitalWrite(PIN_LED[led], LOW);
}

////////////////////////////////////////////////////////////
// void LedOn(int led)
// [機能] 引数で指定されたLEDを点灯する
// [引数] led LEDを表す値
//      LED0,LED1,LED2,LED3のいずれか
// [戻り値]  なし

void LedOn(int led) {
  if (led < LED0 || led > LED3) {
    return;
  }
  digitalWrite(PIN_LED[led], HIGH);
}

////////////////////////////////////////////////////////////
// void LedCorrect(int led)
// [機能] LED全て消灯し、引数で指定されたLEDを点灯する
// [引数] led LEDを表す値
//      LED0,LED1,LED2,LED3のいずれか
// [戻り値]  なし

void LedCorrect(int led){
  for(int i=LED0; i<LED3; i++){
    LedOff(i); 
  }
  LedOn(led);
}
