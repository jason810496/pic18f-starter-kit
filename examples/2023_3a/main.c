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
    ComponentInitialize(COMPONENT_LED | COMPONENT_BUTTON | COMPONENT_ADC | COMPONENT_PWM,
                        &int_config, component_config);
}

void main(void) {
    SystemInitialize();
    while(1){
        MotorRotate(my_flag_1);
        delay(0.1);
    }
    return;
}

HIGH_PRIORITY_INTERRUPT(
    WITH_ADC_CXT(
        int val = AdcGetResultHigh();
        int current_state = val / ( AdcGetMaxResult() / 90);
        my_flag_1 = current_state;
    )
)