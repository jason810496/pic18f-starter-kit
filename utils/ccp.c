#include "ccp.h"
#include "timer.h"
#include "config.h"

double PWMDutyCycle = 0;
int motor_current_angle = 0;

void PWMInitialize(double period_ms){
    TRISCbits.TRISC2 = 0;
    CCP1CONbits.CCP1M = 0b1100;
    if(_XTAL_FREQ <= 1000000){
        Timer2Initialize(INTERRUPT_NONE, 4, 16, 0);
    } else {
        Timer2Initialize(INTERRUPT_NONE, 16, 16, 0);
    }
    PWMSetPeriod(period_ms);
}

void PWMSetPeriod(double period_ms){
    // Set up PR2, CCP to decide PWM period and Duty Cycle
    /** 
     * PWM period
     * = (PR2 + 1) * 4 * Tosc * (TMR2 prescaler)
     */
    int prescaler = Timer2GetPrescaler();
    PR2 = (period_ms * (_XTAL_FREQ / 1000)) / (4 * prescaler) - 1;
}

void PWMSetDutyCycle(double duty_cycle_us){
    /**
     * Duty cycle
     * = (CCPR1L:CCP1CON<5:4>) * Tosc * (TMR2 prescaler)
     * = (0x0b*4 + 0b01) * 8µs * 4
     * = 0.00144s ~= 1450µs
     */
    PWMDutyCycle = duty_cycle_us;
    int prescaler = Timer2GetPrescaler();
    long long val = (PWMDutyCycle * _XTAL_FREQ / 1000000) / prescaler;
    CCPR1L = (val >> 2) & 0xFF;
    CCP1CONbits.DC1B = (val & 0x03);
}

double PWMGetDutyCycle(){
    return PWMDutyCycle;
}

void MotorRotate(int angle){
    int current = (CCPR1L << 2) + CCP1CONbits.DC1B;
    int target = (int)((500 + (double)(angle + 90) / 180 * (2400 - 500)) / 8 / 4) * 8; // angle to pwn
    
    while(current != target){
        if(current < target) current++;
        else current--;
        
        CCPR1L = (current >> 2);
        CCP1CONbits.DC1B = (current & 0b11);
        __delay_ms(1);
    }
    motor_current_angle = angle;
}