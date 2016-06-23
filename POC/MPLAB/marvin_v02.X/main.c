/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on June 22, 2016, 6:34 PM
 */
#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"

m_servo servo1;
int main()
{
/*    T1CONbits.TCS  = 0;
    T1CONbits.TGATE = 0;
    T1CONbits.TCKPS = 0;
    TMR1 = 0;
    T1CONbits.ON = 1;
    PR1 = 64000;*/

    //.....Maping des PIN.......//
    SYSKEY = 0x0;               //  Ensure OSCCON is locked
    SYSKEY = 0xAA996655;        //  Write key1 to SYSKEY
    SYSKEY = 0x556699AA;        //  Write key2 to SYSKEY
    CFGCONbits.IOLOCK = 0;      //  Peripheral Pin Register Select(PPS) is unlocked, Mappind is allowed
    RPB15Rbits.RPB15R = 0b101;  //  Mapping de la PIN RPA4 en OC4
    CFGCONbits.IOLOCK = 1;      //  PPS is relock, Mapping pin is not allowed
    SYSKEY = 0x0;               // Relock the SYSKEY
    //....Fin Mapping des PIN...//

    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);
    marvin_set_periode(MARVIN_PR1, 3, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);

    marvin_set_timer(MARVIN_CONF_TIMER4, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER4);   // setup TIMER2 pour PWM

    marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER2);     // setup TIMER2 pour PWM
    marvin_set_periode(MARVIN_PR2, 20, TYPE_B, MARVIN_CONF_TIMER2, TIME_MSEC);        // setup periode TIMER2 a 19ms pour PWM servo

    marvin_attach_servo(&servo1, MARVIN_OC1, MARVIN_OC1RS, 550, 2400, OC_TIMER2, 20000);

    LATBbits.LATB13 = 1;        //  SIGNAL EYE RIGHT
    TRISBbits.TRISB13 = 0;      //  SIGNAL EYE RIGHT
    
    LATBbits.LATB10 = 0;        // SERVO ENABLE
    TRISBbits.TRISB10 = 0;      // SERVO ENABLE

    LATBbits.LATB9 = 1;        //  SIGNAL EYE LEFT
    TRISBbits.TRISB9 = 0;      //  SIGNAL EYE LEFT

    LATBbits.LATB5 = 1;        //  SERVO SCAN
    TRISBbits.TRISB5 = 0;      //  SERVO SCAN

    LATAbits.LATA4 = 1;        //  SERVO PITCH
    TRISAbits.TRISA4 = 0;      //  SERVO PITCH

    LATBbits.LATB4 = 1;        //  SERVO YAW
    TRISBbits.TRISB4 = 0;      //  SERVO YAW

    LATBbits.LATB8 = 1;        //  ECHO SONAR 1
    TRISBbits.TRISB8 = 0;      //  ECHO SONAR 1

    LATBbits.LATB14 = 1;        // POT YAW
    TRISBbits.TRISB14 = 0;      //  POT YAW

    int i = 0;

    marvin_move_servo(&servo1, 180);
    while (1)
    {
        if (PR1 == TMR1)
        {
            LATBbits.LATB13 = !LATBbits.LATB13;
            _nop();
            if (i == 0)
                marvin_move_servo(&servo1, 0);
            else if (i == 1)
                marvin_move_servo(&servo1, 90);
            else if (i == 2)
                marvin_move_servo(&servo1, 180);
            i++;
            if (i == 3)
                i = 0;
            TMR1 = 0;
        }
    }
    return (0);
}

