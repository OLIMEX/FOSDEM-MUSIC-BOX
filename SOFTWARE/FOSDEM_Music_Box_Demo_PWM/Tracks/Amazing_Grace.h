// Amazing grace based on the notes: https://upload.wikimedia.org/wikipedia/commons/archive/b/bf/20111224005603%21AmazingGraceFamiliarStyle.PNG

#ifndef	_AMAZING_GRACE_H
#define	_AMAZING_GRACE_H

#include "../Notes.h"

int AG1_Tempo = 76;
const int AG1_Note[] PROGMEM =     {_g4, _c5, _e5, _c5, _e5, _d5, _c5, _a4, _g4, _g4, _c5, _e5, _c5, _e5, _d5, _e5, _END};
const int AG1_Duration[] PROGMEM = {_4 , _2 , _8 , _8 , _2 , _4 , _2 , _4 , _2 , _4 , _2 , _8 , _8 , _2 , _8 , _8 , _END};

int AG2_Tempo = 76;
const int AG2_Note[] PROGMEM =     {_g5, _d5, _e5, _g5, _e5, _c5, _e5, _e5, _d5, _c5, _a4, _g4, _g4, _c5, _e5, _c5, _e5, _d5, _c5, _END};
const int AG2_Duration[] PROGMEM = { _2, _8 , _8 , _2 , _8 , _8 , _2 , _8 , _8 , _2 , _4 , _2 , _4 , _2 , _8 , _8 , _2 , _4 , _2 , _END};

#endif
