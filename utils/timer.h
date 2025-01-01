#ifndef TIMER_H
#define TIMER_H

#include "settings.h"
#include "config.h"

#define Timer2IF (PIR1bits.TMR2IF && PIE1bits.TMR2IE)
#define Timer2IntDone() PIR1bits.TMR2IF = 0

void Timer2Initialize(IntPriority priority, int prescaler, int postscaler, double period_ms);
int Timer2GetPrescaler(void);
void delay_if_not_changed(double period_seconds,int *watch_ptr);
void delay(double period_seconds);

#endif