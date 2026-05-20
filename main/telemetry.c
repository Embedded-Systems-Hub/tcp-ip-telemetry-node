#include "telemetry.h"

#include <string.h>
#include "esp_timer.h"

void telemetry_simulate(telemetry_t *msg) {
    strncpy(msg->machine_id, "NODE_01", sizeof(msg->machine_id) - 1);
    msg->machine_id[sizeof(msg->machine_id) - 1] = '\0';

    msg->state          = MACHINE_STATE_RUNNING;
    msg->temperature    = 68.0f + (float)(esp_timer_get_time() % 1000) / 100.0f;
    msg->vibration      = 0.05f + (float)(esp_timer_get_time() % 100) / 1000.0f;
    msg->fault_code     = 0;
    msg->uptime_seconds = (uint32_t)(esp_timer_get_time() / 1000000);
    msg->timestamp      = esp_timer_get_time() / 1000;
}