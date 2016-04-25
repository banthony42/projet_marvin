/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on April 21, 2016, 4:20 PM
 */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"

/*
 * Configuration :
 * - Frequence CPU = 8MHz
 * - Frequence peripheriques = 1MHZ
 */

u16 servo_pulse_min = 500; // Duty Cycle de 0.5ms
u16 servo_pulse_max = 2500; // Duty Cycle de 2.5ms
u16 len;
u8 pwm_way = 0;
u8 debounce = 0;

/*
 * Contexte : test du servo
 * Cet interrupt incremente ou decremente l'angle du servo a chaque periode
 * du timer 1. Une fois en butee, on change le sens de rotation via la
 * variable pwm_way
 *
 */
void __ISR(_TIMER_4_VECTOR, IPL5) timer4_handler(void)
{
//    LATFbits.LATF1 = !LATFbits.LATF1;
    if (pwm_way)
        OC1RS++;
    else if (!pwm_way)
        OC1RS--;
    if (OC1RS == servo_pulse_min || OC1RS == servo_pulse_max)
    {
        pwm_way = !pwm_way;
    }
    IFS0bits.T4IF = 0;
}

/*
 *
 * Cet interrupt envoie une impulsion de 10us sur le pin E0
 */
void __ISR(7, IPL5) btn_interrupt_handler()
{
    LATEbits.LATE0 = 1;
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");

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
    u16 input_value;
//    allinone_servo_test();
//    allinone_sonar_test();
    allinone_IR_test();
    while (1)
    {
        input_value = analogReadIR();
    }
    return (0);
}

/*
 * Routine d'imitialisation pout lecture de la valeur analogique du
 * pin Vout du capteur IR sur le pin RB4
 * Test realise pour module Sharp GP2Y0A02YK0F
 */
void    allinone_IR_test(void)
{
    sharp_pin_setup();
    timer_4_setup();
    PR4 = 10000;
}


/*
 * Routine d'initialisation pour test du servo.
 * Utilise l'interrupt du timer 4 pour faire varier la position du servo
 * au cours du temps
 */
void    allinone_servo_test(void)
{
    timer_4_setup();
    timer_2_setup();
    servo_0_setup();
    interrupt_master_setup();
    interrupt_timer4_setup();
}


