// Copyrights 2023 Eigi Chin

#include "MusicCore.h"
#include "SwitchCore.h"
#include "StateCore.h"
#include "DisplayCore.h"

////////////////////////////
// マクロ定義

#define ID_MUSICID_FIRST 1
#define ID_MUSICID_LAST  5


////////////////////////////
// グローバル変数

extern uint8_t SelectedMusicID;


////////////////////////////
// 関数

/**
* static void RefreshSelect();
*
*  今選択中の曲に応じてディスプレイの更新とプレビュー再生を行う
*/
static void RefreshSelect() 
{
    DisplayTemplates(
        EDisplayTemplate::Type::N,
        EDisplayTemplate::Type::o,
        EDisplayTemplate::Type::Blank,
        (EDisplayTemplate::Type)SelectedMusicID
    );

    if(ReadSwitchState(ESwitchID::Type::DipSW) == ESwitchState::Type::Pressed)
    {
        PlayMusic(SelectedMusicID, true);
    }
    else
    {
        StopMusic();
    }
}

/**
* static void Next();
*
*  次の曲を選択する
*/
static void Next() 
{
    SelectedMusicID = (SelectedMusicID >= ID_MUSICID_LAST) ? ID_MUSICID_FIRST : SelectedMusicID + 1;

    RefreshSelect();
}

void OnStateBegin_MusicSelect(void)
{
    SelectedMusicID = ID_MUSICID_FIRST;
    RefreshSelect();
}

void OnStateEnd_MusicSelect(void)
{
    StopMusic();
}

void UpdateState_MusicSelect(void)
{
    // SW0: 次の曲
    if(GetSwitchAction(ESwitchID::Type::SW1) == ESwitchAction::Type::Tap)
    {
        Next();
    }

    // SW0: 決定
    if(GetSwitchAction(ESwitchID::Type::SW0) == ESwitchAction::Type::Tap)
    {
        SetState(EGameState::Type::Begining);
    }
}