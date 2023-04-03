#include<reg52.h>

sbit beep=P1^5;

void Delay_10us(unsigned int time)
{
	while(time--);
}

void Simulate_Pwm(unsigned char period, unsigned char duty)
{
	unsigned char low = period / 100 * duty; 
	unsigned char high = period - low;       
		
	beep = 0;        
	Delay_10us(low); 
		
	beep = 1;        
	Delay_10us(high);
}