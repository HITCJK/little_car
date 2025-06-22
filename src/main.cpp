#include <Arduino.h>
#include <MsTimer2.h>
#include <Servo.h>

#include "paremeter.h"
#include "device.h"
#include "line_follow.h"

Servo myservo1;
Servo myservo2;

#define  SERVO_PIN1  9
#define  SERVO_PIN2  8

unsigned  int  PWM1=0;
unsigned  int  PWM2=0;

void singleServoControl(){
int i=0;
if(jud==0)
{
PWM1=50;
PWM2=1450;
myservo1.writeMicroseconds(50);
delay(1000);
for(i=0;i<20;i++){//舵机从50状态转到2450,每次增加50
PWM2=PWM2+50;
myservo2.writeMicroseconds(PWM2);
delay(30);      //给舵机写入 PWM//延时10ms 让舵机转到指定位置
}
delay(800);
for(i=0;i<17;i++)
{
  PWM1=PWM1+50;
  myservo1.writeMicroseconds(PWM1);
  delay(30);
}
delay(800);
for(i=19;i>=0;i--){
PWM2=PWM2-50;
myservo2.writeMicroseconds(PWM2);
delay(30);
}
jud=1;
}

else if(jud==2)
{
PWM1=900;
PWM2=1450;
myservo1.writeMicroseconds(900);
delay(1000);
for(i=0;i<20;i++){//舵机从50状态转到2450,每次增加50
PWM2=PWM2+50;
myservo2.writeMicroseconds(PWM2);
delay(30);      //给舵机写入 PWM//延时10ms 让舵机转到指定位置
}
delay(800);
for(i=0;i<17;i++)
{
  PWM1=PWM1-50;
  myservo1.writeMicroseconds(PWM1);
  delay(30);
}
delay(800);
for(i=19;i>=0;i--){
PWM2=PWM2-50;
myservo2.writeMicroseconds(PWM2);
delay(30);
}
jud=1;
}
}

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
    // static int count = 0;
    // count = (count + 1) % 5;
    // if (count == 0)
        line_follow();
    motor_l.control();
    motor_r.control();
}
/* -------------------------------------------------------------------------- */

void setup()
{
    infrared_1.init(); // 初始化红外传感器

    TCCR1B = TCCR1B & B11111000 | B00000001; // PWM 频率调节，设置 9、10 引脚的 PWM 输出频率为 31372Hz，适合于我们使用的电机 pinMode(PWML, OUTPUT);
    motor_l.init();
    motor_r.init();
    attachInterrupt(0, motor_l_get_encoder, CHANGE); // 中断 0 设置，对应 2 引脚
    attachInterrupt(1, motor_r_get_encoder, CHANGE); // 中断 1 设置，对应 3 引脚

    myservo1.attach(SERVO_PIN1);
    myservo2.attach(SERVO_PIN2);
    singleServoControl();

    MsTimer2::set(PERIOD, motor_control); // 设定每隔 PERIOD 时间，执行一次 control
    MsTimer2::start();                    // 开始时间

    Serial.begin(9600);
}

void loop()
{
    singleServoControl();
}