void    allinone_sonar_test(void)
{
    trigger_setup();
    button_setup();
    testPin_setup();
    echo_setup();
    interrupt_master_setup();
    //  interrupt_setup_button(); //interruption sur le btn RD8, ne pas utiliser les
                             // fonctions d'interrupts en meme temps
    //   interrupt_setup();
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

/*
 * Configuration du pin de lecture de la valeur renvoyee par le capteur IR Sharp
 * Note : il faut configurer le mode des pins ANx via le registre AD1PCFG (ADC)
 * pour pouvoir les utiliser en analogique ou en numerique
 */
void sharp_pin_setup()
{
    /*
     * Configuration I/O
     */
    LATBbits.LATB5 = 0;
    AD1PCFGbits.PCFG5 = 0; // RB5 en mode analogique
    TRISBbits.TRISB5 = 1; // RB5 en input
    /*
     * Configuration de l'ADC
     */
    AD1CHSbits.CH0SA = 5; // On selectionne le pin AN5 comme input positif du
                          // multiplexer A.
    AD1CHSbits.CH0NA = 0; // On selectionne Vr- comme tension de ref negative
                          // du multiplexer A
    AD1CON1bits.FORM = 0; // Formatage du resultat de la conversion en entier
                          // non-signe sur 16 bits (10 bits actifs)
    AD1CON1bits.SSRC = 0; // Samle clock source en mode manuel : il faudra clear
                          // le bit SAMP pour arreter le sample et initier la
                          // conversion
    AD1CON2bits.VCFG = 0; // On selectionne AVDD et AVSS comme reference de
                          // tension pour Vr+ et Vr-
    AD1CON2bits.CSCNA = 0; // Ne pas scanner les inputs (car on ne lit qu'un seul
                          // pin, AN5)
    AD1CON2bits.SMPI = 0; // 1 conversion par interrupt
    AD1CON2bits.BUFM = 0; // On replit le buffer avec les 16 bits d'un seul coup
    AD1CON2bits.ALTS = 0; // On utilise uniquement le multiplexer A
    AD1CON3bits.ADRC = 0; // Selection de PBCLK comme clock de conversion
    AD1CON3bits.ADCS = 0; // Prescaler de 2 pour cette clock. TAD = TPB / 2
                          // Donc TAD = 0.5MHz
    AD1CON3bits.SAMC = 1; // Sample time de 1 TAD. Ce n'est peut-etre pas utile,
                          // car en principe nous sommes en sampling manuel
    AD1CON1bits.ON = 1;   // On active le module ADC
}

void button_setup()
{
    TRISDbits.TRISD8 = 1; // on configure le button comme input
}

/*
 * Config du timer 1 (1 MHz), 16 bits
 */
void timer_1_setup(void)
{
    T1CONbits.TCS = 0; // Le timer prend PBCLK comme source
    T1CONbits.TGATE = 0; // Ignore
    T1CONbits.TCKPS = 0; // Prescaler a 1
    TMR1 = 0; // Reset du timer
//    PR1 = timer1_default_period; // Pour obtenir une periode de 1 seconde
    T1CONbits.ON = 1; // On active le timer 1
}

/*
 * Config du timer 4 (62,5 kHz), 16 bits
 * 62 500 ticks pour 1 seconde
 */
void timer_4_setup(void)
{
    T4CONbits.TGATE = 0; // Ignore
    T4CONbits.TCKPS = 4; // Prescaler a 16
    TMR4 = 0; // Reset du timer
    PR4 = 200; // Pour obtenir une periode
    T4CONbits.ON = 1; // On active le timer 4
}

/*
 * Config du timer 2 (utilise pour le PWM, 1MHz), 16 bits
 * La periode du signal PWM ne doit pas depasser 20ms
 */
void timer_2_setup(void)
{
    T2CONbits.TGATE = 0; // Ignore
    T2CONbits.TCKPS = 0; // Prescaler a 1
    TMR2 = 0; // Reset du timer
    PR2 = 19000; // Periode de 19 ms (+1) pour le signal PWM
    T2CONbits.ON = 1; // On active le timer 2
}

void interrupt_button_setup(void)
{
    IFS0bits.INT1IF = 0; // clear le flag d'interrupt
    IPC1bits.INT1IP = 5; // prorite de 5
    IEC0bits.INT1IE = 1; // Activer  l'interrupt pour le button
}

/*
 * Utilise pour faire varier l'angle du servo au cours du temps
 */
void interrupt_timer4_setup(void)
{
    IPC4bits.T4IP = 5; // Prio pour le timer4
    IFS0bits.T4IF = 0; // clear le flag d'interrupt
    IEC0bits.T4IE = 1; // Activer l'interrupt pour le timer 4
}

/*
 * Appeler cette fonction pour activer les interrupts au niveau du CPU
 */
void interrupt_master_setup(void)
{
    INTCONbits.MVEC = 1; // Interrupt controller en mode multi-vector
    __builtin_enable_interrupts(); // Ordonner au CPU de checker les interrupts
}

void testPin_setup(void)
{
    LATFbits.LATF1 = 0; // On met le pin RF1 a 0
    TRISFbits.TRISF1 = 0; // On configure le pin de la led de test comme output
}

/*
 * Cette fonction initialise le pin OC1/RD0 pour l'utilisation d'un servomoteur
 */
void servo_0_setup(void)
{
    OC1CONbits.ON = 0; // OC1 off, on peut modifier les registres
    OC1CONbits.OCM = 6; // OC1 en mode PWM
    OC1CONbits.OCTSEL = 0; // On utilise le timer 2 (a 1MHz)
    OC1RS = 1500; // Duty Cycle initialise a 1.5 ms
    OC1CONbits.ON = 1; // OC1 actif
}

void trigger_setup(void)
{
    LATEbits.LATE0 = 0; // Pin trigger a 0
    TRISEbits.TRISE0 = 0; // output
}


/*
 * Lecture de la tension du Sharp IR via l'utilisation de l'ADC en mode manuel
 */
u16 analogReadIR(void)
{
    AD1CON1bits.SAMP = 1; // On lance le sampling
    TMR4 = 0;
    while (TMR4 < 6250) // On attend 100 ms
        ;
    AD1CON1bits.SAMP = 0; // On lance la conversion
    while (!(AD1CON1 && 0x0001)); // On attend la fin de la conversion
    return (ADC1BUF0);
}