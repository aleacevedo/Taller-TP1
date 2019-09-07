#ifndef _SERVER_H_
#define _SERVER_H_

#include "sudoku.h"
#include "protocol.h"
typedef  struct {
  sudoku_t sudoku;
  protocol_t protocol;
} server_t;

int server_init(const char *service);

#endif
