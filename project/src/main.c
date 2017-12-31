#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void Gonder_Komut(unsigned char);
void Ekran_Temizleme(void);
void String_Yazdir(char*);
void Kursor_Gonder(char,char);
void Lcd_Aktiflestirme(void);
void Karekter_Yazdir(unsigned char);

#define LCDPBASE                 GPIO_PORTB_BASE
#define LCDPENB   		 SYSCTL_PERIPH_GPIOB

void init_port_B() {
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTB_DIR_R |= 0xFF;
    GPIO_PORTB_AFSEL_R &= ~0xFF;
    GPIO_PORTB_DEN_R |= 0xFF;
}

#define Data4                               GPIO_PIN_4
#define Data5                               GPIO_PIN_5
#define Data6                               GPIO_PIN_6
#define Data7                               GPIO_PIN_7
#define RS                               GPIO_PIN_0
#define ENB                                GPIO_PIN_1


int main() {

	init_port_B();
	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |

	SYSCTL_XTAL_16MHZ);

	uint8_t sayi;

	volatile unsigned long delay;



	 volatile unsigned long clock_period_2 = SysCtlClockGet();
	 while(1){
		 sayi = (uint8_t) rand();
		 sayi = sayi %4;
		 switch (sayi){

		 case 0:

			 Lcd_Aktiflestirme();
			 Kursor_Gonder(1,1);
			 String_Yazdir("Kocaeli Uni");
			 for(delay = 0 ; delay < 5000000 ; delay++)
			 	;
			 Kursor_Gonder(2,1);
			 String_Yazdir("Harun YILDIZ");
			 for(delay = 0 ; delay < 5000000 ; delay++)
			 			 	 ;

			 break;
		 case 1:

			 Lcd_Aktiflestirme();
			 Kursor_Gonder(2,1);
			 String_Yazdir("Harun YILDIZ");
			 for(delay = 0 ; delay < 5000000 ; delay++)
			 	 ;
			 Kursor_Gonder(1,1);
			 String_Yazdir("Kocaeli Uni");
			 for(delay = 0 ; delay < 5000000 ; delay++)
			 			 	 ;

			 break;
		 case 2:
			 Lcd_Aktiflestirme();
						 Kursor_Gonder(2,16);
						 String_Yazdir("Harun YILDIZ");
						 for(delay = 0 ; delay < 5000000 ; delay++)
						 	 ;
						 for(int i=0;i<29;i++){
							 Gonder_Komut(0x18);
							 SysCtlDelay(8000000);

						 }
						 Ekran_Temizleme();
						 SysCtlDelay(8000000);
						 Kursor_Gonder(2,16);
						 String_Yazdir("Harun YILDIZ");
						 Kursor_Gonder(1,16);
						 String_Yazdir("Kocaeli Uni");
						 for(delay = 0 ; delay < 5000000 ; delay++)
						 			 	 ;
						 for(int i=0;i<29;i++){
							 Gonder_Komut(0x18);
						 							 SysCtlDelay(8000000);

						 						 }
			 break;
		 case 3:
			 Lcd_Aktiflestirme();
									 Kursor_Gonder(1,1);
									 String_Yazdir("Harun YILDIZ");
									 for(delay = 0 ; delay < 5000000 ; delay++)
									 	 ;
									 for(int i=0;i<29;i++){
										 Gonder_Komut(0x1E);
										 SysCtlDelay(8000000);

									 }
									 Ekran_Temizleme();
									 SysCtlDelay(8000000);
									 Kursor_Gonder(1,1);
					     			 String_Yazdir("Harun YILDIZ");
									 Kursor_Gonder(2,1);
									 String_Yazdir("Kocaeli Uni");
									 for(delay = 0 ; delay < 5000000 ; delay++)
									 			 	 ;
									 for(int i=0;i<29;i++){
										 Gonder_Komut(0x1E);
									 							 SysCtlDelay(8000000);

									 						 }
			 break;
		 default:

			 break;

		 }
	 }

}void Karekter_Yazdir(unsigned char d) {

    GPIOPinWrite(LCDPBASE , Data4 | Data5 | Data6 | Data7, (d & 0xf0) );
    GPIOPinWrite(LCDPBASE , RS, 0x01);
    GPIOPinWrite(LCDPBASE , ENB, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPBASE , ENB, 0x00);

    SysCtlDelay(50000);

    GPIOPinWrite(LCDPBASE , Data4 | Data5 | Data6 | Data7, (d & 0x0f) << 4 );
    GPIOPinWrite(LCDPBASE , RS, 0x01);
    GPIOPinWrite(LCDPBASE , ENB, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPBASE , ENB, 0x00);

    SysCtlDelay(50000);

}

void Kursor_Gonder(char x, char y){

        if(x==1)
        	Gonder_Komut(0x80+((y-1)%16));
        else
        	Gonder_Komut(0xC0+((y-1)%16));
}
void Ekran_Temizleme(void){
	Gonder_Komut(0x01);
        SysCtlDelay(10);
}

void Gonder_Komut(unsigned char c) {

        GPIOPinWrite(LCDPBASE , Data4 | Data5 | Data6 | Data7, (c & 0xf0) );
        GPIOPinWrite(LCDPBASE , RS, 0x00);
        GPIOPinWrite(LCDPBASE , ENB, 0x02);
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPBASE , ENB, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPBASE , Data4 | Data5 | Data6 | Data7, (c & 0x0f) << 4 );
        GPIOPinWrite(LCDPBASE , RS, 0x00);
        GPIOPinWrite(LCDPBASE , ENB, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPBASE , ENB, 0x00);

        SysCtlDelay(50000);

}


void String_Yazdir( char* s){

        while(*s)
                Karekter_Yazdir(*s++);
}


void Lcd_Aktiflestirme() {

        SysCtlPeripheralEnable(LCDPENB);
        GPIOPinTypeGPIOOutput(LCDPBASE , 0xFF);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPBASE , RS,  0x00 );

        GPIOPinWrite(LCDPBASE , Data4 | Data5 | Data6 | Data7,  0x30 );
        GPIOPinWrite(LCDPBASE , ENB, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPBASE , ENB, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPBASE , Data4 | Data5 | Data6 | Data7,  0x30 );
        GPIOPinWrite(LCDPBASE , ENB, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPBASE , ENB, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPBASE , Data4 | Data5 | Data6 | Data7,  0x30 );
        GPIOPinWrite(LCDPBASE , ENB, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPBASE , ENB, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPBASE , Data4 | Data5 | Data6 | Data7,  0x20 );
        GPIOPinWrite(LCDPBASE , ENB, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPBASE , ENB, 0x00);

        SysCtlDelay(50000);

        Gonder_Komut(0x28);
        Gonder_Komut(0xC0);
        Gonder_Komut(0x06);
        Gonder_Komut(0x80);
        Gonder_Komut(0x28);
        Gonder_Komut(0x0f);
        Ekran_Temizleme();

}


