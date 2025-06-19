#include <Arduino.h>
#include <MsTimer2.h>
#include <Servo.h>

#include "paremeter.h"
#include "device.h"

/* -------------------------------- MOTOR SET ------------------------------- */
void motor_l_get_encoder()
{
    motor_l.get_encoder();
}
void motor_r_get_encoder()
{
    motor_r.get_encoder();
}
void motor_control()
{
    motor_l.control();
    motor_r.control();
}
/* -------------------------------------------------------------------------- */

void setup()
{
    infrared_1.init(); // 初始化红外传感器

    TCCR1B = TCCR1B & B11111000 | B00000001;  //PWM 频率调节，设置 9、10 引脚的 PWM 输出频率为 31372Hz，适合于我们使用的电机 pinMode(PWML, OUTPUT);
    motor_l.init();
    motor_r.init();
    attachInterrupt(0, motor_l_get_encoder, CHANGE); // 中断 0 设置，对应 2 引脚
    attachInterrupt(1, motor_r_get_encoder, CHANGE); // 中断 1 设置，对应 3 引脚
    motor_l.chang_target(20);
    motor_r.chang_target(-20);
    MsTimer2::set(PERIOD, motor_control);          // 设定每隔 PERIOD 时间，执行一次 control
    MsTimer2::start(); // 开始时间

    Serial.begin(9600);
}

void loop()
{
}