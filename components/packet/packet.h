#ifndef PACKET_H
#define PACKET_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint8_t start_byte;   // Packet start identifier
    uint8_t length;       // Number of payload bytes
    uint8_t payload[254]; // Packet data
    uint8_t crc;          // CRC8 checksum
} packet_t;

/*
 * Creates a packet from application data.
 *
 * data   : Pointer to payload data
 * length : Number of payload bytes
 *
 * Returns a packet structure containing the payload.
 */
packet_t create_packet(const uint8_t* data, uint8_t length);

/*
 * Encodes a packet into a byte buffer for transmission.
 *
 * Format:
 * [Start Byte][Length][Payload][CRC]
 *
 * Returns the number of encoded bytes.
 * Returns 0 if the buffer is too small.
 */
uint16_t encode_packet(packet_t* pkt, uint8_t encoded_buffer[], uint16_t buffer_size);

/*
 * Calculates CRC8 checksum for error detection.
 *
 * CRC configuration:
 * Polynomial: 0x07
 * Initial value: 0x00
 */
uint8_t calculate_crc8(const uint8_t* data, uint16_t length);

/*
 * Decode a received packet.
 *
 * Checks the packet format and verifies CRC.
 * Extracts payload data if the packet is valid.
 *
 * Returns true if the packet passes CRC validation.
 * Returns false if the packet is corrupted.
 */
bool decode_packet(uint8_t* encoded_buffer, uint16_t buffer_length, packet_t* pkt);

#endif