#include <P18F67J60.h>

#pragma config WDT = OFF
#pragma config FOSC = HSPLL
#pragma config XINST = OFF
#define button PORTBbits.RB0


void pwm60 (void);
void pwm100 (void);
void halfSec_delay (void);

void main(void)
{
int button_press = 0;
int i;	
ADCON1 = 0x06; //Sets RA0-RA5 & RE0-RE2 to digital mode
CMCON = 0x07; //Disable Comparators on RD0-RD3
TRISD = 0;
TRISBbits.TRISB0 = 1;
TRISBbits.TRISB4 = 0;

while(1)
{
	PORTDbits.RD0 = 0;
	PORTDbits.RD1 = 0;
	if(button == 0 ){
		for (i = 0; i<5; i++){
			PORTBbits.RB4 = 0;
			halfSec_delay();
			PORTBbits.RB4 = 1;
			halfSec_delay();
		}
		pwm100();
		button_press = 1;
	}			
	PORTDbits.RD0 = 0;
	PORTDbits.RD1 = 0;
	if(button_press == 1){
		for (i=0; i<3; i++){
			PORTBbits.RB4 = 0;
			halfSec_delay();
			halfSec_delay();
			PORTBbits.RB4 = 1;
			halfSec_delay();
			halfSec_delay();
		}
		pwm60();
		button_press = 0;
	}
}

}
void halfSec_delay (void)
{
	T0CON = 0x07;
	TMR0H = 0xD0;
	TMR0L = 0x51;
	T0CONbits.TMR0ON = 1;
  	while(INTCONbits.TMR0IF == 0);
	T0CONbits.TMR0ON = 0;
	INTCONbits.TMR0IF = 0;
}
void pwm60 (void)
{
	CCP4CON=0;
	PR2 = 148;
	CCPR4L = 51;
	TRISDbits.TRISD2 = 0;
	T2CON = 0x00;
	CCP4CON = 0x3C;
	TMR2 = 0;
	T2CONbits.TMR2ON = 1;
	while(1)
	{
		PIR1bits.TMR2IF = 0;
		while(PIR1bits.TMR2IF == 0){
			PORTDbits.RD0 = 1;
			PORTDbits.RD1 = 0;	
		}
		if (button == 0){
			break;
		}
	}
}
void pwm100 (void)
{
	CCP4CON=0;
	PR2 = 148;
	CCPR4L = 148;
	TRISDbits.TRISD2 = 0;
	T2CON = 0x00;
	CCP4CON = 0x0C;
	TMR2 = 0;
	T2CONbits.TMR2ON = 1;
	while(1)
	{
		PIR1bits.TMR2IF = 0;
		while(PIR1bits.TMR2IF == 0){
			PORTDbits.RD0 = 0;
			PORTDbits.RD1 = 1;	
		}
		if (button == 0){
			break;
		}			  	
	}
}

