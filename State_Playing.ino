// Copyrights 2023 Eigi Chin

#include "MusicCore.h"
#include "SwitchCore.h"
#include "StateCore.h"
#include "DisplayCore.h"
#include "Led.h"

////////////////////////////
// グローバル変数

extern uint8_t SelectedMusicID;

extern volatile uint16_t GameSocre;

static volatile ERhythm::Type CurrentInput = ERhythm::Type::None;

////////////////////////////
// 関数

/**
* static void OnNotePlayed(uint16_t Note)
*
*  音が流れた時に実行
*
* @Param: 再生された音符
*/
static void OnNotePlayed(uint16_t Note)
{
    ERhythm::Type NoteRhythm = GetNoteRhythm(Note);

    if(NoteRhythm == CurrentInput)
    {
        switch (NoteRhythm)
        {
        ////////////////////////////
        // 単押し
        case ERhythm::Type::Tap:
            GameSocre += 10;
            LedCorrect(LED2);
            break;

        ////////////////////////////
        // 長押し
        case ERhythm::Type::Hold:
            GameSocre += 50;
            LedCorrect(LED3);
            break;
        }
    
        RefreshSocre();
    }
    else
    {
        GameSocre -= 5;
        RefreshSocre();
    }

    CurrentInput = ERhythm::Type::None;
}

/**
* static void OnMusicEnd()
*
*  曲が終了した時に実行
*/
static void OnMusicEnd()
{
    SetState(EGameState::Type::Result);
}

/**
* static void RefreshSocre()
*
*  スコア表示を更新する
*/
static void RefreshSocre()
{
    DisplayNumber(GameSocre);
}

void OnStateBegin_Playing(void)
{
    GameSocre = 0;
    RefreshSocre();

    PlayMusic(SelectedMusicID, false, OnNotePlayed, OnMusicEnd);
}

void OnStateEnd_Playing(void)
{
    StopMusic();
    for(int i=LED0; i<LED3; i++){
     LedOff(i); 
    }
}

void UpdateState_Playing(void)
{
    ESwitchAction::Type SWAction = ESwitchAction::Type::None;
    
    SWAction = GetSwitchAction(ESwitchID::Type::SW0);
    if(SWAction == ESwitchAction::Type::None)
    {
        SWAction = GetSwitchAction(ESwitchID::Type::SW1);
        if(SWAction == ESwitchAction::Type::None)
        {
            return;
        }
    }

    if(SWAction == ESwitchAction::Type::Hold)
    {
        CurrentInput = ERhythm::Type::Hold;
    }
    else
    {
        CurrentInput = ERhythm::Type::Tap;
    }
}
