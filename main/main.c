#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi.h"
#include "telemetry.h"
#include "tcp_client.h"

#define TELEMETRY_INTERVAL_MS 5000

static void telemetry_task(void *pvParameters) {
    telemetry_t msg;
    while (1) {
        telemetry_simulate(&msg);
        tcp_send_telemetry(&msg);
        vTaskDelay(pdMS_TO_TICKS(TELEMETRY_INTERVAL_MS));
    }
}

void app_main(void) {
    printf("tcp-ip-telemetry-node starting...\n");
    wifi_init_sta();
    xTaskCreate(telemetry_task, "telemetry_task", 4096, NULL, 5, NULL);
}