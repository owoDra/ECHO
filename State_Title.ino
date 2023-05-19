// Copyrights 2023 Eigi Chin

#include "StateCore.h"
#include "DisplayCore.h"
#include "SwitchCore.h"
#include "MusicCore.h"

////////////////////////////
// 関数

void OnStateBegin_Title(void)
{
    DisplayTemplates(
        EDisplayTemplate::Type::E,
        EDisplayTemplate::Type::C,
        EDisplayTemplate::Type::H,
        EDisplayTemplate::Type::O
    );

    PlayMusic(0);
}

void OnStateEnd_Title(void)
{
    StopMusic();
}

void UpdateState_Title(void)
{
    if((GetSwitchAction(ESwitchID::Type::SW0) == ESwitchAction::Type::Tap) ||
       (GetSwitchAction(ESwitchID::Type::SW1) == ESwitchAction::Type::Tap))
    {
        SetState(EGameState::Type::MusicSelect);
    }
}