/* 
 * File:   guideline.h
 * Author: bocal
 *
 * Created on July 6, 2016, 3:32 PM
 */

#ifndef GUIDELINE_H
# define	GUIDELINE_H

# define PERIODE_GLOBAL_TIMER 1
# define UNIT_PERIODE_G_TIMER TIME_SEC
# define SERVO_PWM_PERIODE 20
# define ACTUATORS_REFRESH_PERIODE 1

/*
 * Objet servo
 * name: nom du servo (yaw ou pitch)
 * pin: Registre complet de la pin a laquelle est attache le servo
 * ocrs: registre de controle correspondant a la PIN du servo
 * periode: periode du servo pour le signal PWM
 * oc_timer: registre de comparaison secondaire correspondant a la PIN du servo
 * lastmove_stamp: timestamp correspondant a l'instant du dernier changement de duty cycle
 *
 * min: duty_cycle minimum du servo en ms (ex: 500  (angle de 0deg))
 * max: duty_cycle maximum du servo en ms (ex: 2500 (angle de 180deg))
 * center: duty_cycle de la position de repos (par defaut au demarrage)
 *
 * pos: derniere pos du servo en deg
 * speed: vitesse de deplacement. Valeur (sans unite) comprise entre 0 et 100
 *
 * incr_stamp: date a atteindre avant le prochain increment de position
 * dest: destination finale (angle) du servo.
 * locked: verouillage du mouvement du servo jusqu'a sa destination
 *
 */
typedef struct  s_servo
{
    u8      id;
    u32     *pin;
    u32     *ocrs;
    u16     periode;
    u8      oc_timer;
    t_time  lastmove_stamp;
    u16     min;
    u16     max;
    u16     dfault;
    s16     pos;
    u8     speed;
    t_time  incr_stamp;
    s16     dest;
    s8      ismoving;
    s8      locked;
}               t_servo;

/*
 * Objet Leds:
 * pin: Registre complet de la pin a laquelle est attache la leds
 * ocrs: registre de control correspondant a la PIN du servo
 * periode: periode du servo pour le signal PWM
 * oc_timer: registre cde comparaison secondaire correspondant a la PIN de l'oeil
 * 
 * min: duty_cycle pour Luminosite min (0 = Led eteinte)
 * max: duty_cycle pour Luminosite max (max = periode : Led allumer au max)
 * dfault: duty_cycle pour Luminosite standard
 * lux_status: Echelle luminosite actuelle (1 a 100)
 * lux_glow_speed: allure de changement de luminosite (de 0 a 100)
 *
 * lux_incr: luminosite intermediaire
 * lux_dst: nouvelle luminosite a atteindre
 * lock: verouillage, interdiction de changement de destination
 */
typedef struct  s_eye
{
    u32     *pin;
    u32     *ocrs;
    u16     periode;
    u8      oc_timer;
    u16     min;
    u16     max;
    u16     dfault;
    s16     lux_status;
    s16     lux_glow_speed;
    s16     lux_incr;
    s16     lux_dst;
    s8      lock;
}               t_eye;

// Probablement superflue (valeurs dans structures servo et capteurs
typedef struct s_status
{
}              t_status;

// Idem
typedef struct s_goal
{
}              t_goal;

// Variables comportementales
typedef struct s_mindset
{
}              t_mindset;

// Reference de date
typedef struct	s_stamp
{
	u16		*tmr_ptr;
	u16		*pr_ptr;
	u16		tmr;
	u16		pr;
	u16		nbr_periodes;
	u16		unit;
}				t_stamp;

#endif	/* GUIDELINE_H */

