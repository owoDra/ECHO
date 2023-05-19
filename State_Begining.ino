// Copyrights 2023 Eigi Chin

#include "StateCore.h"
#include "DisplayCore.h"
#include "MusicCore.h"

////////////////////////////
// 関数

void OnStateBegin_Begining(void)
{
    DisplayTemplates(
        EDisplayTemplate::Type::Four,
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::Blank
    );

    tone(PIN_SPEAKER, ScaleHz(ENoteScale::Type::C, 4), 200);

    delay(1000);

    DisplayTemplates(
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::Three,
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::Blank
    );

    tone(PIN_SPEAKER, ScaleHz(ENoteScale::Type::C, 5), 200);

    delay(1000);

    DisplayTemplates(
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::Two,
        EDisplayTemplate::Type::Blank
    );

    tone(PIN_SPEAKER, ScaleHz(ENoteScale::Type::C, 6), 200);

    delay(1000);

    DisplayTemplates(
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::Blank,
        EDisplayTemplate::Type::One
    );

    tone(PIN_SPEAKER, ScaleHz(ENoteScale::Type::C, 7), 200);

    delay(1000);

    SetState(EGameState::Type::Playing);
}

void OnStateEnd_Begining(void)
{
    // End
}

void UpdateState_Begining(void)
{
    // Loop
}