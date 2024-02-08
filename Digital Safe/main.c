#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Code.h"
#include "KEY_Code.h"
#include "SAFE_Code.h"
#include "MORSE_Code.h"
#include "THEFT_Code.h"

// Removed state -> Moved -> to SAFE_Code.h
int degr;
char first = '1';
char second = '2';
char third = '3';
char fourth = '4';
volatile uint8_t potentiometer_above_50 = 0;

ISR(INT0_vect) { // External interrupt handler
	if (ADC_Read(7) > 500) { // Check if potentiometer is above 50%
		Text("THEFT !!!");
		Convert_Text("THEFT GETTING ROBBED");
		state = 2;
		LCD_Turnoff();
		SAFE_Locked();
	}
}

void initInterrupt() { // Interrupt setup
	GICR = 1<<INT0;		// Enable INT0
	MCUCR = 1<<ISC01 | 1<<ISC00;  // Trigger INT0 on rising edge
	sei();
}

int main(void) {
	ADC_Init();
	initInterrupt();

	while (1) {
		PIN_Enter();
		if (state == 1){
			SAFE_Open();
			if (safe_state == 1){
				Text("SAFE OPENED");
				do {
					if (KEY_Scan() ==' '){
						PIN_Enter();
						if (state == 1){
							Text("RESET MODE","____");
							PIN_Reset();
							if (KEY_Scan() =='='){
								Text("PASSWORD SET");
								_delay_ms(200);
								state = 3;
							}
						}
						else if (state == 2){
							_delay_ms(200);
						}
						}else {
						_delay_ms(200);
						SAFE_Close();
						if (safe_state == 3){
							Text("CLOSING SAFE");
							_delay_ms(200);
							state = 4;
						}
					}
				} while (state<=2);
				if (state==3){
					Text("SAFE OPENED");
					SAFE_Close();
					if (safe_state == 3){
						Text("SAFE CLOSED");
						_delay_ms(200);
					}
				}
				else if (state==4){
					Text("SAFE CLOSED");
					_delay_ms(100);
				}
				
			}
			else if (safe_state == 2){
				Text("TOO LATE","SAFE CLOSED");
				_delay_ms(200);
			}
		}
		else if (state == 2){
			LCD_Turnoff();
			SAFE_Locked();
			_delay_ms(20000);
		}
		_delay_ms(10);
	}
	Text("THEFT !!!");
	Convert_Text("THEFT GETTING ROBBED");
	return 0;
}
void PIN_Enter(void) {
	for (int try=0; try<3; try++){
	Text("ENTER PASSWORD","____");
	LCD_Cmd(0xC0);
	char a =KEY_Scan();
	PIN_Hide();
	char b = KEY_Scan();
	PIN_Hide();
	char c = KEY_Scan();
	PIN_Hide();
	char d = KEY_Scan();
	PIN_Hide();
	LCD_Cmd(0x0C);
	state=0;
	char e = KEY_Scan();
	if (e =='x'){
		LCD_Cmd(0xC0);
		LCD_Char(a);
		LCD_Char(b);
		LCD_Char(c);
		LCD_Char(d);
		state=0;
		char f = KEY_Scan();
		if (f =='x'){
			LCD_Cmd(0xC0);
			PIN_Hide();
			PIN_Hide();
			PIN_Hide();
			PIN_Hide();
			char k = KEY_Scan();
			if (k =='='){
				if (a==first && b==second && c==third && d==fourth){
					Text("CORRECT PASSWORD");
					_delay_ms(100);
					return state=1;
				}
				else
				Text("WRONG PASSWORD","RETRY");
				_delay_ms(200);
			}
		}
		if (f =='='){
			if (a==first && b==second && c==third && d==fourth){
				Text("CORRECT PASSWORD");
				return state=1;
			}
			else
			Text("WRONG PASSWORD","RETRY");
			_delay_ms(200);
		}
	}
	if (e =='='){
		if (a==first && b==second && c==third && d==fourth){
			Text("CORRECT PASSWORD");
			return state=1;
		}
		else
		Text("WRONG PASSWORD","RETRY");
		_delay_ms(200);
	}
	}
	Text("TRYS RAN OUT");
	_delay_ms(200);
	return state=2;
	if (ADC_Read(7) > 500) {
		Text("THEFT !!!");
		Convert_Text("THEFT GETTING ROBBED");
		return 0;
	}
}
void Text(char *x, char *y) {
	LCD_Init();
	Scroll_Left();
	LCD_Clear();
	LCD_String(x);
	LCD_Cmd(0xC0);
	LCD_String(y);
}
void PIN_Hide(void) {
	LCD_String("*");
}
void PIN_Reset(void) {
	LCD_Cmd(0xC0);
	first = KEY_Scan();
	LCD_Char(first);
	second = KEY_Scan();
	LCD_Char(second);
	third = KEY_Scan();
	LCD_Char(third);
	fourth = KEY_Scan();
	LCD_Char(fourth);
}