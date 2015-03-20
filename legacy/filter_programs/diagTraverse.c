#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 15

int main(int argc, char *argv[])
{
  int i, j, k;
  char buf[BOARD_SIZE];
  char board[BOARD_SIZE][BOARD_SIZE];
  FILE *board_input, *board_output;
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
    return EXIT_FAILURE;
  }
  board_input = fopen(argv[1], "r");
  fscanf(board_input, "%s", buf);
  for (i = 0; i < BOARD_SIZE; ++i)
  {
    fscanf(board_input, "%s", buf);
    for (j = 0; j < BOARD_SIZE; ++j)
    {
      board[i][j] = buf[j];
    }
  }
  fclose(board_input);
  board_output = fopen(argv[2], "w");
  for (k = 0; k < 2 * BOARD_SIZE - 1; ++k)
  {
    for (i = k; i >= 0; --i)
    {
      j = k - i;
      if (i >= BOARD_SIZE || j >= BOARD_SIZE)
      {
        continue;
      }
      fputc(board[i][j], board_output);
    }
    fputc('\n', board_output);
  }
  fclose(board_output);
  return EXIT_SUCCESS;
}
