#define _POSIX_C_SOURCE 200112L
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include "socket.h"

int server_init(const char *service) {
  protocol_t protocol;
  if(protocol_init(&protocol, NULL, service)) return 1;
  if(protocol_receive_from_client(&protocol)<=0) return 1;
  printf("El server recibio: %s\n", protocol.last_received);
  if(protocol_send_from_server(&protocol, "HOLA COMO ESTAS\n", 5)<=0) return 1;
  protocol_uninit(&protocol);
  return 0;
}
