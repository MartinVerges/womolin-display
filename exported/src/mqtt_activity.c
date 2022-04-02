
#include "mqtt_activity.h"
#include "posix_sockets.h"
#include <stdlib.h>

struct reconnect_state_t reconnect_state;
struct mqtt_client my_mqtt_client;
pthread_t mqtt_thread;

void reconnect_client(struct mqtt_client* client, void **reconnect_state_vptr) {
  struct reconnect_state_t *reconnect_state = *((struct reconnect_state_t**) reconnect_state_vptr);
  printf("reconect_client() %p %p\n", client, reconnect_state);

  // Close the clients socket if this isn't the initial reconnect call
  if (client->error != MQTT_ERROR_INITIAL_RECONNECT) close(client->socketfd);

  // Perform error handling here.
  if (client->error != MQTT_ERROR_INITIAL_RECONNECT) {
      printf("reconnect_client: called while client was in error state \"%s\"\n", mqtt_error_str(client->error));
  }

  // Open a new socket.
  int sockfd = open_nb_socket(reconnect_state->hostname, reconnect_state->port);
  if (sockfd == -1) {
      perror("Failed to open socket: ");
      mqtt_exit(EXIT_FAILURE, sockfd, NULL);
  }

  // Reinitialize the client.
  mqtt_reinit(client, sockfd,
              reconnect_state->sendbuf, reconnect_state->sendbufsz,
              reconnect_state->recvbuf, reconnect_state->recvbufsz
  );

  // Create a new session
  const char* client_id = "mydisplay";
  uint8_t connect_flags = MQTT_CONNECT_CLEAN_SESSION;
  mqtt_connect(client, client_id, NULL, NULL, 0, reconnect_state->user, reconnect_state->pass, connect_flags, 400);
  mqtt_subscribe(client, reconnect_state->topic, 0);
}

void publish_callback(void** unused, struct mqtt_response_publish *published) {
  /* note that published->topic_name is NOT null-terminated (here we'll change it to a c-string) */
  char* topic_name = (char*) malloc(published->topic_name_size + 1);
  memcpy(topic_name, published->topic_name, published->topic_name_size);
  topic_name[published->topic_name_size] = '\0';

  char* application_message = (char*) malloc(published->application_message_size + 1);
  memcpy(application_message, published->application_message, published->application_message_size);
  application_message[published->application_message_size] = '\0';
 
  printf("Received publish('%s'): %s\n", topic_name, application_message);
  free(topic_name);
  free(application_message);
}

void mqtt_exit(int status, int sockfd, pthread_t *client_daemon) {}

void * mqtt_prepare_loop(struct mqtt_client* client) {
  int bufsize = 2048;
  reconnect_state.hostname = "192.168.254.91";
  reconnect_state.port = "1883";
  reconnect_state.topic = "freshwater/tanklevel";
  reconnect_state.user = "rv-gui";
  reconnect_state.pass = "abcd1234";
  reconnect_state.sendbuf = malloc(bufsize);
  reconnect_state.sendbufsz = bufsize;
  reconnect_state.recvbuf = malloc(bufsize);
  reconnect_state.recvbufsz = bufsize;

  printf("reconnect_state %p\n", &reconnect_state);
  mqtt_init_reconnect(client, reconnect_client, &reconnect_state, publish_callback);

  /* start publishing the time */
  printf("%s listening for '%s' messages.\n", reconnect_state.hostname, reconnect_state.topic);
  
  /*printf("pre pthread %p\n", client);
  if(pthread_create(&mqtt_thread, NULL, mqtt_loop_call, client)) {
      fprintf(stderr, "Failed to start client daemon.\n");
      mqtt_exit(EXIT_SUCCESS, client->socketfd, &mqtt_thread);
  }
  fprintf(stderr, "whatever\n");*/
}
/*
void * mqtt_loop_call(struct mqtt_client* client) {
  while(1) {
      mqtt_sync(client);
      usleep(100000U);
  }
}*/
