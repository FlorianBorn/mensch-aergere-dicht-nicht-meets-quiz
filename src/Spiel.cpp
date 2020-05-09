//
// Created by bornf on 24.01.2019.
//

#include "Spiel.h"
//#include "Spieler.h"
#include "common.h"
#include "Feld.h"
#include "Events.h"
#include "screen.h"

Spiel::Spiel() {}

// Spiellogik
void Spiel::spielzug_ausfuehren(Spieler * s)
{
    // Beantworte Frage
        // Frage richtig
            // Wuerfeln
                // Solange keine gültige Figur ausgewählt wurde oder 3 Eingaben gemacht wurden...
                    // Spielfeld freigeben und User-Input entgegennehmen
                    // Kollisionskontrolle (darf die Figur bewegt werden?)
                    // ja
                        // bewege Figur
                        // aktualisiere
                        // wenn Spieler gewonnen hat, beende Spiel
                    // nein
                        // erhöhe Versuchs-Counter
                        // ACHTUNG: besser, es wird im Vorfeld anhand der Würfelzahl ermitteln, ob überhaupt ein gültiger Wurf möglich ist
                        // continue;
        // Frage falsch
            // Ende

    bool frage_richtig_beantwortet = false;
    int wuerfel_augenzahl = 0;
    int anzahl_auswahlversuche = 0;
    int n_wuerfelversuche;
    Spielfigur * ausgewaehlte_figur = nullptr;
    bool eine_figur_kann_bewegt_werden;

    Serial.print("An der Reihe ist Spieler Nr.: ");
    Serial.println(s->spieler_nr);

    // bestimmte, wie oft der Spieler würfeln darf
    if(alle_spielerfiguren_befinden_sich_in_startzone(s)){
        n_wuerfelversuche = 3;
    } else {
        n_wuerfelversuche = 1;
    }

    // Wiederhole, solange der Spieler wuerfeln darf 
    //      d.h. er beantwortet die Frage richtig und hat eine 6
    do
    {
        // stelle keine Frage, wenn alle Figuren im "Haus" sind (besserer Spielfluss)
        if(this->quizmodus and !alle_spielerfiguren_befinden_sich_in_startzone(s))
        {
            q.create_random_question();
            zeige_quiz(s->spieler_nr);
            if(get_user_input() == q.button_nr_of_correct_question)
            {
                zeige_meldung(RICHTIG, s->spieler_nr);
                frage_richtig_beantwortet = true;
                delay(1000);
            } else
            {
                zeige_meldung(FALSCH, s->spieler_nr);
                frage_richtig_beantwortet = false;
                delay(1000);
            }
            
            
        } else
        {
            frage_richtig_beantwortet = true;
        }

        if(frage_richtig_beantwortet)
        {
            // Wiederhole bis zu 3 Mal, falls alle Figuren des Spieler in der Anfangszone stehen
            do
            {
                wuerfel_augenzahl = random(1,7); //ACHTUNG Später wieder durch 1, 7  ersetzen
                Serial.print("\tDu hast gewuerfelt: ");
                Serial.println(wuerfel_augenzahl);
                
                eine_figur_kann_bewegt_werden = spieler_kann_mindestens_eine_figur_bewegen(s, wuerfel_augenzahl);
                if(eine_figur_kann_bewegt_werden)
                {
                    zeige_meldung(WUERFEL, s->spieler_nr, wuerfel_augenzahl, eine_figur_kann_bewegt_werden);
                    delay(1500);
                    n_wuerfelversuche = 0; // sobald der Spieler eine Figur bewegen kann, erlöschen die restlichen Versuche
                    spielfeld_freigeben(s); // muss in Schleife freigegeben werden, sonst können die Fig. bei einer 6 nicht nochmal bewegt werden
                    // Warte auf Input
                    while(pushed_trellis_button_key == -1)
                    {
                        trellis.read();
                        delay(20);

                        // Wenn ein Button gedrückt wurde
                        if(pushed_trellis_button_key != -1)
                        {                         
                            ausgewaehlte_figur = get_spielfigur_from_trellis_key(pushed_trellis_button_key);
                            //Serial.println("Spiel: Info ueber ausgewaehlte Figur...");
                            //ausgewaehlte_figur->print_info();
                            if(ausgewaehlte_figur_darf_bewegt_werden(ausgewaehlte_figur, wuerfel_augenzahl))
                            {
                                s->bewege_figur(ausgewaehlte_figur->spielfigur_nr, wuerfel_augenzahl);
                            } else
                            {
                                // wenn der Spieler kein Figur zum bewegen findet oder z.B. absichtlich falsche Figuren antippt
                                Serial.println("\tDeine Auswahl ist ungueltig. Bitte wiederhole!");
                                pushed_trellis_button_key = -1;
                            }
                    
                            // Setze ausgewählte Figur wieder zurück (nullptr)
                            ausgewaehlte_figur = nullptr;
                        } 
                    }

                    spielfeld_sperren();

                } else
                {
                    zeige_meldung(WUERFEL, s->spieler_nr, wuerfel_augenzahl, eine_figur_kann_bewegt_werden);
                    delay(1500);
                    n_wuerfelversuche--; // Verringere Versuche, wenn keine 6 gewürfelt wurde
                    Serial.println("\tDu kannst keinen gueltigen Zug ausfuehren!");
                    Serial.print("\tDu hast noch ");
                    Serial.print(n_wuerfelversuche);
                    Serial.println(" Versuch(e).");
                    // Spieler kann keine Figur bewegen
                    // beende Runde!
                }

            } while (n_wuerfelversuche > 0);

            // setze den gedrückten Knopf zurück
            pushed_trellis_button_key = -1;

        } else // Frage falsch beantwortet
        {
            // Beende Runde
            break; 
        }
        
        
    } while (frage_richtig_beantwortet and wuerfel_augenzahl == 6); 
    Serial.print("Spielzug beendet. Spieler Nr.: ");
    Serial.println(s->spieler_nr);
    Serial.println("");

}

