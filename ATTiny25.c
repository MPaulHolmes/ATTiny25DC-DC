#include <stdio.h>
#include <avr/wdt.h>

void InitIOPorts();
void watchdog_disable();
void watchdog_enable();

int main(void) {
	watchdog_enable();
	InitIOPorts();
	while (1) {


		// Set port B3 and B4 to their complements.
//		PORTB ^= ((1 << PB3) | (1 << PB4));  // When one is low, the other is high.  Swap them here.
		PORTB = 0b10111;
		asm("nop");asm("nop");asm("nop");
		PORTB = 0b01111;


		wdt_reset();
	}
	return 0;
}

void InitIOPorts() {
	DDRB = 0;			//  all are inputs at this stage.
	PORTB = 0b11111;  	// turn on all pull up resistors.
	asm("nop");
	DDRB = 0b11000; 	// make PB3 and PB4 outputs.
	//DDRB |= (1 << PB3);    // Data direction register.  Set to 1 to configure as outputs.
	//DDRB |= (1 << PB4);		// PB4 is also an output.
	//PORTB
	//PORTB &= ~(1 << PB3);   // Use PORTB to set the value of pins when they are outputs. PB3 starts as 0.
	//PORTB |= (1 << PB4);    // Start PB4 as 1.
}


void watchdog_disable(void)
{
	wdt_reset();
	wdt_disable();
}

void watchdog_enable(void)
{
	wdt_reset();
	wdt_enable(WDTO_15MS);
}
