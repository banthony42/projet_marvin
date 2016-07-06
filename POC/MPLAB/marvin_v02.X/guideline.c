#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"
#include "setup.h"
#include "marvin.h"

int main()
{
    marvin_init_all();

    while (1)
    {
        marvin_sensor_refresh_all();

        marvin_process();

        marvin_actuator_refresh(); // Ici ou interrupt
    }
    return (0);
}

/*

 * servo: structure du servo
 * dest: angle de destination
 * speed: allure du deplacement, entre 0 et 100, sans unite
 * lock: verrouillage du deplacement (= prio maximale)
 * 
 * Valeur de retour: 0 si ok, 1 si mouvement illegal
 */
u8    servo_move_speed(t_servo *servo, s16 dest, u8 speed, u8 lock)
{
    // Verifier legalite des parametres
       // -> struct servo existe
       // -> angle de destination dans le range autorise
       // -> vitesse dans le range
       // -> verouillage deja actif?
    // Si legal, copier parametres dans structure, mettre ismoving a 1,
    // puis retour 0
        // Sinon retour 1
}

void    servo_refresh(t_servo *servo)
{
    // pos == dest
        // Si oui, on sort
        // Si non, incr_stamp est-il atteint ?
            // Si oui:
                - Appel move_servo
                - Increment pos
                - lastmove_stamp refresh
                - Comparaison pos avec dest. Si dest atteint 
                    - ismoving = 0
                    - speed = 0
                - Calcul du nouveau incr_stamp
            // si non: on sort
}

void    __ISR(_TIMER_3_VECTOR , IPL6) timer3_interrupt()
{
    servo_refresh(servo_yaw);
    servo_refresh(servo_pitch);
}