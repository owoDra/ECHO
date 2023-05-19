// Copyrights 2023 Eigi Chin

#include "DisplayCore.h"

#include <Wire.h>

////////////////////////////
// 定数

/**
* 実際に使用する7セグのアドレス。
*/
static const uint8_t Adrs_Display[] = {
  0x08, 
  0x06, 
  0x02, 
  0x00, 
  0x04 
};

/**
* 7セグ用の16進数変換テンプレート
*/
static const uint8_t Templates_Display[]= {
/*  0     1     2     3     4     5     6     7     8     9   */
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 
/*  A     B     C     D     E     F     G     H     I     J     K     L    */
    0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, 0x76, 0x30, 0x1E, 0x75, 0x38,
/*  M     N     O     P     Q     R     S     T     U     V     W     X    */
    0x55, 0x54, 0x3F, 0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x1C, 0x1D, 0x64, 
/*  Y     Z     */
    0x6E, 0x5B, 
/*  a     b     c     d     e     f     g     h     i     j     k     l    */
    0x5F, 0x7C, 0x58, 0x5E, 0x79, 0x71, 0x3D, 0x74, 0x30, 0x1E, 0x75, 0x38,
/*  m     n     o     p     q     r     s     t     u     v     w     x    */
    0x55, 0x54, 0x5C, 0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x1C, 0x1D, 0x64, 
/*  y     z           */
    0x6E, 0x5B, 0x00
};


////////////////////////////
// 関数

void InitializeDisplay(void)
{
  Wire.begin(DISP_I2C_ADRS);
	DisplayCommand(0x21);		// system setup  : normal operation mode
	DisplayCommand(0xEF);		// dimming set   : 16/16 duty
 	DisplayCommand(0x81);		// display setup : display on / blinking off
	DisplayClear();
}

void DisplayClear(void)
{
  Wire.beginTransmission(DISP_I2C_ADRS);
	Wire.write(0x00);
	for (int Adrs = 0x00; Adrs < 0x0F; Adrs++) {
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

void DisplayCommand(int Cmd)
{
  Wire.beginTransmission(DISP_I2C_ADRS);
	Wire.write(Cmd);
	Wire.endTransmission();
}

static void DisplayData(int Disp, int Data)
{
  if (IsValidDisplay(Disp)) 
  {
		Wire.beginTransmission(DISP_I2C_ADRS);
	  Wire.write(Adrs_Display[Disp]);
	  Wire.write(Data);
	  Wire.endTransmission();
	}
}

void DisplayNumber(int Num)
{
  int Number = max(min(Num, DISPLAY_MAX_NUM), 0);

  // 引数の値を桁ごとに分け、7セグ用の16進数に変換
  // 数字部分は4桁まで表示
  int Digit[EDisplayID::Type::DISPLAYMAX - 1]; 
  for(int i = 0; i < sizeof(Digit)/sizeof(Digit[0]); i++)
  {
    Digit[i] = Templates_Display[Number % 10];
    Number /= 10;
  }

  // 上位桁のゼロを空白に変換
  // 最も大きい桁から10の位まで検証(1の位は必ず表示する)
  for(int i = (sizeof(Digit)/sizeof(Digit[0])) - 1; i > 0; i--)
  {
    // 0 ならば空白に変換
    if(Digit[i] == Templates_Display[0])
    {
      Digit[i] = Templates_Display[EDisplayTemplate::Type::Blank];
    }
    // 0でなければループを終了。
    else
    {
      break;
    }
  }

  for(int i = 0; i < sizeof(Digit)/sizeof(Digit[0]); i++)
  {
    DisplayData(i, Digit[i]);
  }
}

void DisplayTemplates(EDisplayTemplate::Type Data1, EDisplayTemplate::Type Data2,
                      EDisplayTemplate::Type Data3, EDisplayTemplate::Type Data4)
{
  DisplayData(EDisplayID::Type::DISP3, Templates_Display[Data1]);
  DisplayData(EDisplayID::Type::DISP2, Templates_Display[Data2]);
  DisplayData(EDisplayID::Type::DISP1, Templates_Display[Data3]);
  DisplayData(EDisplayID::Type::DISP0, Templates_Display[Data4]);
}

bool IsValidDisplay(int Disp)
{
  return (Disp >= EDisplayID::Type::DISP0) && (Disp < EDisplayID::Type::DISPLAYMAX);
}
