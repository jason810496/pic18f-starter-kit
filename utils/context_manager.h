#ifndef CONTEXT_MANAGER_H
#define CONTEXT_MANAGER_H

#include "utils/interrupt_manager.h"
#include "utils/adc.h"
#include "utils/timer.h"
#include "utils/uart.h"

#define BASE_CONTEXT_MANAGER(trigger_flag,callback,code_block) \
    if(trigger_flag){ \
        code_block \
        callback(); \
        return; \
    }

#define WITH_BUTTON_CXT(code_block) \
    BASE_CONTEXT_MANAGER(BUTTON_IF,ButtonIntDone,code_block)

#define WITH_ADC_CXT(code_block) \
    if(ADC_IF){ \
        code_block \
        AdcIntDone(); \
        AdcStartConversion(); \
        return; \
    }

#define WITH_TIMER2_CXT(code_block) \
    BASE_CONTEXT_MANAGER(Timer2IF,Timer2IntDone,code_block)

#define WITH_UART_CXT(code_block) \
    BASE_CONTEXT_MANAGER(RCIF,UartIntDone,code_block)


#define HIGH_PRIORITY_INTERRUPT(code_block) \
    void __interrupt(high_priority) HighIsr(void){ \
        code_block \
        return; \
    }

#define LOW_PRIORITY_INTERRUPT(code_block) \
    void __interrupt(low_priority) LowIsr(void){ \
        code_block \
        return; \
    }

/*

Example usage:

HIGH_PRIORITY_INTERRUPT(
    WITH_BUTTON_CXT(
        LedSet(LedValue() + 1);
        if(flag == 0){
            PWMSetDutyCycle(MOTOR_POS_90_DEG_US);
            flag = 1;
        }else{
            PWMSetDutyCycle(MOTOR_NEG_90_DEG_US);
            flag = 0;
        }
    )
    WITH_ADC_CXT(
        int val = AdcGetResultHigh();
        if(abs(val - prev_adc_val) > 10){
            LedSet(LedValue() + 1);
            prev_adc_val = val;
            __delay_ms(500);
        }
        AdcStartConversion();
    )
    WITH_TIMER2_CXT(
        // Timer2 code block
    )
)

*/

#endif
