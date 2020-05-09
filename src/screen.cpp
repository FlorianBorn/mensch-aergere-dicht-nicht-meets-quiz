//
// Created by bornf on 09.02.2019.
//
#include "screen.h"
#include "common.h"

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int pixel_x, pixel_y;
int anzahl_aktive_buttons;
Adafruit_GFX_Button q_btn[4];

// Zeige Meldung auf Bildschirm an
void zeige_meldung(int meldungsnummer)
{
    zeige_meldung(meldungsnummer, -1, -1);
}

void zeige_meldung(int meldungsnummer, int spieler_nr)
{
    zeige_meldung(meldungsnummer, spieler_nr, -1);
}

void zeige_meldung(int meldungsnummer, int spieler_nr, int wuerfel_augenzahl)
{
    zeige_meldung(meldungsnummer, spieler_nr, wuerfel_augenzahl, false);
}

void zeige_meldung(int meldungsnummer, int spieler_nr, int wuerfel_augenzahl, bool bewegung_erlaubt)
{
    String s1 = "Spieler Nr. ";
    String str_spieler = s1 + spieler_nr;

    switch (meldungsnummer)
    {
        case WILLKOMMEN:
            init_screen(0); // Spieler 0 ist der 'Game Master'
            tft.setCursor(20, 60);
            tft.setTextSize(3);
            tft.println("Willkommen!");
            break;
        case SPIELERWAHL:
            init_screen(0);
            anzahl_aktive_buttons = MAX_SPIELER;

            q_btn[0].initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "1", 2); 
            q_btn[1].initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "2", 2); 
            q_btn[2].initButton(&tft,  60, 260, 100, 40, WHITE, CYAN, BLACK, "3", 2);
            q_btn[3].initButton(&tft, 180, 260, 100, 40, WHITE, CYAN, BLACK, "4", 2);
            
            tft.fillRoundRect(10, 10, 220, 150, 10, CYAN);
            tft.setCursor(30, 30);
            tft.setTextColor(BLACK);
            tft.setTextSize(3);
            tft.println("Wie viele");
            tft.setCursor(40, 70);
            tft.println("Spieler?");

            q_btn[0].drawButton(false);
            q_btn[1].drawButton(false);
            q_btn[2].drawButton(false);
            q_btn[3].drawButton(false);

            break;
        case NAECHSTER_SPIELER:
            {
            init_screen(spieler_nr);
            tft.setCursor(35, 20);
            tft.println(str_spieler);

            String s2 = "Du bist ";
            tft.setCursor(55, 70);
            tft.setTextSize(3);
            tft.println(s2);
            tft.setCursor(68, 105);
            tft.println("dran!");
            break;
            }
        case WUERFEL:
            {
            // wenn der Spieler etwas machen kann, dann grüner Hintergrund, sonst rot        
            if(bewegung_erlaubt)
            {
                init_screen(spieler_nr, GREEN16);
            } else
            {
                init_screen(spieler_nr, RED16);
            }

            tft.setCursor(35, 20);
            tft.println(str_spieler);

            tft.setTextSize(7);
            tft.setCursor(105, 60);
            tft.println(wuerfel_augenzahl);
            break;
            }
        case SPIELER_HAT_GEWONNEN:
            {
            init_screen(spieler_nr);
            tft.setCursor(35, 20);
            tft.println(str_spieler);

            tft.setTextSize(3);
            tft.setCursor(48, 70);
            tft.println("Du hast");
            tft.setCursor(40, 105);
            tft.println("gewonnen!");
            break;
            }
        case RICHTIG:
            {
            init_screen(spieler_nr, GREEN16);
            tft.setTextSize(4);
            tft.setCursor(24, 60);
            tft.println("Korrekt!");
            break;
            }
        case FALSCH:
            {
            init_screen(spieler_nr, RED16);
            tft.setTextSize(4);
            tft.setCursor(32, 60);
            tft.println("Falsch!");
            break;
            }
        case NOCHMAL:
            {
            anzahl_aktive_buttons = 2;
            init_screen(0); // Richte Bildschirm auf Spieler 0 aus

            q_btn[0].initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "JA", 2); 
            q_btn[1].initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "NEIN", 2); 
            
            tft.setTextColor(BLACK);
            tft.setCursor(45, 68);
            tft.setTextSize(3);
            tft.println("Nochmal?");

            q_btn[0].drawButton(false);
            q_btn[1].drawButton(false);
            break;
            }
        case GOODBYE:
            {
            init_screen(0); // Spieler 0 ist der 'Game Master'

            tft.setCursor(40, 68);
            tft.setTextSize(3);
            tft.println("Goodbye!");
            break;
            }
        case MODUSWAHL:
            {
            anzahl_aktive_buttons = 2;
            init_screen(0); // Spieler 0 ist der 'Game Master'

            q_btn[0].initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "JA", 2); 
            q_btn[1].initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "NEIN", 2); 

            tft.fillRoundRect(10, 10, 220, 150, 10, CYAN);
            tft.setCursor(24, 68);
            tft.setTextColor(BLACK);
            tft.setTextSize(3);
            tft.println("Quizmodus?");

            q_btn[0].drawButton(false);
            q_btn[1].drawButton(false);
            break;
            }

        default:
            break;
    }
}

