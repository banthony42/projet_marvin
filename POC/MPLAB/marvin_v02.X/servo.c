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
}

/*
 * Fonction qui deplace un servo sur l'angle passe en param
 * Param1 : Objet m_servo a move
 * Param2 : Angle du servo voulu (0 a 180 deg)
 */
void    marvin_move_servo(m_servo *servo, s16 angle)
{
    if (servo->pos == angle || angle > 180 || angle < 0) // Gestion d'erreur, Garder les extreme, 0deg et 180 deg ici
        return ;                                         //plutot modifier les duty cycle propre a chaque servo pour limiter les angles extreme
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

void    marvin_set_position(u8 pitch_angle, u8 yaw_angle)
{

    marvin_move_servo_speed(&marvin.servo_pitch, pitch_angle, 1, 10);
    marvin_move_servo_speed(&marvin.servo_yaw, yaw_angle, 1, 20);
}

void    marvin_move_to_position(u8 pitch_angle, u8 yaw_angle, u8 max_periode_msec)
{
    s16  delta_pitch;
    s16  delta_yaw;
    u16  coeff;
//    m_servo *yaw = &marvin.servo_yaw;
//    m_servo *pitch = &marvin.servo_pitch;

    if (yaw_angle < YAW_MIN || yaw_angle > YAW_MAX || pitch_angle < PITCH_MIN || pitch_angle > PITCH_MAX || max_periode_msec < 10)
        return ;

    delta_pitch = (marvin.servo_pitch.pos - pitch_angle);
    delta_yaw = (marvin.servo_yaw.pos - yaw_angle);
    if (delta_pitch < 0)
        delta_pitch *= -1;
    if (delta_yaw < 0)
        delta_yaw *= -1;

    if (!delta_yaw)
        marvin_move_servo_speed(&marvin.servo_pitch, pitch_angle, 1, max_periode_msec);
    if (!delta_pitch)
        marvin_move_servo_speed(&marvin.servo_yaw, yaw_angle, 1, max_periode_msec);

    if (delta_yaw > delta_pitch)
    {
        coeff = delta_yaw / delta_pitch;
        u16 ok = max_periode_msec / coeff;
        if (!ok)
            ok = 10;
        _nop();
        marvin_move_servo_speed(&marvin.servo_pitch, pitch_angle, 1, ok);
        marvin_move_servo_speed(&marvin.servo_yaw, yaw_angle, 1, max_periode_msec);
        _nop();
    }
    else
    {
        coeff = delta_pitch / delta_yaw;
        u16 ok2 = max_periode_msec / coeff;
        if (!ok2)
            ok2 = 10;
        _nop();
        marvin_move_servo_speed(&marvin.servo_pitch, pitch_angle, 1, max_periode_msec);
        marvin_move_servo_speed(&marvin.servo_yaw, yaw_angle, 1, ok2);
        _nop();
    }
}