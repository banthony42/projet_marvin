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

#define REGISTER_BAUD_RATE U1BRG;
#define BAUD_RATE 96000

#define MARVIN_UART &U1MODE
#define MARVIN_UART_STATUS &U1STA
#define MARVIN_UART_SEND &U1TXREG
#define MARVIN_UART_RECEIVE &U1RXREG
#define MARVIN_IS_RECEIVE &U1STAbits.URXDA


#define BRGH 1 << 3

#define PDSEL_00 0b00 << 1
#define PDSEL_01 0b01 << 1
#define PDSEL_10 0b10 << 1
#define PDSEL_11 ob11 << 1

#define STSEL_0 0
#define STSEL_1 1

#define UART_ON 0 << 15
#define UART_OFF 1 << 15

#define UTXEN_0 0 << 10
#define UTXEN_1 1 << 10

#define URXEN_0 0 << 12
#define URXEN_1 1 << 12

#define OERR_1 1 << 1
#define OERR_0 0 << 1

#define PIN_RX
#define PIN_TX

// Focntion qui calcul le Baud Rate // check du speed mode ?????
// Pas forcement utile pck c'est pas comme un timer que l'on vas devoir odifier
// doit checker PBCLK


void    marvin_setup_baud_rate();
void    marvin_setup_uart();
void    marvin_send_message();
void    marvin_receive_message();
#endif	/* UART_H */

