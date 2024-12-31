/*
- variable resistor + 1 LED
- 3 states
    - turn variable resistor to change state from left to right
    - 1. LED frequency is 1s
    - 2. LED frequency is 0.5s
    - 3. LED frequency is 0.25s
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

void SystemInitialize(void){
    IntConfig int_config = {
        .button = INTERRUPT_HIGH,
        .adc = INTERRUPT_HIGH,
        .timer = INTERRUPT_NONE,
        .uart_tx = INTERRUPT_NONE,
        .uart_rx = INTERRUPT_LOW,
        .adc_justify = ADC_RIGHT_JUSTIFIED_RANGE_0_1023,
    };
    ComponentConfig component_config = {
        .prescaler = 16,
        .postscaler = 16,
        .timer_period_ms = 1000,
        .pwm_period_ms = MOTOR_PERIOD_MS,
    };

    OscillatorInitialize();
    ComponentInitialize(COMPONENT_LED | COMPONENT_BUTTON | COMPONENT_ADC,
                        &int_config, component_config);
//    PWMSetDutyCycle(MOTOR_NEG_90_DEG_US);
}

void main(void) {
    SystemInitialize();
    while(1){
        LedSet(1);
        switch(my_flag_1){
            case 1000:
                __delay_ms(40);
                break;
            case 500:
                __delay_ms(10);
                break;
            case 250:
                __delay_ms(1);
                break;
        }
        LedSet(0);
        switch(my_flag_1){
            case 1000:
                __delay_ms(40);
                break;
            case 500:
                __delay_ms(10);
                break;
            case 250:
                __delay_ms(1);
                break;
        }
    }
    return;
}

HIGH_PRIORITY_INTERRUPT(
    WITH_ADC_CXT(
        int val = AdcGetResult();
        val = val / (AdcGetMaxResult() / 3);
        switch(val){
            case 0:
                my_flag_1 = 1000;
                break;
            case 1:
                my_flag_1 = 500;
                break;
            case 2:
                my_flag_1 = 250;
                break;
        }
    )
)