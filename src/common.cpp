//
// Created by bornf on 24.01.2019.
//

#include "common.h"

// Trellis Setup
// siehe https://github.com/adafruit/Adafruit_Seesaw/blob/master/examples/NeoTrellis/multitrellis/basic/basic.ino

// 1 Trellis
#if TRELLIS == 1
    int spielfeld_layout[] = {4,5,6,7,11,10,9,8}; // ACHTUNG: Angabe in Trelliskeys
    int SPIELER_STARTZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {2, 3},
        {12, 13}
    };
    int SPIELER_ENDZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {1, 0},
        {14,15}
    };
    int SPIELER_STARTFELD_KEYS[MAX_SPIELER] = {2,6}; //ACHTUNG: die Keys müssen SPIELFELD KEYS sein, NICHT Trellis Keys (Bsp.: hier ist Spielfeldkey 2 == Trelliskey 6)
                // ACHTUNG II: die Felder werden als INDEX von spielfeld_layout angegeben (vgl. spielfeld_layout)

    Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
        { Adafruit_NeoTrellis(0x2E) } //, Adafruit_NeoTrellis(0x2F)
    };
// ----------------------------------------------------
// 1A Trellis ; Alternatives Layout zum Test
#elif TRELLIS == 'A' 
    int spielfeld_layout[] = {13,9,5,1,2,6,10,14}; // ACHTUNG: Angabe in Trelliskeys
    int SPIELER_STARTZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {8},
        {0},
        {7},
        {15}
    };
    int SPIELER_ENDZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {12},
        {4},
        {3},
        {11}
    };
    int SPIELER_STARTFELD_KEYS[MAX_SPIELER] = {1,3,5,7 }; //ACHTUNG: die Keys müssen SPIELFELD KEYS sein, NICHT Trellis Keys (Bsp.: hier ist Spielfeldkey 2 == Trelliskey 6)
                // ACHTUNG II: die Felder werden als INDEX von spielfeld_layout angegeben (vgl. spielfeld_layout)

    Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
        { Adafruit_NeoTrellis(0x2E) } //, Adafruit_NeoTrellis(0x2F)
    };
// ----------------------------------------------------
#elif TRELLIS == 2
    // 2 Trellis
    int spielfeld_layout[] = {2,3,4,5,6,7,15,23,22,21,29,28,27,26,25,24,16,8,9,10}; // ACHTUNG: Angabe in Trelliskeys
    int SPIELER_STARTZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {0, 1},
        {30, 31}
    };
    int SPIELER_ENDZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {11, 12},
        {20, 19} 
    };
    int SPIELER_STARTFELD_KEYS[MAX_SPIELER] = {0,10}; //ACHTUNG: die Keys müssen SPIELFELD KEYS sein, NICHT Trellis Keys (Bsp.: hier ist Spielfeldkey 2 == Trelliskey 6)
    
    Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
        { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2F) } 
    };
    // ----------------------------------------------------
#elif TRELLIS == 3
    // 2 Trellis
    int spielfeld_layout[] = {2,3,4,5,6,7,15,23,22,21,29,28,27,26,25,24,16,8,9,10}; // ACHTUNG: Angabe in Trelliskeys
    int SPIELER_STARTZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {0, 1},
        {30, 31}
    };
    int SPIELER_ENDZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {11, 12},
        {20, 19} 
    };
    int SPIELER_STARTFELD_KEYS[MAX_SPIELER] = {0,10}; //ACHTUNG: die Keys müssen SPIELFELD KEYS sein, NICHT Trellis Keys (Bsp.: hier ist Spielfeldkey 2 == Trelliskey 6)
    
    Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
        { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2F), Adafruit_NeoTrellis(0x30) } 
    };
    // ----------------------------------------------------
#elif TRELLIS == 8
    //  8 Trellis
    int spielfeld_layout[] = // ACHTUNG: Angabe in Trelliskeys
                {24,25,26,27,15,3,4,5,17,29,41,42,43,31,
                19,7,8,9,21,33,45,46,47,59,71,70,69,68,
                80,92,93,94,95,107,119,118,117,116,128,
                140,139,138,126,114,102,101,100,112,124,
                136,135,134,122,110,98,97,96,84,72,73,74,
                75,63,51,50,49,48,36};
    int SPIELER_STARTZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {0, 1, 12, 13},
        {10, 11,22,23},
        {130,131,142,143},
        {120,121,132,133}
    };
    int SPIELER_ENDZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {37,38,39,40},
        {20,32,44,56},
        {106,105,104,103},
        {123, 111,99,87} 
    };
    int SPIELER_STARTFELD_KEYS[MAX_SPIELER] = {0,17,34,51}; //ACHTUNG: die Keys müssen SPIELFELD KEYS sein, NICHT Trellis Keys (Bsp.: hier ist Spielfeldkey 2 == Trelliskey 6)
