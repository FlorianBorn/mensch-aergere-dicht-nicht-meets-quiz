//
// Created by bornf on 31.01.2019.
//
#ifndef UNTITLED_EVENTS_H
#define UNTITLED_EVENTS_H

#include <Adafruit_NeoTrellis.h>
#include "Spielfigur.h"
#include "Spieler.h"

// Variable für den durch einen Spieler gedrückten Knopf
extern int pushed_trellis_button_key;

uint32_t Wheel(byte WheelPos);
TrellisCallback blink(keyEvent evt);
TrellisCallback feld_gedrueckt(keyEvent evt);
int feld_auswahl();
void set_up_figuren_wahl();
void spielfeld_freigeben(Spieler * s);
void spielfeld_sperren();

// Helfer
Spielfigur* get_spielfigur_from_trellis_key(int trellis_key);
void print_info(int trellis_key);
void show_animation();

#endif //UNTITLED_EVENTS_H
