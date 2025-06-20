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

int infrared::get_error()
{
    int error = 0;
    int num = 0;
    for (int i = 0; i < 8; i++)
    {
        if (data[i])
        {
            error += 2 * i;
            num++;
        }
    }
    if(num == 0)
    {
        return 0; // No line detected
    }
    if(num == 8)
    {
        return 8; // All sensors detect the line
    }
    return -(error / num - 7);
}