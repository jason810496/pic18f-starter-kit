#ifndef TIMER_H
#define TIMER_H

#include "settings.h"
#include "config.h"

#if _XTAL_FREQ <= 1000000
#define TIMER2_PRESCALER 4
#else
#define TIMER2_PRESCALER 16
#endif

void Timer2Initialize();
void Timer2EnableInterrupt(IntPriority priority);

#endif