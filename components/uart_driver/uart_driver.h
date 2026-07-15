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
#define UART_PORT UART_NUM_2

/*
 * GPIO mapping
 *
 * TX:
 * Transmit pin - ESP32 sends data here
 *
 * RX:
 * Receive pin - ESP32 receives data here
 */
#define TX_PIN 17
#define RX_PIN 16

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

/**
 * Send raw bytes through UART.
 * data : buffer containing bytes to transmit
 * length : number of bytes to send
 */
void uart_driver_send(const uint8_t* data, uint16_t length);

/*
 * Receive bytes from UART.
 *
 * rx_buffer : buffer to store received bytes
 * size      : maximum bytes to read
 *
 * Returns number of received bytes.
 */
int uart_driver_receive(uint8_t* rx_buffer, size_t size);

#endif