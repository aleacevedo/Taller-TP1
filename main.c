#include <stdio.h>
#include <string.h>
#include "client.h"
#include "server.h"

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    printf("Modo no soportado, el primer parámetro debe ser server o client\n​");
    return -1;
  }
  if (strcmp(argv[1], "server") == 0) {
    if (argc == 3) {
      printf("Server\n");
      return server_init(argv[2]);
    }
    printf("Uso: ./tp client <host> <puerto>\n");
    return 1;
  }
  if (strcmp(argv[1], "client") == 0) {
    if (argc == 4) {
      printf("Cliente\n");
      client_init(argv[2], argv[3]);
      return 0;
    }
    printf("Uso: ./tp client <host> <puerto>\n");
    return 1;
  }
  printf("Modo no soportado, el primer parámetro debe ser server o client\n​");
  return -1;
}
