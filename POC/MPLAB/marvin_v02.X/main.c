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

/*
void __ISR(_TIMER_1_VECTOR, IPL7) timer1_handler()
{
  marvin_timestamp.time += TIME_TMR1;
  IFS0bits.T1IF = 0; // Clear l'interrupt
}
*/


int main()
{
    marvin_setup(&marvin);
    marvin_init(&marvin);
    LATBbits.LATB11 = 0;        // ALIM SENSOR, 1 = OFF , 0 = ON
    TRISBbits.TRISB11 = 0;

    u8 tab[25] = {0};
    int i_uart = 0;
    while (1)
    {
        while (U1STAbits.URXDA)
        {
            tab[i_uart++] = U1RXREG;
            _nop();
        }

         
        //marvin_receive_message(tab, &i_uart);
         if (*tab)
            _nop();
         
        if (TMR1 == PR1)
       {

            marvin_send_message("yolo", 5);
           // marvin_send_message("Je suis Marvin et j'ai la tete comme une planete", 50);
            TMR1 = 0;
       }
        
        /*
        _nop();
            marvin_refresh(&marvin);
           _nop();
           
        if (marvin_is_someone_found(marvin))
        {
            marvin_stop_move(&marvin);
            marvin_set_lux_speed(&marvin.led_left, 0, 1, 40);
            marvin_set_lux_speed(&marvin.led_right, 0, 1, 40);
         }
        if (marvin_is_someone_left(marvin))
        {
             marvin_move_servo_speed(&marvin.servo_yaw, marvin.servo_yaw.pos +10, 1, 25);
             marvin_set_lux_speed(&marvin.led_left, 20, 1, 40);
        }
        if (marvin_is_someone_right(marvin))
        {
             marvin_move_servo_speed(&marvin.servo_yaw, marvin.servo_yaw.pos - 10, 1, 25);
             marvin_set_lux_speed(&marvin.led_right, 20, 1, 40);
        }

         _nop();
         * */
    }
    return (0);
}

