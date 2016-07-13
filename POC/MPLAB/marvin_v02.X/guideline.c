#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"
#include "setup.h"
#include "marvin.h"

// Instanciation des globales
t_stamp	g_timer;
t_servo	servo_yaw;
t_servo	servo_pitch;

int main()
{
    marvin_init_all();

    while (1)
    {
        marvin_sensor_refresh_all();

        marvin_process();

    }
    return (0);
}

u8		marvin_init_all()
{
	marvin_init_global_timer();
	marvin_init_servo_pwm_timer();
	marvin_init_actuator_refresh_timer();

	marvin_init_servo(&servo_yaw);
	return (0);
}


/*
 *	Le timer global utilise le timer 1, et incremente g_timer.nbr_periodes
 *	chaque seconde.
*/
void	marvin_init_global_timer()
{
	g_timer.nbr_periodes = 0;
	g_timer.tmr = MARVIN_TIMER1;
	g_timer.pr = MARVIN_PR1;
	marvin_set_timer(MARVIN_CONF_TIMER1, TCKPS11, TIMER_GATE_OFF, MARVIN_TIMER1);
	marvin_set_periode(MARVIN_PR1, PERIODE_GLOBAL_TIMER, TYPE_A, MARVIN_CONF_TIMER1,
			UNIT_PERIODE_G_TIMER);
}

/*
 *	Le timer 2 est utilise dans la generation de la periode du signal PWM des
 *	servos. Cette periode est de 20ms.
*/
void	marvin_init_servo_pwm_timer()
{
	marvin_set_timer(MARVIN_CONF_TIMER2, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER2);
	marvin_set_periode(MARVIN_PR2, SERVO_PWM_PERIODE, TYPE_B, MARVIN_CONF_TIMER2,
			TIME_MSEC);
}

/*
 *	Timer 3 interrupt is used to evaluate the need for a servo position refresh,
 *	regardless of the speed of the main while(1) loop.
 *
*/
void	marvin_init_actuator_refresh_timer()
{
	marvin_set_timer(MARVIN_CONF_TIMER3, TCKPS00, TIMER_GATE_OFF, MARVIN_TIMER3);
	marvin_set_periode(MARVIN_PR3, ACTUATORS_REFRESH_PERIODE, TYPE_B,
			MARVIN_CONF_TIMER3, TIME_MSEC);
}

/*
 *	WIP
*/
void	marvin_init_servo(t_servo *servo, char id, u32 *pin, u32 *ocrs, u8 oc_timer)
{
	servo->name = id;
	servo->pin = pin;
	servo->ocrs = ocrs;
	servo->periode = SERVO_PWM_PERIODE;
	servo->oc_timer = oc_timer;
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

	if (!servo_check_legality(servo, dest, speed, lock))
		return (1);
	servo->dest = dest;
	servo->speed = speed;
	servo->lock = lock;
	if (servo->dest != servo->pos)
		servo->ismoving = 1;
	return (0);
}

/*
 *	Check de la validite des parametres de mouvement demandes au servo 
 *	-> struct servo existe ?
 *	-> angle de destination dans le range autorise ?
 *	-> vitesse dans le range ?
 *	-> verouillage deja actif ?
*/
s8		servo_check_legality(t_servo *servo, s16 dest, u8 speed, u8 lock)
{
	if (!servo)
		return (0);
	if (servo->locked)
		return (0);
	if (dest < servo->min || dest > servo->max)
		return (0);
	if (speed < SERVO_SPEED_MIN || speed > SERVO_SPEED_MAX)
		return (0);
	if (lock != 0 || lock != 1)
		return (0);
	return (1);
}

/*
 *	Fonction de rafraichissement de la commande aux actionneurs, non blocante.
 *	La logique est basee sur un timestamp a atteindre pour incrementer la position,
 *	le tout jusqu'a ce que la destination soit atteinte.
 *	Cette fonction est appelee par l'interrupt du timer 3 afin de garantir la
 *	regularite du mouvement des servos.
*/
void    servo_refresh(t_servo *servo)
{
	if (pos != dest)
	{
		if (servo->incr_stamp >= g_time)
		{
			servo_move_speed(servo, (pos = (servo->pos < servo->dest ?
							servo->pos++ : servo->pos--)));
			timestamp_copy(&(servo->lastmove_stamp), &g_timer);
			if (servo->pos == servo->dest)
			{
				servo->ismoving = 0;
				servo->speed = 0;
			}
			else
			{
				timestamp_copy(&(servo->incr_stamp), &g_timer);
				timestamp_add_msec(&(servo->incr_stamp),
						map(servo->speed, SERVO_MIN_SPEED, SERVO_MAX_SPEED,
							SERVO_MAX_STILL, SERVO_MIN_STILL));
			}
		}
	}
	return;
}

//TODO
s8		timestamp_compare(t_stamp *stamp1, t_stamp *stamp2);
s8		timestamp_copy(t_stamp *dst, t_stamp *src);
s8		timestamp_add_msec(t_stamp *stamp, s16 value_msec);
s8		timestamp_add_sec(t_stamp *stamp, s16 value_sec);

void    __ISR(_TIMER_3_VECTOR , IPL6) timer3_interrupt()
{
    servo_refresh(&servo_yaw);
    servo_refresh(&servo_pitch);
	IFS0bits.T3IF = 0;
}

void	__ISR(_TIMER_1_VECTOR , IPL5) timer1_interrupt()
{
	*(g_timer.tmr) = 0;
	(g_timer.nbr_periodes)++;
	IFS0bits.T1IF = 0;
}
