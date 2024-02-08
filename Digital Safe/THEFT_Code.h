#ifndef THEFT_Code_H
#define THEFT_Code_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>

void ADC_Init(){
	DDRA = 0x03;  // Make ADC port as input
	ADCSRA = 0x87; // Enable ADC, fr/128
	ADMUX = 0x40; // Vref: Avcc
}
int ADC_Read(int channel){
	int Ain,AinLow;
	ADMUX = ADMUX|(channel); // Set input channel to read
	ADCSRA |= (1<<ADSC); // Start conversion
	while((ADCSRA & (1<<ADIF)) == 0);// Monitor end of conversion interrupt
	_delay_us(10);
	AinLow = (int)ADCL; // Read lower byte
	Ain = (int)ADCH*256; // Read higher 2 bits and Multiply with weight
	Ain = Ain + AinLow;
	return(Ain); // Return digital value
	}

#endif