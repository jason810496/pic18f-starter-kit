#include "ccp.h"
#include "timer.h"
#include "config.h"

void PWMInitialize(){
    TRISCbits.TRISC2 = 0;
    CCP1CONbits.CCP1M = 0b1100;
    Timer2Initialize();
}

void PWMSetPeriod(double period_ms){
    // Set up PR2, CCP to decide PWM period and Duty Cycle
    /** 
     * PWM period
     * = (PR2 + 1) * 4 * Tosc * (TMR2 prescaler)
     */
    int prescaler = Timer2GetPrescaler();
    PR2 = (period_ms * _XTAL_FREQ / 1000) / (4 * prescaler) - 1;
}

void PWMSetDutyCycle(double duty_cycle_us){
    /**
     * Duty cycle
     * = (CCPR1L:CCP1CON<5:4>) * Tosc * (TMR2 prescaler)
     * = (0x0b*4 + 0b01) * 8µs * 4
     * = 0.00144s ~= 1450µs
     */
    int prescaler = Timer2GetPrescaler();
    long long val = (duty_cycle_us * _XTAL_FREQ / 1000000) / prescaler;
    CCPR1L = (val >> 2) & 0xFF;
    CCP1CONbits.DC1B = (val & 0x03);
}