#include "stm8s.h"
#include "main.h"
#include <math.h>


#define TH  __asm__("nop;");\
			__asm__("nop;");\
			__asm__("nop;");\
			__asm__("nop;");\
			__asm__("nop;");\
			__asm__("nop;");\
			__asm__("nop;");\
			__asm__("nop;");

#define TL  __asm__("nop;");\
			__asm__("nop;");\
			__asm__("nop;");

void CLK_init(void){
    CLK->CKDIVR=0;
}

void write_rgb(char r,char g, char b){
	int i;
	char up = GPIOD -> ODR | _BV(3);
	char down = GPIOD -> ODR & ~_BV(3);

	for(i = 8;i > 0;i--){
		if(g & (1 << (i-1))){
			GPIOD -> ODR = up;
			TH
			GPIOD -> ODR = down;
		}else{
			GPIOD -> ODR = up;
			TL
			GPIOD -> ODR = down;
		}
	}
	for(i = 8;i > 0;i--){
		if(r & (1 << (i-1))){
			GPIOD -> ODR = up;
			TH
			GPIOD -> ODR = down;
		}else{
			GPIOD -> ODR = up;
			TL
			GPIOD -> ODR = down;
		}
	}
	for(i = 8;i > 0;i--){
		if(b & (1 << (i-1))){
			GPIOD -> ODR = up;
			TH
			GPIOD -> ODR = down;
		}else{
			GPIOD -> ODR = up;
			TL
			GPIOD -> ODR = down;
		}
	}
	for(i = 0;i < 250;i++){}
}

int main() {
	unsigned long i,y;
	CLK_init();

	GPIOD -> DDR |= _BV(3);
	GPIOD -> ODR &= ~_BV(3);
	GPIOD -> CR1 = _BV(3);
	while(1){
		for(i = 0;i < 256;i++){
			write_rgb(i,0,0);
			for(y = 0;y < 30000;y++);
		}
		for(i = 0;i < 256;i++){
			write_rgb(0,i,0);
			for(y = 0;y < 30000;y++);
		}
		for(i = 0;i < 256;i++){
			write_rgb(0,0,i);
			for(y = 0;y < 30000;y++);
		}
		for(i = 0;i < 256;i++){
			write_rgb(255 - i,i,i);
			for(y = 0;y < 30000;y++);
		}
		for(i = 0;i < 256;i++){
			write_rgb(i,i,255 - i);
			for(y = 0;y < 30000;y++);
		}
		for(i = 0;i < 256;i++){
			write_rgb(i,255 - i,i);
			for(y = 0;y < 30000;y++);
		}
		for(i = 0;i < 256;i++){
			write_rgb(i,i,i);
			for(y = 0;y < 30000;y++);
		}
	};
}
