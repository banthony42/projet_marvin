/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on April 21, 2016, 4:20 PM
 */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"

u16 timer1_default_period = 62500;

void __ISR(_TIMER_1_VECTOR, IPL5) timer1_handler(void)
{
    LATFbits.LATF1 = !LATFbits.LATF1;
    IFS0bits.T1IF = 0;
}

int main()
{
    timer_setup();
    testPin_setup();
    interrupt_setup();
    while (1)
    {
    }
    return (0);
}

void timer_setup(void)
{
    // Note : les configbits sont configures de maniere a obtenir 62500 tick
    // de l'oscillateur interne par seconde
    T1CONbits.TCS = 0; // Le timer prend PBCLK comme source
    T1CONbits.TGATE = 0; // Ingore
    TMR1 = 0; // Reset du timer
    PR1 = timer1_default_period; // Pour obtenir une periode de 1 seconde
    T1CONbits.ON = 1; // On active le timer 1
}

void interrupt_setup(void)
{
    INTCONbits.MVEC = 1; // Interrupt controller en mode multi-vector
    IEC0bits.T1IE = 1; // Activer l'interrupt pour le timer 1
    IPC1bits.T1IP = 5; // Prio pour le timer1
    IFS0bits.T1IF = 0; // Interrupt flag du timer 1 a 0 (au cas ou)
    __builtin_enable_interrupts(); // Ordonner au CPU de checker les interrupts
}

void testPin_setup(void)
{
    LATFbits.LATF1 = 0; // On met le pin RF1 a 0
    TRISFbits.TRISF1 = 0; // On configure le pin de la led de test comme output
}