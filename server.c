#define _POSIX_C_SOURCE 200112L
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include "socket.h"
#include "message.h"

int server_init(server_t *self, const char *service) {
  if (sudoku_init(&(self->sudoku))) return 1;
  if (protocol_init(&(self->protocol), NULL, service)) return 1;
  return 0;
}

static int _get(server_t *self) {
  char board[BOARD_REPRESENTATION_LEN];
  int board_size = BOARD_REPRESENTATION_LEN;
  sudoku_show(&(self->sudoku), board);
  if (protocol_send_from_server(&(self->protocol), board, board_size) <= 0)
    return 1;
  return 0;
}

static int _put(server_t *self) {
  int size = 37;
  char row = self->protocol.last_received[1];
  char column = self->protocol.last_received[2];
  char value = self->protocol.last_received[3];
  if (sudoku_set(&(self->sudoku), row, column, value)) {
    return protocol_send_from_server(&(self->protocol), ERR_INIT_VAL, size);
  }
  return _get(self);
}

static int _verify(server_t *self) {
  int size;
  if (sudoku_validate(&(self->sudoku))) {
    size = 4;
    if (protocol_send_from_server(&(self->protocol), VERIFY_OK, size) <= 0)
      return 1;
    return 0;
  } else {
    size = 7;
    if (protocol_send_from_server(&(self->protocol), VERIFY_ERR, size) <= 0)
      return 1;
    return 0;
  }
}

static int _reset(server_t *self) {
  sudoku_reset(&(self->sudoku));
  return _get(self);
}

static int _execute_action_received(server_t *self) {
  switch (self->protocol.last_received[0]) {
    case 'P':return _put(self);
    case 'V':return _verify(self);
    case 'R':return _reset(self);
    case 'G':return _get(self);
  }
  return 0;
}

int server_run(server_t *self) {
  int received = protocol_receive_from_client(&(self->protocol));
  while (received > 0) {
    _execute_action_received(self);
    received = protocol_receive_from_client(&(self->protocol));
  }
  server_uninit(self);
  if (received == 0) {
    return 0;
  }
  return 1;
}

int server_uninit(server_t *self) {
  protocol_uninit(&(self->protocol));
  sudoku_uninit(&(self->sudoku));
  return 0;
}
