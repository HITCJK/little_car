#include "infrared.h"

infrared::infrared(unsigned char pin1, unsigned char pin2, unsigned char pin3, unsigned char pin4, unsigned char pin5, unsigned char pin6, unsigned char pin7, unsigned char pin8) : pin{pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8}
{
}

void infrared::init()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(pin[i], INPUT);
    }
}

void infrared::read()
{
    for (int i = 0; i < 8; i++)
    {
        data[i] = digitalRead(pin[i]);
    }
}

unsigned char infrared::get_error()
{
    unsigned char error = 0;
    unsigned char num = 0;
    for (int i = 0; i < 8; i++)
    {
        if (data[i])
        {
            error += 2 * i;
            num++;
        }
    }
    return error / num - 7;
}