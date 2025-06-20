#include "line_follow.h"

void line_follow()
{
    static int pre_error = 0;
    static int integral = 0;
    static bool stop = false;

    float error = 0;
    float output = 0;
    int status = 0;

    if (stop == true)
    {
        motor_l.chang_target(0);
        motor_r.chang_target(0);
        return;
    }

    infrared_1.read();
    status = infrared_1.get_status();
    switch (status)
    {
    case 0: // normal
        error = infrared_1.get_error();
        output = error * Kp + integral * Ki + (error - pre_error) * Kd;
        if (output > MAX_SPEED)
            output = MAX_SPEED;
        if (output < -MAX_SPEED)
            output = -MAX_SPEED;
        integral += error;
        pre_error = error;
        if (output > 0)
        {
            motor_l.chang_target(MAX_SPEED - 0.1 * output);
            motor_r.chang_target(-(MAX_SPEED - 0.1 * output) + output);
        }
        else
        {
            motor_l.chang_target((MAX_SPEED - 0.1 * output) + output);
            motor_r.chang_target(-(MAX_SPEED - 0.1 * output));
        }
        break;
    case 1: // left
        motor_l.chang_target(-MAX_SPEED);
        motor_r.chang_target(-MAX_SPEED / 2);
        break;
    case -1: // right
        motor_r.chang_target(MAX_SPEED / 2);
        motor_l.chang_target(MAX_SPEED);
        break;
    case 2: // stop
        motor_l.chang_target(0);
        motor_r.chang_target(0);
        stop = true;
        break;
    case -2: // out
        motor_l.chang_target(-MAX_SPEED / 2);
        motor_r.chang_target(MAX_SPEED / 2);
    default:
        break;
    }
}