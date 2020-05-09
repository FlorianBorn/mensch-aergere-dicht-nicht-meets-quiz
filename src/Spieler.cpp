//
// Created by bornf on 24.01.2019.
//

#include "Spieler.h"
#include "common.h"
#include "Feld.h"
#include <map>
//#include "Spielfigur.h"

// Konstruktoren

Spieler::Spieler(){}

Spieler::Spieler(int spieler_nr, char farbe[]) 
{
    //Serial.println("Spieler: Konstruktor -- Spieler(int spieler_nr, char farbe[]) ...");
    this->spieler_nr = spieler_nr;
    this->startfeld_key = SPIELER_STARTFELD_KEYS[spieler_nr];
    this->base_key = SPIELER_KEY[spieler_nr]; 
    this->anzahl_figuren_in_endzone = 0;
    set_color(farbe);
    //Serial.println("\tSpieler: Konstruktor abgeschlossen ...");
}

void Spieler::set_color(char farbe[])
{
    //Serial.println("Spieler: set_color...");
    this->farbe[0] = farbe[0];
    this->farbe[1] = farbe[1];
    this->farbe[2] = farbe[2];
    //Serial.println("\tSpieler: set_color abgeschlossen...");
}


void Spieler::add_spielfigur(int spielfigur_nr)
{
    //Serial.println("Spieler: add_spielfigur...");
    int startposition = this->base_key + spielfigur_nr; // ACHTUNG: es erfolgt keine Kontrolle für spielfigur_nr
    Spielfigur * figur = new Spielfigur(this->spieler_nr, spielfigur_nr, startposition, this->farbe, spielbrett[startposition]);
    //ACHTUNG: Wenn Figuren nicht nach aufsteigender Reihenfolge hinzugefügt werden kann es zu problemen kommen!
    this->figuren.push_back(figur);
    //Serial.println("\tSpieler: add_spielfigur abgeschlossen...");
    /*
    Serial.println("DEBUGGIN: Spieler - add_spielfiguren");
    Serial.print("\taktuelles Feld - Spielfeld Nr.: ");
    Serial.println(spielbrett[startposition]->spielfeld_position);
    Serial.print("\taktuelles Feld - Trellis Nr.: ");
    Serial.println(spielbrett[startposition]->trellis_position);
    */
}

void Spieler::add_spielfiguren()
{
    for(int i = 0; i < MAX_FIGUREN; i++)
    {
        add_spielfigur(i);
    }
}

