#include <Arduino.h>
#include "paremeter.h"

class infrared
{
private:
    bool data[8];
    unsigned char pin[8];

public:
    infrared(unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4, unsigned char pin5, unsigned char pin6, unsigned char pin7, unsigned char pin8);
    void init();
    void read();
    unsigned char get_error();
};