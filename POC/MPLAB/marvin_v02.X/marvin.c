/*
 *  FONCTIONS GENERAL DU MARVIN
 */

#include "marvin.h"

void    marvin_behavior1()
{
    marvin_set_lux_speed(&marvin.led_left, 25, 1, 40);
    marvin_set_lux_speed(&marvin.led_right, 25, 1, 40);

    marvin_tempo(1500);
    marvin_move_to_position(60, 90, 10);
    marvin_tempo(1500);
    marvin_move_to_position(100, 170, 10);
    marvin_tempo(1500);
    marvin_move_to_position(60, 90, 10);
    marvin_tempo(800);
    marvin_move_to_position(100, 10, 10);
    marvin_tempo(1500);
    marvin_move_to_position(60, 90, 10);
}

/*
 * Fonction d'Initialisation du MARVIN,
 * Mettre les servo et les Leds dans un etat initial & initialiser quelque variables
 * Param1: La structure de variable global a init
 *
 * BONUS: Jouer un comportement et/ou un son pendant ou apres l'INIT
 */
void    marvin_init(m_marvin *marvin)
{
    marvin->val_ir = 0;
    marvin->val_sonar_l = 0;
    marvin->val_sonar_r = 0;
    marvin->counter1 = 0;
    marvin->counter2 = 0;
 //   marvin_init_ordre();
}
/*
void    marvin_init_ordre()
{
    marvin.ordre[0] = marvin_ordre_right();
    marvin.ordre[1] = marvin_ordre_left();
 //   marvin.ordre[2] = marvin_ordre_find(); Completement CON
    marvin.ordre[3] = marvin_ordre_sleep();
}*/

/*
 * Fonction de refresh de tout les capteurs et variable de mesures associees
 */
void    marvin_refresh(m_marvin *marvin)
{
    marvin->val_sonar_r = marvin_capture(&marvin->sonar_right);
    marvin->val_sonar_l = marvin_capture(&marvin->sonar_left);
    marvin->val_ir = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);
}

/*
 * Fonction de test de presence sur le sonar de gauche, return 1 ou 0
 * Il faut definir des minimums et des maximums
 */
u8    marvin_is_someone_left(m_marvin marvin)
{
    if (marvin.val_sonar_l < marvin.val_sonar_r - 5
            && marvin.val_sonar_l < marvin.val_ir -5 )
        return (1);
    return (0);
}

/*
 * Fonction de test de presence sur le sonar de droite, return 1 ou 0
 * Il faut definir des minimuns et des maximums
 */
u8    marvin_is_someone_right(m_marvin marvin)
{
    if (marvin.val_sonar_r < marvin.val_sonar_l - 5
            && marvin.val_sonar_r < marvin.val_ir - 5)
        return (1);
    return(0);
}

/*
 * Fonction de test de presence en face de MARVIN, return 1 ou 0
 */
u8   marvin_is_someone_found(m_marvin marvin)
{
    if (marvin.val_ir < IR_SCOPE)
        return (1);
    return (0);
}

void    marvin_veille(u32 temps)
{
    // send un message mais utiliser un boolean pour ne l'envoyer qu'une fois
    if (marvin.servo_yaw.pos > 85 && marvin.servo_yaw.pos < 95)
    {
        marvin_stop_move(&marvin);
        if (marvin.led_left.lux < 7)
        {
            marvin_set_lux(&marvin.led_left, 1);
            marvin_set_lux(&marvin.led_right, 1);
        }
        else
        {
            marvin_set_lux_speed(&marvin.led_left, 1, 1, 40);
            marvin_set_lux_speed(&marvin.led_right, 1, 1, 40);
        }
    }
    else
    {
       marvin_set_lux_speed(&marvin.led_left, 1, 1, 40);
       marvin_set_lux_speed(&marvin.led_right, 1, 1, 40);
       marvin_move_servo_speed(&marvin.servo_yaw, 90, 1, 25);
    }
    if (temps + 30000 < marvin.counter1)
    {
        // envoyer un message pour dire qu'il se reveillle
        marvin.counter1 = 0;
    }
}

void    marvin_stop_move(m_marvin *marvin)
{
    marvin->servo_pitch.incr = 0;
    marvin->servo_yaw.incr = 0;
    marvin->servo_scan.incr = 0;
    marvin->led_left.incr = 0;
    marvin->led_right.incr = 0;
}

/*
 * Fonction de changement d'etat des LEDS,
 * Param1: Etat des leds ON ou OFF (resp. 1 ou 0)
 * Decommenter une fois sur NOTRE PIC
 */
void    marvin_eye(u8 state)
{
    if (state == ON)
    {
       marvin_set_lux_speed(&marvin.led_left, 40, 1, 40);
       marvin_set_lux_speed(&marvin.led_right, 40, 1, 40);
    }
    else
    {
       marvin_set_lux_speed(&marvin.led_left, 0, 1, 40);
       marvin_set_lux_speed(&marvin.led_right, 0, 1, 40);
    }
}

/*  FONCTION DE TIMESTAMP,
 *
 * Nbr periode = nombre de fois ou la periode est atteinte, increment via une ISR
 *
 * La fonction get_time_sec/msec renvoie le temps ecouler depuis le timestamp envoyer en parametre
 * Le timestamp est compose, de timestamp: valeur de TMR1,
 * et de nbr_periode,: combien de periode ecoulee
 */
/*
void    __ISR(4, IPL7) timer1_interrupt()
{
    marvin.time->nbr_periode += 1;
    _nop();
    IFS0bits.T1IF = 0;
}

u32     get_time_sec(u32 timestamp, u32 nbr_periode)
{
    u32 actual_time;
    u32 actual_nbr_periode;
    u32 result;

    result = 0;
    actual_time = TMR1;
    actual_nbr_periode = marvin.time->nbr_periode;
    if (actual_nbr_periode != nbr_periode)
        result = map((timestamp - actual_time), 0, PR1, 0, 10) + ((actual_nbr_periode - nbr_periode) * 10);
    return(map((actual_time - timestamp), 0, PR1, 0, 10));
}

u32     get_time_msec(u32 timestamp, u32 nbr_periode)
{
    u32 actual_time;
    u32 actual_nbr_periode;
    u32 result;

    result = 0;
    actual_time = TMR1;
    actual_nbr_periode = marvin.time->nbr_periode;
    if (actual_nbr_periode != nbr_periode)
        result = map((timestamp - actual_time), 0, PR1, 0, 1000) + ((actual_nbr_periode - nbr_periode) * 10);
    return(map((actual_time - timestamp), 0, PR1, 0, 1000));
}
*/