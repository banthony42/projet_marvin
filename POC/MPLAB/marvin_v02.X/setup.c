/*
 *  FONCTIONS DE SETUP DU MARVIN
 */

#include "setup.h"

void    marvin_enable_sensor_servo()
{

    LATBbits.LATB11 = 0;        // ALIM SENSOR, 1 = OFF , 0 = ON
    TRISBbits.TRISB11 = 0;
    LATBbits.LATB10 = 1;        // ALIM SERVO 1 = ON, 0 = OFF
    TRISBbits.TRISB10 = 0;
}

/*
 *  Fonction de Setup General du MARVIN
 *  Param1: Adresse de la structure de variables d'environement du Marvin
 */
void    marvin_setup(m_marvin *marvin)
{
    _nop();
    marvin_mapping_pin();
    marvin_setup_timer(marvin);
    marvin_setup_sonar(&marvin->sonar_right, &marvin->sonar_left);
    marvin_setup_servo(&marvin->servo_yaw, &marvin->servo_pitch, &marvin->servo_scan);
    marvin_setup_ir();
    marvin_setup_interrupt();
    marvin->counter1 = 0;
    marvin_setup_uart();
    marvin_setup_leds();
    marvin_tempo(2000);
    marvin_enable_sensor_servo();
    marvin_tempo(2000);
}

/*
 * Mapping des PIN du PIC32
 * SERVO, UART, PWM LEDS
 */
void    marvin_mapping_pin()
{
    TRISBbits.TRISB2 = 1;       //  Config de la PIN en input pour UARTRX
    ANSELBbits.ANSB2 = 0;       //  Pin en digital pour la reception de l'uart
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
    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);   //  SETUP TMR1
    marvin_set_periode(MARVIN_PR1, TIME_TMR1, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);//  PERIODE DEFINIT a 10 sec , TIME_TMR1 definis dans types.h , il doit etre secondes
    marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER2);   //  SETUP TMR2
    marvin_set_periode(MARVIN_PR2, 20, TYPE_B, MARVIN_CONF_TIMER2, TIME_MSEC);      //  20msec POUR PWM SERVO
    marvin_set_timer(MARVIN_CONF_TIMER3, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER3);   //  SETUP TMR3
    marvin_set_periode(MARVIN_PR3, 1, TYPE_B, MARVIN_CONF_TIMER3, TIME_MSEC);      //  A DEFINIR
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
    marvin_attach_servo(servo1, MARVIN_OC2, MARVIN_OC2RS, 400, 2400, OC_TIMER2, 20000);    //  YAW
    marvin_attach_servo(servo2, MARVIN_OC4, MARVIN_OC4RS, 500, 2500, OC_TIMER2, 20000);    //  PITCH
    marvin_attach_servo(servo3, MARVIN_OC1, MARVIN_OC1RS, 550, 2400, OC_TIMER2, 20000);    //  SCAN
    marvin_move_servo_speed(servo1, 90, 1 ,15);// init position a 90 degres
    marvin_move_servo_speed(servo2, 60, 1 ,15);// init position a 90 degres
    marvin_move_servo_speed(servo3, 90, 1 ,15);// init position a 90 degres
}

/*
 *  Fonction de setup des PIN pour les LEDS
 */
void    marvin_setup_leds()
{
    marvin_attach_led(&marvin.led_right, MARVIN_OC5, MARVIN_OC5RS, 0,1000, OC_TIMER3, 1000);
    marvin_attach_led(&marvin.led_left, MARVIN_OC3, MARVIN_OC3RS, 0,1000, OC_TIMER3, 1000);
    marvin_eye_glow();
    marvin_eye_glow();
    marvin_set_lux_speed(&marvin.led_left, 100, 1, 50);
    marvin_set_lux_speed(&marvin.led_right, 100, 1, 50);
}

void marvin_setup_interrupt()
{
    INTCONbits.MVEC = 1; // INterrupt Controller em mode multi-Vector
    __builtin_enable_interrupts(); // on dit au CPU d'activer les interrupts
//    marvin_setup_interrupt_tmr1();
    marvin_setup_interrupt_tmr3();
    marvin_setup_uart_interrupt(5);     // Setup de l'interrupt de l'uart
}

