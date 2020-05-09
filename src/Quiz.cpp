//
// Created by bornf on 10.02.2019.
//
#include "Quiz.h"
#include "ArduinoSTL.h"

#define ADDITION 1
#define SUBTRAKTION 2
#define MULTIPLIKATION 3
#define DIVISION 4
#define DELTA 5

void Quiz::create_random_question()
{
    int operation = random(1,5); // +, -, *, /
    int lval;
    int rval;
    int vals[4];
    int result;

    switch (operation)
    {
        case ADDITION:
            lval = random(0,200);
            rval = random(0,200);
            vals[0] = lval + rval;
            do
            {
                vals[1] = (lval + random(-DELTA,DELTA)) + (rval + random(-DELTA,DELTA));
            } while (vals[1] == vals[0]);
            do
            {
                vals[2] = (lval + random(-DELTA,DELTA)) + (rval + random(-DELTA,DELTA));
            } while (vals[2] == vals[0]);
            do
            {
                vals[3] = (lval + random(-DELTA,DELTA)) + (rval + random(-DELTA,DELTA));
            } while (vals[3] == vals[0]);
            
            this->q_text = String((String)lval + " + " + (String)rval + "?");

            break;
        case SUBTRAKTION:
            lval = random(0,200);
            rval = random(0,200);
            vals[0] = lval - rval;
            do
            {
                vals[1] = (lval + random(-DELTA,DELTA)) - (rval + random(-DELTA,DELTA));
            } while (vals[1] == vals[0]);
            do
            {
                vals[2] = (lval + random(-DELTA,DELTA)) - (rval + random(-DELTA,DELTA));
            } while (vals[2] == vals[0]);
            do
            {
                vals[3] = (lval + random(-DELTA,DELTA)) - (rval + random(-DELTA,DELTA));
            } while (vals[3] == vals[0]);

            this->q_text = String((String)lval + " - " + (String)rval + "?");
            break;
        case MULTIPLIKATION:
            lval = random(0,40);
            rval = random(0,40);
            vals[0] = lval * rval;
            do
            {
                vals[1] = (lval + random(-DELTA,DELTA)) * (rval + random(-DELTA,DELTA));
            } while (vals[1] == vals[0]);
            do
            {
                vals[2] = (lval + random(-DELTA,DELTA)) * (rval + random(-DELTA,DELTA));
            } while (vals[2] == vals[0]);
            do
            {
                vals[3] = (lval + random(-DELTA,DELTA)) * (rval + random(-DELTA,DELTA));
            } while (vals[3] == vals[0]);

            this->q_text = String((String)lval + " x " + (String)rval + "?");

            break;
        case DIVISION:
            {
            int dividend;
            lval = random(0,40);
            rval = random(0,40);
            dividend = lval * rval; // Ziel: es sollen bei der Aufgabe nur ganze Zahlen als Ergebnis rauskommen
            vals[0] = rval; // (dividend / lval) == rval --> als Ergebnis muss rval rauskommen

            do
            {
                vals[1] = rval + random(-DELTA,DELTA);
            } while (vals[1] == vals[0]);
            do
            {
                vals[2] = rval + random(-DELTA,DELTA);
            } while (vals[2] == vals[0]);
            do
            {
                vals[3] = rval + random(-DELTA,DELTA);
            } while (vals[3] == vals[0]);

            this->q_text = String((String)dividend + " : " + (String)lval + "?");

            break;
            }
            
    
        default:
            break;
    }

    result = vals[0]; // Speichere das richtige Ergebnis
    std::random_shuffle(vals, vals + 3);
    // hole Index der richtigen Frage
    for(int i = 0; i < 4; i++)
    {
        if(vals[i] == result)
        {
            // das richtige Ergebnis wird auf Button Nr i gezeigt
            this->button_nr_of_correct_question = i + 1; // ACHTUNG: Die Buttons beginnen bei 1
        }
    }

    // Speichere die gemischten, möglichen Ergebnisse 
    this->q[0] = String(vals[0]);
    this->q[1] = String(vals[1]);
    this->q[2] = String(vals[2]);
    this->q[3] = String(vals[3]); 
    
}

bool Quiz::antwort_ist_richtig(int button_nr_of_pushed_button)
{
    return button_nr_of_pushed_button == this->button_nr_of_correct_question;
}