//
// Created by bornf on 24.01.2019.
//
#ifndef UNTITLED_COMMON_H
#define UNTITLED_COMMON_H

#include "Adafruit_NeoTrellis.h"
#include <map>
#include "Quiz.h"

class Feld;

// Farbstärke abhängig von Stromversorgung (bei MC-Betrieb auf 0 setzen)
#define STROM_EXTERN 0

// Layout
//#define TRELLIS 1
#define TRELLIS 'A'
//#define TRELLIS 2
//#define TRELLIS 3
//#define TRELLIS 8
//#define TRELLIS 'T'
//#define TRELLIS 'U'

//Spiel
#if TRELLIS == 1
    #define MAX_SPIELER 2
    #define MAX_FIGUREN 2
    #define Y_DIM 4 //number of rows of key
    #define X_DIM 4 //number of columns of keys
#elif TRELLIS == 'A' // Alternatives Layout für einen Trellis
    #define MAX_SPIELER 4
    #define MAX_FIGUREN 1
    #define Y_DIM 4 //number of rows of key
    #define X_DIM 4 //number of columns of keys
#elif TRELLIS == 2
    #define MAX_SPIELER 2
    #define MAX_FIGUREN 2
    #define Y_DIM 4 //number of rows of key
    #define X_DIM 8 //number of columns of keys
#elif TRELLIS == 3
    #define MAX_SPIELER 2
    #define MAX_FIGUREN 2
    #define Y_DIM 4 //number of rows of key
    #define X_DIM 12 //number of columns of keys
#elif TRELLIS == 8
    #define MAX_SPIELER 4
    #define MAX_FIGUREN 4
    #define Y_DIM 12 //number of rows of key
    #define X_DIM 12 //number of columns of keys
#elif TRELLIS == 'T' // Test
    #define MAX_SPIELER 4
    #define MAX_FIGUREN 4
    #define Y_DIM 12 //number of rows of key
    #define X_DIM 12 //number of columns of keys
#elif TRELLIS == 'U' // Test 1 realer Trellis aber mehrere Adressen werden angegeben
    #define MAX_SPIELER 2
    #define MAX_FIGUREN 2
    #define Y_DIM 4 //number of rows of key
    #define X_DIM 8 //number of columns of keys
#endif

// Quiz
extern Quiz q;

extern Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4];
extern Adafruit_MultiTrellis trellis;

#define SPIELER1_STARTFELD_KEY 0
#define SPIELER2_STARTFELD_KEY 3
#define SPIELER3_STARTFELD_KEY 8
#define SPIELER4_STARTFELD_KEY 11

// Spielfeld Layout
extern int spielfeld_layout[];
extern int spielfeld_len;
extern std::map<int, Feld*> spielbrett;
//extern std::map<int, int>trellis_position_to_spielfeld_key;

// Spielbrettfarbe
extern char DEFAULT_COLOR[3];

extern char SPIELER_COLOR[4][3];
extern char SPIELER_FELD_COLOR[4][3];

extern int SPIELER_STARTZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN];
extern int SPIELER_ENDZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN]; 

extern int SPIELER_KEY[4];
extern int SPIELER_ENDZONE_KEY[4];
extern int SPIELER_STARTFELD_KEYS[MAX_SPIELER]; // hierauf wird eine Spielfigur zu Beginn gesetzt



//Helfer
int freeRam();
uint32_t transform_color_array_to_single_value(char rgb[]);



#endif //UNTITLED_COMMON_H
