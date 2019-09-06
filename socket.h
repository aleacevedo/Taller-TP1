#ifndef _SOCKET_H
#define _SOCKET_H

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct {
  int skt;
  int client;
  struct addrinfo hints;
  struct addrinfo *ptr;
  int isServer;
} socket_t;

int socket_init(socket_t *self,const char *host,const  char *service) ;

int socket_listen(socket_t *self, int pool_size);

int socket_accept(socket_t *self);

int socket_receive(socket_t *self, char *buff, int size);

int socket_shutdown_close(int toClose);

int socket_uninit(socket_t *self);



#endif
