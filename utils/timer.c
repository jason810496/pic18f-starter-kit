#include "timer.h"
#include "settings.h"

void Timer2Initialize(OscFrequency osc_freq){
    if(TIMER2_PRESCALER == 4){
        T2CONbits.T2CKPS = 0b01; // prescaler = 4
    } else {
        T2CONbits.T2CKPS = 0b10; // prescaler = 16
    }
    T2CONbits.TMR2ON = 1;
}

int Timer2GetPrescaler(void){
    return TIMER2_PRESCALER;
}