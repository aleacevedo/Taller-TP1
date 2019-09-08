#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "protocol.h"
typedef struct {
  protocol_t protocol;
} client_t;

int client_init(client_t *self, const char *host, const char *service);

int client_run(client_t *self);

int client_uninit(client_t *self);

#endif
