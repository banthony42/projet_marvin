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
#include "uart.h"

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


m_sonar sonar1;
m_sonar sonar2;
u16 speed = 0;

void    __ISR(7, IPL5) btn_interrupt()
{
    //u16 test1 = 0;

   // LATFbits.LATF1 = !LATFbits.LATF1;
   
    //test1 = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);
//  test1 = marvin_capture(&sonar1);
//  test1 = capture_ir(MARVIN_CONF_TIMER3, MARVIN_PR3, MARVIN_TIMER3);
   // _nop();
    // test send message
    u8 tab[100] = "tbeauman a une petite bite, eurghiuergiqeurhgviweuhvbweurhviweurhgviuerhgrgneirughiweurhgirugh";

     marvin_send_message(tab, 100, MARVIN_UART_SEND, MARVIN_UART_STATUS, MARVIN_CONF_TIMER1, MARVIN_PR1, MARVIN_TIMER1);
      IFS0bits.INT1IF = 0;
}

int    main()
{
    m_servo servo1;
    LATFbits.LATF1 = 1;
    TRISFbits.TRISF1 = 0;

    TRISDbits.TRISD8 = 1;// Configuration du btn comme une input;s
    // configuration de linterrupt btn
    IFS0bits.INT1IF = 0;
    IPC1bits.INT1IP = 5;
    IEC0bits.INT1IE = 1;
    //SERVO1 = 0;   // Test si vraiment necessaire pour la sortie OC4
    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);
    marvin_set_periode(MARVIN_PR1, 1, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);
    //UART TEST
       marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER4);   // setup TIMER2 pour PWM

    marvin_setup_uart(MARVIN_UART, MARVIN_UART_STATUS);
   // _nop();
/*  Servo test
 *  marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER2);   // setup TIMER2 pour PWM
    marvin_set_periode(MARVIN_PR2, 20, TYPE_B, MARVIN_CONF_TIMER2, TIME_MSEC);   // setup periode TIMER2 a 19ms pour PWM servo
    marvin_attach_servo(&servo1, MARVIN_OC4, MARVIN_OC4RS, 550, 2400, OC_TIMER2, 20000);*/

/*    Sonar test
 *    sonar1.echo_attachpin = S1_ECHO_NPIN;   // Definition du num de la PIN echo
      sonar1.trig_attachpin = S1_TRIG_NPIN;   // Definition du num de la PIN trigger
      sonar2.echo_attachpin = S2_ECHO_NPIN;
      sonar2.trig_attachpin = S2_TRIG_NPIN;
      marvin_set_sonar(&sonar1, SONAR1_SET_TRIG, SONAR1_STATE_TRIG, SONAR1_SET_ECHO, SONAR1_READ_ECHO);
      marvin_set_sonar(&sonar2, SONAR1_SET_TRIG, SONAR1_STATE_TRIG, SONAR1_SET_ECHO, SONAR1_READ_ECHO);*/
/*    IR test*/
    //marvin_setup_ir();
    marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER4);
   // asm volatile ("nop");

    //int test[10]= { 0, 180, 90, 20, 45, 76, 83 ,45, 180, 90};
   // int i = 0;
    INTCONbits.MVEC = 1; // Interrupt controller en mode multi-vector
    __builtin_enable_interrupts(); // Ordonner au CPU de checker les interrupts


    u8 test[20] = {0};
    u8 nbr;

    while (1)
    {
// coder le watchdog timer si on reste bloquer dans une des fonctions
        if (TMR1 == PR1)
       {
            TMR1 = 0;
            LATFbits.LATF1 = !LATFbits.LATF1;
/*            marvin_move_servo(&servo1, speed);
            if (i == 10)
                i = 0;*/
        }
        if (U1STAbits.URXDA)
        {
            marvin_receive_message(test, 20, MARVIN_UART_RECEIVE, MARVIN_UART_STATUS, &nbr);
            _nop();
        }
    }
    return (0);
}
