//
// Created by bornf on 10.02.2019.
//
#ifndef UNTITLED_QUIZ_H
#define UNTITLED_QUIZ_H

#include "Arduino.h"

class Quiz {

    public:
        String q[4];
        String q_text;
        int button_nr_of_correct_question;

    // Methoden
    void create_random_question();
    bool antwort_ist_richtig(int button_nr_of_pushed_button);
};

#endif //UNTITLED_QUIZ_H