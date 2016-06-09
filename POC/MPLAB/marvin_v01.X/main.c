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


m_sonar sonar1;
m_sonar sonar2;
u16 speed = 0;

u8 test[500] = {0};
u16 nbr = 0;

void    __ISR(7, IPL5) btn_interrupt()
{
    u8 tab[100] = "tbeauman a une petite bite, eurghiuergiqeurhgviweuhvbweurhviweurhgviuerhgrgneirughiweurhgirugh";

     marvin_send_message(tab, 100, MARVIN_UART_SEND, MARVIN_UART_STATUS, MARVIN_CONF_TIMER1, MARVIN_PR1, MARVIN_TIMER1);
     IFS0bits.INT1IF = 0;
}

// Interrupt lecture de message recu
void    __ISR(24, IPL5) uart_interrupt()
{
        while (U1STAbits.URXDA && nbr < 500)
        {
            test[nbr++] = U1RXREG;
        }
        if (nbr == 500)
            nbr = 0;
      IFS0bits.U1RXIF = 0;
     
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

    // Interrupt sur l'Uart receive

    IFS0bits.U1RXIF = 0;
    IPC6bits.U1IP = 5;
    IEC0bits.U1RXIE = 1;

    //SERVO1 = 0;   // Test si vraiment necessaire pour la sortie OC4
    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);
    marvin_set_periode(MARVIN_PR1, 1, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);
    //UART TEST
    marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER4);   // setup TIMER2 pour PWM

    marvin_setup_uart(MARVIN_UART, MARVIN_UART_STATUS);

    marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER4);
   // asm volatile ("nop");

    //int test[10]= { 0, 180, 90, 20, 45, 76, 83 ,45, 180, 90};
   // int i = 0;
    INTCONbits.MVEC = 1; // Interrupt controller en mode multi-vector
    __builtin_enable_interrupts(); // Ordonner au CPU de checker les interrupts
    while (1)
    {
// coder le watchdog timer si on reste bloquer dans une des fonctions
        if (TMR1 == PR1)
       {
            TMR1 = 0;
            LATFbits.LATF1 = !LATFbits.LATF1;
        }
    }
    return (0);
}
