// Copyrights 2023 Eigi Chin

#include "StateCore.h"
#include "DisplayCore.h"
#include "SwitchCore.h"
#include "MusicCore.h"

////////////////////////////
// グローバル変数

extern volatile uint16_t GameSocre;


////////////////////////////
// 関数

void OnStateBegin_Result(void)
{
    for(int i = 0; i < 3; i++)
    {
        DisplayClear();
        UpdateSwitch(200);
        delay(200);
        DisplayNumber(GameSocre);
        UpdateSwitch(200);
        delay(200);
    }
}

void OnStateEnd_Result(void)
{
    // End
}

void UpdateState_Result(void)
{
    if((GetSwitchAction(ESwitchID::Type::SW0) == ESwitchAction::Type::Tap) ||
       (GetSwitchAction(ESwitchID::Type::SW1) == ESwitchAction::Type::Tap))
    {
        SetState(EGameState::Type::MusicSelect);
    }
}