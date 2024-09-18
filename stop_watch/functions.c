/********************************************************************************************************************
 * Name        : functions.c
 * Author      : Youssif Ahmed
 * Description : 
 * Created on  : Sep 17, 2024
 ********************************************************************************************************************/
#include "functions.h"

/*==============================================Global_Variables====================================================*/
/* max time 23:59:59 */
unsigned char seconds_0 = 0 ; // Seconds for the first  7-segment -- from 0 to 9
unsigned char seconds_1 = 0 ; // Seconds for the second 7-segment -- from 0 to 5
unsigned char minutes_0 = 0 ; // Minutes for the third  7-segment -- from 0 to 9
unsigned char minutes_1 = 0 ; // Minutes for the forth  7-segment -- from 0 to 5
unsigned char hours_0   = 0 ; // Hours   for the fifth  7-segment -- from 0 to 9
unsigned char hours_1   = 0 ; // Hours   for the sixth  7-segment -- from 0 to 2

/* flags */
unsigned char timer_flag    = 0;      // detects the second completed
unsigned char counting_flag = 1; 	  // if It is LOW->count_down, else count_up

/*===========================================Timer1_Initialization==================================================*/
void Timer1_CTC_INIT(void){
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);  				// disable PWM mode
	TCCR1B |= (1<<WGM12) | (1<<CS10) | (1<<CS12);  	// 1024 prescaler -> Ftimer= 15625Hz
	TCNT1  = 0;										// intial value is 0
	OCR1A  = 15625;									// 15625 steps to count 1 second
	TIMSK |= (1<<OCIE1A);							// enable interrupt flage of reg A	SREG  |= (1<<7);								// enable I_BIT
}
/*===============================================Timer1_ISR=========================================================*/
ISR(TIMER1_COMPA_vect){
	timer_flag = 1;
}

/*============================================INT0_Initialization===================================================*/
void INT0_INIT(void){
	GICR  |= (1<<INT0);								// activiate the interrupt0
	MCUCR |= (1<<ISC01);							// interrupt with the falling edge
}
/*================================================INT0_ISR==========================================================*/
ISR(INT0_vect){
	/* reset the variables of time */
	seconds_0 = 0;
	seconds_1 = 0;
	minutes_0 = 0;
	minutes_1 = 0;
	hours_0   = 0;
	hours_1   = 0;
	/* stop the buzzer */
	PORTD &= ~(1<<PD0);
	/* reset to default counting which is count_up */
	counting_flag = 1;
}

/*============================================INT1_Initialization===================================================*/
void INT1_INIT(void){
	MCUCR |= (1<<ISC10) | (1<<ISC11);				// interrupt with the raising edge
	GICR  |= (1<<INT1);								// activiate the interrupt 1
}
/*================================================INT1_ISR==========================================================*/
ISR(INT1_vect){
	/* disable the clock source */
	TCCR1B &= ~(1<<CS10) & ~(1<<CS12);
}

/*============================================INT2_Initialization===================================================*/
void INT2_INIT(void){
	GICR   |= (1<<INT2);							// activiate the interrupt 2
	MCUCSR &= ~(1<<ISC2);								// interrupt with the falling edge by default
}
/*================================================INT2_ISR==========================================================*/
ISR(INT2_vect){
	/* enable the clock source with prescaler 1024 */
	TCCR1B |= (1<<CS10) | (1<<CS12);
}