// Zeigt Frage und Antwortmöglichkeiten auf Bildschirm an
void zeige_quiz(int spieler_nr)
{
    anzahl_aktive_buttons = 4;
    Serial.println("Zeige_quiz...");
    switch (spieler_nr)
    {
        
        case 0: 
            Serial.println("\tSpieler 0...");
            tft.setRotation(spieler_nr);            //PORTRAIT
            tft.fillScreen(BLACK);

            q_btn[0].initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, q.q[0].c_str(), 2); // müssen beim Drehen wohl neu initiiert werden wegen den Koordinaten!
            q_btn[1].initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, q.q[1].c_str(), 2); // ACHTUNG: Es funktioniert mit const char*, ggf. prüfen, wenn Fehler auftritt
            q_btn[2].initButton(&tft,  60, 260, 100, 40, WHITE, CYAN, BLACK, q.q[2].c_str(), 2);
            q_btn[3].initButton(&tft, 180, 260, 100, 40, WHITE, CYAN, BLACK, q.q[3].c_str(), 2);

            tft.fillRoundRect(10, 10, 220, 150, 10, CYAN);
            tft.setCursor(20, 20);
            tft.setTextColor(BLACK);
            tft.setTextSize(3);
            tft.setCursor(45, 68);
            tft.println(q.q_text.c_str());
            break;

        case 1:
            Serial.println("\tSpieler 1...");
            tft.setRotation(spieler_nr);            //PORTRAIT
            tft.fillScreen(BLACK);
            q_btn[0].initButton(&tft,  80, 150, 140, 40, WHITE, CYAN, BLACK, q.q[0].c_str(), 2); // müssen beim Drehen wohl neu initiiert werden wegen den Koordinaten!
            q_btn[1].initButton(&tft, 240, 150, 140, 40, WHITE, CYAN, BLACK, q.q[1].c_str(), 2);
            q_btn[2].initButton(&tft,  80, 200, 140, 40, WHITE, CYAN, BLACK, q.q[2].c_str(), 2);
            q_btn[3].initButton(&tft, 240, 200, 140, 40, WHITE, CYAN, BLACK, q.q[3].c_str(), 2);

            tft.fillRoundRect(10, 10, 300, 100, 10, CYAN);
            tft.setTextColor(BLACK);
            tft.setCursor(20, 20);
            tft.setTextSize(3);
            tft.setCursor(45, 58);
            tft.println(q.q_text.c_str());
            break;

        case 2:
            Serial.println("\tSpieler 2...");
            tft.setRotation(spieler_nr);            //PORTRAIT
            tft.fillScreen(BLACK);
            q_btn[0].initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, q.q[0].c_str(), 2); 
            q_btn[1].initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, q.q[1].c_str(), 2);
            q_btn[2].initButton(&tft,  60, 260, 100, 40, WHITE, CYAN, BLACK, q.q[2].c_str(), 2);
            q_btn[3].initButton(&tft, 180, 260, 100, 40, WHITE, CYAN, BLACK, q.q[3].c_str(), 2);

            tft.fillRoundRect(10, 10, 220, 150, 10, CYAN);
            tft.setTextColor(BLACK);
            tft.setCursor(20, 20);
            tft.setTextSize(3);
            tft.setCursor(45, 68);
            tft.println(q.q_text.c_str());
            break;
        case 3:
            Serial.println("\tSpieler 3...");
            tft.setRotation(spieler_nr);            //PORTRAIT
            tft.fillScreen(BLACK);
            q_btn[0].initButton(&tft,  80, 150, 140, 40, WHITE, CYAN, BLACK, q.q[0].c_str(), 2);
            q_btn[1].initButton(&tft, 240, 150, 140, 40, WHITE, CYAN, BLACK, q.q[1].c_str(), 2);
            q_btn[2].initButton(&tft,  80, 200, 140, 40, WHITE, CYAN, BLACK, q.q[2].c_str(), 2);
            q_btn[3].initButton(&tft, 240, 200, 140, 40, WHITE, CYAN, BLACK, q.q[3].c_str(), 2);

            tft.fillRoundRect(10, 10, 300, 100, 10, CYAN);
            tft.setCursor(20, 20);
            tft.setTextColor(BLACK);
            tft.setTextSize(3);
            tft.setCursor(45, 68);
            tft.println(q.q_text.c_str());
            break;
    
        default:
            break;
    }

    q_btn[0].drawButton(false);
    q_btn[1].drawButton(false);
    q_btn[2].drawButton(false);
    q_btn[3].drawButton(false);  
}

