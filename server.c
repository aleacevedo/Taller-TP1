#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

void server_init(const char *service) {
  char boardRepresentation[BOARD_REPRESENTATION_LEN] = "\0";
  sudoku_t sudoku;
  sudoku_init(&sudoku);
  printf("Levanto un server en el puerto: %s \n", service);
  sudoku_show(&sudoku, boardRepresentation);
  printf("%s \n", boardRepresentation);
  bool valid = sudoku_validate(&sudoku);
  printf("El juego es %s \n", valid ? "valido" : "no valido");
  sudoku_set(&sudoku, '1','1','5');
  boardRepresentation[0] = '\0';
  sudoku_show(&sudoku, boardRepresentation);
  printf("%s \n", boardRepresentation);
  bool valid1 = sudoku_validate(&sudoku);
  printf("El juego es %s \n", valid1? "valido" : "no valido");
  sudoku_set(&sudoku, '1','1','9');
  boardRepresentation[0] = '\0';
  sudoku_show(&sudoku, boardRepresentation);
  printf("%s \n", boardRepresentation);
  valid = sudoku_validate(&sudoku);
  printf("El juego es %s \n", valid ? "valido" : "no valido");
  sudoku_reset(&sudoku);
  boardRepresentation[0] = '\0';
  sudoku_show(&sudoku, boardRepresentation);
  printf("%s \n", boardRepresentation);
  sudoku_uninit(&sudoku);
}