void Spiel::spielen()
{
    int spieler_nr = 0; // (aktuell nicht benutzt) ACHTUNG: hier fängt immer Spieler 0 an, ggf. durch zufallszahl festlegen
    int sieger_spieler_nr;
    bool gewonnen;


    do
    {
        for(auto s: this->spieler)
        {
            zeige_meldung(NAECHSTER_SPIELER, s->spieler_nr);
            delay(1500);
            spielzug_ausfuehren(s);
            gewonnen = spieler_hat_gewonnen(s);
            sieger_spieler_nr = s->spieler_nr;
            if(gewonnen) 
            {
                zeige_meldung(SPIELER_HAT_GEWONNEN, s->spieler_nr);
                delay(5000);
                break;
            }
        }  
    } while (!gewonnen);
    
    // Kontrollausgabe
    Serial.println("Das Spiel ist vorbei!");
    Serial.print("Gewonnen hat Spieler: ");
    Serial.println(sieger_spieler_nr);
    Serial.println("");
}


//Spielbrett
void Spiel::erzeuge_spielbrett()
{
    add_fields_to_spielbrett(spielfeld_layout, spielfeld_len);
}

void Spiel::add_fields_to_spielbrett(int layout[], int len, int key, char farbe[])
{
    int spielfeld_position;
    for(int i = 0; i < len; i++)
    {
        spielfeld_position = i + key;
        spielbrett[i + key] = new Feld(layout[i], spielfeld_position, farbe); //ACHTUNG: Wird die Methode 2x mit dem selben Key aufgerufe, werden Felder überschrieben!) Layout Nr. --> Feld
    }
}

void Spiel::add_fields_to_spielbrett(int layout[], int len)
{
    add_fields_to_spielbrett(layout, len, 0, DEFAULT_COLOR);
}

// Spieler
void Spiel::add_spieler(int spieler_nr)
{
    //Serial.println("Spiel: add_spieler...");
    //füge spielerspezifische Felder hinu
    add_fields_to_spielbrett(SPIELER_STARTZONE_LAYOUT[spieler_nr], MAX_FIGUREN, SPIELER_KEY[spieler_nr], SPIELER_FELD_COLOR[spieler_nr]);
    add_fields_to_spielbrett(SPIELER_ENDZONE_LAYOUT[spieler_nr], MAX_FIGUREN, SPIELER_ENDZONE_KEY[spieler_nr], SPIELER_FELD_COLOR[spieler_nr]);

    // ACHTUNG: spielbrett[key] --> hierbei muss der Index des Spielbrett Layouts beachtet werden (siehe common.cpp) und nicht die NeoTrellis Pin-Nummerierung
    spielbrett[SPIELER_STARTFELD_KEYS[spieler_nr]]->set_default_color(SPIELER_FELD_COLOR[spieler_nr]);

    //Spieler
    Spieler * s = new Spieler(spieler_nr, SPIELER_COLOR[spieler_nr]);
    s->add_spielfiguren();

    this->spieler.push_back(s);
}

