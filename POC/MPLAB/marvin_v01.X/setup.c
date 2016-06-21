/*
 *  FONCTIONS DE SETUP DU MARVIN
 */

#include "setup.h"


/*
 *  Fonction de Setup General du MARVIN
 *  Param1: Adresse de la structure de variables d'environement du Marvin
 */
void    marvin_setup(m_marvin *marvin)
{
    marvin_setup_timer(marvin);
    marvin_setup_sonar(&marvin->sonar1, &marvin->sonar2);
    marvin_setup_servo(&marvin->servo1, &marvin->servo2, &marvin->servo3);
    marvin_setup_ir();
    marvin_setup_uart(MARVIN_UART, MARVIN_UART_STATUS);
//  marvin_setup_uart_interrupt(5);     // Setup de l'interrupt de l'uart
//  marvin_setup_leds();                // Setup des leds
    INTCONbits.MVEC = 1;                // Interrupt controller en mode multi-vector
    __builtin_enable_interrupts();      // Ordonner au CPU de checker les interrupts
}

/*
 * Setup des TIMER
 * TIMER1: Timer absolue (definition du temps),     A DEFINIR
 * TIMER2: Reserve aux sortie PWM de servo,         PERIODE: 20msec pour PWM servo
 * TIMER3: Reserve aux sortie PWM des leds,         A DEFINIR
 * TIMER4: Timer temporaire, Dispo pour le reste,   DEFINIT AU BESOIN DANS LES FCT QUI L'UTILISE
 */
void    marvin_setup_timer(m_marvin *marvin)
{
    marvin->time = &time;
    marvin->time->nbr_periode = 0;
    marvin->time->tmr = MARVIN_TIMER1;
    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);   //  SETUP TMR1
    IFS0bits.T1IF = 0;                                                              //  Flag inter a 0
    IPC1bits.T1IP = 1;                                                              // Priority de 1
    IEC0bits.T1IE = 1;                                                              // Inter sur TMR1 enable
    marvin_set_periode(MARVIN_PR1, 10, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);       //  PERIODE DEFINIT a 10 sec
    marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER2);   //  SETUP TMR2
    marvin_set_periode(MARVIN_PR2, 20, TYPE_B, MARVIN_CONF_TIMER2, TIME_MSEC);      //  20msec POUR PWM SERVO
//  marvin_set_timer(MARVIN_CONF_TIMER3, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER3);   //  SETUP TMR3
//  marvin_set_periode(MARVIN_PR3, 20, TYPE_B, MARVIN_CONF_TIMER3, TIME_MSEC);      //  A DEFINIR
    marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER4);   //  SETUP TMR4 POUR FCT QUI L'UTILISE
}

/*
 *  Setup des sonar
 *  Param1: Objet Sonar1 de la struct marvin
 *  Param2: Objet Sonar2 de la struct marvin
 */
void    marvin_setup_sonar(m_sonar *sonar1, m_sonar *sonar2)
{
      sonar1->echo_attachpin = S1_ECHO_NPIN;
      sonar1->trig_attachpin = S1_TRIG_NPIN;
      sonar2->echo_attachpin = S2_ECHO_NPIN;
      sonar2->trig_attachpin = S2_TRIG_NPIN;
      marvin_set_sonar(&sonar1, SONAR1_SET_TRIG, SONAR1_STATE_TRIG, SONAR1_SET_ECHO, SONAR1_READ_ECHO);
      marvin_set_sonar(&sonar2, SONAR1_SET_TRIG, SONAR1_STATE_TRIG, SONAR1_SET_ECHO, SONAR1_READ_ECHO);
}

/*
 *  Setup des servo
 * Param1: Objet Servo1 de la struct marvin
 * Param2: Objet Servo2 de la struct marvin
 */
void    marvin_setup_servo(m_servo *servo1, m_servo *servo2, m_servo *servo3)
{
      marvin_attach_servo(&servo1, MARVIN_OC4, MARVIN_OC4RS, 550, 2400, OC_TIMER2, 20000);
      marvin_attach_servo(&servo2, MARVIN_OC3, MARVIN_OC3RS, 550, 2400, OC_TIMER2, 20000);
      servo3->pin = NULL;
      servo3->ocrs = NULL;
}

/*
 *  Fonction de setup des PIN pour les LEDS
 */
void    marvin_setup_leds()
{
 //   LATBbits.LATFB9 = 1;
 //   TRISBbits.TRISB9 = 0;
  //  LATBbits.LATB13 = 1;
   // TRISBbits.TRISB13 = 0;
}