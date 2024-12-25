#ifndef CCP_H
#define CCP_H

#include "settings.h"
#define CCP_IF PIR1bits.CCP1IF

void PWMInitialize();
void PWMSetPeriod(double period_ms);
void PWMSetDutyCycle(double duty_cycle_us);

#endif