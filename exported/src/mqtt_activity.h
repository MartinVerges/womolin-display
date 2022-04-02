
#include <mqtt.h>

struct reconnect_state_t {
    const char* hostname;
    const char* port;
    const char* topic;
    const char* user;
    const char* pass;
    uint8_t* sendbuf;
    size_t sendbufsz;
    uint8_t* recvbuf;
    size_t recvbufsz;
};

void reconnect_client(struct mqtt_client* client, void **reconnect_state_vptr);
void publish_callback(void** unused, struct mqtt_response_publish *published);
void mqtt_exit(int status, int sockfd, pthread_t *client_daemon);
void * mqtt_prepare_loop();
void * mqtt_loop_call(struct mqtt_client* client);
