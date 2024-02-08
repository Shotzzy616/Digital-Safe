#ifndef KEY_Code_H
#define KEY_Code_H

#include <avr/io.h>
#include <util/delay.h>
// Modified
#include "SAFE_Code.h"
// To here

#define KEY_Dir DDRB
#define KEY_Port PORTB
#define KEY_Pin PINB

// Variables for keypad scanning
unsigned char colNum, rowNum, colChar;
// Define the layout of the keypad
char keypad[4][4] = {{' ', '0', '=', '+'},
					{'1', '2', '3', '-'},
					{'4', '5', '6', 'x'},
					{'7', '8', '9', '/'}};

char KEY_Scan() {
	// made changes here; Original Code Commented Out
	while (1){
		KEY_Dir = 0xF0;
		KEY_Port = 0x0F;
		// Wait until no key is pressed
		do{
			_delay_ms(20);
			colChar = (KEY_Pin & 0x0F);
		}while(colChar != 0x0F);
		 // Wait for a key press
		do{
			do{
				_delay_ms(20);
				colChar = (KEY_Pin & 0x0F);
				// Mark added state != 2
			}while(colChar == 0x0F);
			colChar = (KEY_Pin & 0x0F);
			// Mark added state != 2
		}while(colChar == 0x0F);
		// Determine the pressed key's row
		for (int row=0; row<4; row++){
			KEY_Port = ~(1<<row+4);
			colNum = (KEY_Pin & 0x0F);
			if(colNum != 0x0F){
				rowNum = row;
			}
		}
		// Determine the pressed key's column
		for (int col=0; col<4; col++){
			if ((colChar & (1 << col)) == 0){
				// Determine the pressed key based on row and column
				return keypad[rowNum][3-col];
			}
		}
	}
}

#endif