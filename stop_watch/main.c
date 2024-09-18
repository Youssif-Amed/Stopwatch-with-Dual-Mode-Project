/********************************************************************************************************************
 * Name        : main.c
 * Author      : Youssif Ahmed
 * Description : This project implements a Digital Stopwatch with two modes Increment Mode and Countdown Mode
 * 				 using an ATmega32 microcontroller and multiplexed seven-segment displays.
 * Created on  : Sep 14, 2024
 ********************************************************************************************************************/
#include "functions.h"

/*===============================================Main_function======================================================*/
int main(void){
	/*---------Buttons flags---------*/
	unsigned char toggle_button_flag     = 0; // high when the toggle mode button is being pressed
	unsigned char second_inc_button_flag = 0; // high when the seconds increament button is being pressed
	unsigned char second_dec_button_flag = 0; // high when the seconds decreament button is being pressed
	unsigned char minute_inc_button_flag = 0; // high when the minutes increament button is being pressed
	unsigned char minute_dec_button_flag = 0; // high when the minutes decreament button is being pressed
	unsigned char hours_inc_button_flag  = 0; // high when the hours increament button is being pressed
	unsigned char hours_dec_button_flag  = 0; // high when the hours decreament button is being pressed

	/*--------Pins Direction---------*/
	SREG |= (1<<7);	// enable I_BIT
	DDRC |= 0x0F;  		// direction of first 4 bits of PORTC 7-segment bits as outputs
	DDRA |= 0x3F;  		// direction of first 5 bits of PORTA 7-segment enable bits as outputs
	DDRD |= 0x31;  		// direction of PD4 and PD5 count_up and count_down mode LEDs and PD0 for buzzer as outputs
	DDRD &= ~(1<<PD2);	// direction of PD2 "Reset button" as input
	DDRD &= ~(1<<PD3);	// direction of PD3 "Pause button" as input
	DDRB &= 0x00;		// direction of PORTB as inputs except PB6

	/*-----Pins Initialization-------*/
	PORTD &= ~(1<<PD0); // turn off the buzzer as default
	PORTB |= 0xFF;      // activiate the internal pull-up resistor of PORTB
	PORTD &= ~(1<<PD3);

	Timer1_CTC_INIT();  // Intialization the Timer_1
	INT0_INIT();  		// Intialization the Interrupt_0
	INT1_INIT();  		// Intialization the Interrupt_1
	INT2_INIT();  		// Intialization the Interrupt_2

	for(;;){

		/*--------Second inc. function---------*/
		if(!(PINB & (1<<PB6))){
			_delay_ms(30);
			if(!(PINB & (1<<PB6))){
				if(!second_inc_button_flag){
					if(seconds_0 != 9){
						seconds_0 ++;
					}
					else if(seconds_1 != 5){
						seconds_0 = 0;
						seconds_1 ++;
					}else{

					}
					second_inc_button_flag = 1;
				}
			}
		}else{
			second_inc_button_flag = 0;
		}
		/*--------seconds dec. function---------*/
		if(!(PINB & (1<<PB5))){
			_delay_ms(30);
			if(!(PINB & (1<<PB5))){
				if(!second_dec_button_flag){
					if(seconds_0 != 0){
						seconds_0 --;
					}
					else if(seconds_1 != 0){
						seconds_1 --;
						seconds_0 = 9;
					}else{

					}
					second_dec_button_flag = 1;
				}
			}
		}else{
			second_dec_button_flag = 0;
		}
		/*--------minutes inc. function---------*/
		if(!(PINB & (1<<PB4))){
			_delay_ms(30);
			if(!(PINB & (1<<PB4))){
				if(!minute_inc_button_flag){
					if(minutes_0 != 9){
						minutes_0 ++;
					}
					else if(seconds_1 != 5){
						minutes_1 ++;
						minutes_0 = 0;
					}else{

					}
					minute_inc_button_flag = 1;
				}
			}
		}else{
			minute_inc_button_flag = 0;
		}
		/*--------Minutes dec. function---------*/
		if(!(PINB & (1<<PB3))){
			_delay_ms(30);
			if(!(PINB & (1<<PB3))){
				if(!minute_dec_button_flag){
					if(minutes_0 != 0){
						minutes_0 --;
					}
					else if(minutes_1 != 0){
						minutes_1 --;
						minutes_0 = 9;
					}else{

					}
					minute_dec_button_flag = 1;
				}
			}
		}else{
			minute_dec_button_flag = 0;
		}
		/*--------hours inc. function---------*/
		if(!(PINB & (1<<PB1))){
			_delay_ms(30);
			if(!(PINB & (1<<PB1))){
				if(!hours_inc_button_flag){
					if((hours_0 != 9)&&(hours_1 !=2)){
						hours_0 ++;
					}
					else if((hours_0 != 3)&&(hours_1 ==2)){
						hours_0 ++;
					}
					else if(hours_1 != 2){
						hours_1 ++;
						hours_0 = 0;
					}else{

					}
					hours_inc_button_flag = 1;
				}
			}
		}else{
			hours_inc_button_flag = 0;
		}
		/*--------Hours dec. function---------*/
		if(!(PINB & (1<<PB0))){
			_delay_ms(30);
			if(!(PINB & (1<<PB0))){
				if(!hours_dec_button_flag){
					if(hours_0 != 0){
						hours_0 --;
					}
					else if(hours_1 != 0){
						hours_1 --;
						hours_0 = 9;
					}else{

					}
					hours_dec_button_flag = 1;
				}
			}
		}else{
			hours_dec_button_flag = 0;
		}
		/*--------Toggle mode function---------*/
		if(!(PINB & (1<<PB7))){
			_delay_ms(30);
			if(!(PINB & (1<<PB7))){
				if(!toggle_button_flag){
					if(counting_flag)
						counting_flag = 0;
					else
						counting_flag = 1;
					toggle_button_flag = 1;
				}
			}
		}else{
			toggle_button_flag = 0;
		}
		/*-------Main counting functions-------*/
		if(timer_flag){
			if(counting_flag){
				Count_up();
			}
			else if(!counting_flag){
				Count_down();
			}
			timer_flag = 0;
		}
		/* Display the time on the Six Multiplexed 7-Segment Common Anode */
		Display();
	}

	return 0;
}
