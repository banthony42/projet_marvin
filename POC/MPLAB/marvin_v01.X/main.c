/*
 * Auteur : abary, amulin, banthony, tbelmaison
 * Premiere Version du projet Marvin sur le PIC32MX340F512H
 *
 */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"
#include "sonar.h"

/*
 * Trouver comment faire pour manipuler dirrectement l'adresse memoire des registres
 * et pas par le nom, pour faire des fonctions generiques
*/
/*
 * Fonction qui attend une donne en degree (de 0 a 180) pour faire pivoter le
 * servo
 */


/*
 * Faire une page pour les serovs -> servo.c , servo.h plus propre que
 * d'avoir un main de 50000 fonctions
 */
//OC1/ RDO -> pin 46
//
/*
void    marvin_servo_write(s8 teta)
{
    teta = 0;
}
*/
/*
 * Premier Param -> timer a utiliser
 * Deuzeieme Param -> Periode
 * */



/*
 * Il faut configurer les interruptes;
*/
/*
 * MAAAAAAAAAAAAAAIIIIIIIIIIIIIIIIIIIIIIIIIINNNNNNNNNNNN
 */

//marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);


/*
 * Test des fonctions Timer => OK
 * Test des fonctions Servo =>ok
 * Test des fonctions Sonars => Fonction faites, a tester
 * Test des fonctions IR => fonctions faites, a tester
 * test des fonctios de l'UART -> NONE
 */

m_servo servo1;
m_sonar sonar1;
m_sonar sonar2;
void    __ISR(7, IPL5) btn_interrupt()
{
    u16 test1 = 0;

    LATFbits.LATF1 = !LATFbits.LATF1;
    IFS0bits.INT1IF = 0;
//    test1 = marvin_capture(&sonar1);
    test1 = capture_ir(MARVIN_CONF_TIMER3, MARVIN_PR3, MARVIN_TIMER3);
    _nop();
}

int    main()
{
    LATFbits.LATF1 = 1;
    TRISFbits.TRISF1 = 0;

    TRISDbits.TRISD8 = 1;// Configuration du btn comme une input;s
    // configuration de linterrupt btn
            IFS0bits.INT1IF = 0;
            IPC1bits.INT1IP = 5;
            IEC0bits.INT1IE = 1;
    SERVO1 = 0;   // Test si vraiment necessaire pour la sortie OC4
 
    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS01, TIMER_GATE_OFF, MARVIN_TIMER1);
    marvin_set_periode(MARVIN_PR1, 1, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);

//    marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER2);   // setup TIMER2 pour PWM
//    marvin_set_periode(MARVIN_PR2,1, TYPE_B, MARVIN_CONF_TIMER2, TIME_SEC);   // setup periode TIMER2 a 19ms pour PWM servo

    // marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER4);
    // marvin_attach_servo(&servo1, MARVIN_OC4, MARVIN_OC4RS,544, 2400, OC_TIMER2, 20000);

    marvin_set_timer(MARVIN_CONF_TIMER3, TCKPS011, TIMER_GATE_OFF, MARVIN_TIMER3 );

    sonar1.echo_attachpin = S1_ECHO_NPIN;   // Definition du num de la PIN echo
    sonar1.trig_attachpin = S1_TRIG_NPIN;   // Definition du num de la PIN trigger

    sonar2.echo_attachpin = S2_ECHO_NPIN;
    sonar2.trig_attachpin = S2_TRIG_NPIN;
    //Timer set a 1MHz pour le sonar, periode 1 seconde
    marvin_set_sonar(&sonar1, SONAR1_SET_TRIG, SONAR1_STATE_TRIG, SONAR1_SET_ECHO, SONAR1_READ_ECHO);
 //   marvin_set_sonar(&sonar2, SONAR1_SET_TRIG, SONAR1_STATE_TRIG, SONAR1_SET_ECHO, SONAR1_READ_ECHO);
    asm volatile ("nop");

    // int test[10]= { 0, 180, 90, 20, 45, 76, 83 ,45, 180, 0, 90};
    //int i = 0;
    INTCONbits.MVEC = 1; // Interrupt controller en mode multi-vector
    __builtin_enable_interrupts(); // Ordonner au CPU de checker les interrupts
    while (1)
    {

        // utiliser le btn RD8 pour les tests plutot que le TMR
        /*
        if (TMR1 == PR1)
        {// coder le watchdog timer si on reste bloquer dans une des fonctions
            LATFbits.LATF1 = !LATFbits.LATF1;
            TMR1 = 0;
            //marvin_move_servo(&servo1, i += 5);
            //if (i == 180)
             //   i = 0;
        }
         */
       
            }
    return (0);
}
