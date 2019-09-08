#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "socket.h"

typedef struct {
  socket_t socket;
  char *last_received;
} protocol_t;

int protocol_init(protocol_t *self, const char *host, const char *service);

int protocol_receive_from_server(protocol_t *self);

int protocol_send_from_server(protocol_t *self, char *message, int size);

int protocol_receive_from_client(protocol_t *self);

int protocol_send_from_client(protocol_t *self, char *message, int size);

int protocol_uninit(protocol_t *self);

#endif
