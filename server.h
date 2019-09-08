#ifndef _SERVER_H_
#define _SERVER_H_

#include "sudoku.h"
#include "protocol.h"
typedef struct {
  sudoku_t sudoku;
  protocol_t protocol;
} server_t;

int server_init(server_t *self, const char *service);

int server_run(server_t *self);

int server_uninit(server_t *self);

#endif