void    marvin_setup_interrupt_tmr1()
{
   IPC1bits.T1IP = 7; // Prorite max
   IFS0bits.T1IF = 0; // Clear l'interrupt
   IEC0bits.T1IE = 1; // INterrupt TMR1 enable
}

void    marvin_setup_interrupt_tmr3()
{
   IPC3bits.T3IP = 6;   // Priorite max
   IFS0bits.T3IF = 0;   // Clear l'interrupt
   IEC0bits.T3IE = 1; // INterrupt TMR1 enable
}


void    __ISR(_TIMER_3_VECTOR , IPL6) timer3_interrupt()
{
    /*
     * Au bout de 5 minutes passer en mode bloquant pendant 30~60 secondes
     * Mettre marvin a 90 degrees
     * LED des yeux quasi eteint
     * Envoyer un message UART_SEND_SLEEP en UART
     */
/*    if (marvin.servo_pitch.pos == marvin.servo_pitch.new_pos || marvin.servo_yaw.pos == marvin.servo_yaw.new_pos
            || marvin.servo_scan.pos == marvin.servo_scan.new_pos)
        marvin_stop_move(&marvin);*/

        if ((marvin.servo_pitch.vitesse && !(marvin.counter1 % marvin.servo_pitch.vitesse))
                && (marvin.servo_pitch.incr > 0 &&( marvin.servo_pitch.pos <  marvin.servo_pitch.new_pos)
                  || (marvin.servo_pitch.incr < 0 && (marvin.servo_pitch.pos > marvin.servo_pitch.new_pos))))
              marvin_move_servo(&marvin.servo_pitch, marvin.servo_pitch.pos + marvin.servo_pitch.incr, 0);


        if ((marvin.servo_yaw.vitesse && !(marvin.counter1 % marvin.servo_yaw.vitesse)) &&
                (marvin.servo_yaw.incr > 0 && (marvin.servo_yaw.pos < marvin.servo_yaw.new_pos)
                || (marvin.servo_yaw.incr < 0 && (marvin.servo_yaw.pos > marvin.servo_yaw.new_pos))))
            marvin_move_servo(&marvin.servo_yaw, marvin.servo_yaw.pos + marvin.servo_yaw.incr, 1);

        if ((marvin.servo_scan.vitesse && !(marvin.counter1 % marvin.servo_scan.vitesse)) &&
                (marvin.servo_scan.incr > 0 && (marvin.servo_scan.pos < marvin.servo_scan.new_pos)
                || (marvin.servo_scan.incr < 0 && (marvin.servo_scan.pos > marvin.servo_scan.new_pos))))
            marvin_move_servo(&marvin.servo_scan, marvin.servo_scan.pos + marvin.servo_scan.incr, 0);

        /*
         * Revoir les fonctions pour allumer les Yeux on peut simplifier les conditions
         */
        if ((marvin.led_left.vitesse && !(marvin.counter1 % marvin.led_left.vitesse)) &&
                (marvin.led_left.incr > 0 && (marvin.led_left.lux < marvin.led_left.new_lux)
                || (marvin.led_left.incr < 0 && (marvin.led_left.lux > marvin.led_left.new_lux))))
            marvin_set_lux(&marvin.led_left, marvin.led_left.lux + marvin.led_left.incr);
        else if (marvin.led_left.vitesse == 0)
            marvin_set_lux(&marvin.led_left, 0);

         if ((marvin.led_right.vitesse && !(marvin.counter1 % marvin.led_right.vitesse)) &&
                (marvin.led_right.incr > 0 && (marvin.led_right.lux < marvin.led_right.new_lux)
                || (marvin.led_right.incr < 0 && (marvin.led_right.lux > marvin.led_right.new_lux))))
            marvin_set_lux(&marvin.led_right, marvin.led_right.lux + marvin.led_right.incr);
        else if (marvin.led_right.vitesse == 0)
            marvin_set_lux(&marvin.led_right, 0);
         if (!(marvin.counter1 % 1000))
             marvin.counter3 += 1;
    marvin.counter1 += 1;
    IFS0bits.T3IF = 0;
    _nop();
}