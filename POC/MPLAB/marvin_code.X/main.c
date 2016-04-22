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
u16 len;
u8 pwm_way = 0;
u8 debounce = 0;


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

void __ISR(7, IPL5) btn_interrupt_handler()
{
 //   LATFbits.LATF1 = !LATFbits.LATF1;
 //   IFS0bits.INT1IF = 0; // clear interrupt

    LATEbits.LATE0 = 1;
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    /*
    TMR1 = 0;
    while (TMR1 < 1)
        (void)TMR1;
     * */
   // stop++;
   // stop++;
    LATEbits.LATE0 = 0;
    IFS0bits.INT1IF = 0;
}

void    __ISR(11, IPL6) echo_interrupt()
{
    len = 0;
    TMR1 = 0;
    LATFbits.LATF1 = !LATFbits.LATF1;
    while (PORTDbits.RD9)
        len = TMR1;
    len /= 58;
    IFS0bits.INT2IF = 0;
}
/*
void __ISR(_OUTPUT_COMPARE_1_VECTOR, IPL17) testoutputcompare(void)
{
    IFS0CLR = 0x0040;
}
*/
int main()
{
    OSCCONbits.FRCDIV = 0;
    trigger_setup();
    timer_setup();
    button_setup();
   testPin_setup();
    echo_setup();
   interrupt_setup_button(); //interruption sur le btn RD8, ne pas utiliser les
                             // fonctions d'interrupts em meme temps
//   interrupt_setup();
 //   outputCompare_setup();
    while (1)
    {
    }
    return (0);
}

void    echo_setup()
{
    IEC0bits.INT2IE = 0;  // enable interrupt INT2
    TRISDbits.TRISD9 = 1; // INPUT echo sonar
    IFS0bits.INT2IF = 0;  // clear flag
    IPC2bits.INT2IP = 6;  // set priority level
    INTCONbits.INT2EP = 1; // front montant
    IEC0bits.INT2IE = 1;  // enable interrupt INT2
}
void button_setup()
{
    TRISDbits.TRISD8 = 1; // on configure le button comme input
}

void timer_setup(void)
{
    // Note : les configbits sont configures de maniere a obtenir 62500 tick
    // de l'oscillateur interne par seconde

    // Config du timer1
    T1CONbits.TCS = 0; // Le timer prend PBCLK comme source
    T1CONbits.TGATE = 0; // Ignore
    T1CONbits.TCKPS = 0; // Prescaler a 1
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

void interrupt_setup_button()
{
    INTCONbits.MVEC = 1;
    IFS0bits.INT1IF = 0; // clear le flag d'interrupt;
    IEC0bits.INT1IE = 1; // set inerrupt pour le button
    IPC1bits.INT1IP = 5; // prorite de 5
    __builtin_enable_interrupts(); // Ordonner au CPU de checker les interrupts
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

void trigger_setup(void)
{
    LATEbits.LATE0 = 0; // Pin trigger a 0
    TRISEbits.TRISE0 = 0; // output
}