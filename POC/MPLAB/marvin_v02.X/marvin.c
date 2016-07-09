/*
 *  FONCTIONS GENERAL DU MARVIN
 */

#include "marvin.h"

/*
 *  Mouvement de recherche,
 *  Marvin regarde autour de lui
 */
void    marvin_look_around()
{
    marvin_stop_move(&marvin);
    marvin_set_lux_speed(&marvin.led_left, 25, 1, 40);
    marvin_set_lux_speed(&marvin.led_right, 25, 1, 40);
    marvin_tempo(1500);
    marvin_move_to_position(PITCH_REST, 90, 10);
    marvin_tempo(1500);
    marvin_move_to_position(PITCH_MAX, YAW_MAX, 10);
    marvin_tempo(1500);
    marvin_move_to_position(PITCH_REST, 90, 10);
    marvin_tempo(800);
    marvin_move_to_position(PITCH_MAX, YAW_MIN, 10);
    marvin_tempo(1500);
    marvin_move_to_position(PITCH_REST, 90, 10);
    marvin_tempo(1500);
    behavior.feel_alone = 0;
    behavior.feel_spite++;          // feel more spity every time, he is feeling alone
    marvin.found = marvin.counter3;
}

void    marvin_look_round()
{
    marvin_stop_move(&marvin);
    marvin_set_lux_speed(&marvin.led_left, 25, 1, 40);
    marvin_set_lux_speed(&marvin.led_right, 25, 1, 40);
    marvin_tempo(1500);
    marvin_move_to_position(PITCH_REST, 90, 10);
    marvin_tempo(1500);
    marvin_move_to_position(PITCH_MAX, YAW_MAX, 10);
    marvin_tempo(800);
    marvin_move_to_position(PITCH_MAX, 90, 10);
    marvin_tempo(800);
    marvin_move_to_position(PITCH_MAX, YAW_MIN, 10);
    marvin_tempo(800);
    marvin_move_to_position(PITCH_REST, YAW_MIN, 10);
    marvin_tempo(800);
    marvin_move_to_position(PITCH_MIN, YAW_MIN, 10);
    marvin_tempo(400);
    marvin_move_to_position(PITCH_MIN, 90, 10);
    marvin_tempo(300);
    marvin_move_to_position(PITCH_MIN, YAW_MAX, 10);
    marvin_tempo(300);
    marvin_move_to_position(PITCH_REST, 90, 10);
    marvin_tempo(1500);
    behavior.feel_alone = 0;
    behavior.feel_spite++;          // feel more spity every time, he is feeling alone
    marvin.found = marvin.counter3;
}
/*
 *  Mouvement de tete "depit"
 */
void    marvin_spite()
{
    marvin_stop_move(&marvin);
    marvin_set_lux_speed(&marvin.led_left, 1, 1, 40);
    marvin_set_lux_speed(&marvin.led_right, 1, 1, 40);
    marvin_move_to_position(PITCH_MAX, 90, 15); //1
    marvin_tempo(1500);
    marvin_move_to_position(PITCH_MAX - 15, 130, 15); // 2
    marvin_tempo(700);
    marvin_move_to_position(PITCH_MAX - 30, 50, 15); // 3
    marvin_tempo(800);
    marvin_move_to_position(PITCH_MAX - 45, 130, 15); // 4
    marvin_tempo(800);
    marvin_move_to_position(PITCH_MIN, 90, 15); // 5
    marvin_tempo(800);
    behavior.feel_spite = 0;
    behavior.feel_sleepy++;     // he is feeling more sleepy every time he is feeling spite
    marvin.booleen++;
    marvin.found = marvin.counter3;
}

/*
 * Fonction de refresh de tout les capteurs et variable de mesures associees
 */
void    marvin_refresh(m_marvin *marvin)
{
    u8 alone = 0;

    marvin_refresh_sensor(marvin);
    alone = marvin->counter3 - marvin->found;
    if (!(alone % 20) && alone != 0)          // Apres 20 secondes sans detection, feel alone
        behavior.feel_alone++;
}

void    marvin_refresh_sensor(m_marvin *marvin)
{
    marvin->val_sonar_r = marvin_capture(&marvin->sonar_right);
    marvin->val_sonar_l = marvin_capture(&marvin->sonar_left);
    marvin->val_ir = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);
}

