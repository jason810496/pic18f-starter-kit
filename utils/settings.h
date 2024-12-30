#ifndef SETTING_H
#define SETTING_H
#include <xc.h>
#include "config.h"

#if _XTAL_FREQ == 31000
#define IRCF_VALUE 0
#elif _XTAL_FREQ == 125000
#define IRCF_VALUE 1
#elif _XTAL_FREQ == 250000
#define IRCF_VALUE 2
#elif _XTAL_FREQ == 500000
#define IRCF_VALUE 3
#elif _XTAL_FREQ == 1000000
#define IRCF_VALUE 4
#elif _XTAL_FREQ == 2000000
#define IRCF_VALUE 5
#elif _XTAL_FREQ == 4000000
#define IRCF_VALUE 6
#elif _XTAL_FREQ == 8000000
#define IRCF_VALUE 7
#else
#define IRCF_VALUE 6
#endif

typedef enum {
    ADC_LEFT_JUSTIFIED_RANGE_0_255,
    ADC_RIGHT_JUSTIFIED_RANGE_0_1023,
} AdcJustify;

typedef enum {
    INTERRUPT_LOW,
    INTERRUPT_HIGH,
    INTERRUPT_NONE
} IntPriority;

typedef struct {
    IntPriority button;
    IntPriority adc;
    IntPriority timer;
    IntPriority uart_tx;
    IntPriority uart_rx;
    AdcJustify adc_justify;
} IntConfig;

typedef struct {
    int prescaler;
    int postscaler;
    int timer_period_ms;
    int pwm_period_ms;
} ComponentConfig;

// Define an enumeration for frequency selection
typedef enum {
    FREQ_31KHZ,
    FREQ_125KHZ,
    FREQ_250KHZ,
    FREQ_500KHZ,
    FREQ_1MHZ,
    FREQ_2MHZ,
    FREQ_4MHZ,
    FREQ_8MHZ
} OscFrequency;

typedef enum {
    COMPONENT_NONE          = 0x00,
    COMPONENT_LED          = 0x01,
    COMPONENT_BUTTON       = 0x02,
    COMPONENT_ADC         = 0x04,
    COMPONENT_PWM         = 0x08,
    COMPONENT_UART        = 0x10,
    COMPONENT_TIMER       = 0x20,
    COMPONENT_ALL         = 0x3F
} SystemComponents;

typedef enum {
    UART_BAUD_300,
    UART_BAUD_1200,
    UART_BAUD_2400,
    UART_BAUD_9600,
    UART_BAUD_19200,
    UART_BAUD_57600,
    UART_BAUD_115200
} UartBaudRate;

void ComponentInitialize(SystemComponents components, IntConfig *int_config, ComponentConfig component_config);
void OscillatorInitialize();
#endif