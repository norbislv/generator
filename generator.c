#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setup();
void generate();
void silence();


void main(){
	setup();
	while (1){//loops
		generate();
		_delay_ms(500);
		silence();
		_delay_ms(500);
	}
}

void setup(){
	//šeit mēs rakstam dažādus bitus kontroles reģistros. io.h satur aliasus reģistriem un varam nerakstīt *ADRESE |= (1<<7)
	DDRB |= (1 << PINB7); //PINB7 ir outputs
	OCR0A =64; //skaitam 64 tikšķus (250khz)
	TCCR0A |= (1 << COM0A0); //setupojam, ka OC0A pins (PINB7) pārslēdzas katru reizi, kad ir compare match taimerim.
	TCCR0A |= (1 << WGM01); //Clear on compare match - noreseto taimeri un sāk skaitīt no sākuma
	TCCR0B |= (1 << WGM02); //waveform generation mode
}
	
void generate(){
	TCCR0B |= (1 << CS00); //nav pulksteņa prescalera, 16Mhz
}

void silence(){
	TCCR0B &= ~(1 << CS00); //izslēdzam pulksteni
	TCNT0 = 0; //resetojam taimeri no sākuma
}

	
	
