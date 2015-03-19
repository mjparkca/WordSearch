#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int m, n, c, i, j;
  fscanf(stdin, "%d,%d", &m, &n);
  fprintf(stdout, "%d,%d\n", m, n);
  for (i = 0; i < m; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      c = fgetc(stdin);
      if (c == '\n')
      {
        c = fgetc(stdin);
      }
      if (c == EOF)
      {
        fprintf(stderr, "Unexpected EOF in readBoard\n");
        return EXIT_FAILURE;
      }
      fprintf(stdout, "%c,%d,%d\n", c, i, j);
    }
  }
  return EXIT_SUCCESS;
}
