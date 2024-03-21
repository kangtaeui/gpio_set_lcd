

#include "LCD.h"

static void write_command(char command);
static void write_data(char ch);
static void checkbusy();
uint8_t CurState = 0;

void GPIO_MODER()
{
  //SET D0~D7 MODER
  GPIOA->MODER |= ( 1 << 0 );	// SET PA0 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 2 );	// SET PA1 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 8 );	// SET PA4 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 12 );  // SET PA6 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 14 );	// SET PA7 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 16 );	// SET PA8 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 18 );	// SET PA9 OUTPUT MODE
  GPIOA->MODER |= ( 1 << 20 );	// SET PA10 OUTPUT MODE

  //SET RW,RS,E MODER
  GPIOB->MODER |= ( 1 << 8 );	//SET PB4 OUTPUT MODE
  GPIOB->MODER |= ( 1 << 10 );	//SET PB5 OUTPUT MODE
  GPIOB->MODER |= ( 1 << 12 );	//SET PB6 OUTPUT MODE
}

void LcdInit()
{
	//LCD_PORT	= 0xFF; // ddr on

	HAL_Delay(15);
	write_command(0x30);
	HAL_Delay(5);
	write_command(0x30);
	HAL_Delay(1);
	write_command(0x32);

	LcdCommand(FUNSET);
	LcdCommand(DISP_OFF);
	LcdCommand(ALLCLR);
	LcdCommand(ENTMOD);
	LcdCommand(DISP_ON);
}


void LcdCommand(char command)
{
	checkbusy();
	write_command(command);
}


void LcdMove(char line, char pos)
{
    char addr;
        
    addr = (line << 6) + pos;
    addr |= 0x80;	//beat set
    HAL_Delay(10);
    LcdCommand(addr);
}


void LcdPutchar(char ch)
{
      checkbusy();
      write_data(ch);
}


void LcdPuts(char *str)
{
  //str != NULL
	while (*str)
	{
                /*if(HAL_GPIO_ReadPin(LCD_BUTTON_PORT, LCD_BUTTON_PIN) == PUSHED)
                {
                    if( CurState == PUSHED)
                    {
                        LcdPutchar(*str);
                        CurState = RELEASED;
                        str++;
                        HAL_Delay(200);
                    } 
                }
                CurState = PUSHED;*/
                LcdPutchar(*str);
                str++;
	}
}

