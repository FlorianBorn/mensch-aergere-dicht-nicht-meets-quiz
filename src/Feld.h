//
// Created by bornf on 24.01.2019.
//

#ifndef UNTITLED_FELD_H
#define UNTITLED_FELD_H

//class Spielfigur;
#include "Spielfigur.h"

class Feld {

public:
    int trellis_position; // Koordinate auf dem Spielbrett (d.h. Nummer des NeoPixels)
    int spielfeld_position;
    char farbe[3];
    char temp_farbe[3];
    Spielfigur * figur; // Zeiger auf die Spielfigur, die gerade auf dem Feld steht

    Feld();
    Feld(int trellis_position, int spielfeld_position, char farbe[]);

    void set_default_color(char farbe[]); // setzt eine Standardfarbe für ein Feld-Obj
    void change_color(); // ändert die Farbe auf die Standard-Feldfarbe
    void change_color(char farbe[]); // ändert die Farbe des korrospondierenden Trellis-Pixel
    void set_trellis_position(int pos);
    void set_spielfeld_position(int pos);
    void set_figur(Spielfigur * f);

    //Helfer
    void print_info();
};


#endif //UNTITLED_FELD_H
