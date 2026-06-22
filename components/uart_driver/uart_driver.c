#include <stdio.h>

#include "driver/uart.h"
#include "sdkconfig.h"
#include "uart_driver.h"


/*
 * UART driver initialization
 *
 * This function configures the UART peripheral:
 * 1. Communication parameters (baud rate, data format)
 * 2. GPIO mapping for TX/RX
 * 3. Driver installation (allocates buffers and enables UART driver)
 *
 * Application layer should only call this function.
 * Hardware-specific configuration stays inside this driver.
 */
void uart_driver_init()
{

    /*
     * UART communication configuration
     *
     * 8N1 format:
     * 8 data bits
     * No parity
     * 1 stop bit
     */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, /* Hardware flow control disabled.*/
        .rx_flow_ctrl_thresh = 122,
    };
    /*
     * Apply UART communication parameters
     *
     * Configures the UART peripheral registers internally
     * through ESP-IDF HAL/driver layer.
     */
    ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));

    /*
     * Connect UART peripheral signals to ESP32 GPIO pins.
     *
     * TX -> Data leaving ESP32
     * RX -> Data entering ESP32
     *
     * For UART0 on DevKit, USB-UART bridge is normally connected
     * internally. Other UARTs require external wiring.
     */
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    /*
     * Install UART driver.
     *
     * Creates software buffers for TX/RX.
     *
     * TX buffer: Stores outgoing data before transmission.
     *
     * RX buffer: Stores received bytes until application reads them.
     *
     * No event queue used currently.
     * Interrupt/ring-buffer handling will be added later.
     */
    ESP_ERROR_CHECK(uart_driver_install(UART_PORT, UART_TX_BUFFER_SIZE, UART_RX_BUFFER_SIZE, 0, NULL, 0));
}

/*
 * UART transmit API
 * This abstraction allows us to replace the lower layer later
 * without changing application code.
 */
void uart_driver_send(const char *data)
{
    uart_write_bytes(UART_PORT, data, strlen(data));
}