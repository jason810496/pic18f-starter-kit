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
    };
    ComponentConfig component_config = {
        .prescaler = 16,
        .postscaler = 16,
        .timer_period_ms = 1000,
        .pwm_period_ms = MOTOR_PERIOD_MS,
    };

    OscillatorInitialize();
    ComponentInitialize(COMPONENT_LED | COMPONENT_ADC,
                        &int_config, component_config);
}

void main(void) {
    SystemInitialize();
    double delay_duration = 1;
    while(1){
        LedSet(1);
        delay_duration = (double)my_flag_1 / (double)100;
        delay_if_not_changed(delay_duration, &my_flag_1);
        LedSet(0);
    }
    return;
}

HIGH_PRIORITY_INTERRUPT(
    WITH_ADC_CXT(
        int val = AdcGetResultHigh();
        int current_state = val / ( AdcGetMaxResult() / 3);
        switch(current_state){
            case 0:
                my_flag_1 = 100;
                break;
            case 1:
                my_flag_1 = 50;
                break;
            case 2:
                my_flag_1 = 25;
                break;
        }
    )
)