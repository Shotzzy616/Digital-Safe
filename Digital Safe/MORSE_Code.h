#ifndef MORSE_Code_H
#define MORSE_Code_H

#include <avr/io.h>
#include <util/delay.h>

#define LED_Dir DDRA
#define LED_Port PORTA

void Morse_Init(void) {
	LED_Dir = 0x04;
}
void Convert_Text(char *text) {
	for (int i=0;text[i] != 0; i++ ){
		Convert_Letter(text[i]);
		_delay_ms(40);
	}
}
void Convert_Letter(char Letter) {
	Morse_Init();
	if (Letter == 'A' || Letter == 'a') {
		Dot();
		Dash();
		} else if (Letter == 'B' || Letter == 'b') {
		Dash();
		Dot();
		Dot();
		Dot();
		} else if (Letter == 'C' || Letter == 'c') {
		Dash();
		Dot();
		Dash();
		Dot();
		} else if (Letter == 'D' || Letter == 'd') {
		Dash();
		Dot();
		Dot();
		} else if (Letter == 'E' || Letter == 'e') {
		Dot();
		} else if (Letter == 'F' || Letter == 'f') {
		Dot();
		Dot();
		Dash();
		Dot();
		} else if (Letter == 'G' || Letter == 'g') {
		Dash();
		Dash();
		Dot();
		} else if (Letter == 'H' || Letter == 'h') {
		Dot();
		Dot();
		Dot();
		Dot();
		} else if (Letter == 'I' || Letter == 'i') {
		Dot();
		Dot();
		} else if (Letter == 'J' || Letter == 'j') {
		Dot();
		Dash();
		Dash();
		Dash();
		} else if (Letter == 'K' || Letter == 'k') {
		Dash();
		Dot();
		Dash();
		} else if (Letter == 'L' || Letter == 'l') {
		Dot();
		Dash();
		Dot();
		Dot();
		} else if (Letter == 'M' || Letter == 'm') {
		Dash();
		Dash();
		} else if (Letter == 'N' || Letter == 'n') {
		Dash();
		Dot();
		} else if (Letter == 'O' || Letter == 'o') {
		Dash();
		Dash();
		Dash();
		} else if (Letter == 'P' || Letter == 'p') {
		Dot();
		Dash();
		Dash();
		Dot();
		} else if (Letter == 'Q' || Letter == 'q') {
		Dash();
		Dash();
		Dot();
		Dash();
		} else if (Letter == 'R' || Letter == 'r') {
		Dot();
		Dash();
		Dot();
		} else if (Letter == 'S' || Letter == 's') {
		Dot();
		Dot();
		Dot();
		} else if (Letter == 'T' || Letter == 't') {
		Dash();
		} else if (Letter == 'U' || Letter == 'u') {
		Dot();
		Dot();
		Dash();
		} else if (Letter == 'V' || Letter == 'v') {
		Dot();
		Dot();
		Dot();
		Dash();
		} else if (Letter == 'W' || Letter == 'w') {
		Dot();
		Dash();
		Dash();
		} else if (Letter == 'X' || Letter == 'x') {
		Dash();
		Dot();
		Dot();
		Dash();
		} else if (Letter == 'Y' || Letter == 'y') {
		Dash();
		Dot();
		Dash();
		Dash();
		} else if (Letter == 'Z' || Letter == 'z') {
		Dash();
		Dash();
		Dot();
		Dot();
		} else if (Letter == '1') {
		Dot();
		Dash();
		Dash();
		Dash();
		Dash();
		} else if (Letter == '2') {
		Dot();
		Dot();
		Dash();
		Dash();
		Dash();
		} else if (Letter == '3') {
		Dot();
		Dot();
		Dot();
		Dash();
		Dash();
		} else if (Letter == '4') {
		Dot();
		Dot();
		Dot();
		Dot();
		Dash();
		} else if (Letter == '5') {
		Dot();
		Dot();
		Dot();
		Dot();
		Dot();
		} else if (Letter == '6') {
		Dash();
		Dot();
		Dot();
		Dot();
		Dot();
		} else if (Letter == '7') {
		Dash();
		Dash();
		Dot();
		Dot();
		Dot();
		} else if (Letter == '8') {
		Dash();
		Dash();
		Dash();
		Dot();
		Dot();
		} else if (Letter == '9') {
		Dash();
		Dash();
		Dash();
		Dash();
		Dot();
		} else if (Letter == '0') {
		Dash();
		Dash();
		Dash();
		Dash();
		Dash();
		} else if (Letter == ' ') {
		Space();
		}
}
void Dot(void) {
	LED_Port = 0x04;
	_delay_ms(40);
	LED_Port = 0x00;
	_delay_ms(40);
}
void Dash(void) {
	LED_Port = 0x04;
	_delay_ms(120);
	LED_Port = 0x00;
	_delay_ms(40);
}
void Space(void) {
	LED_Port = 0x00;
	_delay_ms(40);
}

#endif