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
    marvin_mapping_pin();
    marvin_setup_timer(marvin);
    marvin_setup_sonar(&marvin->sonar1, &marvin->sonar2);
    marvin_setup_servo(&marvin->servo1, &marvin->servo2, &marvin->servo3);
    marvin_setup_ir();
//  marvin_setup_uart(MARVIN_UART, MARVIN_UART_STATUS);
//  marvin_setup_uart_interrupt(5);     // Setup de l'interrupt de l'uart
//  marvin_setup_leds();                // Setup des leds
//    INTCONbits.MVEC = 1;                // Interrupt controller en mode multi-vector
//    __builtin_enable_interrupts();      // Ordonner au CPU de checker les interrupts
}

/*
 * Mapping des PIN du PIC32
 * SERVO, UART, PWM LEDS
 */
void    marvin_mapping_pin()
{
    SYSKEY = 0x0;               //  Ensure OSCCON is locked
    SYSKEY = 0xAA996655;        //  Write key1 to SYSKEY
    SYSKEY = 0x556699AA;        //  Write key2 to SYSKEY - Cette sequence debloque la securite de IOLOCK, (ouvre droit en ecriture)
    CFGCONbits.IOLOCK = 0;      //  Peripheral Pin Register Select(PPS) is unlocked, Mappind is allowed
    RPB4Rbits.RPB4R = 0b0101;   //  Mapping de la PIN RPB4 en OC1   (SCAN SERVO)
    RPB5Rbits.RPB5R = 0b0101;   //  Mapping de la PIN RPB5 en OC2   (YAW SERVO)
    RPB9Rbits.RPB9R = 0b0101;   //  Mapping de la PIN RPB9 en OC3   (EYE LEFT)
    RPA4Rbits.RPA4R = 0b0101;   //  Mapping de la PIN RPA4 en OC4   (PITCH SERVO)
    RPB13Rbits.RPB13R = 0b0110; //  Mapping de la PIN RPB13 en OC5  (EYE RIGHT)
    RPB3Rbits.RPB3R = 0b0001;   //  Mapping de la PIN RPB3 en U1TX  (UART TRANSMIT)
    U1RXRbits.U1RXR = 0b0100;   //  Mapping de la PIN RPB2 en U1RX  (UART RECEIVE)
    CFGCONbits.IOLOCK = 1;      //  PPS is relock, Mapping pin is not allowed
    SYSKEY = 0x0;               // Relock the SYSKEY
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
    marvin_set_periode(MARVIN_PR1, 3, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);       //  PERIODE DEFINIT a 10 sec
    marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER2);   //  SETUP TMR2
    marvin_set_periode(MARVIN_PR2, 20, TYPE_B, MARVIN_CONF_TIMER2, TIME_MSEC);      //  20msec POUR PWM SERVO
    marvin_set_timer(MARVIN_CONF_TIMER3, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER3);   //  SETUP TMR3
    marvin_set_periode(MARVIN_PR3, 20, TYPE_B, MARVIN_CONF_TIMER3, TIME_MSEC);      //  A DEFINIR
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
      marvin_set_sonar(sonar1, SONAR_SET_TRIG, SONAR_STATE_TRIG, SONAR_SET_ECHO, SONAR_READ_ECHO);
      marvin_set_sonar(sonar2, SONAR_SET_TRIG, SONAR_STATE_TRIG, SONAR_SET_ECHO, SONAR_READ_ECHO);
}

/*
 *  Setup des servo
 * Param1: Objet Servo1 de la struct marvin
 * Param2: Objet Servo2 de la struct marvin
 */
void    marvin_setup_servo(m_servo *servo1, m_servo *servo2, m_servo *servo3)
{
    marvin_attach_servo(servo1, MARVIN_OC2, MARVIN_OC2RS, 550, 2400, OC_TIMER2, 20000);    //  YAW
    marvin_attach_servo(servo2, MARVIN_OC4, MARVIN_OC4RS, 550, 2400, OC_TIMER2, 20000);    //  PITCH
    marvin_attach_servo(servo3, MARVIN_OC1, MARVIN_OC1RS, 550, 2400, OC_TIMER2, 20000);    //  SCAN
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
