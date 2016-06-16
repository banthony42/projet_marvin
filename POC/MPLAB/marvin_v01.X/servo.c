#include <p32xxxx.h>
#include "timer.h"
#include "types.h"
#include "Servo.h"
#include <p32xxxx.h>

/*
 * Fonction qui configure un servo
 * Param1 : Objet m_servo, a setup
 * Param2 : Adresse du REGISTRE OCxCON (OutputCompare) correspondant a la PIN OC choisit
 * Param3 : Duty_cycle minimum du servo (0deg) en microsecondes
 * Param4 : Duty_cycle maximum du servo (180deg) en microsecondes
 * Param5 : Timer choisit pour le module de l'OutputCompare
 * Param6 : Periode du signal PWM propre a ce servo
 */
void    marvin_attach_servo(m_servo *servo, u32 *pin, u32 *ocrs, u16 min, u16 max, u8 oc_timer, u16 periode)
{
    servo->pin = pin;           //stockage adresse registre OCxCON
    servo->ocrs = ocrs;         //stockage adresse registre OCxRS
    servo->min = min;           //stockage min duty_cycle
    servo->max = max;           //stockage max duty_cycle
    servo->pos = -1;            //pos initial
    servo->periode = periode;   //stockage periode
    servo->oc_timer = oc_timer; //stockage timer
    *pin = OC_OFF;              //Registre disable le temps de la config
    *pin = 0 | OCM | oc_timer;  // configuration du registre: OC1 disabled, OC1 mode: PWM, OC1 use TIMER2
    *pin |=  OC_ON;             // OC1 enabled
    marvin_move_servo(servo, 0);// init position a 0 degres
}

/*
 * Fonction qui deplace un servo sur l'angle passe en param
 * Param1 : Objet m_servo a move
 * Param2 : Angle du servo voulu (0 a 180 deg)
 */
void    marvin_move_servo(m_servo *servo, u8 angle)
{
    if (servo->pos == angle || angle > 180 || angle < 0)                                                        // Gestion d'erreur, angle impossible ou servo deja en place
        return ;
    servo->pos = angle;                                                                                         // Enregistrement de la nouvelle position
    if (servo->oc_timer == OC_TIMER2)
        *(servo->ocrs) = (PR2 * (servo->min + (angle * ((servo->max  - servo->min ) / 180)))) / servo->periode; // Ecriture du nouveau duty_cycle dans le registre OCxRS, cas du TIMER2
    else
        *(servo->ocrs) = (PR3 * (servo->min + (angle * ((servo->max - servo->min) / 180)))) / servo->periode;   // Ecriture du nouveau duty_cycle dans le registre OCxRS, cas du TIMER3
}

/*
 *  Fonction qui deplace un servo sur l'angle passe en param, fonction de la vitesse voulue en degres par periode de x msec.
 *  Param1: Objet m_servo a move
 *  Param2: Angle du servo voulu (0 a 180deg)
 *  Param3: Nbr de degres a incrementer par periode
 *  Param4: Periode d'attente en msec entre chaque increment
 */
void    marvin_move_servo_speed(m_servo *servo, u8 angle, u16 deg_per_periode, u16 periode_msec)
{
    s8 sign;

    sign = 0;
    marvin_set_periode(MARVIN_PR4, periode_msec, TYPE_B, MARVIN_CONF_TIMER4, TIME_MSEC);    // Set de la periode du TIMER4 a la periode voulue
    if (servo->pos == angle || angle > 180 || angle < 0)                                    // Gestion d'erreur, angle impossible, ou servo deja en position
        return ;
     if (angle > servo->pos)                                                                // Determination de l'operation a effectuer pour l'increment, (addition ou soustraction)
         sign = 1 * deg_per_periode;
     else
         sign = -1 * deg_per_periode;
    TMR4 = 0;                                                                               // Reset du TIMER4
    while (servo->pos != angle)                                                             // Tant que le servo n'est pas arrive en position
    {
        if (TMR4 == PR4)                                                                    //Increment a chaque periode, de la valeur voulue en degres
            marvin_move_servo(servo, (servo->pos + sign));
    }
}