// Helfer
bool Spiel::ausgewaehlte_figur_darf_bewegt_werden(Spielfigur * figur, int wuerfel_augenzahl)
{   
    //ACHTUNG: diese Methode wird von spieler_kann_mindestens_eine_figur_bewege aufgerufen
    // daher kann es, wenn die print-Ausgaben eingeschaltet sind, zu irritierenden Ausgaben kommen

    // ermittle das Zielfeld
    int spielfeld_key = figur->aktuelles_feld->spielfeld_position;
    int ziel_key;
    int neue_entfernung_von_start = figur->entfernung_von_start + wuerfel_augenzahl;
    int temp_entfernung_von_start = figur->entfernung_von_start; // Entfernung der Spielfigur von dem Startfeld des jeweiligen Spielers
    int spieler_nr = figur->spieler_nr;

    // Erlaubt wenn...
    // 1. das Zielfeld ist leer
    // 2. alles, was nicht verboten ist
    #ifdef DEBUGGING_SPIEL
        Serial.println("Spiel: ausgewaehlte_figur_darf_bewegt_werden...");
        Serial.print("\tAusgewaehlte Figur: ");
        Serial.println(figur->spielfigur_nr);

        Serial.println("\tAusgewaehlte Figur Info: ");
        figur->print_info();
    #endif

    // Verboten wenn...
    // 1. Figur in Startzone wurde ausgewählt, obwohl Augenzahl nicht 6
    bool figur_ist_in_startzone = figur->aktuelles_feld->spielfeld_position >= 100 && figur->aktuelles_feld->spielfeld_position < 1000;
    if(wuerfel_augenzahl != 6 && figur_ist_in_startzone)
    {
        #ifdef DEBUGGING_SPIEL
            Serial.println("\tVerboten: Figur darf nur mit einer 6 auf Spielfeld bewegt werden!");
            Serial.print("\tWuerfel Augenzahl: ");
            Serial.println(wuerfel_augenzahl);
            Serial.print("\tFigur Spielfeld Position: ");
            Serial.println(figur->aktuelles_feld->spielfeld_position);
        #endif
       
        return false;
    }
    // 2. Figur würde mit einer Figur des selben Spielers kollidieren
    // 2.1 Figur soll von Startzone auf Spielfeld bewegt werden
    if(wuerfel_augenzahl == 6 && figur_ist_in_startzone)
    {
        bool eine_figur_steht_auf_feld = spielbrett[SPIELER_STARTFELD_KEYS[figur->spieler_nr]]->figur != nullptr;
        if(spieler_nr == spielbrett[SPIELER_STARTFELD_KEYS[figur->spieler_nr]]->figur->spieler_nr and eine_figur_steht_auf_feld)
        {
            #ifdef DEBUGGING_SPIEL
                Serial.println("\tVerboten: Figur darf nicht rausgesetzt werden, weil das Startfeld durch eine eigene Figur belegt ist!");
                Serial.print("\t\tspieler_nr: ");
                Serial.println(figur->spieler_nr);
                Serial.print("\t\tstartfeld_key: ");
                Serial.println(SPIELER_STARTFELD_KEYS[figur->spieler_nr]);
                Serial.print("\t\tfigur auf startfeld: ");
                Serial.println(spielbrett[SPIELER_STARTFELD_KEYS[figur->spieler_nr]]->figur->spielfigur_nr); 
                if(spielbrett[SPIELER_STARTFELD_KEYS[figur->spieler_nr]]->figur == nullptr)
                {
                    Serial.print("\t\tACHTUNG: NULLPOINTER ");
                }
            #endif
            return false;
        }
    }

    // 2.2 Figur ist bereits im Spiel
    // 2.2.1 Figur landet in Endzone
    if(neue_entfernung_von_start > (spielfeld_len - 1))
    {
        int delta = neue_entfernung_von_start - spielfeld_len;
        ziel_key = SPIELER_ENDZONE_KEY[figur->spieler_nr];
        bool eine_figur_steht_auf_feld = spielbrett[ziel_key + delta]->figur != nullptr;
        if(spieler_nr == spielbrett[ziel_key + delta]->figur->spieler_nr and eine_figur_steht_auf_feld)
        {
            #ifdef DEBUGGING_SPIEL
                Serial.println("\tVerboten: Auf dem Zielfeld (Endzone) befindet sich bereits eine Figur des Spielers!");
            #endif
            return false;
        }
    } 
    // 2.2.2 Figur bleibt auf 'öffentlichem Spielfeld
    if(neue_entfernung_von_start <= (spielfeld_len - 1))
    {
        ziel_key = (spielfeld_key + wuerfel_augenzahl) % spielfeld_len;
        bool eine_figur_steht_auf_feld = spielbrett[ziel_key]->figur != nullptr;
        if(spieler_nr == spielbrett[ziel_key]->figur->spieler_nr and eine_figur_steht_auf_feld)
        {
            #ifdef DEBUGGING_SPIEL
                Serial.println("\tVerboten: Auf dem Zielfeld befindet sich bereits eine Figur des Spielers!");
                Serial.println("\t\tInfo zu Figur auf Zielfeld");
                spielbrett[ziel_key]->figur->print_info();
            #endif
            return false;
        }
        
    }
    // 3. Figur würde über die Endzone hinausschießen
    if(neue_entfernung_von_start > (spielfeld_len-1 + MAX_FIGUREN))
    {
        #ifdef DEBUGGING_SPIEL
            Serial.println("\tVerboten: Figur wuerde sich über die Endzone hinaus bewegen!");
        #endif
        return false;
    }

    #ifdef DEBUGGING_SPIEL
        Serial.println("\tErlaubt: Figur darf bewegt werden!");
    #endif
    return true;
}

