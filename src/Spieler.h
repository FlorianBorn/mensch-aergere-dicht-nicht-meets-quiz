//
// Created by bornf on 24.01.2019.
//

#ifndef UNTITLED_SPIELER_H
#define UNTITLED_SPIELER_H

#include "common.h"
#include "Spielfigur.h"
#include <ArduinoSTL.h>
#include <map>

class Spieler {

public:
    char farbe[3];
    int spieler_nr;
    std::vector<Spielfigur*> figuren;
    int base_key;
    int startfeld_key; // Key des Feldes, auf dem die Figuren das Brett betreten (spielfeld key)
    int anzahl_figuren_in_endzone;
    std::map <int, int> spieler_key_to_spielfeld_key;

    Spieler();
    Spieler(int spieler_nr, char farbe[]);

    void set_color(char farbe[]);
    void add_spielfigur(int spielfigur_nr);
    void add_spielfiguren();
    void bewege_figur(Spielfigur * figur, int anzahl_felder);
    void bewege_figur(int spielfigur_nr, int anzahl_felder);
    void bewege_figur_auf_start(int spielfigur_nr);
    void bewege_figur_zurueck_in_startzone(Spielfigur * figur);
    void erstelle_spieler_key();
    bool spielfigur_kann_bewegt_werden(Spielfigur * figur, int wuerfelzahl);

    // Helferfunktion
    int get_spielfeld_key_from_figur(int spielfigur_nr);
    void zeige_bewegung(int bewegunsart, int anzahl_felder, int spielfeld_key, Spielfigur * figur, int temp_entfernung_von_start);

};


#endif //UNTITLED_SPIELER_H
