#ifndef	_MARIO_BROS_H
#define	_MARIO_BROS_H

#include "../Notes.h"

int MB1_Tempo = 200;
const int MB1_NoteC0[] PROGMEM =   {_e7, _e7, _P, _e7, _P, _c7, _e7, _P, _g7, _P, _P, _P, _g6, _P, _P, _P, _END};
const int MB1_NoteC1[] PROGMEM =   {_e5, _e5, _P, _e5, _P, _c5, _e5, _P, _g5, _P, _P, _P, _g4, _P, _P, _P, _END};
const int MB1_Duration[] PROGMEM = {_8 , _8 , _8, _8 , _8, _8 , _8 , _8, _8 , _8, _8, _8, _8 , _8, _8, _8, _END};

int MB2_Tempo = 200;
const int MB2_NoteC0[] PROGMEM =   {_g6, _e7, _P , _g7, _a7, _P, _f7, _g7, _P, _e7, _P, _c7, _d7, _b6, _P, _P, _END};
const int MB2_NoteC1[] PROGMEM =   {_g4, _e5, _P , _g5, _a5, _P, _f5, _g5, _P, _e5, _P, _c5, _d5, _b4, _P, _P, _END};
const int MB2_Duration[] PROGMEM = {_8 , _8 , _8 , _8 , _8 , _8, _8 , _8 , _8, _8 , _8, _8 , _8 , _8 , _8, _8, _END};

int MB3_Tempo = 200;
const int MB3_NoteC0[] PROGMEM =   {_c7, _P, _P, _g6, _P, _P, _e6, _P, _P, _a6, _P, _b6, _P, _bB6, _a6, _P, _END};
const int MB3_NoteC1[] PROGMEM =   {_c5, _P, _P, _g4, _P, _P, _e4, _P, _P, _a4, _P, _b4, _P, _bB4, _a4, _P, _END};
const int MB3_Duration[] PROGMEM = {_8 , _8, _8, _8 , _8, _8, _8 , _8, _8, _8 , _8, _8 , _8, _8  , _8 , _8, _END};

#endif
