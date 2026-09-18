#include <avr/io.h>
#include <avr/interrupt.h>

// ISR for External Interrupt 0
ISR(INT0_vect)
{
    PORTB ^= (1 << PB0);    // Toggle LED on PB0
}

int main(void)
{
    DDRB |= (1 << PB0);     // Set PB0 as Output
    PORTB &= ~(1 << PB0);   // Initially LED OFF

    DDRD &= ~(1 << PD2);    // Set INT0 (PD2) as Input
    PORTD |= (1 << PD2);    // Enable internal Pull-up resistor

    // Falling edge on INT0 generates interrupt
    MCUCR |= (1 << ISC01);
    MCUCR &= ~(1 << ISC00);

    GICR |= (1 << INT0);    // Enable INT0 external interrupt

    sei();                  // Enable Global Interrupts

    while (1)
    {
        // Main loop stays free for other tasks
    }

    return 0;
}