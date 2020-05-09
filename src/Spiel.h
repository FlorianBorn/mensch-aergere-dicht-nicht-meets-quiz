//
// Created by bornf on 24.01.2019.
//

#ifndef UNTITLED_SPIEL_H
#define UNTITLED_SPIEL_H

#include "ArduinoSTL.h"
#include <map>
#include "Feld.h"
#include "Spieler.h"

class Spiel
{
public:
    std::vector<Spieler*> spieler;
    bool quizmodus;

public:

    Spiel();

    // Spieler
    void add_spieler(int spieler_nr);

    // Spielbrett

    // Spielrunde
    void spielzug_ausfuehren(Spieler * s);
    void spielen();

    //Test
    void test();

    //Helfer
    bool ausgewaehlte_figur_darf_bewegt_werden(Spielfigur * figur, int wuerfel_augenzahl);
    bool spieler_kann_mindestens_eine_figur_bewegen(Spieler *s, int wuerfel_augenzahl);
    bool spieler_hat_gewonnen(Spieler *s);
    bool alle_spielerfiguren_befinden_sich_in_startzone(Spieler *s);

    //Setup
    void erzeuge_spielbrett(); // erzeuge die Felder, unabhängig von den Spielern existieren
    void add_fields_to_spielbrett(int layout[], int len);
    void add_fields_to_spielbrett(int layout[], int len, int key, char farbe[]); // Key bestimmt die Art des Feldes (0... Spielfeld, x00.. Startzone)
    int get_spieleranzahl();
    void setup();


};


#endif //UNTITLED_SPIEL_H
