/*
 * ultrasonic.c
 *
 *  Created on: Oct 18, 2023
 *      Author: Tarek Emad
 */


#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include "common_macros.h"
#include <util/delay.h>



static uint16 Ultrasonic_time_high = 0;

void Ultrasonic_init(void)
{
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};

	ICU_init(&ICU_Configurations);

	ICU_setCallBack(Ultrasonic_edgeProcessing);

	GPIO_setupPinDirection(Ultrasonic_Trigger_Port,Ultrasonic_Trigger_pin,PIN_OUTPUT);
}

void Ultrasonic_Trigger(void)
{
	GPIO_writePin(Ultrasonic_Trigger_Port,Ultrasonic_Trigger_pin,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(Ultrasonic_Trigger_Port,Ultrasonic_Trigger_pin,LOGIC_LOW);
}


uint16 Ultrasonic_readDistance(void)
{
	uint16 Distance;

	Ultrasonic_Trigger();

	Distance = Ultrasonic_time_high/58.8;

	return Distance+3;
}


void Ultrasonic_edgeProcessing(void)
{
	static uint8 g_edgeCount = 0;
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
	    g_edgeCount = 0;
		Ultrasonic_time_high = ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING);
		ICU_clearTimerValue();
	}
}
