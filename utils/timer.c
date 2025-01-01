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


void delay_if_not_changed(double period_seconds,int *watch_ptr){
    int period_ms = period_seconds * 1000;
    int original_value = *watch_ptr;
    // 10ms as a chunk
    int chunks = period_ms / 10;
    for(int i = 0; i < chunks; i++){
        if(*watch_ptr != original_value){
            return;
        }
        __delay_ms(10);
    }
}

void delay(double period_seconds){
    int period_ms = period_seconds * 1000;
    // 10ms as a chunk
    int chunks = period_ms / 10;
    for(int i = 0; i < chunks; i++){
        __delay_ms(10);
    }
}