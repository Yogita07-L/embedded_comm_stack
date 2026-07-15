#include "packet.h"
#include "uart_driver.h"
#include <stdio.h>

void app_main(void)
{
    // static const char* TAG = "UART_TEST";
    // ESP_LOGI(TAG, "before init");

    // uart_driver_init();
    // ESP_LOGI(TAG, "Init Complete");

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
    //         uart_driver_send(buff er);
    //     }
    // }

    packet_t pkt;
    uint8_t input[] = "ABC";
    pkt = create_packet(input, 10);

    printf("%X\n", pkt.start_byte);
    printf("%d\n", pkt.length);
    printf("%X\n", pkt.payload[0]);
    printf("%X\n", pkt.payload[1]);
    printf("%X\n", pkt.payload[2]);
}