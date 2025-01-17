// Requires headers for AVR defines and ISR function
//#include <avr/io.h>
//#include <avr/interrupt.h>


#define INTERRUPT_PIN PCINT1  // This is PB1 per the schematic
#define INT_PIN PB1 //BUTTON_PIN //PB1           // Interrupt pin of choice: PB1 (same as PCINT1) - Pin 6
// #define LED_PIN PB4           // PB4 - Pin 3
#define PCINT_VECTOR PCINT1_vect      // This step is not necessary - it's a naming thing for clarit

typedef void func_t();
func_t* pfunc = NULL;


void button_init(func_t* pf) {
    pfunc = pf;
/*
    // pinMode(LED_PIN, OUTPUT);
    cli();                            // Disable interrupts during setup
    PCMSK |= (1 << INTERRUPT_PIN);    // Enable interrupt handler (ISR) for our chosen interrupt pin (PCINT1/PB1/pin 6)
    GIMSK |= (1 << PCIE);             // Enable PCINT interrupt in the general interrupt mask
    // pinMode(INT_PIN, INPUT_PULLUP);   // Set our interrupt pin as input with a pullup to keep it stable
        // DDRB = _BV(INT_PIN); // set pin as digital output
    sei();                            //last line of setup - enable interrupts after setup
    // if (pfunc) (*pfunc)();
*/
DDRB |= (1<<PB1);

    MCUCR |= (1<<ISC00) | (1<<ISC01); //INT0 as rising edge
    PCMSK |= (1<<PCINT1);   // pin change mask: listen to portb, pin PB4
    GIMSK |= (1<<PCIE); // enable PCINT interrupt
    sei();          // enable all interrupts

}
// This is the interrupt handler called when there is any change on the INT_PIN
// ISR is defined in the headers - the ATtiny85 only has one handler


ISR(PCINT_VECTOR)
{
    // if( digitalRead(INT_PIN) == HIGH ) {
    //     // digitalWrite(LED_PIN, HIGH);
    //     if (pfunc) (*pfunc)();
    // }else{
    //     // digitalWrite(LED_PIN, LOW);
    // }

    if( PORTB & _BV(INT_PIN) ) {
        // digitalWrite(LED_PIN, HIGH);
        if (pfunc) (*pfunc)();
    }

    if (pfunc) (*pfunc)();
}
