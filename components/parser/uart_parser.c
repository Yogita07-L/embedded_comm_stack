#include "uart_parser.h"

/*
 * Initialize parser state.
 *
 * Parser starts by waiting for the
 * start byte of a new packet.
 */
void parser_init(parser_t* parser)
{
    parser->state = WAIT_START;
    parser->payload_index = 0;
}

/*
 * Process incoming UART bytes and build a packet.
 *
 * The parser works as a state machine.
 * A packet is complete after the CRC byte
 * has been received.
 */
bool parser_process_byte(parser_t* parser, uint8_t byte, packet_t* pkt)
{
    switch (parser->state)
    {

    case WAIT_START:

        /*
         * Ignore all bytes until a valid
         * packet start byte is received.
         */
        if (byte == 0xAA)
        {
            pkt->start_byte = byte;

            parser->payload_index = 0;

            parser->state = READ_LENGTH;
        }

        break;

    case READ_LENGTH:

        /*
         * Length defines how many payload
         * bytes are expected.
         */
        pkt->length = byte;

        parser->state = READ_PAYLOAD;

        break;

    case READ_PAYLOAD:

        /*
         * Store received payload bytes
         * until the expected length is reached.
         */
        pkt->payload[parser->payload_index] = byte;

        parser->payload_index++;

        if (parser->payload_index >= pkt->length)
        {
            parser->state = READ_CRC;
        }

        break;

    case READ_CRC:

        /*
         * Last byte of the packet contains CRC.
         */
        pkt->crc = byte;

        /*
         * Packet completed.
         * Reset parser for the next packet.
         */
        parser->state = WAIT_START;

        parser->payload_index = 0;

        return true;

    default:

        /*
         * Recover parser if an invalid
         * state occurs.
         */
        parser->state = WAIT_START;

        break;
    }

    return false;
}