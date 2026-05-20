idf_component_register(SRCS "main.c" "wifi.c" "tcp_client.c" "telemetry.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES esp_wifi esp_event esp_netif nvs_flash esp_timer)