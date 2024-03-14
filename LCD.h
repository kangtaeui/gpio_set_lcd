
/*
 * LCD.h
 *
 *  Created on: 2024. 3. 5.
 *      Author: 강태의
 */

#ifndef CORE_INC_LCD_H_
#define CORE_INC_LCD_H_

#include "main.h"
#include "stm32f4xx_hal.h"

#include "string.h"


#define ALLCLR			0x01	//clear screen
#define HOME 			0x02	//move cursor to home
#define LN21			0xc0	//move cursor to second line

#define ENTMOD			0x06	//entry mode
#define FUNSET			0x38	//function set for 8bit
#define DISP_ON			0x0c	//turn on display
#define DISP_OFF		0x08	//turn of display
#define CURSOR_ON		0x0e	//print cursor on screen
#define CURSOR_OFF  	        0x0c    //delete cursor on screen
#define CURSOR_LSHIFT 	        0x10  	//move cursor to left
#define CURSOR_RSHIFT           0x14 	//move cursor to right
#define DISP_LSHIFT		0x18	//move display to left
#define DISP_RSHIFT		0x1c	//move display to right




//--------------------------------------------------------------------
//PORT BASE SET
//#define D_PIN_BASE 0x40020000
//#define R_PIN_BASE 0x40020400
//#define BUTTON_PIN_BASE 0x40020800


//push button port
#define LCD_BUTTON_PORT 	((GPIO_TypeDef *) BUTTON_PIN_BASE)              //GPIOC
//push button pin
#define LCD_BUTTON_PIN 		(1U << 13)       //GPIO_PIN_13

//button state
//enum ButtonState { PUSHED =0 , RELEASED };
//uint8_t CurState = 0;
   
   
//LCD D0~D7 PORT
//#define LCD_Dx_PORT     ((GPIO_TypeDef *) D_PIN_BASE)     //GPIOA
//LCD D-~D7 PIN
#define LCD_D0_PIN      (1U << 0)				//GPIO_PIN_0
#define LCD_D1_PIN      (1U << 1)				//((uint16_t)0x0002)      GPIO_PIN_1
#define LCD_D2_PIN      (1U << 4)				//((uint16_t)0x0010)      //GPIO_PIN_4
#define LCD_D3_PIN      (1U << 6)				//((uint16_t)0x0040)      //GPIO_PIN_6
#define LCD_D4_PIN      (1U << 7)				//((uint16_t)0x0080)      //GPIO_PIN_7
#define LCD_D5_PIN      (1U << 8)				//((uint16_t)0x0100)      //GPIO_PIN_8
#define LCD_D6_PIN      (1U << 9)				//((uint16_t)0x0200)      //GPIO_PIN_9
#define LCD_D7_PIN      (1U << 10)				//((uint16_t)0x0400)      //GPIO_PIN_10

//LCD RS,RW,E PORT
// E : ENABLE SIGNAL
// RS : SIGNAL FOR SETTING DR or IR
// R/W : Read & Write
//#define LCD_R_PORT      ((GPIO_TypeDef *) R_PIN_BASE)      //GPIOB
//LCD RS,RW,E PIN
#define LCD_E_PIN       (1U << 6)      //GPIO_PIN_6
#define LCD_RW_PIN      (1U << 5)      //GPIO_PIN_5
#define LCD_RS_PIN      (1U << 4)      //GPIO_PIN_4
//------------------------------------------------------------------


//lcd control function
void LcdInit();
void LcdCommand(char command);
void LcdMove(char line, char pos);
void LcdPutchar(char ch);
void LcdPuts(char *str);



#endif /* CORE_INC_LCD_H_ */
