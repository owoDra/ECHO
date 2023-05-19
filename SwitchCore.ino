// Copyrights 2023 Eigi Chin

#include "SwitchCore.h"

////////////////////////////
// 定数

/**
* 実際に使用するスイッチのピン番号。
*/
static const uint8_t Pin_Switches[] = {
  A0,  // SW0
  A1,  // SW1
  13   // DipSwitch
};


////////////////////////////
// グローバル変数

/**
* スイッチごとに押し続けた時間
*/
static SSwitchState SwitchStates[ESwitchID::Type::SWMAX];


////////////////////////////
// 関数

void InitializeSwitch(void)
{
  for (int SW = ESwitchID::Type::SW0; SW < ESwitchID::Type::SWMAX; SW++) 
  {
		pinMode(Pin_Switches[SW], INPUT);

    SSwitchState NewState = {
      -1,
      ESwitchState::Type::Released,
      ESwitchAction::Type::None      
    };

    SwitchStates[SW] = NewState;
	}
}

void UpdateSwitch(int DeltaTime)
{
  for (int SW = ESwitchID::Type::SW0; SW < ESwitchID::Type::SWMAX; SW++) 
  {
    ESwitchState::Type CurrentState = SwitchStates[SW].State;
    ESwitchState::Type NewState = ReadSwitchState(SW);
    bool StateHasChanged = false;

    // ステートが変化した場合
    if(CurrentState != NewState)
    {
      SwitchStates[SW].State = NewState;
      CurrentState = NewState;
      StateHasChanged = true;   // ステート変更フラグをtrueに
    }    

    // 押されている状態
    if(CurrentState == ESwitchState::Type::Pressed)
    {
      // ステートが直前に変更していた場合のみ実行
      if(StateHasChanged)
      {
        SwitchStates[SW].ElapseTime = 0;
        SwitchStates[SW].Action = ESwitchAction::Type::Wait;        
      }
      
      // ステートが直前に変更されてない場合のみ実行    
      // ※ステート変更直後の更新で経過時間を増やさない。
      else
      {
        SwitchStates[SW].ElapseTime += DeltaTime;   // 経過時間を増やす
      }

      if( SwitchStates[SW].ElapseTime > SW_TAP_THRESHOLD)
      {
        SwitchStates[SW].Action = ESwitchAction::Type::Hold;
      }
    }

    // 押されていない状態
    else
    {
      // アクションがNoneなら何もしない
      if(SwitchStates[SW].Action == ESwitchAction::Type::None)
      {
        continue;
      }

      // 経過時間が閾値以下ならTapアクションと判定
      else if((SwitchStates[SW].ElapseTime <= SW_TAP_THRESHOLD) &&
              (SwitchStates[SW].Action != ESwitchAction::Type::Tap))
      {
        SwitchStates[SW].Action = ESwitchAction::Type::Tap;
      }

      //その他はアクションはNoneに設定
      else 
      {
        SwitchStates[SW].Action = ESwitchAction::Type::None;
      }
    }
  }
}

bool IsValidSwitch(int Switch)
{
  return (Switch >= ESwitchID::Type::SW0) && (Switch < ESwitchID::Type::SWMAX);
}

ESwitchState::Type ReadSwitchState(int Switch)
{
  if(IsValidSwitch(Switch))
  {
    const bool isPressed = (digitalRead(Pin_Switches[Switch]) == HIGH);
    return  isPressed ? ESwitchState::Type::Pressed : ESwitchState::Type::Released;
  }
  return ESwitchState::Type::Released;
}

ESwitchAction::Type GetSwitchAction(int Switch)
{
  if(IsValidSwitch(Switch))
  {
    return SwitchStates[Switch].Action;
  }
  return ESwitchAction::Type::None;
}