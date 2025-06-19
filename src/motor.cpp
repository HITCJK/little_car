#include "motor.h"

motor::motor(unsigned char encoder_a, unsigned char encoder_b, unsigned char pwm, unsigned char dir, float encoder_val)
    : encoder_a(encoder_a), encoder_b(encoder_b), pwm(pwm), dir(dir), encoder_val(encoder_val)
{
}

void motor::init()
{
    pinMode(encoder_a, INPUT);
    pinMode(encoder_b, INPUT);
    pinMode(pwm, OUTPUT);
    pinMode(dir, OUTPUT);
}

void motor::get_encoder()
{
    if (digitalRead(encoder_a) == LOW)
    {
        if (digitalRead(encoder_b) == LOW)
        {
            encoder_val--;
        }
        else
        {
            encoder_val++;
        }
    }
    else
    {
        if (digitalRead(encoder_b) == LOW)
        {
            encoder_val++;
        }
        else
        {
            encoder_val--;
        }
    }
}

int motor::pidcontrol(float target, float current)
{
    eI = target - current;
    float q0 = kp * (1 + PERIOD / TI + TD / PERIOD);
    float q1 = -kp * (1 + 2 * TD / PERIOD);
    float q2 = kp * TD / PERIOD;
    u = u + q0 * eI + q1 * eII + q2 * eIII;
    eIII = eII;
    eII = eI;
    if (u > 255)
    {
        u = 255;
    }
    else if (u <= -255)
    {
        u = -255;
    }
    return (int)u;
}

void motor::control()
{
    float velocity= (encoder_val / 780.0) * 3.1415 * 2.0 * (1000 / PERIOD); // 计算轮子转动速度（弧度制的速度，2πRn）
    int output = pidcontrol(target, velocity);
    if (output > 0)
    {
        digitalWrite(dir, LOW);
        analogWrite(pwm, output);
    }
    else
    {
        digitalWrite(dir, HIGH);
        analogWrite(pwm, abs(output));
    }
    encoder_val = 0;
}

void motor::chang_target(float new_target)
{
    target = new_target;
    eI = 0;
    eII = 0;
    eIII = 0;
    u = 0; // Reset PID control variables
}