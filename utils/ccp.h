#ifndef CCP_H
#define CCP_H

#include "settings.h"
#define CCP_IF PIR1bits.CCP1IF
#define PWM_MOTOR_STRIDE 15

void PWMInitialize(double period_ms);
void PWMSetPeriod(double period_ms);
void PWMSetDutyCycle(double duty_cycle_us);
double PWMGetDutyCycle();
void MotorRotate(int angle);

extern int motor_current_angle;
#endif