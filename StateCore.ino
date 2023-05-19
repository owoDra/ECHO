// Copyrights 2023 Eigi Chin

#include "StateCore.h"

////////////////////////////
// グローバル変数

/**
* 現在のステート
*/
static volatile EGameState::Type CurrentGameState = EGameState::Type::None;

/**
* 現在選択中の曲ID
*/
uint8_t SelectedMusicID = 0;

/**
* 現在スコア
*/
volatile uint16_t GameSocre = 0;


////////////////////////////
// 関数

void SetState(EGameState::Type NewState)
{
    if(NewState != CurrentGameState)
    {
        OnStateEnd(CurrentGameState);

        CurrentGameState = NewState;

        OnStateBegin(CurrentGameState);
    }
}

void OnStateBegin(EGameState::Type InState)
{
    switch (InState)
    {
    ////////////////////////////
    // タイトル
    case EGameState::Type::Title:
        OnStateBegin_Title();
        break;

    ////////////////////////////
    // 曲選択
    case EGameState::Type::MusicSelect:
        OnStateBegin_MusicSelect();
        break;

    ////////////////////////////
    // 開始中
    case EGameState::Type::Begining:
        OnStateBegin_Begining();
        break;

    ////////////////////////////
    // 進行中
    case EGameState::Type::Playing:
        OnStateBegin_Playing();
        break;

    ////////////////////////////
    // リザルト
    case EGameState::Type::Result:
        OnStateBegin_Result();
        break;
    }
}

void OnStateEnd(EGameState::Type InState)
{
    switch (InState)
    {
    ////////////////////////////
    // タイトル
    case EGameState::Type::Title:
        OnStateEnd_Title();
        break;

    ////////////////////////////
    // 曲選択
    case EGameState::Type::MusicSelect:
        OnStateEnd_MusicSelect();
        break;

    ////////////////////////////
    // 開始中
    case EGameState::Type::Begining:
        OnStateEnd_Begining();
        break;

    ////////////////////////////
    // 進行中
    case EGameState::Type::Playing:
        OnStateEnd_Playing();
        break;

    ////////////////////////////
    // リザルト
    case EGameState::Type::Result:
        OnStateEnd_Result();
        break;
    }
}

void UpdateState(void)
{
    switch (CurrentGameState)
    {
    ////////////////////////////
    // タイトル
    case EGameState::Type::Title:
        UpdateState_Title();
        break;

    ////////////////////////////
    // 曲選択
    case EGameState::Type::MusicSelect:
        UpdateState_MusicSelect();
        break;

    ////////////////////////////
    // 開始中
    case EGameState::Type::Begining:
        UpdateState_Begining();
        break;

    ////////////////////////////
    // 進行中
    case EGameState::Type::Playing:
        UpdateState_Playing();
        break;

    ////////////////////////////
    // リザルト
    case EGameState::Type::Result:
        UpdateState_Result();
        break;
    }
}
