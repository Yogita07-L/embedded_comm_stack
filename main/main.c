#include "packet.h"
#include "uart_driver.h"
#include <stdio.h>

void app_main(void)
{
    static const char* TAG = "UART_TEST";
    ESP_LOGI(TAG, "before init");

    uart_driver_init();
    ESP_LOGI(TAG, "Init Complete");
    ESP_LOGI("UART_TEST", "UART%d TX=%d RX=%d", UART_PORT, TX_PIN, RX_PIN);

    // uart_driver_send("This is a test string. \n");
    // ESP_LOGI(TAG, "Send Complete");

    // char buffer[100];
    // ESP_LOGI(TAG, "Waiting for UART data...");

    // while (1)
    // {
    //     int bytes = uart_driver_receive(buffer, sizeof(buffer) - 1);

    //     if (bytes > 0)
    //     {
    //         buffer[bytes] = '\0';
    //         ESP_LOGI(TAG, "\n Bytes received = %d", bytes);
    //         uart_driver_send(buffer);
    //     }
    // }

    uint8_t data[] = {0x41, 0x42, 0x43};

    /* Tx Side - create packet */
    packet_t tx_packet = create_packet(data, 3);

    /*Encode Packet*/
    uint8_t tx_buffer[260];
    uint16_t tx_length = encode_packet(&tx_packet, tx_buffer, sizeof(tx_buffer));

    printf("Sending packet:\n");

    for (int i = 0; i < tx_length; i++)
    {
        printf("0x%02X ", tx_buffer[i]);
    }

    printf("\n");

    uart_flush_input(UART_PORT);
    /* Send through UART*/
    uart_driver_send(tx_buffer, tx_length);

    uint8_t rx_buffer[260];
    uint16_t rx_length = uart_driver_receive(rx_buffer, sizeof(rx_buffer));

    packet_t rx_packet;
    printf("Received bytes:\n");

    for (int i = 0; i < rx_length; i++)
    {
        printf("0x%02X ", rx_buffer[i]);
    }

    printf("\n");

    /* Decode received packet */
    if (decode_packet(rx_buffer, rx_length, &rx_packet))
    {
        printf("Packet OK\n");

        printf("Payload:\n");

        for (int i = 0; i < rx_packet.length; i++)
        {
            printf("0x%02X ", rx_packet.payload[i]);
        }
    }
    else
    {
        printf("Packet CRC failed\n");
    }
}