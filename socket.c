#include <errno.h>
#include "socket.h"
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>



int socket_init(socket_t *self, const char *host, const char *service) {
  memset(&(self->hints), 0, sizeof(struct addrinfo));
  self->client = -1;
  self->skt = -1;
  self->hints.ai_family = AF_INET;
  self->hints.ai_socktype = SOCK_STREAM;
  if (host == NULL) {
    self->hints.ai_flags = AI_PASSIVE;
    self->isServer = 1;
  } else {
    self->hints.ai_flags = 0;
    self->isServer = 0;
  }
  int resAddr;
  if ((resAddr = getaddrinfo(host, service, &(self->hints), &(self->ptr))) != 0) {
    printf("Error getaddrinfo: %s \n", gai_strerror(resAddr));
    return 1;
  };
  self->skt = socket(self->ptr->ai_family, self->ptr->ai_socktype, self->ptr->ai_protocol);
  if (self->skt == -1) {
    printf("Error socket %s \n", strerror(errno));
    freeaddrinfo(self->ptr);
    return 1;
  }
  return 0;
}

int socket_listen(socket_t *self, int pool_size) {
  if (!self->isServer) return -1;
  if (bind(self->skt, self->ptr->ai_addr, self->ptr->ai_addrlen) == -1) {
    printf("Error bind: %s\n", strerror(errno));
    close(self->skt);
    freeaddrinfo(self->ptr);
    return 1;
  }
  if (listen(self->skt, pool_size) == -1) {
    printf("Error listen: %s\n", strerror(errno));
    close(self->skt);
    freeaddrinfo(self->ptr);
    return 1;
  }
  return 0;
}

int socket_accept(socket_t *self) {
  if (!self->isServer) return -1;
  self->client = accept(self->skt, NULL, NULL);
  if (self->client == -1) {
    printf("Error accept: %s\n", strerror(errno));
    close(self->skt);
    freeaddrinfo(self->ptr);
    return 1;
  }
  printf("NUEVO CLIENTE\n");
  return 0;
}

int socket_receive(socket_t *self, char *buff, int size) {
  int s = recv(self->skt, buff, size, 0);
  int received = s;
  while (received < size) {
    s = recv(self->client, buff + received, size - received, 0);
    received += s;
    if (s == 0) {
      printf("Cliente cerro la conexion");
      return 0;
    }
    if (s == -1) {
      printf("Error receiving: %s\n", strerror(errno));
      return -1;
    };
  }
  return received;
}

int socket_shutdown_close(int toClose){
  printf("Closing %i\n", toClose);
  shutdown(toClose, SHUT_RDWR);
  close(toClose);
  return 0;
}

int socket_uninit(socket_t *self){
  if(self->client != -1) socket_shutdown_close(self->client);
  if(self->skt != -1) socket_shutdown_close(self->skt);
  return 0;
}
