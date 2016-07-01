/*
 * File:   uart.h
 * Author: bocal
 *
 * Created on June 3, 2016, 2:44 PM
 */

#ifndef UART_H
#define	UART_H

#include "types.h"
#include <p32xxxx.h>

#define REGISTER_BAUD_RATE U1BRG
#define BAUD_RATE 9600

#define MARVIN_UART &U1MODE
#define MARVIN_UART_STATUS &U1STA
#define MARVIN_UART_SEND &U1TXREG
#define MARVIN_UART_RECEIVE &U1RXREG


#define BRGH_x4 1 << 3             // High Baud rate speed mode (x4)
#define BRGH_x16 0                  // Standard Baud rate speed mode (x16)

#define PDSEL_00 0b00 << 1      // 8 bit data no parity
#define PDSEL_01 0b01 << 1      // 8 bit data even parity
#define PDSEL_10 0b10 << 1      // 8 bit data odd parity
#define PDSEL_11 ob11 << 1      // 9 bit data no parity

#define STSEL_0 0               // 1 Stop selection bit
#define STSEL_1 1               // 2 Stop selection bit

#define UART_ON 1 << 15
#define UART_OFF 0 << 15

#define UTXEN_0 0 << 10         // Transmit Enable bit
#define UTXEN_1 1 << 10

#define URXISEL_00 0            // Interrupt when a char is receive
#define URXISEL_01 1 << 6       // Interrupt when the buffer is 1/2 more full
#define URXISEL_10 0b10 << 6    // Interrupt when the buffer is 3/4 more full

#define URXEN_0 0 << 12         // Receiver Enable bit
#define URXEN_1 1 << 12

#define OERR_0 0                // If OERR == 1, buffer has overflowed, Set the bit to 0 reset the receiver buffer

#define PIN_RX
#define PIN_TX


// finir les transmissions avec /n/r ?????

/*
 * Les messages de l'uart sont codes sur un octet( voi finirr peut etre pluspour envoyer
 * une finfo sur la vitesse et la POSITIOn
 */

/*
 * Defines sur les ordres a envoyer en UART
 */
#define UART_SEND_RIGHT "0" // Quand marvin tourne a droite
#define UART_SEND_LEFT "1" // Quand Marvin tourne a gauche
#define UART_SEND_SLEEP "2" // quand marvin tourne a droite
#define UART_SEND_FIND "3" // Quand marvin  trouver une personne


void    marvin_setup_baud_rate();
void    marvin_setup_uart();
void    marvin_send_message(u8 *tab);
void    marvin_ordre_right();
void    marvin_ordre_left();
void    marvin_ordre_find();
void    marvin_ordre_sleep();
u8      marvin_check_trans();
char    *marvin_receive_message(u8 *receive, u16 *uart_nbr);
#endif	/* UART_H */


