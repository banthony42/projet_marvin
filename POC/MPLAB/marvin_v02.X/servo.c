#include <p32xxxx.h>
#include "timer.h"
#include "types.h"
#include "Servo.h"
#include "uart.h"
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
 * Param3 : 1 si servo Yaw
 */
void    marvin_move_servo(m_servo *servo, s16 angle, u8 which_servo)
{
    if (servo->pos == angle || angle > 180 || angle < 0) // Gestion d'erreur, Garder les extreme, 0deg et 180 deg ici
        return ;                                         //plutot modifier les duty cycle propre a chaque servo pour limiter les angles extreme
    servo->pos = angle;
    if (servo->oc_timer == OC_TIMER2)
    {
        *(servo->ocrs) = (PR2 * (servo->min + (angle * ((servo->max  - servo->min ) / 180)))) / servo->periode; // Ecriture du nouveau duty_cycle dans le registre OCxRS, cas du TIMER2
        if (which_servo && marvin.servo_yaw.incr < 0)
            marvin_send_message("1\n");
        else if (which_servo && marvin.servo_yaw.incr > 0)
            marvin_send_message("2\n");
    }
    else
    {
        *(servo->ocrs) = (PR3 * (servo->min + (angle * ((servo->max - servo->min) / 180)))) / servo->periode;   // Ecriture du nouveau duty_cycle dans le registre OCxRS, cas du TIMER3
    }
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

void    marvin_move_to_position(u8 pitch_angle, u8 yaw_angle, u16 min_periode_msec)
{
    s16  delta_pitch = 0;
    s16  delta_yaw = 0;
    u16  coeff = 0;
    u16  yaw_period = 0;
    u16  pitch_period = 0;

    if (yaw_angle < YAW_MIN || yaw_angle > YAW_MAX || pitch_angle < PITCH_MIN || pitch_angle > PITCH_MAX || min_periode_msec < 10 || min_periode_msec > 100)
        return ;

    delta_pitch = (marvin.servo_pitch.pos - pitch_angle);
    delta_yaw = (marvin.servo_yaw.pos - yaw_angle);
    if (delta_pitch < 0)
        delta_pitch *= -1;
    if (delta_yaw < 0)
        delta_yaw *= -1;

    if (!delta_yaw)
    {
        _nop();
        marvin_move_servo_speed(&marvin.servo_pitch, pitch_angle, 1, min_periode_msec);
        return;
    }
    if (!delta_pitch)
    {
        _nop();
        marvin_move_servo_speed(&marvin.servo_yaw, yaw_angle, 1, min_periode_msec);
        return;
    }

    if (delta_yaw > delta_pitch)
    {
        _nop();
        coeff = delta_yaw / delta_pitch;
        pitch_period = min_periode_msec * delta_yaw / delta_pitch;
        yaw_period = min_periode_msec;
        _nop();
    }
    else
    {
        _nop();
        coeff = delta_pitch / delta_yaw;
        pitch_period = min_periode_msec;
        yaw_period = min_periode_msec * delta_pitch / delta_yaw;
        _nop();
    }
    marvin_move_servo_speed(&marvin.servo_pitch, pitch_angle, 1, pitch_period);
    marvin_move_servo_speed(&marvin.servo_yaw, yaw_angle, 1, yaw_period);
}