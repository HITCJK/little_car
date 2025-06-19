#include "line_follow.h"

void line_follow()
{
    static int pre_error = 0;
    static int integral = 0;

    infrared_1.read();
    int error = infrared_1.get_error();
    float output = error * Kp + integral * Ki + (error - pre_error) * Kd;
    if(output > MAX_SPEED) output = MAX_SPEED;
    if(output < -MAX_SPEED) output = -MAX_SPEED;
    integral += error;
    pre_error = error;
    integral += error;

    if (output > 0)
    {
        motor_l.chang_target(MAX_SPEED);
        motor_r.chang_target(-MAX_SPEED+output);
    }
    else
    {
        motor_l.chang_target(MAX_SPEED+output);
        motor_r.chang_target(-MAX_SPEED);
    }
}