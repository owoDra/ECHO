#ifndef _LED_H_
#define _LED_H_

enum { LED0, LED1, LED2, LED3 };

void InitializeLed();
void LedOff(int led);
void LedOn(int led);
void LedCorrect(int led);

#endif