void    marvin_veille(u32 wait)
{
    marvin_set_lux_speed(&marvin.led_left, 1, 1, 40);
    marvin_set_lux_speed(&marvin.led_right, 1, 1, 40);
    LATBbits.LATB10 = 0;        // ALIM SERVO 1 = ON, 0 = OFF
    if (behavior.feel_sleepy == 2)
        marvin_send_trame("3\n");   // Tell to the Pi marvin is sleeping
    marvin_tempo(5000);
    marvin.booleen = 0;
    if (time.stamp1 == 0)
        time.stamp1 = marvin.counter1;
    if (marvin.servo_yaw.pos > 85 && marvin.servo_yaw.pos < 95)
    {
        marvin_stop_move(&marvin);
        marvin_set_lux_speed(&marvin.led_left, 1, 1, 40);
        marvin_set_lux_speed(&marvin.led_right, 1, 1, 40);
    }
    else
       marvin_move_servo_speed(&marvin.servo_yaw, 90, 1, 25);
    marvin_move_servo_speed(&marvin.servo_pitch, PITCH_REST, 1, 25);
    if (marvin.counter1 < time.stamp1 + wait)
    {
        // Attente, veille pendant wait secondes
        marvin.val_ir = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);
        // Test sur IR, si presence sortit du mode veille
        if (marvin_is_someone_found(marvin))
            marvin_force_awaken();
    }
    else
        marvin_force_awaken();
}

void    marvin_force_awaken()
{
            behavior.feel_sleepy = 0;       // Ou sortit de la veille, car temps d'attente termine
        behavior.feel_alone = 0;
        behavior.feel_spite = 0;
        marvin.found = marvin.counter3;
        marvin.counter1 = 0;
        marvin_eye_glow();
        marvin_send_trame("4\n");       // Tell to the Pi marvin is awaking
        marvin_tempo(5000);
        LATBbits.LATB11 = 0;        // ALIM SENSOR, 1 = OFF , 0 = ON
        LATBbits.LATB10 = 1;        // ALIM SERVO 1 = ON, 0 = OFF
}

void    marvin_eye_glow()
{
          // Sequence Glow Leds
        marvin_set_lux_speed(&marvin.led_left, 100, 1, 50);
        marvin_set_lux_speed(&marvin.led_right, 100, 1, 50);
        marvin_tempo(700);
        marvin_set_lux_speed(&marvin.led_left, 1, 1, 50);
        marvin_set_lux_speed(&marvin.led_right, 1, 1, 50);
        marvin_tempo(700);
        marvin_set_lux_speed(&marvin.led_left, 40, 1, 50);
        marvin_set_lux_speed(&marvin.led_right, 40, 1, 50);
        marvin_tempo(700);
        marvin_set_lux_speed(&marvin.led_left, 1, 1, 50);
        marvin_set_lux_speed(&marvin.led_right, 1, 1, 50);
        marvin_tempo(700);
        // Fin Sequence glow
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
    marvin->counter3 = 0;
    marvin->found = 0;
    time.nbr_periode= 0;
    marvin_pos_initial();
    behavior.feel_alone = 0;
    behavior.feel_spite = 0;
    behavior.feel_sleepy = 0;
    marvin->booleen = 0;
}

/*
 *  Met les actionneurs de Marvin
 *  en etat initial 
 */
void    marvin_pos_initial()
{
    marvin_set_lux_speed(&marvin.led_right, 40, 1, 20);
    marvin_set_lux_speed(&marvin.led_left, 40, 1, 20);
    marvin_move_servo_speed(&marvin.servo_yaw, 90, 1 ,15);
    marvin_move_servo_speed(&marvin.servo_pitch, 60, 1 ,15);
    marvin_move_servo_speed(&marvin.servo_scan, 90, 1 ,15);
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
 *//*
void    __ISR(4, IPL7) timer1_interrupt()
{
    time.nbr_periode += 1;
    _nop();
    IFS0bits.T1IF = 0;
}*/
/*
u32     get_time_sec(u32 timestamp, u32 nbr_periode)
{
    u32 actual_time;
    u32 actual_nbr_periode;
    u32 result;

    result = 0;
    actual_time = TMR1;
    actual_nbr_periode = time.nbr_periode;
    if (timestamp > actual_time)
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
    actual_nbr_periode = time.nbr_periode;
    if (actual_nbr_periode != nbr_periode)
        result = map((timestamp - actual_time), 0, PR1, 0, 1000) + ((actual_nbr_periode - nbr_periode) * 10);
    return(map((actual_time - timestamp), 0, PR1, 0, 1000));
}*/