#include "line_follow.h"

void line_follow()
{
    static int pre_error = 0;
    static int integral = 0;

    infrared_1.read();
    int error = infrared_1.get_error();
    if (error == 8)
    {
        motor_l.chang_target(0);
        motor_r.chang_target(0);
        return;
    }
    float output = error * Kp + integral * Ki + (error - pre_error) * Kd;
    if (output > MAX_SPEED)
        output = MAX_SPEED;
    if (output < -MAX_SPEED)
        output = -MAX_SPEED;
    integral += error;
    pre_error = error;
    integral += error;

    Serial.print("error: ");
    Serial.println(error);
    Serial.print("output: ");
    Serial.println(output);

    if (output > 0)
    {
        motor_l.chang_target(MAX_SPEED);
        motor_r.chang_target(-MAX_SPEED + output);

        Serial.print("l_speed: ");
        Serial.println(MAX_SPEED);
        Serial.print("r_speed: ");
        Serial.println(-MAX_SPEED + output);

    }
    else
    {
        motor_l.chang_target(MAX_SPEED + output);
        motor_r.chang_target(-MAX_SPEED);

        Serial.print("l_speed: ");
        Serial.println(MAX_SPEED + output);
        Serial.print("r_speed: ");
        Serial.println(-MAX_SPEED);

    }
}