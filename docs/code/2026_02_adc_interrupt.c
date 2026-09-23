#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>

#define F_CPU 8000000UL

#define TRUE  1u
#define FALSE 0u
#define PD0_ENABLE_DELAY_MS 80u

volatile uint8_t timer_task_10ms  = FALSE;
volatile uint8_t timer_task_100ms = FALSE;
volatile uint8_t timer_task_500ms = FALSE;
volatile uint8_t timer_task_1s    = FALSE;

volatile uint8_t pd0_reenable_ms = PD0_ENABLE_DELAY_MS;
volatile uint16_t adc_result = 0u;

static uint8_t timer_cnt = 0u;
static uint8_t pb0_pushed = FALSE;

static void port_init(void)
{
    DDRA = 0xffu;

    /* PF0/ADC0 input; PF1-PF3 diagnostic LED outputs. */
    DDRF &= ~(1u << PF0);
    DDRF |= (1u << PF1) |
            (1u << PF2) |
            (1u << PF3);

    /* PB0 button input with internal pull-up. */
    DDRB &= ~(1u << PB0);
    PORTB |= (1u << PB0);

    /* PD0/INT0 input with internal pull-up. */
    DDRD &= ~(1u << PD0);
    PORTD |= (1u << PD0);
}

static void timer_init(void)
{
    TCCR0A = (1u << WGM01) |
             (1u << CS02)  |
             (1u << CS00);

    OCR0A = 77u;
    TIMSK0 |= (1u << OCIE0A);
}

static void external_interrupt_init(void)
{
    /* INT0 on falling edge: ISC01:ISC00 = 10. */
    EICRA = (EICRA & ~((1u << ISC01) | (1u << ISC00))) |
            (1u << ISC01);
    EIMSK |= (1u << INT0);
}

static void adc_init(void)
{
    /* AT90CAN128: ADC0 channel, external AREF reference. */
    ADMUX = 0x00u;

    /* Enable ADC and ADC interrupt; ADC clock = f_CPU / 128 = 62.5 kHz. */
    ADCSRA = (1u << ADEN)  |
             (1u << ADIE)  |
             (1u << ADPS2) |
             (1u << ADPS1) |
             (1u << ADPS0);
}

int main(void)
{
    uint16_t adc_snapshot;

    port_init();
    timer_init();
    external_interrupt_init();
    adc_init();
    sei();

    while (1)
    {
        if (timer_task_10ms)
        {
            timer_task_10ms = FALSE;

            if (((PINB & (1u << PB0)) == 0u) && (pb0_pushed == FALSE))
            {
                PORTA ^= 0x01u;
                pb0_pushed = TRUE;
            }
            else if (((PINB & (1u << PB0)) != 0u) && (pb0_pushed == TRUE))
            {
                pb0_pushed = FALSE;
            }

            if (pd0_reenable_ms < PD0_ENABLE_DELAY_MS)
            {
                pd0_reenable_ms += 10u;
            }
        }

        if (timer_task_100ms)
        {
            timer_task_100ms = FALSE;

            /* adc_result is 16-bit on an 8-bit CPU, so copy it atomically. */
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
            {
                adc_snapshot = adc_result;
            }

            PORTA = (uint8_t)(adc_snapshot >> 2);
            ADCSRA |= (1u << ADSC);
            PORTF ^= (1u << PF1);
        }

        if (timer_task_500ms)
        {
            timer_task_500ms = FALSE;
            PORTF ^= (1u << PF2);
        }

        if (timer_task_1s)
        {
            timer_task_1s = FALSE;
            PORTF ^= (1u << PF3);
        }
    }
}

ISR(TIMER0_COMP_vect)
{
    timer_task_10ms = TRUE;
    timer_cnt++;

    if ((timer_cnt % 10u) == 0u)
    {
        timer_task_100ms = TRUE;
    }

    if ((timer_cnt % 50u) == 0u)
    {
        timer_task_500ms = TRUE;
    }

    if (timer_cnt >= 100u)
    {
        timer_task_1s = TRUE;
        timer_cnt = 0u;
    }
}

ISR(INT0_vect)
{
    if (pd0_reenable_ms >= PD0_ENABLE_DELAY_MS)
    {
        PORTA ^= 0xffu;
        pd0_reenable_ms = 0u;
    }
}

ISR(ADC_vect)
{
    adc_result = ADC;
}
