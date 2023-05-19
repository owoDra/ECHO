// Copyrights 2023 Eigi Chin

#include "MusicCore.h"

#include "Debug.h"

////////////////////////////
// 定数

static const float Freq_Notes[]
{
    0,  // None
    130.813, // ド
    138.591, // ド＃
    146.832, // レ
    155.563, // レ＃
    164.814, // ミ
    174.614, // ファ
    184.997, // ファ＃
    195.998, // ソ
    207.652, // ソ＃
    220.000, // ラ
    233.082, // ラ＃
    246.942  // シ
};


////////////////////////////
// グローバル変数

// 現在の曲
uint16_t MusicNotes[512];

// 曲の現在の再生位置
static volatile int PlayingPosition = -1;

// 曲の音ごとの再生してから次の音までの経過時間
static volatile int TimeToWaitNote = 0;

// 曲をループ再生するかどうか
static bool Looping = false;

// 音が再生されるたびに呼び出される関数
static void (*MusicPlayingFunc)(uint16_t) = nullptr;

// 曲が終わったときに呼び出される関数
static void (*MusicEndFunc)() = nullptr;


////////////////////////////
// 関数

void PlayMusic(int8_t ID, bool Loop, void (*PlayingFunc)(uint16_t), void (*EndFunc)())
{
    StopMusic();

    if(!SetMusic(ID))
    {
        return;
    }

    MusicPlayingFunc = PlayingFunc;
    MusicEndFunc = EndFunc;
    
    TimeToWaitNote = 0;
    PlayingPosition = -1;
    Looping = Loop;

    ////////////////////////////
    // タイマー設定
    TCCR4A = 0;
    TCCR4B = 0;
    TCCR4C = 0;
    TCCR4D = 0;
    TCCR4E = 0;
    TCNT4  = 0;

    OCR4C  = (F_CPU / 64 / 1000) - 1;

    bitWrite(TIMSK4, TOIE4, 1);
    bitWrite(TIFR4, TOV4, 1);

    bitWrite(TCCR4B, CS42, 1);
    bitWrite(TCCR4B, CS41, 1);
    bitWrite(TCCR4B, CS40, 1);
}

void StopMusic(void)
{
    noTone(PIN_SPEAKER);
    TCCR4B = 0;
}

void PlayNote(uint16_t Note)
{
    const int Scale = GetNoteScale(Note);
    const int Range = GetNoteRange(Note);
    const int PlayTime = GetNotePlayTime(Note);
    const int Duration = GetNoteDuration(Note);

    const float Freq = ScaleHz(Scale, Range);

#if ENABLE_DEBUG_LOG
    Serial.print("Position:");
    Serial.println(PlayingPosition);
    Serial.print("Scale:");
    Serial.println(Scale);
    Serial.print("Range:");
    Serial.println(Range);
    Serial.print("OriginalFreq:");
    Serial.println(Freq_Notes[Scale]);
    Serial.print("Freq:");
    Serial.println(Freq);
    Serial.print("Duration:");
    Serial.println(Duration);
    Serial.print("PlayTime:");
    Serial.println(PlayTime);

    const int Rhythm = GetNoteRhythm(Note);
    Serial.print("Rhythm:");
    Serial.println(Rhythm);

    Serial.println("");
#endif

    TimeToWaitNote = Duration;
    tone(PIN_SPEAKER, Freq, PlayTime);

    if(MusicPlayingFunc != nullptr)
    {
        interrupts();
        (*MusicPlayingFunc)(Note);
    }
}

bool HasMusicEnd(uint16_t Note)
{
    return (Note == MUSIC_ENDPOINT_VALUE);
}

ISR(TIMER4_OVF_vect) 
{
	if (TimeToWaitNote == 0) 
    {
        PlayingPosition++;

        uint16_t Note = MusicNotes[PlayingPosition];

        if(HasMusicEnd(Note))
        {
            #if ENABLE_DEBUG_LOG
            Serial.println("End");
            #endif

            if(MusicEndFunc != nullptr)
            {   
                interrupts();
                (*MusicEndFunc)();
            }

            if(Looping)
            {
                PlayingPosition = 0;
                Note = MusicNotes[PlayingPosition];
                PlayNote(Note);
            }
            else
            {
                StopMusic();
            }
        }
        else
        {
            PlayNote(Note);
        }
	} 
    else 
    {
		TimeToWaitNote--;
	}
}

