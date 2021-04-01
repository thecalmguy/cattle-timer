/* 
 * File:   first_picf.c
 * Author: Manik Mittal
 *
 * Created on 22 March, 2021, 11:40 PM
 */

#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = ON       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
#define RELAY_PIN RA0
#define INPUT_PIN RA5

#define MODE1_ONE 1
#define MODE1_TWO 2
#define MODE1_THREE 5

#define MODE2_ONE 1
#define MODE2_TWO 2
#define MODE2_THREE 5

int mode1=0;
int mode2=0;

void __interrupt() LEARN(void){
    INTF = 0;
//    unsigned short on_or_off = RA1;
    if (INPUT_PIN!=0){
        mode1 += 1;
        mode1 %= 3;
    }else if(INPUT_PIN==0){
        mode2 += 1;
        mode2 %= 3;
    }
}

void custom_delay_on(unsigned short mode_given,  unsigned short mode_given2){
    extern int mode1;
    extern int mode2;
    int seconds=0;
    
    if(mode_given==0){
        seconds = MODE1_ONE;
    }else if(mode_given==1){
        seconds = MODE1_TWO;
    }else if(mode_given==2){
        seconds = MODE1_THREE;
    }
    seconds*=10;
    for(int i=0;i<seconds;i++){
        if(mode1!=mode_given || mode2!=mode_given2){
            break;
        }
        __delay_ms(100);
    }
}

void custom_delay_off( unsigned short mode_given2, unsigned short mode_given){
    extern int mode2;
    extern int mode1;
    int seconds=0;
    
    if(mode_given==0){
        seconds = MODE2_ONE;
    }else if(mode_given==1){
        seconds = MODE2_TWO;
    }else if(mode_given==2){
        seconds = MODE2_THREE;
    }
    seconds*=10;
    for(int i=0;i<seconds;i++){
        if(mode2!=mode_given || mode1!=mode_given2){
            break;
        }
        __delay_ms(100);
    }
}

int main(int argc, char** argv) {
    
    ANSEL=0X00;
    TRISA=0XFE;
    TRISC=0X00;
    nRAPU=0;
    INTEDG=1;
    GIE=1;
    INTF=0;
    INTE=1;
    
    extern int mode1;
    extern int mode2;
    
    while (1) {
        RC0 = 0;
        RC1 = 0;
        RC2 = 0;
        RC3 = 0;
        RC4 = 0;
        RC5 = 0;
                
        if (mode1==0 && mode2==0) {
            RC0=1;
            RC5=1;
            
            RELAY_PIN = 1;
            custom_delay_on(0,0);
            RELAY_PIN = 0;
            custom_delay_off(0,0);
        } else if (mode1==0 && mode2==1) {
            RC0=1;
            RC4=1;
            
            RELAY_PIN = 1;
            custom_delay_on(0,1);
            RELAY_PIN = 0;
            custom_delay_off(0,1);
        } else if (mode1==0 && mode2==2) {
            RC0=1;
            RC3=1;
            
            RELAY_PIN = 1;
            custom_delay_on(0,2);
            RELAY_PIN = 0;
            custom_delay_off(0,2);
        } else if (mode1==1 && mode2==0) {
            RC1=1;
            RC5=1;
            
            RELAY_PIN = 1;
            custom_delay_on(1,0);
            RELAY_PIN = 0;
            custom_delay_off(1,0);
        } else if (mode1==1 && mode2==1) {
            RC1=1;
            RC4=1;
            
            RELAY_PIN = 1;
            custom_delay_on(1,1);
            RELAY_PIN = 0;
            custom_delay_off(1,1);
        } else if (mode1==1 && mode2==2) {
            RC1=1;
            RC3=1;
            
            RELAY_PIN = 1;
            custom_delay_on(1,2);
            RELAY_PIN = 0;
            custom_delay_off(1,2);
        } else if (mode1==2 && mode2==0) {
            RC2=1;
            RC5=1;
            
            RELAY_PIN = 1;
            custom_delay_on(2,0);
            RELAY_PIN = 0;
            custom_delay_off(2,0);
        } else if (mode1==2 && mode2==1) {
            RC2=1;
            RC4=1;
            
            RELAY_PIN = 1;
            custom_delay_on(2,1);
            RELAY_PIN = 0;
            custom_delay_off(2,1);
        } else if (mode1==2 && mode2==2) {
            RC2=1;
            RC3=1;
            
            RELAY_PIN = 1;
            custom_delay_on(2,2);
            RELAY_PIN = 0;
            custom_delay_off(2,2);            
        }

    }
//    return (EXIT_SUCCESS);
}