//set initial value
static void write_command(char command)
{
	/*char temp;
	temp = (command & 0xFF) | 0x04;*/ //use for upper beat & turn on enable pin
	
	/*LCD_PORT = temp;
	LCD_PORT = temp & ~0x04;	// E  0*/
  
        
	//lower
	/*HAL_GPIO_WritePin(LCD_Dx_PORT, GPIO_PIN_0, (command >> 0) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D1_PIN, (command >> 1) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D2_PIN, (command >> 2) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D3_PIN, (command >> 3) & 0x01 );
	//upper
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D4_PIN, (command >> 4) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D5_PIN, (command >> 5) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D6_PIN, (command >> 6) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D7_PIN, (command >> 7) & 0x01 );
        // RS = 0, RW = 0, E = 1;
	HAL_GPIO_WritePin(LCD_R_PORT, LCD_RS_PIN, RESET);
	HAL_GPIO_WritePin(LCD_R_PORT, LCD_RW_PIN, RESET);
        HAL_GPIO_WritePin(LCD_R_PORT, LCD_E_PIN, SET);
	HAL_Delay(1);
        // ENABLE = 0
	HAL_GPIO_WritePin(LCD_R_PORT, LCD_E_PIN, RESET);
        HAL_Delay(1);*/
        

        //lower
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D0_PIN, (command >> 0) & 0x01 );
	if( ((command >> 0) & 0x01) == SET)
	{
		GPIOA->ODR |= LCD_D0_PIN;
	}
	else if( ((command >> 0) & 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D0_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D1_PIN, (command >> 1) & 0x01 );
	if( ((command >> 1) & 0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D1_PIN;
	}
	else if( ((command >> 1) & 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D1_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D2_PIN, (command >> 2) & 0x01 );
	if( ((command >> 2) & 0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D2_PIN;
	}
	else if( ((command >> 2)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D2_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D3_PIN, (command >> 3) & 0x01 );
	if( ((command >> 3)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D3_PIN;
	}
	else if( ((command >> 3)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D3_PIN;
	}

	//upper
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D4_PIN, (command >> 4) & 0x01 );
	if( ((command >> 4)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D4_PIN;
	}
	else if( ((command >> 4)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D4_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D5_PIN, (command >> 5) & 0x01 );
	if( ((command >> 5)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D5_PIN;
	}
	else if( ((command >> 5)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D5_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D6_PIN, (command >> 6) & 0x01 );
	if( ((command >> 6)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D6_PIN;
	}
	else if( ((command >> 6)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D6_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D7_PIN, (command >> 7) & 0x01 );
	if( ((command >> 7)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D7_PIN;
	}
	else if( ((command >> 7)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D7_PIN;
	}

	// RS = 0, RW = 0, E = 1;
	//HAL_GPIO_WritePin(LCD_R_PORT, LCD_RS_PIN, RESET);
	GPIOB->ODR &=  ~LCD_RS_PIN;
	//HAL_GPIO_WritePin(LCD_R_PORT, LCD_RW_PIN, RESET);
        GPIOB->ODR &=  ~LCD_RW_PIN;
	
	//HAL_GPIO_WritePin(LCD_R_PORT, LCD_E_PIN, SET);
	GPIOB->ODR |=  LCD_E_PIN;

	HAL_Delay(1);
    // ENABLE = 0
	//HAL_GPIO_WritePin(LCD_R_PORT, LCD_E_PIN, RESET);
	GPIOB->ODR &= ~LCD_E_PIN;
	HAL_Delay(1);


        
}


static void write_data(char ch)
{
	//0x05 = 101, RS=1 , RW=0, E=1
	/*unsigned char temp;
	temp = (ch & 0xF0) | 0x05;*/

	/*//RS = 1, RW = 0 , ENABLE = 1
	HAL_GPIO_WritePin(LCD_R_PORT, LCD_RS_PIN, SET);
	HAL_GPIO_WritePin(LCD_R_PORT, LCD_RW_PIN, RESET);
	//LCD_PORT = temp;
	LCD_PORT = temp & ~0x08;
	//8bit print
	//lower
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D0_PIN, (ch >> 0) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D1_PIN, (ch >> 1) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D2_PIN, (ch >> 2) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D3_PIN, (ch >> 3) & 0x01 );
	//upper
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D4_PIN, (ch >> 4) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D5_PIN, (ch >> 5) & 0x01 );
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D6_PIN, (ch >> 6) & 0x01);
	HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D7_PIN, (ch >> 7) & 0x01 );

        //RS = 1, RW = 0 , ENABLE = 1
	HAL_GPIO_WritePin(LCD_R_PORT, LCD_RS_PIN, SET);
	HAL_GPIO_WritePin(LCD_R_PORT, LCD_RW_PIN, RESET);
        HAL_GPIO_WritePin(LCD_R_PORT, LCD_E_PIN, SET);
	HAL_Delay(1);
        //ENABLE = 0;
	HAL_GPIO_WritePin(LCD_R_PORT, LCD_E_PIN, RESET);
        HAL_Delay(1);*/
  
        	//lower
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D0_PIN, (command >> 0) & 0x01 );
	  //lower
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D0_PIN, (command >> 0) & 0x01 );
	if( ((ch >> 0) & 0x01) == SET)
	{
		GPIOA->ODR |= LCD_D0_PIN;
	}
	else if( ((ch >> 0) & 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D0_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D1_PIN, (command >> 1) & 0x01 );
	if( ((ch >> 1) & 0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D1_PIN;
	}
	else if( ((ch >> 1) & 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D1_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D2_PIN, (command >> 2) & 0x01 );
	if( ((ch >> 2) & 0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D2_PIN;
	}
	else if( ((ch >> 2)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D2_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D3_PIN, (command >> 3) & 0x01 );
	if( ((ch >> 3)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D3_PIN;
	}
	else if( ((ch >> 3)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D3_PIN;
	}

	//upper
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D4_PIN, (command >> 4) & 0x01 );
	if( ((ch >> 4)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D4_PIN;
	}
	else if( ((ch >> 4)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D4_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D5_PIN, (command >> 5) & 0x01 );
	if( ((ch >> 5)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D5_PIN;
	}
	else if( ((ch >> 5)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D5_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D6_PIN, (command >> 6) & 0x01 );
	if( ((ch >> 6)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D6_PIN;
	}
	else if( ((ch >> 6)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D6_PIN;
	}
	//HAL_GPIO_WritePin(LCD_Dx_PORT, LCD_D7_PIN, (command >> 7) & 0x01 );
	if( ((ch >> 7)&0x01) == SET)
	{
		GPIOA->ODR |=  LCD_D7_PIN;
	}
	else if( ((ch >> 7)& 0x01) == RESET)
	{
		GPIOA->ODR &= ~LCD_D7_PIN;
	}

	// RS = 0, RW = 0, E = 1;
	//HAL_GPIO_WritePin(LCD_R_PORT, LCD_RS_PIN, SET);
	GPIOB->ODR |=  LCD_RS_PIN;
	//HAL_GPIO_WritePin(LCD_R_PORT, LCD_RW_PIN, RESET);
        GPIOB->ODR &=  ~LCD_RW_PIN;
	
	//HAL_GPIO_WritePin(LCD_R_PORT, LCD_E_PIN, SET);
	GPIOB->ODR |=  LCD_E_PIN;
	
	HAL_Delay(1);
        // ENABLE = 0
	//HAL_GPIO_WritePin(LCD_R_PORT, LCD_E_PIN, RESET);
	GPIOB->ODR &= ~LCD_E_PIN;
	HAL_Delay(1);
}



static void checkbusy()
{
	HAL_Delay(1);
}




