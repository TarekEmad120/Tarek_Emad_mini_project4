/*
 * miniproject4.c
 *
 *  Created on: Oct 18, 2023
 *      Author: Tarek Emad
 */

#include <avr/io.h>
#include "lcd.h"
#include "ultrasonic.h"
#include "common_macros.h"
#include "std_types.h"



int main()
{
	LCD_init();
	LCD_displayStringRowColumn(0,0,"Measure Distance");
	LCD_displayStringRowColumn(1,0,"using ultrasonic");
	LCD_displayStringRowColumn(2,0,"Distance=     cm");


	SET_BIT(SREG,7);

	uint16 Distance = 0;

	Ultrasonic_init();

	while(1)
	{

		Distance = Ultrasonic_readDistance();
		LCD_moveCursor(2,10);
		LCD_intgerToString(Distance);
		if(Distance<100)
			LCD_displayString(" ");
		if(Distance<10)
			LCD_displayString("  ");
	}
}