/*===========================================Counting_UP_function===================================================*/
void Count_up(void){
	PORTD |=  (1<<PD4);	// turn on  the coun_Up   LED "red LED"
	PORTD &= ~(1<<PD5);	// turn off the coun_down LED "yellow LED"

	seconds_0 ++;
	if(seconds_0 == 10){
		seconds_0 = 0;
		seconds_1 ++;
		if(seconds_1 == 6){
			seconds_1 = 0;
			minutes_0 ++;
			if(minutes_0==10){
				minutes_0 = 0;
				minutes_1 ++;
				if(minutes_1 == 6){
					minutes_1 = 0;
					hours_0 ++;
					if(hours_0 == 10){
						hours_0 = 0;
						hours_1 ++;
						if(hours_1 == 2){
							if(hours_0 == 4){
								seconds_0 = 0;
								seconds_1 = 0;
								minutes_0 = 0;
								minutes_1 = 0;
								hours_0   = 0;
								hours_1   = 0;
							}
						}
					}
				}
			}
		}
	}
}
/*==========================================Counting_DOWN_function==================================================*/
void Count_down(void){
	PORTD |=  (1<<PD5);	// turn off  the coun_Up   LED "red LED"
	PORTD &= ~(1<<PD4);	// turn on the coun_down LED "yellow LED"

	/* check if it reach the time 0 */
	if((!seconds_0) && (!seconds_1) && (!minutes_0) && (!minutes_1) && (!hours_0) && (!hours_1)){
		PORTD |= (1<<PD0);  //turn on the buzzer
	}
	else{
		if(seconds_0 != 0){
			seconds_0 --;
		}else{
			seconds_0 = 9;
			if(seconds_1 != 0){
				seconds_1 --;
			}else{
				seconds_1 = 5;
				if(minutes_0 != 0){
					minutes_0 --;
				}else{
					minutes_0 = 9;
					if(minutes_1 != 0){
						minutes_1 --;
					}else{
						minutes_1 = 5;
						if(hours_0 != 0){
							hours_0 --;
						}else{
							hours_0 = 9;
							if(hours_1 != 0){
								hours_1 --;
							}
						}
					}
				}
			}
		}
	}
}

/*========================================Display_On_7-segment_function=============================================*/
void Display(void){
	/*==========seconds=============*/
	PORTA = (PORTA & 0xC0) | (1<<PA5);   		 // enable the first 7-seg that belongs to seconds_0
	PORTC = (PORTC & 0xF0) | (seconds_0 & 0x0F); // insert seconds_0 into the first 4 bits of PORTC
	_delay_ms(DELAY_TIME);						 // delay to update the 7-segment

	PORTA = (PORTA & 0xC0) | (1<<PA4);   		 // enable the second 7-seg that belongs to seconds_1
	PORTC = (PORTC & 0xF0) | (seconds_1 & 0x0F); // insert seconds_1 into the first 4 bits of PORTC
	_delay_ms(DELAY_TIME);						// delay to update the 7-segment
	/*==========minutes=============*/
	PORTA = (PORTA & 0xC0) | (1<<PA3);   		 // enable the third 7-seg that belongs to minutes_0
	PORTC = (PORTC & 0xF0) | (minutes_0 & 0x0F); // insert minutes_0 into the first 4 bits of PORTC
	_delay_ms(DELAY_TIME);						 // delay to update the 7-segment

	PORTA = (PORTA & 0xC0) | (1<<PA2);   		 // enable the forth 7-seg that belongs to minutes_1
	PORTC = (PORTC & 0xF0) | (minutes_1 & 0x0F); // insert minutes_1 into the first 4 bits of PORTC
	_delay_ms(DELAY_TIME);						 // delay to update the 7-segment
	/*===========hours==============*/
	PORTA = (PORTA & 0xC0) | (1<<PA1);   		 // enable the forth 7-seg that belongs to hours_0
	PORTC = (PORTC & 0xF0) | (hours_0 & 0x0F);   // insert hours_0 into the first 4 bits of PORTC
	_delay_ms(DELAY_TIME);						 // delay to update the 7-segment

	PORTA = (PORTA & 0xC0) | (1<<PA0);   		 // enable the forth 7-seg that belongs to hours_1
	PORTC = (PORTC & 0xF0) | (hours_1 & 0x0F);   // insert hours_1 into the first 4 bits of PORTC
	_delay_ms(DELAY_TIME);						 // delay to update the 7-segment
}
