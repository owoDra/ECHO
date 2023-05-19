// Copyright 2023 Tokai University Project Basics2 Group 1

#include "MusicCore.h"

extern uint16_t MusicNotes[512];

void SetMusic_Three(void)
{
////////////////////////////////////////////////////////
// 曲設定

    const int BeatInterval = 200; //ms

////////////////////////////////////////////////////////
// 曲名 : 

    MusicNotes[0] = MakeNote(ENoteScale::Type::B, 1, 200);
    MusicNotes[1] = MakeNote(ENoteScale::Type::Fs, 2, 400);
    MusicNotes[2] = MakeNote(ENoteScale::Type::Gs, 2, 200);
    MusicNotes[3] = MakeNote(ENoteScale::Type::Fs, 2, 400);
    MusicNotes[4] = MakeNote(ENoteScale::Type::B, 1, 200);
    MusicNotes[5] = MakeNote(ENoteScale::Type::B, 1, 200);
    
    MusicNotes[6] = MakeNote(ENoteScale::Type::Cs, 2, 400);
    MusicNotes[7] = MakeNote(ENoteScale::Type::B, 1, 400);
    MusicNotes[8] = MakeNote(ENoteScale::Type::Fs, 1, 200);
    MusicNotes[9] = MakeNote(ENoteScale::Type::B, 1, 200);
    MusicNotes[10] = MakeNote(ENoteScale::Type::B, 1, 200);
    MusicNotes[11] = MakeNote(ENoteScale::Type::B, 1, 200);
    
    MusicNotes[12] = MakeNote(ENoteScale::Type::Cs, 2, 400);
    MusicNotes[13] = MakeNote(ENoteScale::Type::B, 1, 400);
    MusicNotes[14] = MakeNote(ENoteScale::Type::Fs, 1, 200);
    MusicNotes[15] = MakeNote(ENoteScale::Type::B, 1, 200);
    MusicNotes[16] = MakeNote(ENoteScale::Type::B, 1, 200);
    MusicNotes[17] = MakeNote(ENoteScale::Type::B, 1, 200);
    
    MusicNotes[18] = MakeNote(ENoteScale::Type::Cs, 2, 400);
    MusicNotes[19] = MakeNote(ENoteScale::Type::Ds, 2, 400);
    MusicNotes[20] = MakeNote(ENoteScale::Type::B, 1, 200);
    MusicNotes[21] = MakeNote(ENoteScale::Type::Cs, 2, 200);
    MusicNotes[22] = MakeNote(ENoteScale::Type::Ds, 2, 400);

    MusicNotes[23] = MakeBlank(1000);
    
    MusicNotes[24] = MakeEnd();

// 曲名 : 
////////////////////////////////////////////////////////
}
