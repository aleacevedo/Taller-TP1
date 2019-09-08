#include "protocol.h"
#include <stdlib.h>
#include <stdio.h>

int protocol_init(protocol_t *self, const char *host, const char *service) {
  self->last_received = NULL;
  if (socket_init(&(self->socket), host, service)) return 1;
  if (socket_is_server(&(self->socket))) {
    if (socket_listen(&(self->socket), 5)) return 1;
    if (socket_accept(&(self->socket))) return 1;
    return 0;
  }
  if (socket_connect(&(self->socket))) return 1;
  return 0;
}

int protocol_receive_from_server(protocol_t *self) {
  if(self->last_received != NULL) free(self->last_received);
  char msg_len[4];
  int msg_len_int;
  int received = socket_receive(&(self->socket), msg_len, 4);
  if (received <= 0) return received;
  msg_len_int = ntohl(*((int*) msg_len));
  self->last_received = malloc(msg_len_int * sizeof(char));
  return socket_receive(&(self->socket), self->last_received, msg_len_int);
}

int protocol_send_from_server(protocol_t *self, char *message, int size) {
  int size_ = htonl(size);
  int sent = socket_send(&(self->socket),(char *) &size_, 4);
  if (sent <= 0) {
    return sent;
  }
  return socket_send(&(self->socket), message, size);
}

int protocol_receive_from_client(protocol_t *self) {
  if(self->last_received != NULL) free(self->last_received);
  self->last_received = malloc(4 * sizeof(char));
  int received = socket_receive(&(self->socket), self->last_received, 1);
  if (received <= 0) {
    return received;
  }
  if (self->last_received[0] == 'P') {
    return socket_receive(&(self->socket), self->last_received + 1, 3);
  }
  return received;
}

int protocol_send_from_client(protocol_t *self, char *message, int size) {
  return socket_send(&(self->socket), message, size);
}

int protocol_uninit(protocol_t *self) {
  socket_uninit(&(self->socket));
  if(self->last_received != NULL) free(self->last_received);
  return 0;
}
