#define _POSIX_C_SOURCE 200112L
#include "client.h"
#include "protocol.h"
#include <stdio.h>

void client_init(const char* host, const char* service) {
  protocol_t protocol;
  protocol_init(&protocol, host, service);
  protocol_send_from_client(&protocol, "Hola soy un cliente\n", 20);
  protocol_receive_from_server(&protocol);
  printf("El cliente recibio: %s\n", protocol.last_received);
  protocol_uninit(&protocol);
}
