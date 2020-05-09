#include "Adafruit_NeoTrellis.h"
#include "common.h"
#include "Spiel.h"
#include "Events.h"
#include "screen.h"

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(97)); // ACHTUNG: Je nach MC muss der Pin angepasst werden (https://www.cs.ou.edu/~fagg/classes/general/atmel/ArduinoMega.pdf)

    // initialisiere TFT
    tft.reset();
    tft.begin(get_identifier());

    // aktiviere NeoTrellis
    if (!trellis.begin()) {
        Serial.println("Could not start trellis, check wiring?");
        while(1);
    } else {
        Serial.println("NeoPixel Trellis started");
    }

    // zeige LED-Animation
    show_animation();
    
    // Hauptprogramm
    bool nochmal_spielen = false;
    do
    {
        Spiel * s = new Spiel();
        s->setup();
        s->spielen();

        zeige_meldung(NOCHMAL);
        (get_user_input() == 1)? (nochmal_spielen = true): (nochmal_spielen = false);
    } while (nochmal_spielen);
    zeige_meldung(GOODBYE);
 

  // das Spiel ist vorbei, es passiert nichts mehr
  // bei Knopfdruck leuchte einfach bunt
  for(int i = 0; i < X_DIM*Y_DIM; i++)
  {
    #if TRELLIS == 8
      if(i == 52 or i == 64 or i == 76 or i == 88) i += 4;
    #endif
    
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);

  }
}

void loop() {
  trellis.read();  // interrupt management does all the work! :)
  delay(20); //the trellis has a resolution of around 60hz
}



