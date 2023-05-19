// Copyright 2023 Eigi Chin

#include "MusicCore.h"

extern uint16_t MusicNotes[512];

void SetMusic_One(void)
{
////////////////////////////////////////////////////////
// 曲設定

    int BeatInterval = 330; //ms

////////////////////////////////////////////////////////
// 曲名 : 

    MusicNotes[0] = MakeNote(ENoteScale::Type::C, 2, BeatInterval);
    MusicNotes[1] = MakeNote(ENoteScale::Type::As, 1, 110);
    
    MusicNotes[2] = MakeBlank(220);
    
    MusicNotes[3] = MakeNote(ENoteScale::Type::Gs, 1, 330);
    MusicNotes[4] = MakeNote(ENoteScale::Type::G, 1, 110);

    MusicNotes[5] = MakeBlank(220);

    MusicNotes[6] = MakeNote(ENoteScale::Type::F, 1, 330);
    
    MusicNotes[7] = MakeBlank(110);

    MusicNotes[8] = MakeNote(ENoteScale::Type::As, 1, 330);
    MusicNotes[9] = MakeNote(ENoteScale::Type::Gs, 1, 110);
    
    MusicNotes[10] = MakeBlank(220);
   
    MusicNotes[11] = MakeNote(ENoteScale::Type::G, 1, 330);
    MusicNotes[12] = MakeNote(ENoteScale::Type::F, 1, 110);

    MusicNotes[13] = MakeBlank(220);

    MusicNotes[14] = MakeNote(ENoteScale::Type::Ds, 1, 330);
    
    MusicNotes[15] = MakeBlank(110);

    MusicNotes[16] = MakeNote(ENoteScale::Type::Gs, 1, 330);
    MusicNotes[17] = MakeNote(ENoteScale::Type::G, 1, 110);
    
    MusicNotes[18] = MakeBlank(220);
    
    MusicNotes[19] = MakeNote(ENoteScale::Type::F, 1, 330);
    MusicNotes[20] = MakeNote(ENoteScale::Type::Ds, 1, 110);

    MusicNotes[21] = MakeBlank(220);

        BeatInterval = 220;
    MusicNotes[22] = MakeNote(ENoteScale::Type::Cs, 1, BeatInterval);
    MusicNotes[23] = MakeNote(ENoteScale::Type::Ds, 1, BeatInterval);
    MusicNotes[24] = MakeNote(ENoteScale::Type::F, 1, BeatInterval);
    MusicNotes[25] = MakeNote(ENoteScale::Type::G, 1, BeatInterval);
    MusicNotes[26] = MakeNote(ENoteScale::Type::F, 1, BeatInterval);
    
    MusicNotes[27] = MakeNote(ENoteScale::Type::C, 2, BeatInterval);

    MusicNotes[28] = MakeBlank(BeatInterval);

    MusicNotes[29] = MakeNote(ENoteScale::Type::As, 1, 660);

    MusicNotes[30] = MakeBlank(1000);

    MusicNotes[31] = MakeEnd();

// 曲名 : 
////////////////////////////////////////////////////////
}
