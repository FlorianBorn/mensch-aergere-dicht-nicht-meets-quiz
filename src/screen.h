//
// Created by bornf on 09.02.2019.
//
#ifndef UNTITLED_SCREEN_H
#define UNTITLED_SCREEN_H

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
//extern MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

#include "Quiz.h"

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x9341
const int TS_LEFT=925,TS_RT=111,TS_TOP=66,TS_BOT=911;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define	BLACK16   0x0000
#define	BLUE16    0x001F
#define	RED16     0xF800
#define	GREEN16   0x07E0
#define CYAN16    0x07FF
#define MAGENTA16 0xF81F
#define YELLOW16  0xFFE0
#define WHITE16   0xFFFF

#define WILLKOMMEN 0
#define SPIELERWAHL 1
#define NAECHSTER_SPIELER 2
#define WUERFEL 3
#define SPIELER_HAT_GEWONNEN 4
#define RICHTIG 5
#define FALSCH 6
#define NOCHMAL 7
#define GOODBYE 8
#define MODUSWAHL 9

extern TouchScreen ts;
extern MCUFRIEND_kbv tft;
extern int pixel_x, pixel_y; 
extern Adafruit_GFX_Button q_btn[4];
extern int anzahl_aktive_buttons;

void zeige_meldung(int meldungsnummer);
void zeige_meldung(int meldungsnummer, int spieler_nr);
void zeige_meldung(int meldungsnummer, int spieler_nr, int wuerfel_augenzahl);
void zeige_meldung(int meldungsnummer, int spieler_nr, int wuerfel_augenzahl, bool bewegung_erlaubt);
void zeige_quiz(int spieler_nr);
int get_user_input(); // gibt die Nummer des gedrückten Buttons zurück (beginnt bei 1)

bool Touch_getXY(void);
void init_screen(int spieler_nr);
void init_screen(int spieler_nr, uint16_t background_color);

uint16_t get_identifier();

#endif //UNTITLED_SCREEN_H