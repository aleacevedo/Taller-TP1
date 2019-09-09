#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <string.h>
#include "client.h"
#include "server.h"
#include "message.h"

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, ERR_NOT_SUPPORTED);
    return 1;
  }
  if (strcmp(argv[1], "server") == 0) {
    if (argc == 3) {
      server_t server;
      if (server_init(&server, argv[2])) return 1;
      return server_run(&server);
    }
    fprintf(stderr, ERR_SERVER);
    return 1;
  }
  if (strcmp(argv[1], "client") == 0) {
    if (argc == 4) {
      client_t client;
      if (client_init(&client, argv[2], argv[3])) return 1;
      return client_run(&client);
    }
    fprintf(stderr, ERR_CLIENT);
    return 1;
  }
  fprintf(stderr, ERR_NOT_SUPPORTED);
  return 1;
}
