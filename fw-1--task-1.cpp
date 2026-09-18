#include <avr/io.h>

/*
 * Configure Timer 0 in CTC Mode (F_CPU = 8 MHz) for a 1 ms delay 
 * (Toggle period for square wave).
 * 
 * Prescaler Calculation: T_count = (Prescaler / F_CPU). 
 * For Prescaler = 64 : T_count = 64 / 8 MHz = 8 µs. 
 * Required Counts = 1 ms / 8 µs = 125 counts.
 * 
 * OCR0 Value = 125 - 1 = 124 (0x7C).
 * Selected Prescaler: 64 (CS01=1, CS00=1)
 */

void T0_delay_1ms_CTC() {
    OCR0 = 124; // Load compare value for 1ms delay
    TCCR0 = (1<<WGM01) | (1<<CS01) | (1<<CS00); // CTC mode, Prescaler 64
    while((TIFR & (1<<OCF0)) == 0); // Wait for Output Compare Flag
    TCCR0 = 0; // Stop timer
    TIFR = (1<<OCF0); // Clear OCF0 flag
}

int main(void) {
  DDRB |= (1<<PB0); // Set PB0 as output
  while (1){
    for (int i = 0; i < 500; i++) {
      T0_delay_1ms_CTC();    
    }
    PORTB ^= (1 << PB0);
  }
  return 0;
}