/* 
    Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
        { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2F), Adafruit_NeoTrellis(0x30),
          Adafruit_NeoTrellis(0x31), Adafruit_NeoTrellis(0x00), Adafruit_NeoTrellis(0x33),
          Adafruit_NeoTrellis(0x34), Adafruit_NeoTrellis(0x35), Adafruit_NeoTrellis(0x36)
        } 
    }; */

    Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
        { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2F), Adafruit_NeoTrellis(0x30) },
         { Adafruit_NeoTrellis(0x31), Adafruit_NeoTrellis(0x00), Adafruit_NeoTrellis(0x33) },
         { Adafruit_NeoTrellis(0x34), Adafruit_NeoTrellis(0x35), Adafruit_NeoTrellis(0x36) }
         
    };

#elif TRELLIS == 'T'
    //  8 Trellis
    int spielfeld_layout[] = // ACHTUNG: Angabe in Trelliskeys
                {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                 0,1,2,3 //,4,5,6,7,8,9,10,11,12,13,14,15,
                 //0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
                };
    int SPIELER_STARTZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11},
        {12,13,14,15} 
    };
    int SPIELER_ENDZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11},
        {12,13,14,15} 
    };
    int SPIELER_STARTFELD_KEYS[MAX_SPIELER] = {0,1,2,3}; //ACHTUNG: die Keys müssen SPIELFELD KEYS sein, NICHT Trellis Keys (Bsp.: hier ist Spielfeldkey 2 == Trelliskey 6)

    Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
        { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2E) },
         { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2E) },
         { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x2E) }
         
    };
#elif TRELLIS == 'U'
    // 2 Trellis
    int spielfeld_layout[] = {8,9,10,11,19,18,17,16}; // ACHTUNG: Angabe in Trelliskeys
    int SPIELER_STARTZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {3, 2},
        {24, 25}
    };
    int SPIELER_ENDZONE_LAYOUT[MAX_SPIELER][MAX_FIGUREN] = { // ACHTUNG: Angabe in Trelliskeys
        {0, 1},
        {26, 27} 
    };
    int SPIELER_STARTFELD_KEYS[MAX_SPIELER] = {2,6}; //ACHTUNG: die Keys müssen SPIELFELD KEYS sein, NICHT Trellis Keys (Bsp.: hier ist Spielfeldkey 2 == Trelliskey 6)
    
    Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
        { Adafruit_NeoTrellis(0x2E), Adafruit_NeoTrellis(0x00) } 
    };
#endif

// Quiz
Quiz q;

//Adafruit_NeoTrellis trellis;
Adafruit_MultiTrellis trellis((Adafruit_NeoTrellis *)t_array, Y_DIM/4, X_DIM/4);

int spielfeld_len = sizeof(spielfeld_layout)/sizeof(int);
std::map<int, Feld*> spielbrett;

// Helfer

#if STROM_EXTERN == 1
// Farben und Positionen
#define ROT {0x30, 0x00, 0x00}
#define GREEN {0x05, 0x2A, 0x00}
#define BLUE {0x00, 0x05, 0x2E}
#define PURPLE {0x10, 0x00, 0x30}
#define WEISS {0x20, 0x20, 0x20}

#define LIGHT_RED {0x08, 0x00, 0x00}
#define LIGHT_GREEN {0x00, 0x8, 0x00}
#define LIGHT_BLUE {0x00, 0x05, 0x08}
#define LIGHT_PURPLE {0x04, 0x00, 0x08}

#else // Zuhause: Bitte den MC nicht rösten
// Farben und Positionen
#define ROT {0x07, 0x00, 0x00}
#define GREEN {0x01, 0x06, 0x00}
#define BLUE {0x00, 0x02, 0x05}
#define PURPLE {0x03, 0x00, 0x04}
#define WEISS {0x02, 0x02, 0x02}

#define LIGHT_RED {0x02, 0x00, 0x00}
#define LIGHT_GREEN {0x00, 0x02, 0x00}
#define LIGHT_BLUE {0x00, 0x01, 0x02}
#define LIGHT_PURPLE {0x01, 0x00, 0x02}

#endif

//char DEFAULT_COLOR[] = {0x02, 0x02, 0x02};
char DEFAULT_COLOR[] = WEISS;

char SPIELER_COLOR[4][3] = {
	ROT,
	GREEN,
	BLUE,
	PURPLE
};

char SPIELER_FELD_COLOR[4][3] = {
	LIGHT_RED,
	LIGHT_GREEN,
	LIGHT_BLUE,
	LIGHT_PURPLE
};

int SPIELER_KEY[4] = {100, 200, 300, 400};
int SPIELER_ENDZONE_KEY[4] = {1000, 2000, 3000, 4000};


// Zeige freien Arbeitsspeicher an
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

// Transformiere char-Array in 32-bit Integer
uint32_t transform_color_array_to_single_value(char rgb[])
{
	uint32_t c;
    c = rgb[0];
    c <<= 8;
    c |= rgb[1];
    c <<= 8;
    c |= rgb[2];
    return c;
}

