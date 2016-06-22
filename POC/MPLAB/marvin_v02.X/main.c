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

int main()
{
/*    T1CONbits.TCS  = 0;
    T1CONbits.TGATE = 0;
    T1CONbits.TCKPS = 1;
    TMR1 = 0;
    T1CONbits.ON = 1;
    PR1 = 64000;*/


    marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);
    marvin_set_periode(MARVIN_PR1, 1, TYPE_A, MARVIN_CONF_TIMER1, TIME_SEC);

    LATBbits.LATB10 = 1;
    TRISBbits.TRISB10 = 0;
    while (1)
    {
        if (PR1 == TMR1)
        {
            LATBbits.LATB10 = !LATBbits.LATB10;
            _nop();

        }
    }
    return (0);
}

