/* 
 * File:   types.h
 * Author: bocal
 *
 * Created on June 22, 2016, 6:33 PM
 */

#ifndef TYPES_H
#define	TYPES_H


#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define s8 signed char
#define s16 signed short
#define s32 signed long


#define TIME_TMR1 1
#define NBR_ORDRES 4
#define SIZE_MESS 100           // Taille maximum d'un message UART


/*
 *  Structure de gestion du temps
 *  tmr = TMR1,
 *  nbr_cycle sera incremente via une interrupt
 *  est sera egale au nbr de fois ou la periode sera atteinte
 */
typedef struct  s_marvin_time
{
    u32     *tmr;
    u32     nbr_periode;
}               m_marvin_time;

/*
 * Objet servo:
 * pin: Registre complet de la pin a laquelle est attache le servo
 * min: duty_cycle minimum du servo en ms (ex: 500  (angle de 0deg))
 * max: duty_cycle maximum du servo en ms (ex: 2500 (angle de 180deg))
 * pos: derniere pos du servo en deg
 * ocrs: registre de control correspondant a la PIN du servo
 * periode: periode du servo pour le signal PWM
 * oc_timer: registre cde comparaison secondaire correspondant a la PIN du servo
 * incr: Valeur d'increment de position (pas encore utilise)
 * move_count: 
 */

typedef struct  s_servo
{
    u32     *pin;
    u16      min;
    u16      max;
    s16      pos;
    s16      new_pos;
    u32     *ocrs;
    u16     periode;
    u8      oc_timer;
    s8      incr;
    u8      vitesse;
    u8      move_count;
}               m_servo;

/*
 * Objet Leds:
 * pin: Registre complet de la pin a laquelle est attache la leds
 * min: duty_cycle pour Luminosite min (0 = Led eteinte)
 * max: duty_cycle pour Luminosite max (max = periode : Led allumer au max)
 * lux: Echelle luminosite (1 a 100)
 * new_lux: nouvelle luminosite a atteindre
 * ocrs: registre de control correspondant a la PIN du servo
 * periode: periode du servo pour le signal PWM
 * oc_timer: registre cde comparaison secondaire correspondant a la PIN du servo
 */

typedef struct  s_led
{
    u32     *pin;
    u16     min;
    u16     max;
    s16     lux;
    s16     new_lux;
    u8      vitesse;
    s8      incr;
    u32     *ocrs;
    u16     periode;
    u8      oc_timer;
}               m_led;

/*
 * Objet sonar:
 * echo_attachpin: Numero de pin a laquelle est attache l'echo
 * trig_attachpin: Numero de pin a laquelle est attache le trigger
 * state_trig_pin: Registre d'etat du trigger (LATx)
 * read_echo_pin: Registre de lecture d'etat de l'echo (PORTx)
 */
typedef struct  s_sonar
{
    u8      echo_attachpin;     //Numeros de la PIN
    u8      trig_attachpin;     // Numeros de la PIN
    u32     *state_trig_pin;    // registre etat
    u32     *read_echo_pin;     // registre read
}               m_sonar;

/*
 * struct des fonctions de l'ordre UART
 */
typedef struct  s_ordre
{
    void (*f)(void);
}               t_ordre;

/*
 *  Structure de variables global
 */
typedef struct      s_marvin
{
    m_marvin_time   *time;               // structure de gestion du temps
    m_servo         servo_yaw;           // Objet servo1
    m_servo         servo_pitch;         // Objet servo2
    m_servo         servo_scan;          // Objet servo3
    m_led           led_right;           // Objet Led1
    m_led           led_left;            // Objet Led2
    m_sonar         sonar_right;         // Objet sonar1
    m_sonar         sonar_left;          // Objet sonar2
    u16             val_sonar_r;         // Valeur de mesure du sonar1
    u16             val_sonar_l;         // Valeur de mesure du sonar2
    u16             val_ir;              // Valeur de mesure de l'IR
    u8              send[SIZE_MESS];     // Tableau pour l'envoi de message UART
    u8              receive[SIZE_MESS] ; // Tableau pour la reception de message UART
    u32             counter1;            // Counter nbr periode du TMR3 /!\ Remettre a zero quand Marvin fais rien
    u16             counter2;            //
    u16             tmp_sl;
    u16             tmp_sr;
    t_ordre         ordre[NBR_ORDRES];
}                   m_marvin;

m_marvin_time time;
m_marvin marvin;

#endif	/* TYPES_H */

