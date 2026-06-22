#include <stdio.h>
#include "uart_driver.h"

void app_main(void)
{
    uart_driver_init();
    uart_driver_send("This is a test string. \n");
} 