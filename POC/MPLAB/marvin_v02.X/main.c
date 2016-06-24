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
#include "setup.h"

/*  PB AVEC LE RELAIS ALIM TOUT LE TEMPS A 5V SUR SERVO
 *      INTGRATION CODE
 *  FONCTION TIMER => OK
 *  FONCTION SERVO => OK
 *  FONCTION SONAR => OK
 *  FONCTION IR    => OK
 *
 *  FAIRE FCT LEDS
 *  FAIRE FONCTIONNER L'UART
 */

m_servo led;

int main()
{
    marvin_setup(&marvin);

    LATBbits.LATB11 = 0;        // ALIM SENSOR, 1 = OFF , 0 = ON
    TRISBbits.TRISB11 = 0;
    marvin_attach_servo(&led, MARVIN_OC5, MARVIN_OC5RS, 0, 20000, OC_TIMER2, 20000);    //  LED RIGHT
 // marvin_move_servo(&marvin.servo3, 180);
    while (1)
    {
        if (PR1 == TMR1)
        {
            marvin_move_servo_speed(&led, 0, 5, 20);
/*          marvin.val_sonar1 = marvin_capture(&marvin.sonar1);
            marvin.val_sonar2 = marvin_capture(&marvin.sonar2);
            marvin.val_ir = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);*/
            _nop();
            TMR1 = 0;
        }
        marvin_move_servo_speed(&led, 180, 5, 20);
    }
    return (0);
}

