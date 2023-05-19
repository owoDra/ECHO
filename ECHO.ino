// Copyrights 2023 Eigi Chin

#include "MusicCore.h"
#include "SwitchCore.h"
#include "StateCore.h"
#include "DisplayCore.h"
#include "Led.h"

#include "Debug.h"

#define LOOP_INTERVAL 15

////////////////////////////

void setup() 
{
#if ENABLE_DEBUG_LOG
  Serial.begin(9600);
#endif

  InitializeSwitch();
  InitializeDisplay();
  SetState(EGameState::Type::Title);
}

void loop() 
{  
  UpdateSwitch(LOOP_INTERVAL);
  UpdateState();

  delay(LOOP_INTERVAL);
}