////////////////////////////

static uint16_t SetField(uint16_t Data, uint16_t NewValue, uint16_t BitMask)
{
    return (Data & ~BitMask) | (NewValue & BitMask);
}

static uint16_t GetField(uint16_t Data, uint16_t Shift, uint16_t BitMask)
{
    return (Data & BitMask) >> Shift;
}

uint16_t MakeNote(ENoteScale::Type Scale, uint16_t Range, int Duration, ERhythm::Type Rhythm, uint16_t Division)
{
    uint16_t Encoded = 0;

    Encoded = SetField(Encoded, (uint16_t)Scale                         , BITMASK_MUSIC_SCALE);
    Encoded = SetField(Encoded, max(min(Range, 7), 1)           << 4    , BITMASK_MUSIC_RANGE);
    Encoded = SetField(Encoded, max(min(Duration/100, 15), 1)   << 7    , BITMASK_MUSIC_DURATION);
    Encoded = SetField(Encoded, max(min(Division-1, 7), 0)      << 11   , BITMASK_MUSIC_DIVISION);
    Encoded = SetField(Encoded, (uint16_t)Rhythm                << 14   , BITMASK_MUSIC_RHYTHM);
    
    return Encoded;
}

uint16_t MakeBlank(int Duration)
{
    return MakeNote(ENoteScale::Type::None, 1, Duration, ERhythm::Type::None, 1);
}

uint16_t MakeEnd()
{
    return MUSIC_ENDPOINT_VALUE;
}

ENoteScale::Type GetNoteScale(uint16_t Note)
{
    uint16_t Value = GetField(Note, 0, BITMASK_MUSIC_SCALE);
    return (ENoteScale::Type)Value;
}

uint16_t GetNoteRange(uint16_t Note)
{
    return GetField(Note, 4, BITMASK_MUSIC_RANGE);
}

int GetNoteDuration(uint16_t Note)
{
    // 値は1～15なので100倍して単位を合わせる。
    uint16_t Value = GetField(Note, 7, BITMASK_MUSIC_DURATION) * 100;
    return Value;
}

int GetNotePlayTime(uint16_t Note)
{
    uint16_t Division = GetField(Note, 11, BITMASK_MUSIC_DIVISION);
    return GetNoteDuration(Note) / (Division+1);
}

ERhythm::Type GetNoteRhythm(uint16_t Note)
{
    uint16_t Value = GetField(Note, 14, BITMASK_MUSIC_RHYTHM);
    return (ERhythm::Type)Value;
}

float ScaleHz(ENoteScale::Type Scale, uint8_t Range)
{
    float temp = Freq_Notes[Scale];
    for(int i = 1; i <= Range; i++)
    {
        temp *= 2;
    }
    return temp;
}

////////////////////////////

bool SetMusic(int8_t ID)
{
    switch (ID)
    {
    ////////////////////////////
    // 0曲目: 起動音
    case 0://///////////////////
        
        SetMusic_Zero();
        break;

    ////////////////////////////
    // 1曲目: 
    case 1://///////////////////
        
        SetMusic_One();
        break;

    ////////////////////////////
    // 2曲目: 
    case 2://///////////////////
        
        SetMusic_Two();
        break;

    ////////////////////////////
    // 3曲目: 
    case 3://///////////////////
        
        SetMusic_Three();
        break;

    ////////////////////////////
    // 4曲目: 
    case 4://///////////////////
        
        SetMusic_Four();
        break;

    ////////////////////////////
    // 5曲目: 
    case 5://///////////////////
        
        SetMusic_Five();
        break;
    
    ////////////////////////////
    // 例外: 曲無し
    default:////////////////////

        // なし

        return false;
    }
    return true;
}