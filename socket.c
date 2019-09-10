#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include "socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

static int _getaddrinfo(socket_t *self, const char *host, const char *service) {
  int resAddr;
  if ((resAddr = getaddrinfo(host, service,
                    &(self->hints),
                    &(self->ptr))) != 0) {
    fprintf(stderr, "Error getaddrinfo: %s \n", gai_strerror(resAddr));
    return 1;
  }
  return 0;
}

static int _create_server(socket_t *self) {
  self->skt = socket(self->ptr->ai_family,
                self->ptr->ai_socktype,
                self->ptr->ai_protocol);
  if (self->skt == -1) {
    fprintf(stderr, "Error socket %s \n", strerror(errno));
    freeaddrinfo(self->ptr);
    return 1;
  }
  return 0;
}

static int _create_client(socket_t *self) {
  struct addrinfo *directions = self->ptr;
  for (; directions != NULL; directions = directions->ai_next) {
    self->skt = socket(self->ptr->ai_family,
                  self->ptr->ai_socktype,
                  self->ptr->ai_protocol);
    if (self->skt == -1) {
      printf("Error socket %s \n", strerror(errno));
      freeaddrinfo(self->ptr);
      continue;
    }
    return 0;
  }
  return 1;
}

int socket_init(socket_t *self, const char *host, const char *service) {
  memset(&(self->hints), 0, sizeof(struct addrinfo));
  self->connection = -1;
  self->skt = -1;
  self->ptr = NULL;
  self->hints.ai_family = AF_INET;
  self->hints.ai_socktype = SOCK_STREAM;
  if (host == NULL) {
    self->hints.ai_flags = AI_PASSIVE;
    self->isServer = 1;
    if (_getaddrinfo(self, host, service)) return 1;
    if (_create_server(self)) {
      freeaddrinfo(self->ptr);
      return 1;
    }
  } else {
    self->hints.ai_flags = 0;
    self->isServer = 0;
    if (_getaddrinfo(self, host, service)) return 1;
    if (_create_client(self)) {
      freeaddrinfo(self->ptr);
      return 1;
    }
  }
  return 0;
}

int socket_is_server(socket_t *self) {
  return self->isServer;
}

int socket_listen(socket_t *self, int pool_size) {
  if (!self->isServer) return -1;
  if (bind(self->skt, self->ptr->ai_addr, self->ptr->ai_addrlen) == -1) {
    fprintf(stderr, "Error bind: %s\n", strerror(errno));
    close(self->skt);
    freeaddrinfo(self->ptr);
    return 1;
  }
  if (listen(self->skt, pool_size) == -1) {
    fprintf(stderr, "Error listen: %s\n", strerror(errno));
    close(self->skt);
    freeaddrinfo(self->ptr);
    return 1;
  }
  return 0;
}

int socket_accept(socket_t *self) {
  if (!self->isServer) return -1;
  self->connection = accept(self->skt, NULL, NULL);
  if (self->connection == -1) {
    fprintf(stderr, "Error accept: %s\n", strerror(errno));
    close(self->skt);
    freeaddrinfo(self->ptr);
    return 1;
  }
  return 0;
}

int socket_connect(socket_t *self) {
  if (self->isServer) return 1;
  if (connect(self->skt, self->ptr->ai_addr, self->ptr->ai_addrlen) == -1) {
    fprintf(stderr, "Error connecting: %s \n", strerror(errno));
    close(self->skt);
    freeaddrinfo(self->ptr);
    return 1;
  }
  self->connection = self->skt;
  return 0;
}

int socket_receive(socket_t *self, char *buff, int size) {
  int s = recv(self->connection, buff, size, 0);
  int received = s;
  while (received < size) {
    s = recv(self->connection, buff + received, size - received, 0);
    received += s;
    if (s == 0) {
      fprintf(stdout, "Cliente cerro la conexion\n");
      return 0;
    }
    if (s == -1) {
      fprintf(stderr, "Error receiving: %s\n", strerror(errno));
      return -1;
    }
  }
  return received;
}

int socket_send(socket_t *self, char *buff, int size) {
  int s = send(self->connection, buff, size, 0);
  int sent = s;
  while (sent < size) {
    s = send(self->connection, buff + sent, size - sent, 0);
    sent += s;
    if (s == 0) {
      printf("Cliente cerro la conexion");
      return 0;
    }
    if (s == -1) {
      printf("Error sending: %s\n", strerror(errno));
      return -1;
    }
  }
  return sent;
}

static int _shutdown_close(int toClose) {
  shutdown(toClose, SHUT_RDWR);
  close(toClose);
  return 0;
}

int socket_uninit(socket_t *self) {
  if (self->connection != -1 && self->isServer)
    _shutdown_close(self->connection);
  if (self->skt != -1) _shutdown_close(self->skt);
  if (self->ptr != NULL) freeaddrinfo(self->ptr);
  return 0;
}
