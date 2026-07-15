#include "packet.h"

packet_t create_packet(const uint8_t* data, uint8_t length)
{
    packet_t pkt;

    pkt.start_byte = 0xAA;
    pkt.length = length;

    for (uint8_t i = 0; i < length; i++)
    {
        pkt.payload[i] = data[i];
    }

    pkt.crc = 0x00;

    return pkt;
}

uint16_t encode_packet(packet_t* pkt, uint8_t encoded_buffer[], uint16_t buffer_size)
{
    // Packet format:
    // Start byte + Length + Payload + CRC

    if (buffer_size < pkt->length + 3)
    {
        return 0;
    }

    encoded_buffer[0] = pkt->start_byte;
    encoded_buffer[1] = pkt->length;

    // Copy payload bytes into transmit buffer
    for (uint16_t i = 0; i < pkt->length; i++)
    {
        encoded_buffer[2 + i] = pkt->payload[i];
    }

    // CRC is calculated over length byte + payload
    uint8_t crc_buffer_payload[260];

    crc_buffer_payload[0] = pkt->length;

    for (uint16_t i = 0; i < pkt->length; i++)
    {
        crc_buffer_payload[i + 1] = pkt->payload[i];
    }

    pkt->crc = calculate_crc8(crc_buffer_payload, pkt->length + 1);

    encoded_buffer[2 + pkt->length] = pkt->crc;

    return pkt->length + 3;
}

uint8_t calculate_crc8(const uint8_t* data, uint16_t length)
{
    uint8_t crc = 0x00;
    uint8_t crc_polynomial = 0x07;

    for (uint8_t i = 0; i < length; i++)
    {
        crc ^= data[i];

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ crc_polynomial;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

bool decode_packet(uint8_t* encoded_buffer, uint16_t buffer_length, packet_t* pkt)
{
    if (encoded_buffer[0] != 0xAA)
        return false;

    if (buffer_length < pkt->length + 3)
        return false;

    pkt->start_byte = encoded_buffer[0];
    pkt->length = encoded_buffer[1];
    for (uint16_t itr = 0; itr < pkt->length; itr++)
    {
        pkt->payload[itr] = encoded_buffer[itr + 2];
    }

    // Prepare CRC calculation buffer
    uint8_t crc_buffer[255];
    crc_buffer[0] = pkt->length;

    for (uint16_t i = 0; i < pkt->length; i++)
    {
        crc_buffer[i + 1] = pkt->payload[i];
    }

    uint8_t calc_crc = calculate_crc8(crc_buffer, pkt->length + 1);

    uint8_t received_crc = encoded_buffer[pkt->length + 2];

    if (received_crc != calc_crc)
    {
        return false;
    }

    pkt->crc = received_crc;
    return true;
}