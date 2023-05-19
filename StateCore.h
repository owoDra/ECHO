// Copyrights 2023 Eigi Chin

#pragma once

////////////////////////////
// 列挙型

/**
* ゲームの進行状態
*/
namespace EGameState
{
  enum Type
  {
    None,
    Title,
    MusicSelect,
    Begining,
    Playing,
    Result,
  };
}

////////////////////////////
// 関数

/**
* void SetState(EGameState::Type NewState);
*
*  ステートを変更する
*
* @Param: NewState 新しいステート
*/
void SetState(EGameState::Type NewState);

/**
* void OnStateBegin(EGameState::Type InState);
*
*  ステートが始まったとき
*
* @Param: InState ステート
*/
void OnStateBegin(EGameState::Type InState);

void OnStateBegin_Title(void);
void OnStateBegin_MusicSelect(void);
void OnStateBegin_Begining(void);
void OnStateBegin_Playing(void);
void OnStateBegin_Result(void);

/**
* void OnStateEnd(EGameState::Type InState);
*
*  ステートが終了したとき
*
* @Param: InState ステート
*/
void OnStateEnd(EGameState::Type InState);

void OnStateEnd_Title(void);
void OnStateEnd_MusicSelect(void);
void OnStateEnd_Begining(void);
void OnStateEnd_Playing(void);
void OnStateEnd_Result(void);

/**
* void UpdateState(void);
*
*  ステート更新
*/
void UpdateState(void);

void UpdateState_Title(void);
void UpdateState_MusicSelect(void);
void UpdateState_Begining(void);
void UpdateState_Playing(void);
void UpdateState_Result(void);