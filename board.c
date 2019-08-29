#include "board.h"

#include <stdio.h>

int board_init(board_t *self)
{
  FILE *fileBoard = fopen(PATH_BOARD, "r");
  int row = 0;
  char line[LEN_STRING + 1];
  if (fileBoard == NULL)
    return -2;
  while (fgets(line, LEN_STRING + 1, fileBoard) != NULL)
  {
    printf("LINEA: %s\n", line);
    if (row > 8)
    {
      fclose(fileBoard);
      return -1; // El archivo tiene mas de 9 filas
    }
    for (int column = 0; column < 9; column++)
    {
      if (line[column] == '0')
      {
        self[row][column]->value = ' ';
        continue;
      }
      self[row][column]->value = line[column];
      self[row][column]->ini = 1;
    }
    row++;
    if (fgets(line, LEN_STRING + 1, fileBoard) == NULL)
    {
      break;
    }
  }
  return fclose(fileBoard);
}

int board_set(board_t *self, int row, int column, int value)
{
  return 0;
}

char board_get(board_t *self, int row, int column)
{
  return self[row][column]->value;
}

int board_reset(board_t *self)
{
  return 0;
}
