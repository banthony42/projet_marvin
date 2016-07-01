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
 *  FONCTION LEDS  => OK
 * 
 *  FAIRE FONCTIONNER L'UART
 */

int main()
{
    marvin_setup(&marvin);
    marvin_init(&marvin);

    while (1)
    {
        /*
         * Useless
        if (TMR1 == PR1)
       {
            marvin_send_message("Je suis Marvin et j'ai la tete comme une planete", 50);
            TMR1 = 0;
       }
         */
        if (marvin.counter1 > 60000)
                marvin_veille(60000);
            else
            {
                
                if (marvin_check_trans(marvin.receive))
                {
                }
                else
                {
                    marvin_refresh(&marvin);
                    if (marvin_is_someone_found(marvin))
                    {
                        marvin_stop_move(&marvin);
                        marvin_set_lux_speed(&marvin.led_left, 0, 1, 40);
                        marvin_set_lux_speed(&marvin.led_right, 0, 1, 40);
                        marvin_send_message(UART_SEND_FIND);
                     }
                    if (marvin_is_someone_left(marvin))
                    {
                         marvin_move_servo_speed(&marvin.servo_yaw, marvin.servo_yaw.pos +10, 1, 25);
                         marvin_set_lux_speed(&marvin.led_left, 20, 1, 40);
                          marvin_send_message(UART_SEND_LEFT);
                    }
                    if (marvin_is_someone_right(marvin))
                    {
                         marvin_move_servo_speed(&marvin.servo_yaw, marvin.servo_yaw.pos - 10, 1, 25);
                         marvin_set_lux_speed(&marvin.led_right, 20, 1, 40);
                         marvin_send_message(UART_SEND_RIGHT);

                    }
                }
           }
    }
    return (0);
}

