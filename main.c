/*
 * File:   main.c
 * Author: simon
 *
 * Created on December 23, 2024, 5:09 PM
 */

#include <xc.h>
#include "utils/settings.h"
#include "utils/led.h"
#include "utils/interrupt_manager.h"
#include "utils/adc.h"
#include "utils/ccp.h"
#include "utils/uart.h"
#include "utils/config.h"
#include "utils/timer.h"
#include "utils/context_manager.h"

#define MOTOR_PERIOD_MS 20
#define MOTOR_POS_90_DEG_US 2400
#define MOTOR_0_DEG_US 1450
#define MOTOR_NEG_90_DEG_US 500

int flag = 0;
int prev_adc_val = 0;

void SystemInitialize(void){
    IntConfig int_config = {
        .button = INTERRUPT_HIGH,
        .adc = INTERRUPT_HIGH,
        .timer = INTERRUPT_NONE,
        .uart_tx = INTERRUPT_NONE,
        .uart_rx = INTERRUPT_LOW,
    };
    ComponentConfig component_config = {
        .prescaler = 16,
        .postscaler = 16,
        .timer_period_ms = 1000,
        .pwm_period_ms = MOTOR_PERIOD_MS,
    };

    OscillatorInitialize();
    ComponentInitialize(COMPONENT_LED | COMPONENT_BUTTON | COMPONENT_PWM,
                        &int_config, component_config);
    PWMSetDutyCycle(MOTOR_NEG_90_DEG_US);
}

void main(void) {
    SystemInitialize();
    while(1);
    return;
}

void __interrupt(high_priority) HighIsr(void){
    if(BUTTON_IF){
        LedSet(LedValue() + 1);
        if(flag == 0){
            PWMSetDutyCycle(MOTOR_POS_90_DEG_US);
            flag = 1;
        }else{
            PWMSetDutyCycle(MOTOR_NEG_90_DEG_US);
            flag = 0;
        }
        ButtonIntDone();
    }
    if(ADC_IF){
        int val = AdcGetResultHigh();
        if(abs(val - prev_adc_val) > 10){
            LedSet(LedValue() + 1);
            prev_adc_val = val;
            __delay_ms(500);
        }

        AdcIntDone();
        AdcStartConversion();
    }
    if(Timer2IF){
        LedSet(LedValue() + 1);
        Timer2IntDone();
    }
}

void __interrupt(low_priority) LowIsr(void){
    if(RCIF){
        UartReceiveChar();
    }
}