int get_user_input()
{
    int nr_q_btn;
    bool button_released = false;
    do
    {
        bool down = Touch_getXY();
        for(int i = 0; i < anzahl_aktive_buttons; i++)
        {
            q_btn[i].press(down && q_btn[i].contains(pixel_x, pixel_y));
            if (q_btn[i].justPressed())
            {
                q_btn[i].drawButton(true);
                nr_q_btn = i + 1;
            }
        }

    } while (!(q_btn[0 % anzahl_aktive_buttons].justReleased() or q_btn[1 % anzahl_aktive_buttons].justReleased() or q_btn[2 % anzahl_aktive_buttons].justReleased() or q_btn[3 % anzahl_aktive_buttons].justReleased()));
    
    for(int i = 0; i < anzahl_aktive_buttons; i++)
    {
        q_btn[i].drawButton();
    }

    return nr_q_btn;
}

bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    int rotation = tft.getRotation();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        // Horizontal
        if(rotation == 0)
        {
            pixel_x = map(p.x, 925, 111, 0, tft.width()); //.kbv makes sense to me
            pixel_y = map(p.y, 66, 911, 0, tft.height());
        } else if(rotation == 2)
        {
            pixel_x = map(p.x, 111, 925, 0, tft.width()); //.kbv makes sense to me
            pixel_y = map(p.y, 911, 66, 0, tft.height());   
        } 
        // Vertikal
        else if (rotation == 1)
        {
            pixel_x = map(p.y, 66, 911, 0, tft.width()); //.kbv makes sense to me
            pixel_y = map(p.x, 111, 925, 0, tft.height());
        } else if (rotation == 3)
        {
            pixel_x = map(p.y, 911, 66, 0, tft.width()); //.kbv makes sense to me
            pixel_y = map(p.x, 925, 111, 0, tft.height());
        }
        
        
        
    }
    return pressed;
}

// Standardaufgaben, die vor jedem angezeigten Bildschirm erledigt werden
void init_screen(int spieler_nr)
{
    tft.setRotation(spieler_nr);
    tft.fillScreen(BLACK16);
    // ACHTUNG bei der größe des Rechtecks wird die Orientierung des Bildschirms nicht beachtet
    tft.fillRoundRect(10, 10, 220, 150, 10, CYAN);
    tft.setCursor(20, 20);
    tft.setTextColor(BLACK16);
    tft.setTextSize(2);
}

void init_screen(int spieler_nr, uint16_t background_color)
{
    tft.setRotation(spieler_nr);
    tft.fillScreen(BLACK16);
    tft.fillRoundRect(10, 10, 220, 150, 10, background_color);
    tft.setCursor(20, 20);
    tft.setTextColor(BLACK16);
    tft.setTextSize(2);
}

uint16_t get_identifier()
{
  
  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;
  
  }
  return identifier;
}