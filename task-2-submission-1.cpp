/*
 * PROBLEM STATEMENT & CALCULATIONS
 *
 * Goal: Generate Non-Inverted Phase Correct PWM with Duty Cycle = 25%,
 * Frequency = 1.960 kHz (F_CPU = 8 MHz).
 *
 * 1. Prescaler Selection:
 *    F_PWM = F_CPU / (510 * 8)
 *          = 8,000,000 / (510 * 8)
 *          = 1960.78431373 Hz
 *          ≈ 1.96 kHz
 *
 *    N = 8 (Prescaler = 8)
 *
 * 2. Duty Cycle Calculation:
 *    Duty% = ((2 * OCR0) / 510) * 100%
 *
 *    25% = ((2 * OCR0) / 510) * 100%
 *
 *    OCR0 = (25 * 510) / (2 * 100)
 *         = 63.75
 *         ≈ 64 (0x40)
 *
 * 3. OCR0 Value:
 *    2 * OCR0 = 128
 *    OCR0 ≈ 64 (0x40)
 *
 * 4. Mode Configuration:
 *    TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << CS01);
 *
 *    OCR0  = 0x40;    // 64
 *
 *    WGM01 = 0, WGM00 = 1
 *    COM01 = 1, COM00 = 0   // Non-inverting output
 *
 *    CS02  = 0, CS01 = 1, CS00 = 0
 *    // Prescaler = 8
 *
 */
#include <avr/io.h>

void PMW0_PhaseCorrect_Init() {

    DDRB |= (1 << PB3);     // Set OC0 (PB3) as output

    OCR0 = 64;             // Load compare value for 25% duty cycle

    TCCR0 = (1 << WGM00) |  // Phase Correct PWM Mode
            (1 << COM01) |  // Non-Inverted (Clear OC0 on Compare up-counting)
            (1 << CS01);    // Prescaler = 8
}

int main(void) {

    PMW0_PhaseCorrect_Init();   // Initialize Phase Correct PWM

    while (1) {
        // PWM runs automatically in hardware
    }

    return 0;
}