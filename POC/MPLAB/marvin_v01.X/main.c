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


//m_sonar sonar1;
//m_sonar sonar2;
//u16 speed = 0;

//u8 test[500] = {0};
//u16 nbr = 0;

m_servo servo1;
m_servo servo2;
//u16 m_sonar1;
//u16 m_sonar2;
//u16 IR;

void    __ISR(7, IPL5) btn_interrupt()
{
//    u8 tab[100] = "tbeauman a une petite bite, eurghiuergiqeurhgviweuhvbweurhviweurhgviuerhgrgneirughiweurhgirugh";

    LATFbits.LATF1 = !LATFbits.LATF1;
//  marvin_send_message(tab, 100, MARVIN_UART_SEND, MARVIN_UART_STATUS, MARVIN_CONF_TIMER1, MARVIN_PR1, MARVIN_TIMER1);
//    m_sonar1 = marvin_capture(&sonar1);
    _nop();
//    m_sonar2 = marvin_capture(&sonar2);
    _nop();
        IFS0bits.INT1IF = 0;
}

/*// Interrupt lecture de message recu
void    __ISR(24, IPL5) uart_interrupt()
{
        while (U1STAbits.URXDA && nbr < 500)
        {
            test[nbr++] = U1RXREG;
        }
        if (nbr == 500)
            nbr = 0;
      IFS0bits.U1RXIF = 0;

}*/

int    main()
{
 //   m_sonar1 = 0;
 //   m_sonar2 = 0;
 //   IR = -1;
    u16 pos = 90;
    LATFbits.LATF1 = 1;
    TRISFbits.TRISF1 = 0;
    TRISDbits.TRISD8 = 1;
    // configuration de linterrupt btn
    IFS0bits.INT1IF = 0;
    IPC1bits.INT1IP = 5;
    IEC0bits.INT1IE = 1;

/*    // Interrupt sur l'Uart receive
    IFS0bits.U1RXIF = 0;
    IPC6bits.U1IP = 5;
    IEC0bits.U1RXIE = 1;*/

    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);
    marvin_set_periode(MARVIN_PR1, 3, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);

    //UART TEST
    marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER4);   // setup TIMER2 pour PWM
    //marvin_setup_uart(MARVIN_UART, MARVIN_UART_STATUS);
   // marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER4);
   // asm volatile ("nop");

      marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER2);     // setup TIMER2 pour PWM
      marvin_set_periode(MARVIN_PR2, 20, TYPE_B, MARVIN_CONF_TIMER2, TIME_MSEC);        // setup periode TIMER2 a 19ms pour PWM servo
    //marvin_set_timer(MARVIN_CONF_TIMER3, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER3);     // setup TIMER2 pour PWM
    //marvin_set_periode(MARVIN_PR3, 15, TYPE_B, MARVIN_CONF_TIMER3, TIME_MSEC);
/*      sonar1.echo_attachpin = S1_ECHO_NPIN;
      sonar1.trig_attachpin = S1_TRIG_NPIN;
      sonar2.echo_attachpin = S2_ECHO_NPIN;
      sonar2.trig_attachpin = S2_TRIG_NPIN;
      marvin_set_sonar(&sonar1, SONAR1_SET_TRIG, SONAR1_STATE_TRIG, SONAR1_SET_ECHO, SONAR1_READ_ECHO);
      marvin_set_sonar(&sonar2, SONAR1_SET_TRIG, SONAR1_STATE_TRIG, SONAR1_SET_ECHO, SONAR1_READ_ECHO);*/
      marvin_attach_servo(&servo1, MARVIN_OC4, MARVIN_OC4RS, 550, 2400, OC_TIMER2, 20000);
//      marvin_attach_servo(&servo2, MARVIN_OC3, MARVIN_OC3RS, 550, 2400, OC_TIMER2, 20000);
//      marvin_setup_ir();
    int test[10] = { 0, 180, 90, 20, 45, 76, 83 ,45, 180, 90};
    int test2[2] = {0, 180};
    int i = 0;
    int i2 = 0;
    INTCONbits.MVEC = 1;                // Interrupt controller en mode multi-vector
    __builtin_enable_interrupts();      // Ordonner au CPU de checker les interrupts
    marvin_move_servo(&servo1, pos);    // Pos Initial, tete au centre
    while (1)
    {
// coder le watchdog timer si on reste bloquer dans une des fonctions
/*        while (m_sonar1 < m_sonar2)
        {
            IR = 0;
            while ( IR < 100 && servo1.pos != 180)
            {
                marvin_move_servo(&servo1, servo1.pos + 10);
                IR = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);
            }
            m_sonar1 = 0;
            m_sonar2 = 0;

        }
        while ((m_sonar1 > 0 && m_sonar2 > 0) && (m_sonar1 < 180 || m_sonar2 < 180))
        {
            IR = 0;
            while (IR < 100 && servo1.pos != 0)
            {
                marvin_move_servo(&servo1, servo1.pos - 10);
                IR = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);
            }
            m_sonar1 = 0;
            m_sonar2 = 0;

        }*/
        if (TMR1 == PR1)
        {
            TMR1 = 0;
            LATFbits.LATF1 = !LATFbits.LATF1;
//            marvin_move2_servo(&servo1, test2[i2++]);
//            marvin_move_servo_speed(&servo1, test2[i2++], 1, 25);
            if (i2 == 2)
                i2 = 0;
            if (i == 10)
                i = 0;
        }
    }
    return (0);
}