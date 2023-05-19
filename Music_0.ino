// Copyright 2023 Tokai University Project Basics2 Group 1

#include "MusicCore.h"

extern uint16_t MusicNotes[512];

void SetMusic_Zero(void)
{
////////////////////////////////////////////////////////
// 曲設定

    const int BeatInterval = 300; //ms

////////////////////////////////////////////////////////
// 曲名 : 起動音

    MusicNotes[0] = MakeNote(ENoteScale::Type::G, 2, 300);
    MusicNotes[1] = MakeNote(ENoteScale::Type::F, 2, 300);
    MusicNotes[2] = MakeNote(ENoteScale::Type::G, 2, 300);

    MusicNotes[3] = MakeBlank(300);

    MusicNotes[4] = MakeNote(ENoteScale::Type::G, 2, 300);
    MusicNotes[5] = MakeNote(ENoteScale::Type::F, 2, 300);
    MusicNotes[6] = MakeNote(ENoteScale::Type::G, 2, 300);

    MusicNotes[7] = MakeBlank(300);

    MusicNotes[8] = MakeEnd();

// 曲名 : 起動音
////////////////////////////////////////////////////////
}