void Spieler::bewege_figur(int spielfigur_nr, int anzahl_felder)
{
    Serial.println("Spieler: bewege_figur...");
    Spielfigur * figur = figuren[spielfigur_nr];

    int spielfeld_key = get_spielfeld_key_from_figur(spielfigur_nr);
    int ziel_key;
    int neue_entfernung_von_start = figur->entfernung_von_start + anzahl_felder;
    int temp_entfernung_von_start = figur->entfernung_von_start; // Entfernung der Spielfigur von dem Startfeld des jeweiligen Spielers

    // Kleiner Check auf Gueltigkeit
    if(neue_entfernung_von_start > (spielfeld_len + MAX_FIGUREN - 1))
    {
        //Serial.println("Ungueltiger Zug: Figur wuerde Endzone verlassen");
    }

    // In jedem Fall: Setze Pointer des Anfangsfeldes auf Null (Figur verlässt Feld)
    spielbrett[spielfeld_key]->figur = nullptr;

    // 1. Figur befindet sich in Startzone
    if(spielfeld_key == figuren[spielfigur_nr]->startposition && anzahl_felder == 6)
    //if(spielfeld_key >= 100 && spielfeld_key < 500 ) // ACHTUNG: Genau müsste es sein spielfeld_key < 400 + MAX_FIGUREN
    {
        Serial.println("\tBewege Figur von Startzone auf Startfeld...");

        Serial.print("\t\tZiel SPielfeld Key: ");
        int ziel_key = spielbrett[SPIELER_STARTFELD_KEYS[this->spieler_nr]]->spielfeld_position;
        Serial.println(ziel_key);

        // Wenn Start durch Gegner belegt ist, schlage ihn
        if(spielbrett[ziel_key]->figur != nullptr)
        {
            Serial.println("\t\tSpieler schlaegt andere Figur. Rufe 'bewege_figur_zurueck_in_startzone' auf...");
            bewege_figur_zurueck_in_startzone(spielbrett[ziel_key]->figur);
        }

        // Zeige das Verlassen optisch an
        figuren[spielfigur_nr]->aktuelles_feld->change_color();
        delay(300);
        // Ändere Feld der Figur auf Startfeld
        figuren[spielfigur_nr]->set_aktuelles_feld(spielbrett[SPIELER_STARTFELD_KEYS[this->spieler_nr]]);
        return;
    }

    // 2. Figur befindet sich bereits auf dem Spielbrett
    // Fall: Figur landet in Endzone
    if(neue_entfernung_von_start > (spielfeld_len - 1))
    {
        Serial.println("\tSpieler: Figur landet in Endzone...");
        //ACHTUNG es wird nirgends geprüft, ob die Figur über die Endzone "hinausschießt"
        // Spieler hat nun eine weitere Figur in der Endzone
        figur->figur_steht_in_endzone = true;

        // Stelle Bewegung optisch dar
        zeige_bewegung(1, anzahl_felder, spielfeld_key, figur, temp_entfernung_von_start);

        int delta = neue_entfernung_von_start - spielfeld_len;
        ziel_key = SPIELER_ENDZONE_KEY[this->spieler_nr];
        figur->set_aktuelles_feld(spielbrett[ziel_key + delta]);
        figur->entfernung_von_start = neue_entfernung_von_start;

    } else // Figur bewegt sich nur innerhalb des "öffentlichen" Spielfeldes
    {
        Serial.println("\tSpieler: Figur bewegt sich nur auf oeffentlichen Spielfeld...");
        
        // Stelle Bewegung optisch dar
        zeige_bewegung(0, anzahl_felder, spielfeld_key, figur, temp_entfernung_von_start);

        ziel_key = (spielfeld_key + anzahl_felder) % spielfeld_len;

        // Wenn auf dem Zielfeld bereits eine Figur steht, bewege sie in die Startzone zurück
        // ACHTUNG: Es wird hier angenommen, dass es eine gegnerische Figur ist, die dort steht
        // Ein Check, ob es eine eigene Figur ist (ob die Bewegung ausgeführt werden darf, muss dann
        // vor dem Aufruf dieser Methode durchgeführt werden!)
        
        if(spielbrett[ziel_key]->figur != nullptr)
        {
            Serial.println("\t\tSpieler schlaegt andere Figur. Rufe 'bewege_figur_zurueck_in_startzone' auf...");
            bewege_figur_zurueck_in_startzone(spielbrett[ziel_key]->figur);
        }

        figur->set_aktuelles_feld(spielbrett[ziel_key]);
        figur->entfernung_von_start = neue_entfernung_von_start;
    }
}

void Spieler::zeige_bewegung(int bewegunsart, int anzahl_felder, int spielfeld_key, Spielfigur * figur, int temp_entfernung_von_start)
{
    //Serial.println("Spieler: Zeige Bewegung...");
    int key;
    int next_key;
    
    // Bewegung nur auf dem öffentlichen Spielfeld
    if(bewegunsart == 0) 
    {
        //Serial.println("\tFigur bewegt sich nur auf oeffentlichen Spielfeld...");
        // Stelle Bewegung optisch dar
        key = spielfeld_key;
        next_key = key + 1;
        for(int i = 0; i < anzahl_felder; i++, key++, next_key++)
        {
            key = key % spielfeld_len;
            next_key = next_key % spielfeld_len;

            spielbrett[key]->change_color();
            delay(200);
            spielbrett[next_key]->change_color(figur->farbe);
            delay(400);
        }
    } else
    {
        //Serial.println("\tFigur wird sich in Endzone bewegen...");
        // Stelle Bewegung optisch dar
        key = spielfeld_key;
        next_key = key + 1;
        for(int i = 0; i < anzahl_felder; i++, key++, next_key++)
        {
            // D.h. wenn die Figur bereits in der Endzone steht, dann darf der Key durch
            // Modulo nicht mehr zurückgesetzt werden
            if(key < 999)
            {
                key = key % spielfeld_len;
                next_key = next_key % spielfeld_len;
            }
                
            // Wenn sie die Figur (logisch) genau auf dem letzten Feld vor ihrer Endzone befindet
            if(temp_entfernung_von_start == (spielfeld_len - 1))
            {
                Serial.println("\tFigur steht vor der Endzone...");
                next_key = SPIELER_ENDZONE_KEY[this->spieler_nr];

                spielbrett[key]->change_color();
                delay(200);
                spielbrett[next_key]->change_color(figur->farbe);
                delay(400);
                temp_entfernung_von_start++;
                
                key = next_key - 1;
                Serial.println(key);
                Serial.println(next_key);
                
                continue;
            }

            spielbrett[key]->change_color();
            delay(200);
            spielbrett[next_key]->change_color(figur->farbe);
            delay(400);
            temp_entfernung_von_start++;
        }
    }
    //Serial.println("Spieler: Zeige Bewegung abgeschlossen...");
}

