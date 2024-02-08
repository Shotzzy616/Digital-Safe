#ifndef SAFE_Code_H
#define SAFE_Code_H

#include <util/delay.h>
#include <avr/io.h>

#define SAFE_Dir DDRA
#define SAFE_Port PORTA

///.Modified code is here
int state;
// Up to here
int safe_state;

void SAFE_Init(void) {
	SAFE_Dir = 0x03;
}
void SAFE_Open(void) {
	SAFE_Init();
	do 
	{
		for (int z=0; z<5; z++){ //counts for 5 sec
			LED_blink();
			if (PINA == 0x02 || PINA == 0x03 || PINA == 0x82 || PINA == 0x83){ //check if button pressed
				SAFE_Port = 0x01;
				safe_state=1;
				return safe_state; //if button pressed safe state is 1
			}
		}
		safe_state=2;
	} while (safe_state == 0);
	return safe_state; //is button is not pressed
}

void SAFE_Close(void) {
	while (1)
	{
		SAFE_Init();
		if (PINA == 0x03 || PINA == 0x83){ // checks if button pressed 
			LED_Off();
			safe_state=3;
			return safe_state; //if pressed safe state is 3
		}
	}
}
void LED_blink(void) {
	SAFE_Port = 0x01; //turn led on
	_delay_ms(100);
	SAFE_Port = 0x00; //turn led off
	_delay_ms(100);
}

void LED_Off(void) {
	_delay_ms(100);
	SAFE_Port = 0x00;
	_delay_ms(100);
}

void SAFE_Locked(void) {
	LED_Off();
}

#endif