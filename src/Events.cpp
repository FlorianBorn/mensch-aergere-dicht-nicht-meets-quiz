//
// Created by bornf on 31.01.2019.
//

#include "common.h"
#include "Events.h"
#include "Feld.h"

// Variable für den durch einen Spieler gedrückten Knopf
int pushed_trellis_button_key;

//define a callback for key presses
TrellisCallback blink(keyEvent evt){
  // Check is the pad pressed?
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    trellis.setPixelColor(evt.bit.NUM, Wheel(map(evt.bit.NUM, 0, (X_DIM * Y_DIM), 0, 255))); //on rising
    Serial.print("Pushed Trellis Position: ");
    Serial.println(evt.bit.NUM);
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
  // or is the pad released?
    trellis.setPixelColor(evt.bit.NUM, 0); //off falling
  }

  // Turn on/off the neopixels!
  trellis.show();

  return 0;
}

//define a callback for key presses
TrellisCallback feld_gedrueckt(keyEvent evt){
  // Check is the pad pressed?
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    pushed_trellis_button_key = evt.bit.NUM;
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
  // or is the pad released?
  }

  // Turn on/off the neopixels!
  trellis.show();

  return 0;
}

// Warte darauf, dass ein Feld angetippt wird
int feld_auswahl()
{
    //activate all keys and set callbacks
    int trellis_position;
	pushed_trellis_button_key = -1;
    for(auto f: spielbrett){

        trellis_position = f.second->trellis_position;
        //Serial.print("activateKey: ");
        //Serial.println(trellis_position);
        trellis.activateKey(trellis_position, SEESAW_KEYPAD_EDGE_RISING);
        trellis.activateKey(trellis_position, SEESAW_KEYPAD_EDGE_FALLING);
        trellis.registerCallback(trellis_position, feld_gedrueckt);
    }

    while(true)
    {
        trellis.read();
		delay(20);
        if(pushed_trellis_button_key != -1)
        {
			Serial.println("trellis_button pushed...");
			for(auto f: spielbrett)
			{
				if(f.second->trellis_position == pushed_trellis_button_key)
				{
					Serial.println("\tInfo ueber gedruecktes Feld:");
					Serial.println("\t\tSpieler auf Feld:");
					if(f.second->figur == nullptr) 
                    {
                        Serial.println("\t\t\tkeiner");
                    }
					else 
					{
						Serial.print("\t\t\t");
						Serial.println(f.second->figur->spieler_nr);
						Serial.print("\t\tSpielerfigur Nr: ");
						Serial.println(f.second->figur->spielfigur_nr);
					}
					//Serial.println("\t\tSpieler auf Feld:");
					
				}
			}
          	pushed_trellis_button_key = -1;
        }
        
    }
    return 0;
}

void spielfeld_freigeben(Spieler * s)
{
	//activate all keys and set callbacks
    int trellis_position;
    int spieler_nr = s->spieler_nr;
	pushed_trellis_button_key = -1;
    for(auto f: spielbrett){

        trellis_position = f.second->trellis_position;
        //Serial.print("activateKey: ");
        //Serial.println(trellis_position);
        if(f.second->figur->spieler_nr == spieler_nr)
        {
            //Serial.print("spielbrett_freigeben: Spielbrett Key freigegeben: ");
            //Serial.println(f.first);
            trellis.activateKey(trellis_position, SEESAW_KEYPAD_EDGE_RISING);
            trellis.activateKey(trellis_position, SEESAW_KEYPAD_EDGE_FALLING);
            trellis.registerCallback(trellis_position, feld_gedrueckt);
        }
        
	}
}

void spielfeld_sperren()
{
    //deactivate all keys and unregister callbacks
    int trellis_position;
	pushed_trellis_button_key = -1;
    for(auto f: spielbrett){

        trellis_position = f.second->trellis_position;
        //Serial.print("activateKey: ");
        //Serial.println(trellis_position);
        trellis.activateKey(trellis_position, SEESAW_KEYPAD_EDGE_RISING, false);
        trellis.activateKey(trellis_position, SEESAW_KEYPAD_EDGE_FALLING, false);
        trellis.unregisterCallback(trellis_position);
    }
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  	if(WheelPos < 85) {
   		//return t_array[0][0].pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        Serial.println(t_array[0][0].pixels.Color(WheelPos * 1, 85 - WheelPos * 1, 0));
        return t_array[0][0].pixels.Color(WheelPos * 1, 85 - WheelPos * 1, 0);
  	} else if(WheelPos < 170) {
   		WheelPos -= 85;
        Serial.println(t_array[0][0].pixels.Color(WheelPos * 1, 85 - WheelPos * 1, 0));
   		//return t_array[0][0].pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
        return t_array[0][0].pixels.Color(85 - WheelPos * 1, 0, WheelPos * 1);
  	} else {
   		WheelPos -= 170;
        Serial.println(t_array[0][0].pixels.Color(WheelPos * 1, 85 - WheelPos * 1, 0));
   		//return t_array[0][0].pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
        return t_array[0][0].pixels.Color(85 - WheelPos * 1, 0, WheelPos * 1);
  	}
  	return 0;
}


// Helfer

// gib die Figur, die auf einem Feld steht zurück (oder nullptr)
Spielfigur* get_spielfigur_from_trellis_key(int trellis_key)
{
    for(auto f: spielbrett)
    {
        if(f.second->trellis_position == pushed_trellis_button_key)
        {
            return f.second->figur;
        }
    }
    return nullptr;
}

// Zeige Info über gedrücktes Feld
void print_info(int trellis_key)
{
    for(auto f: spielbrett)
    {
        if(f.second->trellis_position == trellis_key)
        {
            Serial.println("\tInfo ueber gedruecktes Feld:");
            Serial.println("\t\tSpieler auf Feld:");
            if(f.second->figur == nullptr)
            {
                Serial.println("\t\t\tkeiner");
            } 
            else 
            {
                Serial.print("\t\t\t");
                Serial.println(f.second->figur->spieler_nr);
                Serial.print("\t\tSpielerfigur Nr: ");
                Serial.println(f.second->figur->spielfigur_nr);
            }
        }
    }

    
}

// Zeigt alle durchlaufend alle LEDs
void show_animation()
{
    //do a little animation to show we're on
    for(int j = 0; j<1; j++) // nur für einen Spieler leuchten
    {
        for (uint16_t i=0; i< (X_DIM * Y_DIM); i++) {
            #if TRELLIS == 8
                if(i == 52 or i == 64 or i == 76 or i == 88) i += 4;
            #endif
            trellis.setPixelColor(i, Wheel(map(i, 0, (X_DIM * Y_DIM), 0, 255)));
            //trellis.setPixelColor(i, transform_color_array_to_single_value(SPIELER_COLOR[j]));
            trellis.show();
            delay(20);
        }
        for (uint16_t i=0; i< (X_DIM * Y_DIM); i++) {
            //if(i == 4 or i == 8 or i == 12 or i == 16) i += 4;
            #if TRELLIS == 8
                if(i == 52 or i == 64 or i == 76 or i == 88) i += 4;
            #endif
            trellis.setPixelColor(i, 0x000000);
            trellis.show();
            delay(20);
        }
    }
}