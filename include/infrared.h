#include <Arduino.h>
#include "paremeter.h"

#ifndef INFRARED_H
#define INFRARED_H

class infrared
{
private:
    volatile bool data[8];
    unsigned char pin[8];

public:
    infrared(unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4, unsigned char pin5, unsigned char pin6, unsigned char pin7, unsigned char pin8);
    void init();
    void read();
    int get_status();
    float get_error();
};

#endif