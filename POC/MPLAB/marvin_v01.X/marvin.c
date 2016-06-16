/*
 *  FONCTIONS GENERAL DU MARVIN
 */

#include "marvin.h"

/*
 * Fonction d'Initialisation du MARVIN,
 * Mettre les servo et les Leds dans un etat initial & initialiser quelque variables
 * Param1: La structure de variable global a init
 * 
 * BONUS: Jouer un comportement et/ou un son pendant ou apres l'INIT
 */
void    marvin_init(m_marvin *marvin)
{
    //bzero sur marvin->send
    //bzero sur marvin->receive
    marvin->val_ir = 0;
    marvin->val_sonar1 = 0;
    marvin->val_sonar2 = 0;
    marvin->counter1 = 0;
    marvin->counter2 = 0;
    marvin_move_servo(&marvin->servo1, 90);
    marvin_move_servo(&marvin->servo2, 90);
}

/*
 * Fonction de refresh de tout les capteurs et variable de mesures associees
 */
void    marvin_refresh(m_marvin *marvin)
{
    marvin->val_sonar1 = marvin_capture(&marvin->sonar1);
    marvin->val_sonar2 = marvin_capture(&marvin->sonar2);
    marvin->val_ir = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);
    //  marvin_receive_message(...) => marvin->receive  ?
    //  Clear marvin->send ?
}

/*
 * Fonction de test de presence sur le sonar de gauche, return 1 ou 0
 */
void    marvin_is_someone_left(m_marvin marvin)
{
    if (marvin->val_sonar2 < marvin->val_sonar1)
        return (1);
    return (0);
}

/*
 * Fonction de test de presence sur le sonar de droite, return 1 ou 0
 */
void    marvin_is_someone_right(m_marvin marvin)
{
    if (marvin->val_sonar1 < marvin->val_sonar2)
        return (1);
    return(0);
}

/*
 * Fonction de test de presence en face de MARVIN, return 1 ou 0
 */
void    marvin_is_someone_found(m_marvin marvin)
{
    if (IR < IR_SCOPE)
        return (1);
    return (0);
}

/*
 * Fonction qui
 * Determine une valeur d'incrementation (+ ou -) pour tourner la tete vers la droite
 */
void    marvin_turn_right(m_marvin *marvin);

/*
 * Fonction qui
 * Determine une valeur d'incrementation (+ ou -) pour tourner la tete vers la gauche
 */
void    marvin_turn_left(m_marvin *marvin);

/*
 * Fonction d'arret d'incrementation
 * La fonction met la valeur d'increment a zero
 */
void    marvin_stop_move(m_marvin *marvin)
{
    marvin->servo1.incr = 0;
    marvin->servo2.incr = 0;
}

/*
 * Fonction de changement d'etat des LEDS,
 * Param1: Etat des leds ON ou OFF (resp. 1 ou 0)
 */
void    marvin_eye(u8 state)
{
    if (state == ON)
    {
        LATBbits.LATFB9 = 1;
        LATBbits.LATB13 = 1;
    }
    else
        LATBbits.LATFB9 = 0;
        LATBbits.LATB13 = 0;
}