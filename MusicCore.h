// Copyrights 2023 Eigi Chin

#pragma once

////////////////////////////
// マクロ定義

/**
* uint16_t (00 000 0000 000 0000)
*
*   ・1～4bit (0～15)
*     音階
* 
*   ・5～7bit (0～7)
*     音域
* 
*   ・8～11bit (0～15)
*     次の音が鳴るまでの、この音の再生時間(0.1s)
*   
*   ・12～14bit (0～8)
*     音の再生時間中の何分の何、実際に鳴らすか
* 
*   ・15～16bit (0～3)
*     リズム判定用
*/
#define BITMASK_MUSIC_SCALE     0b0000000000001111
#define BITMASK_MUSIC_RANGE     0b0000000001110000
#define BITMASK_MUSIC_DURATION  0b0000011110000000
#define BITMASK_MUSIC_DIVISION  0b0011100000000000
#define BITMASK_MUSIC_RHYTHM    0b1100000000000000

#define PIN_SPEAKER 7

#define MUSIC_ENDPOINT_VALUE 0b1111111111111111


////////////////////////////
// 列挙型

/**
* ENoteScale::Type
*
*  音階名を定義する
*/
namespace ENoteScale
{
    enum Type
    {
        None,
        C,  // ド
        Cs, // ド＃
        D,  // レ
        Ds, // レ＃
        E,  // ミ
        F,  // ファ
        Fs, // ファ＃
        G,  // ソ
        Gs, // ソ＃
        A,  // ラ
        As, // ラ＃
        B   // シ
    };
}

/**
* ERhythm::Type
*
*  音階名を定義する
*/
namespace ERhythm
{
    enum Type
    {
        None,
        Hold,       // 長押し
        Tap         // 単押し
    };
}


////////////////////////////
// 関数

/**
* void PlayMusic(int8_t ID, void (*Func)() = nullptr);
*
*  IDに基づいて曲を再生。任意で関数を紐づけることができる。
*  注意: 紐づけた関数内でこの関数を実行してはいけない。
*
* @Param ID             曲のID
* @Param Loop           ループ再生するか
* @Param PlayingFunc    曲の再生中に呼び出される関数
* @Param EndFunc        曲の終了後に呼び出される関数
*/
void PlayMusic(int8_t ID, bool Loop = false, void (*PlayingFunc)(uint16_t) = nullptr, void (*EndFunc)() = nullptr);

/**
* void StopMusic(void);
*
*  現在再生中の曲を止める
*/
void StopMusic(void);

/**
* void PlayNote(uint16_t Note);
*
*  曲の現在の演奏位置における音の再生を行う
*
* @Param: Note 音符
*/
void PlayNote(uint16_t Note);

/**
* bool HasMusicEnd(uint16_t Note);
*
*  音符から曲が終了したかどうかを判断する
* 
* @Param: Note 音符
* @Return: 曲が終了したかどうか
*/
bool HasMusicEnd(uint16_t Note);

////////////////////////////

/**
* static uint16_t SetField(uint16_t Data, uint16_t NewValue, uint16_t BitMask);
*
*  16bit データに値を書き込む
*
* @Param Data       書き込む先のデータ
* @Param NewValue   新しい値
* @Param BitMask    書き込む位置のマスク
*/
static uint16_t SetField(uint16_t Data, uint16_t NewValue, uint16_t BitMask);

/**
* static uint16_t GetField(uint16_t Data, uint16_t Shift, uint16_t BitMask);
*
*  16bit データに値を読み取る
*
* @Param Data       読み取る先のデータ
* @Param Shift      何個値を右にシフトするか
* @Param BitMask    書き込む位置のマスク
*/
static uint16_t GetField(uint16_t Data, uint16_t Shift, uint16_t BitMask);


/**
* uint16_t MakeNote(ENoteScale::Type Note, uint8_t Scale, uint8_t Duration, uint8_t Division, ERhythm::Type Rhythm);
*
*  音符の作成
*
* @Param Scale      音程
* @Param Range      音階 (1～7)
* @Param Duration   時間 (1～15)
* @Param Division   Durationの間、実際に何分の何、音を出すか (1～8)
* @Param Rhythm     リズム判定
*/
uint16_t MakeNote(
    ENoteScale::Type Scale,
     uint16_t Range,
      int Duration,
       ERhythm::Type Rhythm = ERhythm::Type::Tap,
        uint16_t Division = 1);

/**
* uint16_t MakeBlank(uint8_t Duration);
*
*  無音部分を作成
*
* @Param Duration 無音の時間
*/
uint16_t MakeBlank(int Duration);

/**
* uint16_t MakeEnd();
*
*  終了位置を作成
*/
uint16_t MakeEnd();

/**
* ENoteScale::Type GetNoteScale(uint16_t Note);
*
*  音階を取得する
*
* @Param Note 音符
*/
ENoteScale::Type GetNoteScale(uint16_t Note);

/**
* uint16_t GetNoteRange(uint16_t Note);
*
*  音域を取得する
*
* @Param Note 音符
*/
uint16_t GetNoteRange(uint16_t Note);

/**
* int GetNoteDuration(uint16_t Note);
*
*  音が流れる時間を取得する
*
* @Param Note 音符
*/
int GetNoteDuration(uint16_t Note);

/**
* int GetNotePlayTime(uint16_t Note);
*
*  音が実際になる時間を取得する
*
* @Param Note 音符
*/
int GetNotePlayTime(uint16_t Note);

/**
* ERhythm::Type GetNoteRhythm(uint16_t Note);
*
*  リズム判定タイプを取得する
*
* @Param Note 音符
*/
ERhythm::Type GetNoteRhythm(uint16_t Note);

/**
* int ScaleHz(ENoteScale::Type Scale, uint8_t Range);
*
*  音が実際になる時間を取得する
*
* @Param Scale  音階
* @Param Range  音域
*/
float ScaleHz(ENoteScale::Type Scale, uint8_t Range);

////////////////////////////

/**
* bool GetMusic(int8_t ID);
*
*  IDに基づいて曲を設定
*
* @Return: 設定できたかどうか
*/
bool SetMusic(int8_t ID);

void SetMusic_Zero(void);
void SetMusic_One(void);
void SetMusic_Two(void);
void SetMusic_Three(void);
void SetMusic_Four(void);
void SetMusic_Five(void);