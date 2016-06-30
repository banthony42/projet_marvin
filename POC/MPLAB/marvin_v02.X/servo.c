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
    servo->incr = 0;
    servo->periode = periode;   //stockage periode
    servo->oc_timer = oc_timer; //stockage timer
    servo->vitesse = 0;
    servo->new_pos = 0;
    *pin = OC_OFF;              //Registre disable le temps de la config
    *pin = 0 | OCM | oc_timer;  // configuration du registre: OC1 disabled, OC1 mode: PWM, OC1 use TIMER2
    *pin |=  OC_ON;             // OC1 enabled
    marvin_move_servo_speed(servo, 90, 1 ,5);// init position a 90 degres
}

/*
 * Fonction qui deplace un servo sur l'angle passe en param
 * Param1 : Objet m_servo a move
 * Param2 : Angle du servo voulu (0 a 180 deg)
 */
void    marvin_move_servo(m_servo *servo, s16 angle)
{
    if (servo->pos == angle || angle > 170 || angle < 0) // Gestion d'erreur, angle impossible ou servo deja en place
        return ;
    servo->pos = angle;                                                                                         // Enregistrement de la nouvelle position
    if (servo->oc_timer == OC_TIMER2)
        *(servo->ocrs) = (PR2 * (servo->min + (angle * ((servo->max  - servo->min ) / 180)))) / servo->periode; // Ecriture du nouveau duty_cycle dans le registre OCxRS, cas du TIMER2
    else
        *(servo->ocrs) = (PR3 * (servo->min + (angle * ((servo->max - servo->min) / 180)))) / servo->periode;   // Ecriture du nouveau duty_cycle dans le registre OCxRS, cas du TIMER3
}

void    marvin_move_servo_speed(m_servo *servo, s16 angle, u16 deg_per_periode, u16 periode_msec)
{
    if (servo->pos == angle || angle > 180 || angle < 0)                                    // Gestion d'erreur, angle impossible, ou servo deja en position
        return ;
    servo->new_pos = angle;
    servo->vitesse = periode_msec;
    if (angle > servo->pos)                                                                // Determination de l'operation a effectuer pour l'increment, (addition ou soustraction)
        servo->incr = 1 * deg_per_periode;
    else
        servo->incr = -1 * deg_per_periode;
}