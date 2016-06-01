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
void	marvin_setup_pwm(u32 timer, u32 period, u32 pin)
{
	OC1CON = 0x000;
	OC1R = 0x0064; // Initialize primary Compare register
	OC1RS = 0x0064; // Initialize secondary Compare register
	OC1CON = 0x0006; // Configure


	PR2 = 0x00C7; // Il faut faire calcul pour avoir une periode de 20ms;
				 // Il faut faire une fonction liee Au tImers pours les configurer
				 // de maniere simple
	//Interruptions .....
	//Utiliser OCTSEL pour
	IFS0CLR = 0x00000100; // Clear the T2 interrupt flag
	IEC0SET = 0x00000100; // Enable T2 interrupt
	IPC2SET = 0x0000001C; // Set T2 interrupt priority to 7
	T2CONSET = 0x8000; // Enable Timer2
	OC1CONSET = 0x8000; // Enable OC1
}
*/
/*
void	marvin_set_timner("PR1.. PR2...", "La periode demande")
{
// il faut recuprer la valeurs des OCS avec les Prescaler et faire un
// calcul en fonctions de ses donnes;
modification de PR1, PR2.....
}
*/
/*
 * Il faut configurer les interruptes;
*/
/*
 * MAAAAAAAAAAAAAAIIIIIIIIIIIIIIIIIIIIIIIIIINNNNNNNNNNNN
 */

//marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);


/*
 * Test des fonctions Timer => OK
 * Test des fonctions Servo => EN COURS
 */

int    main()
{
    m_servo servo1;

    LATFbits.LATF1 = 0;
    TRISFbits.TRISF1 = 0;

    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11 , TIMER_GATE_OFF, MARVIN_TIMER1);
    marvin_set_periode_s(MARVIN_PR1, 5, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);

    marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS01, TIMER_GATE_OFF, MARVIN_TIMER2);   // setup TIMER2 pour PWM
    marvin_set_periode_ms(MARVIN_PR2, 19, TYPE_B, MARVIN_CONF_TIMER2, TIME_MSEC);   // setup periode TIMER2 a 19ms pour PWM servo

    marvin_attach_servo(&servo1, MARVIN_OC1, MARVIN_OC1RS,500, 2500, OC_TIMER2);
    while (1)
    {
        if (!TMR1)
        {
            LATFbits.LATF1 = !LATFbits.LATF1;
            marvin_moove_servo(&servo1, 180);
        }
        marvin_moove_servo(&servo1, 0);
    }
    return (0);
}
