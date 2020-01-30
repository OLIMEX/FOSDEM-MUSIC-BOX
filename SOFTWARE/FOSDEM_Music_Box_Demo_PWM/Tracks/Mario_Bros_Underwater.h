// Mario Bros underwater theme based on the notes: https://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0109707

#ifndef	_MARIO_BROS_UNDERWATER_H
#define	_MARIO_BROS_UNDERWATER_H
#include "../Notes.h"

int MBU1_Tempo = 132;
const int MBU1_Note[] PROGMEM =     {_e5, _c5, _g4, _a4, _fS4, _g4, _g4, _a4, _b4, _END};
const int MBU1_Duration[] PROGMEM = {_2D, _2D, _4 , _4 , _4  , _2D, _4 , _4 , _4 , _END};

int MBU2_Tempo = 132;
const int MBU2_Note[] PROGMEM =     {_e5, _c5, _g4, _a4, _fS5, _g4, _g4, _a4, _b4, _END};
const int MBU2_Duration[] PROGMEM = {_2D, _2D, _4 , _4 , _4  , _2D, _4 , _4 , _4 , _END};

int MBU3_Tempo = 132;
const int MBU3_Note[] PROGMEM =     {_c5, _d5, _e5, _g5, _f5, _e5, _d5, _f5, _d5, _END};
const int MBU3_Duration[] PROGMEM = {_4 , _4 , _4 , _4 , _4 , _4 , _2D, _2D, _2D, _END};

int MBU4_Tempo = 132;
const int MBU4_Note[] PROGMEM =     {_a4, _b4, _g4, _a4, _b4, _c5, _d5, _a5, _g5, _d5, _eB5, _e5, _END};
const int MBU4_Duration[] PROGMEM = {_4 , _4 , _4 , _4 , _4 , _4 , _2 , _4 , _4 , _4 , _4  , _2D, _END};

#endif
