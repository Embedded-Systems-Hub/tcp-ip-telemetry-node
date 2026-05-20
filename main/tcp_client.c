#include "tcp_client.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "lwip/sockets.h"

#define SERVER_IP   "192.168.1.133"
#define SERVER_PORT 5001

static const char *TAG = "tcp_client";

void tcp_send_test_message(void) {
    const char *message = "hello from ESP32\n";

    struct sockaddr_in dest_addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(SERVER_PORT),
    };
    inet_pton(AF_INET, SERVER_IP, &dest_addr.sin_addr);

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        ESP_LOGE(TAG, "failed to create socket: errno %d", errno);
        return;
    }

    if (connect(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != 0) {
        ESP_LOGE(TAG, "connect failed: errno %d", errno);
        close(sock);
        return;
    }

    ESP_LOGI(TAG, "connected to %s:%d", SERVER_IP, SERVER_PORT);

    int err = send(sock, message, strlen(message), 0);
    if (err < 0) {
        ESP_LOGE(TAG, "send failed: errno %d", errno);
    } else {
        ESP_LOGI(TAG, "message sent");
    }

    close(sock);
}