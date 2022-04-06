
#include <mqtt.h>
#include <lvgl.h>
#include <string>
using namespace std;

int nav_screen = 1;

const char* config_filename = "config.json";
struct config_t {
  string mqtt_hostname;
  string mqtt_port;
  string mqtt_user;
  string mqtt_pass;
  bool freshwater_enabled;
  string freshwater_topic;
  bool greywater_enabled;
  string greywater_topic;
  bool gas_bottle1_enabled;
  string gas_bottle1_topic;
  bool gas_bottle2_enabled;
  string gas_bottle2_topic;
};
void load_configuration();
bool save_configuration();

void display_update_clock(lv_timer_t *timer);
void mqtt_sync_wrapper(lv_timer_t * timer);

void hal_init_simulator(void);
void hal_init_raspberry(void);

void set_level(lv_obj_t * bar, lv_obj_t * label, int level);
void refresh_levels();
struct received_mqtt_data_t {
  uint8_t freshwater;
  uint8_t greywater;
  uint8_t gas_bottle1;
  uint8_t gas_bottle2;
};

struct mqtt_buffer_t {
    uint8_t* sendbuf;
    size_t sendbufsz;
    uint8_t* recvbuf;
    size_t recvbufsz;
};
void mqtt_force_reconnect();
void mqtt_prepare(struct mqtt_client* client, config_t &config);
void mqtt_reconnect_client(struct mqtt_client* client, void **reconnect_state_vptr);
void mqtt_publish_callback(void** unused, struct mqtt_response_publish *published);
