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
#include "marvin.h"

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

/* En travaux

void __ISR(4, IPL1) timer1_handler()
{
    marvin_timestamp.time += TIME_TMR1;
    IFS0bits.T1IF = 0; // Clear l'interrupt
}
*/

int main()
{
    marvin_setup(&marvin);
    marvin_init(&marvin); // mise a zero des inputs
  
    LATBbits.LATB11 = 0;        // ALIM SENSOR, 1 = OFF , 0 = ON
    TRISBbits.TRISB11 = 0;
    marvin_timestamp.time = 0;
    marvin_attach_led(&marvin.led_right, MARVIN_OC5, MARVIN_OC5RS, 0,20000, OC_TIMER3, 20000);
    marvin_attach_led(&marvin.led_left, MARVIN_OC3, MARVIN_OC3RS, 0,20000, OC_TIMER3, 20000);
    u8 yolo = 0;
    while (1)
    {   
        if (PR1 == TMR1)
        {
            marvin_set_lux(&marvin.led_left, yolo);
            marvin_set_lux(&marvin.led_right, yolo );
            yolo++;
            if (yolo > 100)
                yolo = 0;
            _nop();
            TMR1 = 0;
      }
        
    }
    return (0);
}

