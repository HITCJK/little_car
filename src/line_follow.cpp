#include "line_follow.h"

void line_follow()
{
    static int pre_error = 0;
    static int integral = 0;
    static bool stop = false;
    static float speed_l = 0;
    static float speed_r = 0;
    static int count_down = 0;

    float error = 0;
    float output = 0;
    int status = 0;

    if (stop == true)
    {
        return;
    }

    if (count_down > 0)
    {
        count_down--;
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
            speed_l = MAX_SPEED - abs(0.1 * output);
            speed_r = -(MAX_SPEED - abs(0.1 * output)) + output;
        }
        else
        {
            speed_l = (MAX_SPEED - abs(0.1 * output)) + output;
            speed_r = -(MAX_SPEED - abs(0.1 * output));
        }
        break;
    case 1: // left
        speed_l = 0;
        speed_r = -MAX_SPEED;
        break;
    case -1: // right
        speed_r = 0;
        speed_l = MAX_SPEED;
        break;
    case 2: // stop
        speed_l = 0;
        speed_r = 0;
        stop = true;
        break;
    case -2: // out
        if (speed_l + speed_r > 0)
        {
            speed_l = MAX_SPEED;
            speed_r = 2*MAX_SPEED;
        }
        else
        {
            speed_l = -2*MAX_SPEED;
            speed_r = -MAX_SPEED;
        }
        count_down = 8;
    default:
        break;
    }
    motor_l.chang_target(speed_l);
    motor_r.chang_target(speed_r);
}