bool Spiel::spieler_kann_mindestens_eine_figur_bewegen(Spieler *s, int wuerfel_augenzahl)
{
    //Serial.println("Check ob Spieler ueberhaupt eine Figur bewegen kann...");
    for(int i = 0; i < MAX_FIGUREN; i++ )
    {
        if(ausgewaehlte_figur_darf_bewegt_werden(s->figuren[i], wuerfel_augenzahl))
        {
            //Serial.println("\tSpieler kann mind. eine Figur bewegen!");
            return true;
        } else
        {
            //Serial.println("\tSpieler kann mind. nicht bewegen...");
            //Serial.print("\t\tFigur Nr.: ");
            //Serial.println(s->figuren[i]->spielfigur_nr);
            //Serial.print("\t\tAuf Spielfeldposition: ");
            //Serial.println(s->figuren[i]->aktuelles_feld->spielfeld_position);
        }  
    }
    return false;
}

bool Spiel::spieler_hat_gewonnen(Spieler *s)
{
    int anzahl_figure_in_endzone = 0;
    for(auto figur: s->figuren)
    {
        if(figur->figur_steht_in_endzone) 
            anzahl_figure_in_endzone++;
    }

    if(anzahl_figure_in_endzone == MAX_FIGUREN)
    {
         return true;
    } else
    {
        return false;
    }
    
}

bool Spiel::alle_spielerfiguren_befinden_sich_in_startzone(Spieler *s)
{
    int n_figuren_in_startzone = 0;
    for(auto *figur: s->figuren)
    {
        if(figur->steht_in_startzone())
        {
            #ifdef DEBUGGING_SPIEL
                Serial.print("DEBUGGING: Spieler in Startzone: ");
                Serial.print(n_figuren_in_startzone);
            #endif
            n_figuren_in_startzone++;
        }
    }
    if( n_figuren_in_startzone == MAX_FIGUREN) { return true; }
    else { return false; }
}

// Wie viele Spieler nehmen teil?
int Spiel::get_spieleranzahl()
{
    zeige_meldung(SPIELERWAHL);
    return get_user_input();
}

void Spiel::setup()
{
    int anzahl_spieler;

    // Zuerst alle LEDs ausschalten (von ggf. altem Spiel)
    for (uint16_t i=0; i< (X_DIM * Y_DIM); i++) {
            //if(i == 4 or i == 8 or i == 12 or i == 16) i += 4;
            #if TRELLIS == 8
                if(i == 52 or i == 64 or i == 76 or i == 88) i += 4;
            #endif
            trellis.setPixelColor(i, 0x000000);
            //trellis.show();
        }


    erzeuge_spielbrett();

    // Spieleranzahl abfragen und Spieler hinzufügen
    anzahl_spieler = get_spieleranzahl();
    for(int i = 0; i < anzahl_spieler; i++)
    {
        add_spieler(i);
    }

    // Spielmodus einstellen
    zeige_meldung(MODUSWAHL);
    (get_user_input() == 1)? quizmodus = true : quizmodus = false;

}