#ifndef UART_PARSER_H
#define UART_PARSER_H

#include "packet.h"
#include <stdbool.h>
#include <stdint.h>

/*
 * Parser states used to reconstruct a packet
 * from incoming UART bytes.
 */
typedef enum
{
    WAIT_START,   // Waiting for packet start byte
    READ_LENGTH,  // Reading payload length
    READ_PAYLOAD, // Collecting payload bytes
    READ_CRC      // Reading CRC byte

} parser_state_t;

/*
 * Parser context.
 *
 * Stores the current parsing state and
 * the current payload position while receiving
 * a packet byte-by-byte.
 */
typedef struct
{
    parser_state_t state;

    uint8_t payload_index;

} parser_t;

/*
 * Initialize parser before receiving data.
 */
void parser_init(parser_t* parser);

/*
 * Process one received byte.
 *
 * Bytes are received one at a time from UART.
 * Returns true when a complete packet has been received.
 */
bool parser_process_byte(parser_t* parser, uint8_t byte, packet_t* pkt);

#endif