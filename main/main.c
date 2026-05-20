#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi.h"
#include "tcp_client.h"

void app_main(void) {
    printf("tcp-ip-telemetry-node starting...\n");
    wifi_init_sta();
    tcp_send_test_message();
}