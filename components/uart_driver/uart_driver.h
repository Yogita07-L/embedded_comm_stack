#ifndef UART_DRIVER_H
#define UART_DRIVER_H


#include "driver/uart.h"

/*
 * UART peripheral used by this driver.
 *
 * ESP32 has UART0, UART1, UART2.
 *
 * UART0 is currently used because it is connected
 * to the USB serial converter on the DevKit board,
 * allowing testing through idf.py monitor.
 */
#define UART_PORT UART_NUM_0

/*
 * GPIO mapping
 *
 * TX:
 * Transmit pin - ESP32 sends data here
 *
 * RX:
 * Receive pin - ESP32 receives data here
 */
#define TX_PIN 1
#define RX_PIN 3

/*
 * Driver software buffer sizes.
 *
 * These are not hardware registers.
 *
 * They are RAM buffers managed by the ESP-IDF UART driver.
 */
#define UART_RX_BUFFER_SIZE 1024 * 2
#define UART_TX_BUFFER_SIZE 1024 * 2

/*
 * Public driver API.
 *
 * Application layer should only interact with
 * these functions, not ESP-IDF UART functions directly.
 */
void uart_driver_init(void);

void uart_driver_send(const char *data);

#endif