
#define _POSIX_C_SOURCE 200112L
#include "client.h"
#include <stdio.h>
#include "protocol.h"
#include "message.h"


int client_init(client_t *self, const char *host, const char *service) {
  return protocol_init(&(self->protocol), host, service);
}

static int _check_range(int row, int column, int value) {
  if (value < 1 || 9 < value) {
    fprintf(stderr, ERR_VALUE);
    return 0;
  }
  if (row < 1 || 9 < row) {
    fprintf(stderr, ERR_INDEX);
    return 0;
  }
  if (column < 1 || 9 < column) {
    fprintf(stderr, ERR_INDEX);
    return 0;
  }
  return 1;
}

static int _send_put(client_t *self, char *command) {
  char toSend[4] = "P";
  int column = 0, row = 0, value = 0;
  sscanf(command, "%*s %i %*s %i,%i", &value, &row, &column);
  if (!_check_range(row, column, value)) return 0;
  toSend[1] = command[9];
  toSend[2] = command[11];
  toSend[3] = command[4];
  protocol_send_from_client(&(self->protocol), toSend, 4);
  protocol_receive_from_server(&(self->protocol));
  fprintf(stdout, "%s", self->protocol.last_received);
  return 0;
}

static int _send_show(client_t *self, char *command) {
  protocol_send_from_client(&(self->protocol), command, 1);
  protocol_receive_from_server(&(self->protocol));
  fprintf(stdout, "%s", self->protocol.last_received);
  return 0;
}

int _execute_action(client_t *self, char *command) {
  switch (command[0]) {
    case 'p': return _send_put(self, command);
    case 'v': return _send_show(self, "V");
    case 'r': return _send_show(self, "R");
    case 'g': return _send_show(self, "G");
    case 'e': return 1;
  }
  return 0;
}

int client_run(client_t *self) {
  char command[14];
  while (1) {
    if (fgets(command, 14, stdin) != NULL) {
      if (_execute_action(self, command)) {
        client_uninit(self);
        return 0;
      }
    } else {
      client_uninit(self);
      return 0;
    }
  }
}

int client_uninit(client_t *self) {
  protocol_uninit(&(self->protocol));
  return 0;
}
