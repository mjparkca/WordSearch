#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char **board;
  int c, i, j, k, m, n;

  scanf("%d,%d\n", &m, &n);
  printf("%d,%d\n", n, m);

  board = (char **)malloc(n * sizeof(char *));
  for (i = 0; i < n; ++i)
  {
    board[i] = (char *)malloc(m * sizeof(char));
  }
  for (k = 0; k < m * n; ++k)
  {
    scanf("%c,%d,%d\n", &c, &j, &i);
    board[i][j] = c;
  }
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < m; ++j)
    {
      printf("%c,%d,%d\n", board[i][j], i, j);
    }
  }
  for (i = 0; i < n; ++i)
  {
    free(board[i]);
  }
  free(board);
  return EXIT_SUCCESS;
}
