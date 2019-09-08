#define _POSIX_C_SOURCE 200112L
#include "client.h"
#include "protocol.h"
#include <stdio.h>

int client_init(client_t *self, const char* host, const char* service) {
  return protocol_init(&(self->protocol), host, service);
}

int check_range(char value){
  return '0' < value && value < '9';
}

int client_put(client_t *self, char* command){
  char toSend[4] = "P";
  toSend[1] = command[9];
  toSend[2] = command[11];
  toSend[3] = command[4];
  if(!(check_range(toSend[1])&&check_range(toSend[2])&&check_range(toSend[3])))
    return 0;
  protocol_send_from_client(&(self->protocol), toSend, 4);
  protocol_receive_from_server(&(self->protocol));
  printf("%s", self->protocol.last_received);
  return 0;
}

int client_send_show(client_t *self, char* command){
  protocol_send_from_client(&(self->protocol), command, 1);
  protocol_receive_from_server(&(self->protocol));
  printf("%s", self->protocol.last_received);
  return 0;
}

int client_execute_action(client_t *self, char* command){
  switch (command[0]){
    case 'p': return client_put(self, command);
    case 'v': return client_send_show(self, "V");
    case 'r': return client_send_show(self, "R");
    case 'g': return client_send_show(self, "G");
    case 'e': return 1;
  }
  return 0;
}

int client_run(client_t *self) {
  char command[14];
  while(1){
    fgets(command, 14, stdin);
    if(client_execute_action(self, command)){
      client_uninit(self);
      return 0;
    }
  }
}

int client_uninit(client_t *self){
  protocol_uninit(&(self->protocol));
  return 0;
}
