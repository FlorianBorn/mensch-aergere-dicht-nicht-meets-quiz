//
// Created by bornf on 24.01.2019.
//

#include "Spielfigur.h"
#include "Feld.h"
#include "common.h"

// Konstruktoren
Spielfigur::Spielfigur(){}

Spielfigur::Spielfigur(int spieler_nr, int spielfigur_nr,  int startposition, char farbe[], Feld * f)
{
    this->spieler_nr = spieler_nr;
    this->startposition = startposition; // key ... jede Figur hat hier ein festes Startfeld
    this->spielfigur_nr = spielfigur_nr;
    this->entfernung_von_start = 0;
    this->figur_steht_in_endzone = false;
    set_color(farbe);
    set_aktuelles_feld(f);
}

void Spielfigur::set_color(char farbe[])
{
    this->farbe[0] = farbe[0];
    this->farbe[1] = farbe[1];
    this->farbe[2] = farbe[2];
}


void Spielfigur::set_aktuelles_feld(Feld * f)
{
    this->aktuelles_feld = f;
    this->aktuelles_feld->set_figur(this);
    this->aktuelles_feld->change_color(this->farbe);
}

//Helfer
bool Spielfigur::steht_in_startzone()
{
    // Startzonen im Bereich 100 - 500 
    //Serial.print("\tDEBUGGING steht in startzone: ");
    bool figur_steht_in_startzone = (this->aktuelles_feld->spielfeld_position >= SPIELER_KEY[0]) and (this->aktuelles_feld->spielfeld_position <= (SPIELER_KEY[MAX_SPIELER-1] + MAX_FIGUREN));
    //Serial.println(figur_steht_in_startzone? "JA":"NEIN");
    //Serial.println(this->aktuelles_feld->spielfeld_position >= SPIELER_KEY[0]);
    //Serial.println((this->aktuelles_feld->spielfeld_position <= (SPIELER_KEY[MAX_SPIELER-1] + MAX_FIGUREN)) );
    //Serial.println(this->aktuelles_feld->spielfeld_position);
    return figur_steht_in_startzone;
}

/* Einkommentieren für Debugging, sonst Speicher sparen
void Spielfigur::print_info()
{
    Serial.println("Spielfigur: print_info...");
    Serial.print("\tstartposition: ");
    Serial.println(this->startposition);
    Serial.print("\tspieler_nr: ");
    Serial.println(this->spieler_nr);
    Serial.print("\tspielfigur_nr: ");
    Serial.println(this->spielfigur_nr);
    Serial.print("\tfigur_steht_in_endzone: ");
    Serial.println(this->figur_steht_in_endzone ? "true" : "false");
    Serial.print("\entfernung_von_start: ");
    Serial.println(this->entfernung_von_start);
    Serial.println("\taktuelles Feld: ");
    Serial.print("\t\tspielfeld_position: ");
    Serial.println(this->aktuelles_feld->spielfeld_position);
    Serial.print("\t\ttrellis_position: ");
    Serial.println(this->aktuelles_feld->trellis_position);
}
*/
