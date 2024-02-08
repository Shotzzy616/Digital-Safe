#ifndef LCD_Code_H
#define LCD_Code_H

#include <avr/io.h>
#include <util/delay.h>

#define LCD_Dir DDRC
#define LCD_Port PORTC
#define LCD_Data_Dir DDRD
#define LCD_Data_Port PORTD
#define RS PC0
#define RW PC1
#define EN PC2

void LCD_Cmd(unsigned char cmd) { // Function to send a command to the LCD
	LCD_Data_Port = cmd;
	LCD_Port &= ~(1 << RS);     // Set RS low for command mode
	LCD_Port &= ~(1 << RW);     // Set RW low for write operation
	_delay_us(1);
	LCD_Port |= (1 << EN);      // Set EN high to enable the LCD
	_delay_us(1);
	LCD_Port &= ~(1 << EN);     // Set EN low to disable the LCD
	_delay_us(2);
}

void LCD_Char(unsigned char char_data) { // Function to write a character to the LCD
	LCD_Data_Port = char_data;
	LCD_Port |= (1 << RS);      // Set RS high for data mode
	LCD_Port &= ~(1 << RW);     // Set RW low for write operation
	_delay_us(1);
	LCD_Port |= (1 << EN);      // Set EN high to enable the LCD
	_delay_us(1);
	LCD_Port &= ~(1 << EN);     // Set EN low to disable the LCD
	_delay_us(2);
}

void LCD_Init(void) {
	LCD_Dir = 0xFF;             // Set all pins of the control port as output
	LCD_Data_Dir = 0xFF;        // Set data port as output
	_delay_us(50);
	LCD_Cmd(0x38);              // 2 lines, 5x8 matrix
	LCD_Cmd(0x0C);              // Display on, cursor on, blinking cursor on
	LCD_Cmd(0x02);              // Return home
	LCD_Cmd(0x06);              // Entry mode, auto-increment with no shift
}

void LCD_Clear(void) {
	LCD_Cmd(0x01);              // Clear display
	LCD_Cmd(0x02);              // Return home
	_delay_ms(4);
}

void Scroll_Left() {
	int letters = 16;
	for (int letter = 0; letter < 16; letter++) {
		LCD_Cmd(0x18);          // Shift entire display to the left
		_delay_ms(5);
	}
}

void LCD_String(char *str) { // Function to write a string to the LCD
	
	for(int i=0;str[i] !=0;i++){
		LCD_Char(str[i]);
	}
}

void LCD_String_xy(char row, char pos, char *str) {
	if (row == 0 && pos < 16){
		LCD_Cmd((pos & 0x0F) | 0x80);
	}
	else if (row == 1 && pos < 16){
		LCD_Cmd((pos & 0x0F) | 0xC0);
	}
	LCD_String(str);
}

void LCD_Turnoff(void) {
	LCD_Cmd(0x08);
}

#endif