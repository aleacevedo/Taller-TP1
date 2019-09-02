#include "sudoku.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

int sudoku_init(sudoku_t *self) {
  board_init(self->board);
  self->plays= malloc(sizeof(list_t));
  list_init(self->plays);
  return 0;
}

char *sudoku_show(sudoku_t *self, char *boardRepresentation) {
  for (int row = 0; row < 9; row++) {
    if (row % 3 == 0) {
      strcat(boardRepresentation, SECTOR_DIVISOR);
    } else {
      strcat(boardRepresentation, ROW_DIVISOR);
    }
    for (int column = 0; column < 9; column = column + 3) {
      char valor0 = board_get(self->board, row, column);
      char valor1 = board_get(self->board, row, column + 1);
      char valor2 = board_get(self->board, row, column + 2);
      char row[13] = "\0";
      snprintf(row, 13, ROW_REPRESENTATION, valor0, valor1, valor2);
      strcat(boardRepresentation, row);
    }
    strcat(boardRepresentation, "U\n");
  }
  strcat(boardRepresentation, SECTOR_DIVISOR);
  return boardRepresentation;
}

int sudoku_set(sudoku_t *self, char row, char column, char value) {
  int row_int = atoi(&row) - 1;
  int column_int = atoi(&row) -1;
  if(!sudoku_check_value(row) || !sudoku_check_value(column)){
    return 1;
  }
  if(!board_is_ini(self->board, row_int, column_int) && sudoku_check_value(value)){
    board_set(self->board, row_int, column_int, value);
    play_t *play = malloc(sizeof(play_t));
    play->column = column;
    play->row = row;
    list_append(self->plays, play);
    return 0;
  }
  return 1;
}

int sudoku_check_value(char value) {
  int value_int  = atoi(&value);
  return value_int > 0 && value_int < 10;
}

bool validate_column(sudoku_t *self, int column, char value){
  int apariciones = 0;
  for(int row = 0; row < BOARD_SIZE; row++){
    if(board_get(self->board, row, column) == value){
      apariciones++;
      if(apariciones == 2) return false;
    }
  }
  return true;
}

bool validate_row(sudoku_t *self, int row, char value){
  int apariciones = 0;
  for(int column = 0; column < BOARD_SIZE; column++){
    if(board_get(self->board, row, column) == value){
      apariciones++;
      if(apariciones == 2) return false;
    }
  }
  return true;
}

bool validate_sector(sudoku_t *self, int row_ini, int column_ini, char value){
  int row_offset = row_ini / 3;
  int column_offset = column_ini /3;
  int apariciones = 0;
  for(int row = 0; row < 3; row++){
    for(int column = 0; column < 3; column++) {
      if(board_get(self->board, row + row_offset, column + column_offset) == value){
        apariciones++;
        if(apariciones == 2) return false;
      }
    }
  }
  return true;
}

bool sudoku_validate(sudoku_t *self) {
  list_iter_reset(self->plays);
  play_t *play = list_iter_next(self->plays);
  for (; play != NULL; play = list_iter_next(self->plays)) {
    printf("VALIDATE 1");
    char value = board_get(self->board, play->row, play->column);
    bool column = validate_column(self, play->column, value);
    bool row = validate_column(self, play->row, value);
    bool sector = validate_column(self, play->row, value);
    if(!row || !column || !sector){
      return false;
    }
  }
  return true;
}



int sudoku_reset(sudoku_t *self) {
  board_reset(self->board);
  return 0;
}

void sudoku_uninit(sudoku_t *self) {
  play_t *play = list_iter_next(self->plays);
  for(;play != NULL; play = list_iter_next(self->plays)){
    free(play);
  }
  free(self->plays);
}
