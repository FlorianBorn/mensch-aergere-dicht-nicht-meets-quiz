//
// Created by bornf on 24.01.2019.
//

#ifndef UNTITLED_SPIELFIGUR_H
#define UNTITLED_SPIELFIGUR_H

//#include "Feld.h"

class Feld;

class Spielfigur {
public:
    //int figur_nr; // kann sich für jeden Spieler wiederholen; ggf. redundant mit id
    int startposition; // startposition ... key des Startfeldes
    char farbe[3];
    int spieler_nr;
    int spielfigur_nr;
    bool figur_steht_in_endzone;
    int entfernung_von_start;
    Feld * aktuelles_feld;

    Spielfigur();
    //Spielfigur(int spieler_nr, int startposition, char farbe[], Feld * f); //ACHTUNG: soll durch unteren Constr ersetzt werden startposition ... key des Startfeldes
    Spielfigur(int spieler_nr, int spielfigur_nr, int startposition, char farbe[], Feld * f); // startposition ... key des Startfeldes

    void set_color(char farbe[]);
    void set_aktuelles_feld(Feld * f);

    // Helfer
    bool steht_in_startzone();
    void print_info();


};


#endif //UNTITLED_SPIELFIGUR_H
