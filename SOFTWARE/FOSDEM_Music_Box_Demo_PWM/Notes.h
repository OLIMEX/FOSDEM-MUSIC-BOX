#ifndef	_NOTES_H
#define	_NOTES_H
#include <avr/pgmspace.h>

// Here is an order of the notes in the array NoteFrequency (in Notes.c file).
// Alternation signs (flat and sharp) are done both for some notes and have the same index (for example cS = dB)
enum NoteOrder
{
	_P  =  0,	// pause
	_c0 =  1, _cS0 =  2, _dB0 =  2, _d0 =  3, _dS0 =  4, _eB0 =  4, _e0 =  5, _f0 =  6, _fS0 =  7, _gB0 =  7, _g0 =  8, _gS0=  9, _aB0=  9, _a0 = 10, _aS0 = 11, _bB0 = 11, _b0 = 12,
	_c1 = 13, _cS1 = 14, _dB1 = 14, _d1 = 15, _dS1 = 16, _eB1 = 16, _e1 = 17, _f1 = 18, _fS1 = 19, _gB1 = 19, _g1 = 20, _gS1= 21, _aB1= 21, _a1 = 22, _aS1 = 23, _bB1 = 23, _b1 = 24,
	_c2 = 25, _cS2 = 26, _dB2 = 26, _d2 = 27, _dS2 = 28, _eB2 = 28, _e2 = 29, _f2 = 30, _fS2 = 31, _gB2 = 31, _g2 = 32, _gS2= 33, _aB2= 33, _a2 = 34, _aS2 = 35, _bB2 = 35, _b2 = 36,
	_c3 = 37, _cS3 = 38, _dB3 = 38, _d3 = 39, _dS3 = 40, _eB3 = 40, _e3 = 41, _f3 = 42, _fS3 = 43, _gB3 = 43, _g3 = 44, _gS3= 45, _aB3= 45, _a3 = 46, _aS3 = 47, _bB3 = 47, _b3 = 48,
	_c4 = 49, _cS4 = 50, _dB4 = 50, _d4 = 51, _dS4 = 52, _eB4 = 52, _e4 = 53, _f4 = 54, _fS4 = 55, _gB4 = 55, _g4 = 56, _gS4= 57, _aB4= 57, _a4 = 58, _aS4 = 59, _bB4 = 59, _b4 = 60,
	_c5 = 61, _cS5 = 62, _dB5 = 62, _d5 = 63, _dS5 = 64, _eB5 = 64, _e5 = 65, _f5 = 66, _fS5 = 67, _gB5 = 67, _g5 = 68, _gS5= 69, _aB5= 69, _a5 = 70, _aS5 = 71, _bB5 = 71, _b5 = 72,
	_c6 = 73, _cS6 = 74, _dB6 = 74, _d6 = 75, _dS6 = 76, _eB6 = 76, _e6 = 77, _f6 = 78, _fS6 = 79, _gB6 = 79, _g6 = 80, _gS6= 81, _aB6= 81, _a6 = 82, _aS6 = 83, _bB6 = 83, _b6 = 84,
	_c7 = 85, _cS7 = 86, _dB7 = 86, _d7 = 87, _dS7 = 88, _eB7 = 88, _e7 = 89, _f7 = 90, _fS7 = 91, _gB7 = 91, _g7 = 92, _gS7= 93, _aB7= 93, _a7 = 94, _aS7 = 95, _bB7 = 95, _b7 = 96,
	_c8 = 97, _cS8 = 98, _dB8 = 98, _d8 = 99, _dS8 =100, _eB8 =100, _e8 =101, _f8 =102, _fS8 =103, _gB8 =103, _g8 =104, _gS8=105, _aB8=105, _a8 =106, _aS8 =107, _bB8 =107, _b8 =108,
};

extern const int NoteFrequency [] PROGMEM;

// note durations multiplied by the time for one quarter 60/tempo seconds; (60000/tempo milliseconds)
#define	_8T		 166	// eighth note triplet (must be used in set of 3 to equal an eight note)
#define	_16		 250	// sixteenth note
#define	_4T		 333	// quarter note triplet (must be used in set of 3 to equal a quarter note)
#define	_16D	 375	// sixteenth note dotted
#define	_8		 500	// eighth note
#define	_8D		 750	// eighth note dotted
#define	_4		1000	// quarter note
#define	_4D		1500	// quarter note dotted
#define	_2		2000	// half note
#define	_2D		3000	// half note dotted
#define	_1		4000	// whole note
#define	_1D		6000	// whole note dotted

#define	_END	-1

#endif
