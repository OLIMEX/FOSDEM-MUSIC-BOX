// Silent night holy night based on the notes: https://www.8notes.com/scores/6363.asp

#ifndef	_SILENT_NIGHT_HOLY_NIGHT_H
#define	_SILENT_NIGHT_HOLY_NIGHT_H

#include "../Notes.h"

int SNHN1_Tempo = 82;
const int SNHN1_Note[] PROGMEM =     {_f4, _g4, _f4, _d4, _f4, _g4, _f4, _d4, _c5, _c5, _a4, _bB4, _bB4, _f4, _P, _END};
const int SNHN1_Duration[] PROGMEM = {_4D, _8 , _4 , _2D, _4D, _8 , _4 , _2D, _2 , _4 , _2D, _2  , _4  , _2 , _4, _END};

int SNHN2_Tempo = 82;
const int SNHN2_Note[] PROGMEM =     {_g4, _g4, _bB4, _a4, _g4, _f4, _g4, _f4, _d4, _P, _g4, _g4, _bB4, _a4, _g4, _f4, _g4, _f4, _END};
const int SNHN2_Duration[] PROGMEM = {_2 , _4 , _4D , _8 , _4 , _4D, _8 , _4 , _2 , _4, _2 , _4 , _4D , _8 , _4 , _4D, _8 , _4 , _END};

int SNHN3_Tempo = 82;
const int SNHN3_Note[] PROGMEM =     {_d4, _c5, _c5, _eB5, _c5, _a4, _bB4, _d5, _bB4, _f4, _d4, _f4, _eB4, _c4, _bB3, _END};
const int SNHN3_Duration[] PROGMEM = {_2D, _2 , _4 , _4D , _8 , _4 , _2D , _2D, _4  , _4 , _4 , _4D, _8  , _4 , _2D , _END};

#endif
