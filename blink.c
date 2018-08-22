#define F_CPU 16000000
#define led_pin 6
#define led_ddr DDRD
#define led_port PORTD

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>


uint16_t tipa_random(){
        uint16_t m, a, c; 
        static uint16_t x0;
        m = 65111;
        a = 3928+PIND;
        c = 654;
        x0 +=  PINB+PINC;
        x0 = (a*x0+c)%m;
        if (x0>m) x0 = 6302; 
        return x0;    

}

void pwm_init(){
        TCCR0A |= (1 << COM0A1)|(1 << WGM01)|(1 << WGM00);
        TCCR0B |= (1 << CS01);
        TCNT0 = 0x00;     
}

void algo (uint16_t num){
        if (num > 60461) {
            OCR0A = 255;  
        } else if (num > 49976) {
            OCR0A = 230;
        } else if (num > 43801) {
            OCR0A = 215;
        } else if (num > 38524) {
            OCR0A = 200;
        } else if (num > 35971) {
            OCR0A = 180;
        } else if (num > 28694) {
            OCR0A = 160;
        } else if (num > 21417) {
            OCR0A = 140;
        } else if (num > 11140) {
            OCR0A = 120;
        } else if (num > 4863) {
            OCR0A = 100;
        } else if (num > 2087) {
            OCR0A = 90;
        } else if (num > 1065) {
            OCR0A = 70;
        } else if (num > 310) {
            OCR0A = 60;
        } else if (num > 154) {
            OCR0A = 40;
        } else {
            OCR0A = 20;
        }
}
        
int main(void)
{
        led_ddr |= 1 << led_pin ;
	led_port &= ~(1 << led_pin);
        pwm_init();
        while(1){
                uint16_t n = tipa_random();
                algo(n);
                _delay_ms(40);
        }
	return 0;
}