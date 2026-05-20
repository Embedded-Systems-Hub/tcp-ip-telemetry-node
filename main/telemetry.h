#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>

typedef enum {
    MACHINE_STATE_IDLE    = 0,
    MACHINE_STATE_RUNNING = 1,
    MACHINE_STATE_FAULT   = 2,
} machine_state_t;

/*
 * Telemetry message sent over TCP as a single-line JSON object, terminated by '\n'.
 *
 * Example:
 *   {
 *     "machine_id":"NODE_01",
 *     "state":1,
 *     "temp":72.4,
 *     "vibration":0.12,
 *     "fault_code":0,
 *     "uptime":3600,
 *     "ts":1747000000
 *   }
 *
 * Fields:
 *   machine_id  - node identifier (string)
 *   state       - machine_state_t: 0=IDLE, 1=RUNNING, 2=FAULT
 *   temp        - temperature in Celsius (float)
 *   vibration   - vibration level in g (float)
 *   fault_code  - active fault code, 0 = no fault (uint8)
 *   uptime      - seconds since boot (uint32)
 *   ts          - milliseconds since boot, used as timestamp (int64)
 */
typedef struct {
    char            machine_id[16];
    machine_state_t state;
    float           temperature;
    float           vibration;
    uint8_t         fault_code;
    uint32_t        uptime_seconds;
    int64_t         timestamp;
} telemetry_t;

void telemetry_simulate(telemetry_t *msg);

#endif /* TELEMETRY_H */