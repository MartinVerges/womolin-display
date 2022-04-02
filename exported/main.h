
#include <mqtt.h>
#include <lvgl.h>

void display_update_clock(lv_timer_t *timer);
void mqtt_sync_wrapper(lv_timer_t * timer);

void hal_init_simulator(void);
void hal_init_raspberry(void);

struct reconnect_state_t {
    const char* hostname;
    const char* port;
    const char* topic;
    const char* user;
    const char* pass;
    const char* client_id;
    uint8_t* sendbuf;
    size_t sendbufsz;
    uint8_t* recvbuf;
    size_t recvbufsz;
};

void mqtt_prepare(struct mqtt_client* client);
void mqtt_reconnect_client(struct mqtt_client* client, void **reconnect_state_vptr);
void mqtt_publish_callback(void** unused, struct mqtt_response_publish *published);
