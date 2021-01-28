/*
 * File:       Carrera.c
 * Author:     Diego Sebastian Mazariegos Guzman
 * Carne:      18808
 * Intitucion: UVG
 * Created on January 22, 2021, 9:29 AM
 */


#include <xc.h>    //libreia que contiene todas las definiciones

//******************************************************************************
//                          CONFIGURACION  
//******************************************************************************

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 8000000
#define PUSH1 PORTBbits.RB0
#define PUSH2 PORTBbits.RB1
#define PUSH3 PORTBbits.RB2
#define PUSH4 PORTBbits.RB3

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//******************************************************************************
//                              VARIABLES
//******************************************************************************

int ban = 0; // es la que permite que nuestro programa, para que mis contadores empiecen a funcionar
 
// int para numero enter 
// char para caracter

// EL PROTOTIPO SIEMPRE TIENE QUE IR ANTES DEL MAIN, ESTE LEE LAS FUNCIONES

//******************************************************************************
//                     PROTOTIPOS DE FUNCIONES
//******************************************************************************

//declaracion de funciones

void setup(void);
void semaforo(void);
void reset(void);
void cuenta1(void);
void cuenta2(void);

//******************************************************************************
//                           CODIGO PRINCIPAL
//******************************************************************************

void main(void) {
    
    setup();
    
    while(1)
    {
        if ((PUSH1 == 1) && (!ban)) // cuando el boton de semaforo esta presionado y la bandera desactivada empezara el funcionamiento del semaforo 
        {
            semaforo();
        }
        if ((PUSH2 == 1) && (ban))
        {
            cuenta1();
            __delay_ms(100);
        }
        if ((PUSH3 == 1) && (ban))
        {
            cuenta2();
            __delay_ms(100);
        }
        if (PUSH4 == 1){
            reset();
            __delay_ms(100);
            }
        }
    }
    
    //**************************************************************************
    //                       LOOP PRINCIPAL
    //**************************************************************************
    
   
        //    }
        //    }
        //    }
        //    }

//******************************************************************************
//                           CONFIGURACION
//******************************************************************************

void setup(void){

    ANSEL  = 0; // indica que los puertos son analogicos 
    ANSELH = 0; 
    
    TRISE  = 0; // limpia el puerto
    PORTE  = 0; 
    
    TRISA = 0;  // indica que mi puerto es una salida y que limpia dicho puerto
    PORTA = 0; 
    
    TRISC = 0;
    PORTC = 0;
    
    TRISB = 0B00001111;    //los primeros 3 puertos conectados como entradas
    PORTB = 0;
}
void semaforo(void){
    PORTE = 1;               // enciendo el primer led con delay de 100 ms
    __delay_ms(100);
    for(int i=0; i<=2; i++)  // 
    {
        PORTE = PORTE <<1;   // el bit se va a mover a la derecha
        __delay_ms(100);
    }
        ban =   1;
        PORTC = 0;
        PORTB = 0;
        PORTA = 0;
}
void cuenta1(void)   // primer jugador
{
    if (PORTA == 0)   // empieza desde cero
    {
        PORTA = PORTA++;
    }
    else
    {
        PORTA = PORTA << 1;
        if (PORTAbits.RA7 == 1)
        {
            PORTDbits.RD6 = 1;  // el primer jugador gano
            ban = 0;           // apagamos la bandera
        }
        else
        {
            PORTDbits.RD6 = 0;
        }
    }
}

void cuenta2(void)
{
    if (PORTB == 0)
    {
        PORTC = PORTC++;
    }
    else
    {
        PORTC = PORTC << 1;
        if (PORTCbits.RC7 == 1)
        {
            PORTDbits.RD7 = 1;
            ban = 0;
        }
        else
        {
            PORTDbits.RD7 = 0;
        }
    }
}

void reset(void)
{
PORTC = 0;
        PORTB = 0;
        PORTA = 0;
        PORTE = 0;
        ban  = 0;
}

