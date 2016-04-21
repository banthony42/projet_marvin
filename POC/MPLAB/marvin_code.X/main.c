/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on April 21, 2016, 4:20 PM
 */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"

// 1s = 62500 ticks

u16 timer1_default_period = 62500 / 10; // Frequence de 10 hertz pour le timer 1
u16 timer2_default_period = 62500 / 50; // Frequence de 50 hertz pour le PWM
u16 timer2_1ms_ref = 62500 / 1000; // Periode de 1ms
u16 timer2_2ms_ref = 62500 / 500;
u8 pwm_way = 0;

void __ISR(_TIMER_1_VECTOR, IPL5) timer1_handler(void)
{
//    LATFbits.LATF1 = !LATFbits.LATF1;
    if (pwm_way)
        OC1RS++;
    else if (!pwm_way)
        OC1RS--;
    if (OC1RS == timer2_1ms_ref || OC1RS == timer2_2ms_ref)
    {
        if (pwm_way == 0)
        {
            OC1RS = 62500 / 1000 ;
        }
        pwm_way = !pwm_way;
    }
    IFS0bits.T1IF = 0;
}

/*
void __ISR(_OUTPUT_COMPARE_1_VECTOR, IPL17) testoutputcompare(void)
{
    IFS0CLR = 0x0040;
}
*/
int main()
{
    timer_setup();
    testPin_setup();
    interrupt_setup();
    outputCompare_setup();
    while (1)
    {
    }
    return (0);
}

void timer_setup(void)
{
    // Note : les configbits sont configures de maniere a obtenir 62500 tick
    // de l'oscillateur interne par seconde

    // Config du timer1
    T1CONbits.TCS = 0; // Le timer prend PBCLK comme source
    T1CONbits.TGATE = 0; // Ignore
    TMR1 = 0; // Reset du timer
    PR1 = timer1_default_period; // Pour obtenir une periode de 1 seconde
    T1CONbits.ON = 1; // On active le timer 1

    // Config du timer2 (utilise pour le PWM)
//    T2CONbits. = 0; // Le timer prend PBCLK comme source
    T2CONbits.TGATE = 0; // Ignore
    TMR2 = 0; // Reset du timer
    PR2 = timer2_default_period; // Pour obtenir une periode de 1 seconde
    T2CONbits.ON = 1; // On active le timer 2
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

void outputCompare_setup(void)
{
    OC1CONbits.ON = 0; // OC1 off, on peut modifier les registres
    OC1CONbits.OCM = 6; // OC1 en mode PWM
    OC1CONbits.OCTSEL = 0; // On utilise le timer 2
    OC1RS = 62500 / 700;
    OC1CONbits.ON = 1; // OC1 actif
}