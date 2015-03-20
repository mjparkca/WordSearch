#include <stdlib.h>
#include "wordsearch.h"

Board *readBoard(FILE *board_input)
{
  int i, j, m, n;
  Board *retval;
  char *buf;
  retval = (Board *)malloc(sizeof(Board));
  fscanf(board_input, "%d,%d", &m, &n);
  retval->width = n;
  retval->height = m;
  retval->board = (char **)malloc(m * sizeof(char *));
  for (i = 0; i < m; ++i)
  {
    retval->board[i] = (char *)malloc(n * sizeof(char));
  }
  buf = (char *)malloc(n * sizeof(char) + 1);
  for (i = 0; i < m; ++i)
  {
    fscanf(board_input, "%s", buf);
    for (j = 0; j < n; ++j)
    {
      retval->board[i][j] = tolower(buf[j]);
    }
  }
  free(buf);
  return retval;
}

void deleteBoard(Board ** bpp)
{
  int i, j;
  Board *this_board = *bpp;
  for (i = 0; i < this_board->height; ++i)
  {
    free(this_board->board[i]);
  }
  free(this_board->board);
  free(*bpp);
  *bpp = NULL;
}
