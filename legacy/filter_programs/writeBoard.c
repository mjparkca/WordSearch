#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char **board;
  int c, i, j, k, m, n;

  scanf("%d,%d\n", &m, &n);
  printf("%d,%d\n", m, n);

  board = (char **)malloc(m * sizeof(char *));
  for (i = 0; i < m; ++i)
  {
    board[i] = (char *)malloc(n * sizeof(char));
  }
  for (k = 0; k < m * n; ++k)
  {
    scanf("%c,%d,%d\n", &c, &i, &j);
    board[i][j] = c;
  }
  for (i = 0; i < m; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      putchar(board[i][j]);
    }
    putchar('\n');
  }
  for (i = 0; i < m; ++i)
  {
    free(board[i]);
  }
  free(board);
  return EXIT_SUCCESS;
}
