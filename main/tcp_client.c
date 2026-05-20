#include "tcp_client.h"

#include <string.h>
#include "esp_log.h"
#include "lwip/sockets.h"
#include "cJSON.h"

#define SERVER_IP   "192.168.1.133"
#define SERVER_PORT 5001

static const char *TAG = "tcp_client";

void tcp_send_telemetry(const telemetry_t *msg) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "machine_id", msg->machine_id);
    cJSON_AddNumberToObject(root, "state",      msg->state);
    cJSON_AddNumberToObject(root, "temp",        msg->temperature);
    cJSON_AddNumberToObject(root, "vibration",   msg->vibration);
    cJSON_AddNumberToObject(root, "fault_code",  msg->fault_code);
    cJSON_AddNumberToObject(root, "uptime",      msg->uptime_seconds);
    cJSON_AddNumberToObject(root, "ts",          msg->timestamp);

    char *json_str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);

    if (json_str == NULL) {
        ESP_LOGE(TAG, "failed to serialize telemetry");
        return;
    }

    struct sockaddr_in dest_addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(SERVER_PORT),
    };
    inet_pton(AF_INET, SERVER_IP, &dest_addr.sin_addr);

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        ESP_LOGE(TAG, "failed to create socket: errno %d", errno);
        free(json_str);
        return;
    }

    if (connect(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != 0) {
        ESP_LOGE(TAG, "connect failed: errno %d", errno);
        close(sock);
        free(json_str);
        return;
    }

    size_t len = strlen(json_str);
    json_str[len] = '\n';

    int err = send(sock, json_str, len + 1, 0);
    if (err < 0) {
        ESP_LOGE(TAG, "send failed: errno %d", errno);
    } else {
        ESP_LOGI(TAG, "telemetry sent: %s", json_str);
    }

    close(sock);
    free(json_str);
}