void Spieler::bewege_figur_auf_start(int spielfigur_nr)
{
    //Serial.println("Spieler: bewege_spielfigur_auf_start...");

    // Prüfe, ob ausgewählte Figur überhaupt im Startbereich sitzt
    int position = get_spielfeld_key_from_figur(spielfigur_nr);
    if(position != figuren[spielfigur_nr]->startposition)
    {
        //Serial.println("Figur nicht in Startbereich");
        return;
    }
    // Spielfigur verlässt Startzone
    spielbrett[this->figuren[spielfigur_nr]->startposition]->figur = nullptr;
    // Zeige das Verlassen optisch an
    figuren[spielfigur_nr]->aktuelles_feld->change_color();
    delay(300);
    // Ändere Feld der Figur auf Startfeld
    figuren[spielfigur_nr]->set_aktuelles_feld(spielbrett[SPIELER_STARTFELD_KEYS[this->spieler_nr]]);
    //Serial.println("\tSpieler: bewege_spielfigur_auf_start abgeschlossen...");
}

void Spieler::bewege_figur_zurueck_in_startzone(Spielfigur * figur)
{
    Serial.println("Spieler: bewege_figur_zurueck_in_startzone...");
    //ACHTUNG: Das aktuelle Feld wird nicht auf Null gesetzt, weil die Methode nur beim 'Schlagen' aufgerufen wird
    // und die schlagende Spielfigur ihre Adresse in das Feld einträgt
    // Alternativ: Lösche Pointer und rufe Methode auf, bevor die andere Figur ihren Pointer setzt
    figur->aktuelles_feld->figur = nullptr;
    figur->set_aktuelles_feld(spielbrett[figur->startposition]);
    figur->entfernung_von_start = 0;
}

int Spieler::get_spielfeld_key_from_figur(int spielfigur_nr)
{
    //Serial.println("Spieler: get_key...");
    int spielfeld_position = this->figuren[spielfigur_nr]->aktuelles_feld->spielfeld_position;
    //Serial.println("\tSpieler: get_key abgeschlossen...");
    return spielfeld_position;
}

bool Spieler::spielfigur_kann_bewegt_werden(Spielfigur * figur, int wuerfelzahl)
{
    //Serial.println("Spieler: spielfigur_kann_bewegt_werden...");

    // Fall: Spielfigur soll vom 'Haus' auf ihr Startfeld bewegt werden
    Spielfigur * f = spielbrett[this->startfeld_key]->figur;
    if(wuerfelzahl == 0)
    {
        if(f == nullptr)
        {
            //Serial.println("\tFigur kann bewegt werden. Das Startfeld ist leer!");
            return true;
        }
        if(f->spieler_nr == this->spieler_nr)
        {
            //Serial.println("\tFigur kann nicht bewegt werden. Das Startfeld ist durch eine eigene Figur belegt!");
            return false;
        }
        if(f->spieler_nr != this->spieler_nr)
        {
            //Serial.println("\tFigur kann bewegt werden. Spielfigur auf dem Zielfeld wird geschlagen");
            return true;
        }
    }

    return true;
}
