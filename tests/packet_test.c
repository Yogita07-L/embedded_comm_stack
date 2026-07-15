#include "packet.h"
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Test payload */
    uint8_t payload[] = {'A', 'B', 'C'};

    /*----------------------------------------------------------
     * Test 1 : Create Packet
     *---------------------------------------------------------*/
    printf("========== CREATE PACKET TEST ==========\n");

    packet_t pkt = create_packet(payload, 3);

    printf("Start Byte : 0x%02X\n", pkt.start_byte);
    printf("Length     : %d\n", pkt.length);

    printf("Payload    : ");
    for (uint8_t i = 0; i < pkt.length; i++)
    {
        printf("0x%02X ", pkt.payload[i]);
    }
    printf("\n\n");

    /*----------------------------------------------------------
     * Test 2 : CRC-8 Calculation
     * CRC is calculated over:
     * Length + Payload
     *---------------------------------------------------------*/
    printf("========== CRC TEST ==========\n");

    uint8_t crc_input[] = {pkt.length, pkt.payload[0], pkt.payload[1], pkt.payload[2]};

    uint8_t crc = calculate_crc8(crc_input, 4);

    printf("CRC Input  : ");
    for (uint8_t i = 0; i < 4; i++)
    {
        printf("0x%02X ", crc_input[i]);
    }

    printf("\n");
    printf("CRC8       : 0x%02X\n\n", crc);

    /*----------------------------------------------------------
     * Test 3 : Encode Packet
     *---------------------------------------------------------*/
    printf("========== ENCODE PACKET TEST ==========\n");

    uint8_t encoded_buffer[260] = {0};

    uint16_t encoded_length = encode_packet(&pkt, encoded_buffer, sizeof(encoded_buffer));

    printf("Encoded Length : %d\n", encoded_length);

    printf("Encoded Packet : ");

    for (uint16_t i = 0; i < encoded_length; i++)
    {
        printf("0x%02X ", encoded_buffer[i]);
    }

    printf("\n");

    return 0;
}