//
// Created by bornf on 24.01.2019.
//

#include "Feld.h"
#include "common.h"

using namespace std;

// Konstrukor
Feld::Feld()
{
    set_trellis_position(-1);
    set_default_color(DEFAULT_COLOR);
    set_figur(nullptr);
}

Feld::Feld(int trellis_position, int spielfeld_position, char farbe[])
{
    set_trellis_position(trellis_position);
    set_spielfeld_position(spielfeld_position);
    set_default_color(farbe);
    set_figur(nullptr);
}

void Feld::set_default_color(char farbe[])
{
    this->farbe[0] = farbe[0];
    this->farbe[1] = farbe[1];
    this->farbe[2] = farbe[2];
    trellis.setPixelColor(this->trellis_position, transform_color_array_to_single_value(this->farbe));
    trellis.show();
}

void Feld::change_color()
{
    
    if(this->figur == nullptr)
    {
        change_color(this->farbe);
    } else
    {
        change_color(this->figur->farbe);
    }
    
}

void Feld::change_color(char farbe[])
{
    this->temp_farbe[0] = farbe[0];
    this->temp_farbe[1] = farbe[1];
    this->temp_farbe[2] = farbe[2];
    trellis.setPixelColor(this->trellis_position, transform_color_array_to_single_value(farbe));
    trellis.show();
}

void Feld::set_trellis_position(int trellis_position)
{
    this->trellis_position = trellis_position;
}

void Feld::set_spielfeld_position(int spielfeld_position)
{
    this->spielfeld_position = spielfeld_position;
}

// Wird gesetzt, wenn eine Figur auf dem Feld steht
void Feld::set_figur(Spielfigur * figur)
{
    this->figur = figur;
}

//Helfer
void Feld::print_info()
{
    Serial.println("Feld Info...");
    Serial.print("\ttrellis_position: ");
    Serial.println(this->trellis_position);
    Serial.print("\tspielfeld_position: ");
    Serial.println(this->spielfeld_position);
    Serial.print("\tFigur auf Feld: ");
    Serial.println(this->figur == nullptr? "keine": (String)this->figur->spieler_nr);
}
