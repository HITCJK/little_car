/* ----------------------------- INFRARED_SENSOR ---------------------------- */

#define INFRARED_PIN_1 (A0)
#define INFRARED_PIN_2 (A1)
#define INFRARED_PIN_3 (A2)
#define INFRARED_PIN_4 (A3)
#define INFRARED_PIN_4 (A3)
#define INFRARED_PIN_5 (A4)
#define INFRARED_PIN_6 (A5)
#define INFRARED_PIN_7 (A6)
#define INFRARED_PIN_8 (A7)

/* -------------------------------------------------------------------------- */

/* ---------------------------------- MOTOR --------------------------------- */

#define ENCODER_A_L (2) // 电机 1 的编码器 A 项接 Arduino 的 2 中断口，用于编码器计数
#define ENCODER_B_L (4)
#define ENCODER_A_R (3) // 电机 2 的编码器 A 项接 Arduino 的 3 中断口，用于编码器计数
#define ENCODER_B_R (5)
#define PWML (11) // 用于电机 1 的 PWM 输出，调节电机速度
#define DIR_L (6) // 用于电机 1 的转动方向控制
#define PWMR (12) // 用于电机 2 的 PWM 输出，调节电机速度
#define DIR_R (7)  // 用于电机 2 的转动方向控制

#define PERIOD (20) // PID控制周期，单位为 ms
#define kp (6)
#define TI (100)
#define TD (15)

/* -------------------------------------------------------------------------- */