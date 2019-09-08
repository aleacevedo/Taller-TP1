#define _POSIX_C_SOURCE 200112L
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include "socket.h"

int server_init(server_t *self, const char *service) {
  if (protocol_init(&(self->protocol), NULL, service)) return 1;
  if (sudoku_init(&(self->sudoku))) return 1;
  return 0;
}

int server_get(server_t *self) {
  char board[BOARD_REPRESENTATION_LEN];
  int board_size = BOARD_REPRESENTATION_LEN;
  sudoku_show(&(self->sudoku), board);
  if (protocol_send_from_server(&(self->protocol), board, board_size) <= 0) return 1;
  return 0;
}

int server_put(server_t *self) {
  int size = 37;
  char row = self->protocol.last_received[1];
  char column = self->protocol.last_received[2];
  char value = self->protocol.last_received[3];
  if (sudoku_set(&(self->sudoku), row, column, value)) {
    return protocol_send_from_server(&(self->protocol), "La celda indicada no es modificable\n\0", size);
  };
  return server_get(self);
}

int server_verify(server_t *self) {
  int size;
  if(sudoku_validate(&(self->sudoku))){
    size = 4;
    if (protocol_send_from_server(&(self->protocol), "OK\n\0", size) <= 0) return 1;
    return 0;
  }else{
    size = 7;
    if (protocol_send_from_server(&(self->protocol), "ERROR\n\0", size) <= 0) return 1;
    return 0;
  }
}

int server_reset(server_t *self) {
  sudoku_reset(&(self->sudoku));
  return server_get(self);
}

int server_execute_action(server_t *self) {
  switch (self->protocol.last_received[0]) {
    case 'P':return server_put(self);
    case 'V':return server_verify(self);
    case 'R':return server_reset(self);
    case 'G':return server_get(self);
  }
  return 0;
}

int server_run(server_t *self) {
  int received = protocol_receive_from_client(&(self->protocol));
  while (received > 0) {
    server_execute_action(self);
    received = protocol_receive_from_client(&(self->protocol));
  }
  server_uninit(self);
  if(received == 0){
    return 0;
  }
  return 1;
}

int server_uninit(server_t *self){
  protocol_uninit(&(self->protocol));
  sudoku_uninit(&(self->sudoku));
  return 0;
}
