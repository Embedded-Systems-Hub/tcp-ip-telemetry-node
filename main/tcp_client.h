#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "telemetry.h"

void tcp_send_telemetry(const telemetry_t *msg);

#endif /* TCP_CLIENT_H */