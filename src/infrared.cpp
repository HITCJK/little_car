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

int infrared::get_status()
{
    int num = 0;
    int sum = 0;
    for (int i = 0; i < 8; i++)
    {
        if (data[i])
        {
            sum += i;
            num++;
        }
    }
    if (num == 8)
    {
        return 2; // destination
    }
    if (num < 3)
    {
        return 0; // normal
    }
    sum /= num;
    if (sum < 3.5)
    {
        return -1; // left
    }
    else
    {
        return 1; // right
    }
}

float infrared::get_error()
{
    int error = 0;
    for (int i = 0; i < 8; i++)
    {
        if (data[i])
        {
            error += -((2 * i - 7) / abs(2 * i - 7)) * pow(2, abs(2 * i - 7) / 2);
        }
    }
    return error;
}