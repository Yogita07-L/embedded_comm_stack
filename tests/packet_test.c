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

    printf("\n\n");

    printf("========== DECODE PACKET TEST ==========\n");

    /*
        Received packet from UART:

        START LENGTH PAYLOAD CRC

        AA    03     41 42 43  68
    */

    uint8_t received_buffer[] = {0xAA, 0x03, 0x41, 0x42, 0x43, 0x68};

    packet_t decoded_packet;

    bool status = decode_packet(received_buffer, sizeof(received_buffer), &decoded_packet);

    if (status)
    {
        printf("Packet valid\n");

        printf("Start byte : 0x%02X\n", decoded_packet.start_byte);

        printf("Length     : %d\n", decoded_packet.length);

        printf("Payload    : ");

        for (uint8_t i = 0; i < decoded_packet.length; i++)
        {
            printf("0x%02X ", decoded_packet.payload[i]);
        }

        printf("\n");

        printf("CRC        : 0x%02X\n", decoded_packet.crc);
    }
    else
    {
        printf("Packet invalid\n");
    }
    return 0;
}