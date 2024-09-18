/********************************************************************************************************************
 * Name        : functions.h
 * Author      : Youssif Ahmed
 * Description : 
 * Created on  : Sep 17, 2024
 ********************************************************************************************************************/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/*===============================================AVR Libraries======================================================*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*===============================================Macros #define=====================================================*/
#define DELAY_TIME 2

/*==============================================Global_Variables====================================================*/
/* max time 23:59:59 */
extern unsigned char seconds_0 ; // Seconds for the first  7-segment -- from 0 to 9
extern unsigned char seconds_1 ; // Seconds for the second 7-segment -- from 0 to 5
extern unsigned char minutes_0 ; // Minutes for the third  7-segment -- from 0 to 9
extern unsigned char minutes_1 ; // Minutes for the forth  7-segment -- from 0 to 5
extern unsigned char hours_0   ; // Hours   for the fifth  7-segment -- from 0 to 9
extern unsigned char hours_1   ; // Hours   for the sixth  7-segment -- from 0 to 2

/* flags */
extern unsigned char timer_flag    ;      // detects the second completed
extern unsigned char counting_flag ; 	  // if It is LOW->count_down, else count_up
/*=============================================functions prototype==================================================*/
extern void Timer1_CTC_INIT(void);
extern void INT0_INIT(void);
extern void INT1_INIT(void);
extern void INT2_INIT(void);
extern void Count_up(void);
extern void Count_down(void);
extern void Display(void);


#endif /* FUNCTIONS_H_ */
