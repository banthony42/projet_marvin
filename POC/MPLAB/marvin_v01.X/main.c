/*
 * Auteur : abary, amulin, banthony, tbelmaison
 * Premiere Version du projet Marvin sur le PIC32MX340F512H
 *
 */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Servo.h"
#include "types.h"
#include "timer.h"
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
 * Test des fonctions IR => en Travaux
 */



int    main()
{
    m_servo servo1;
    m_sonar sonar1;

    LATFbits.LATF1 = 1;
    TRISFbits.TRISF1 = 0;

    SERVO1 = 0;   // Test si vraiment necessaire pour la sortie OC4
 
    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11 , TIMER_GATE_OFF, MARVIN_TIMER1);
    marvin_set_periode(MARVIN_PR1, 1, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);
    
    marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER2);   // setup TIMER2 pour PWM
    marvin_set_periode(MARVIN_PR2,20, TYPE_B, MARVIN_CONF_TIMER2, TIME_MSEC);   // setup periode TIMER2 a 19ms pour PWM servo

   // marvin_attach_servo(&servo1, MARVIN_OC4, MARVIN_OC4RS,544, 2400, OC_TIMER2, 20000);
//    marvin_set_sonar(&sonar1);

   // int test[10]= { 0, 180, 90, 20, 45, 76, 83 ,45, 180, 0, 90};
    //int i = 0;
    // test du Sonar -> meme PIn que le POC; -> on feras les tests plus tard
    while (1)
    {
        if (TMR1 == PR1)
        {
            TMR1 = 0;
            LATFbits.LATF1 = !LATFbits.LATF1;
            //marvin_move_servo(&servo1, i += 5);
            //if (i == 180)
             //   i = 0;
        }
       
    }
    return (0);
}
