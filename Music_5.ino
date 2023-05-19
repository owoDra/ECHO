// Copyright 2023 Tokai University Project Basics2 Group 1

#include "MusicCore.h"

extern uint16_t MusicNotes[512];

void SetMusic_Five(void)
{
////////////////////////////////////////////////////////
// 曲設定

    const int BeatInterval = 200; //ms

////////////////////////////////////////////////////////
// 曲名 : 

    MusicNotes[0] = MakeNote(ENoteScale::Type::C, 7, BeatInterval);
    MusicNotes[1] = MakeNote(ENoteScale::Type::E, 7, BeatInterval);
    MusicNotes[2] = MakeNote(ENoteScale::Type::G, 7, BeatInterval);
    MusicNotes[3] = MakeNote(ENoteScale::Type::B, 6, BeatInterval);

    MusicNotes[4] = MakeBlank(BeatInterval);

    MusicNotes[5] = MakeNote(ENoteScale::Type::A, 7, BeatInterval);
    MusicNotes[6] = MakeNote(ENoteScale::Type::B, 7, BeatInterval);

    MusicNotes[7] = MakeEnd();

// 曲名 : 
////////////////////////////////////////////////////////
}