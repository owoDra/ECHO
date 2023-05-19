// Copyrights 2023 Eigi Chin

#pragma once

////////////////////////////
// マクロ定義

#define DISPLAY_MAX_NUM 9999   // 表示する値の最大
#define DISP_I2C_ADRS	0x70

////////////////////////////
// 列挙型

/**
* 実際に使用するDisplayの番号。
* 最後はDISPLAYMAXとする。Forなどで使用する。
*/
namespace EDisplayID
{
  enum Type
  {
    DISP0,
    DISP1, 
    DISP2, 
    DISP3, 
    DISPLAYMAX
  };
}

/**
* ディスプレイに表示する物のテンプレート
*/
namespace EDisplayTemplate
{
  enum Type
  {
    Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
    Blank
  };
}


////////////////////////////
// 関数

/**
* void	InitializeDisplay(void);
*
*  7セグの初期化を行う
*/
void InitializeDisplay(void);

/**
* void	InitializeDisplay(void);
*
*  7セグを非表示
*/
void DisplayClear(void);

/**
* void	DisplayCommand(int Cmd);
*
*  指定したコマンドを実行する
*
* @Param cmd 表示する数値
*/
void DisplayCommand(int Cmd);

/**
* static void DisplayData(int Disp, int Data);
*
*  指定した数値を7セグに表示する
*
* @Param Disp 表示するディスプレイ番号
* @Param Data 表示するデータ
*/
static void DisplayData(int Disp, int Data);

/**
* void DisplayTemplates(EDisplayTemplate::Type Data1, EDisplayTemplate::Type Data2,
*                       EDisplayTemplate::Type Data3, EDisplayTemplate::Type Data4,);
*
*  7セグにテンプレートを表示する
*
* @Param Data1 ディスプレイ1に表示するデータ
* @Param Data2 ディスプレイ1に表示するデータ
* @Param Data3 ディスプレイ1に表示するデータ
* @Param Data4 ディスプレイ1に表示するデータ
*/
void DisplayTemplates(EDisplayTemplate::Type Data1,
                       EDisplayTemplate::Type Data2,
                        EDisplayTemplate::Type Data3,
                         EDisplayTemplate::Type Data4);

/**
* void DisplayNumber(int Num);
*
*  指定した数値を7セグに表示する
*
* @Param Num 表示する数値
*/
void DisplayNumber(int Num);

/**
* bool IsValidDisplay(int Disp);
*
*  Displayが有効かどうか
*
* @Param  Disp 検証するDisplayの番号
* @Return 有効ならtrue, 無効ならfalse
*/
bool IsValidDisplay(int Disp);
