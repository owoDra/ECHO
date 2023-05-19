// Copyrights 2023 Eigi Chin

#pragma once

////////////////////////////
// マクロ定義

/**
* スイッチのタップアクションと判定されるために押してから放すまでにかかる最長時間
* (単位はms)
*/
#define SW_TAP_THRESHOLD 500


////////////////////////////
// 列挙型

/**
* 実際に使用するスイッチの番号。
* 最後はSWMAXとする。Forなどで使用する。
*/
namespace ESwitchID
{
  enum Type
  {
    SW0,
    SW1,
    DipSW,
    SWMAX
  };
}

/**
* スイッチの状態
*/
namespace ESwitchState
{
  enum Type
  {
    Released,
    Pressed
  };
}

/**
* スイッチのアクション
*/
namespace ESwitchAction
{
  enum Type
  {
    None,
    Wait,
    Tap,
    Hold
  };
}


////////////////////////////
// 構造体

/**
* スイッチの情報
*/
typedef struct
{
  int                 ElapseTime;
  ESwitchState::Type  State;
  ESwitchAction::Type Action;
} SSwitchState;


////////////////////////////
// 関数

/**
* void InitializeSwitch();
*
*  スイッチの初期化を行う
*/
void InitializeSwitch(void);

/**
* void UpdateSwitch(int DeltaTime);
*
*  スイッチの更新を行う
*
* @Param DeltaTime 更新の間に経過した時間
*/
void UpdateSwitch(int DeltaTime);

/**
* bool IsValidSwitch(int Switch);
*
*  Switchが有効かどうか
*
* @Param  Switch 検証するSwitchの番号
* @Return 有効ならtrue, 無効ならfalse
*/
bool IsValidSwitch(int Switch);

/**
* ESwitchState::Type ReadSwitchState(int Switch);
*
*  Switchの現在の状態を読み取る
*
* @Param  Switch 読み取るSwitchの番号
* @Return Switchの現在の状態
*/
ESwitchState::Type ReadSwitchState(int Switch);

/**
* ESwitchAction::Type GetSwitchAction(int Switch);
*
*  Switchの現在のアクションを読み取る
*
* @Param  Switch 読み取るSwitchの番号
* @Return Switchの現在のアクション
*/
ESwitchAction::Type GetSwitchAction(int Switch);

