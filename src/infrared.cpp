#include "infrared.h"

void infrared_init()
{
    pinMode(INFRARED_PIN_1, INPUT);
    pinMode(INFRARED_PIN_2, INPUT);
    pinMode(INFRARED_PIN_3, INPUT);
    pinMode(INFRARED_PIN_4, INPUT);
    pinMode(INFRARED_PIN_5, INPUT);
    pinMode(INFRARED_PIN_6, INPUT);
    pinMode(INFRARED_PIN_7, INPUT);
    pinMode(INFRARED_PIN_8, INPUT);
}

void Infrared_read(bool infrared_data[])
{
    infrared_data[0] = digitalRead(INFRARED_PIN_1);
    infrared_data[1] = digitalRead(INFRARED_PIN_2);
    infrared_data[2] = digitalRead(INFRARED_PIN_3);
    infrared_data[3] = digitalRead(INFRARED_PIN_4);
    infrared_data[4] = digitalRead(INFRARED_PIN_5);
    infrared_data[5] = digitalRead(INFRARED_PIN_6);
    infrared_data[6] = digitalRead(INFRARED_PIN_7);
    infrared_data[7] = digitalRead(INFRARED_PIN_8);
}