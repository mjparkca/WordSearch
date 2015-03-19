#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 15

typedef struct Board {
  int width;
  int height;
  char **board;
} Board;

Board *readBoard(FILE *board_input);
void deleteBoard(Board ** bpp);

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

int main(int argc, char *argv[])
{
  int i, j;
  FILE *board_input, *word_input, *board_output;
  Board *this_board;
  if (argc < 4)
  {
    fprintf(stderr, "Usage: %s board_input word_input board_output\n", argv[0]);
    return EXIT_FAILURE;
  }
  board_input = fopen(argv[1], "r");
  word_input = fopen(argv[2], "r");
  this_board = readBoard(board_input);
  fclose(board_input);
  fclose(word_input);
  board_output = fopen(argv[3], "w");
  for (i = 0; i < this_board->height; ++i)
  {
    for (j = 0; j < this_board->width; ++j)
    {
      fputc(this_board->board[i][j], board_output);
    }
    fputc('\n', board_output);
  }
  fclose(board_output);
  deleteBoard(&this_board);
  return EXIT_SUCCESS;
}
