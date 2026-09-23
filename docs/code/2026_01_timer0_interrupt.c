#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define F_CPU 8000000UL

#define TRUE  1u
#define FALSE 0u

volatile uint8_t timer_task_10ms  = FALSE;
volatile uint8_t timer_task_100ms = FALSE;
volatile uint8_t timer_task_500ms = FALSE;
volatile uint8_t timer_task_1s    = FALSE;

static uint8_t timer_cnt = 0u;

static void port_init(void)
{
    DDRF |= (1u << PF0) |
            (1u << PF1) |
            (1u << PF2) |
            (1u << PF3);
}

static void timer_init(void)
{
    /* Timer0: CTC mode, f_CPU / 1024, compare match every 9.984 ms. */
    TCCR0A = (1u << WGM01) |
             (1u << CS02)  |
             (1u << CS00);

    OCR0A = 77u;
    TIMSK0 |= (1u << OCIE0A);
}

int main(void)
{
    port_init();
    timer_init();
    sei();

    while (1)
    {
        if (timer_task_10ms)
        {
            timer_task_10ms = FALSE;
            PORTF ^= (1u << PF0);
        }

        if (timer_task_100ms)
        {
            timer_task_100ms = FALSE;
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
