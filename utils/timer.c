#include "timer.h"
#include "settings.h"

int Timer2Prescaler = 16;
int Timer2Postscaler = 16;

void Timer2Initialize(IntPriority priority, int prescaler, int postscaler, double period_ms){
    Timer2Prescaler = prescaler;
    Timer2Postscaler = postscaler;
    if(Timer2Prescaler == 4){
        T2CONbits.T2CKPS = 0b01; // prescaler = 4
    } else {
        T2CONbits.T2CKPS = 0b10; // prescaler = 16
    }

    T2CONbits.T2OUTPS = Timer2Postscaler - 1;

    if(priority != INTERRUPT_NONE){
        PIE1bits.TMR2IE = 1;
        IPR1bits.TMR2IP = priority;
    }

    PR2 = (period_ms * (_XTAL_FREQ / 1000)) / (4 * Timer2Prescaler * Timer2Postscaler) - 1;
    T2CONbits.TMR2ON = 1;
}

int Timer2GetPrescaler(void){
    return Timer2Prescaler;
}
