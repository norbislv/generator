compile:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega32u4 -c -o generator.o generator.c
	avr-gcc -mmcu=atmega32u4 generator.o -o generator
	avr-objcopy -O ihex -R .eeprom generator generator.hex
	
clean:
	rm generator 
	rm generator.o
	rm generator.hex
	
program:
	avrdude -F -V -c avr109 -p ATMEGA32U4 -P /dev/ttyACM0 -b 115200 -U flash:w:generator.hex

	

