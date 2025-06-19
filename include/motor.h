#include <Arduino.h>
#include "paremeter.h"

class motor
{
private:
    unsigned char encoder_a;
    unsigned char encoder_b;
    unsigned char pwm;
    unsigned char dir;
    volatile float encoder_val = 0;
    volatile float target = 0;

    volatile float eI = 0, eII = 0, eIII = 0, u = 0; // for PID control

    int pidcontrol(float target, float current);

public:
    motor(unsigned char encoder_a, unsigned char encoder_b, unsigned char pwm, unsigned char dir, float encoder_val);
    void init();
    void get_encoder();
    void control();
    void chang_target(float target);
};