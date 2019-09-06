#define _POSIX_C_SOURCE 200112L
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include "socket.h"

int server_init(const char *service) {
  socket_t socket;
  if (socket_init(&socket, NULL, service) == 1) return 1;
  if (socket_listen(&socket, 20) == 1) return 1;
  if (socket_accept(&socket) == 1) return 1;
  char cadena[20];
  int recived = socket_receive(&socket, cadena, 20);
  if (recived > 0) {
    printf("RECIBI: %s\n", cadena);
    socket_uninit(&socket);
    return 0;
  }
  printf("%i\n", recived);
  socket_uninit(&socket);
  return 1;
}
