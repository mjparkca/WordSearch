/* Filename: main.c
 * Author: mjp014
 * Date: March 19, 2015
 * Description: C program to solve word search puzzle
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 2 by 2 char array with dimensions */
typedef struct Board {
  int width;
  int height;
  char **board;
} Board;

/* linked list */
typedef struct Node {
  char letter;
  int row;
  int col;
  struct Node *next;
} Node;

/* list of list */
typedef struct List {
  struct Node *item;
  struct List *next;
} List;

Board *readBoard(FILE *board_input);
void deleteBoard(Board ** bpp);
List *hor_obv(Board *this_board);
List *hor_rev(Board *this_board);
List *ver_obv(Board *this_board);
List *ver_rev(Board *this_board);
List *maj_obv(Board *this_board);
List *maj_rev(Board *this_board);
List *min_obv(Board *this_board);
List *min_rev(Board *this_board);
void searchWord(List *str_set, FILE *word_input, FILE *board_output);
Node *newNode(char letter, int row, int col);
void deleteNode(Node **npp);
void insertNode(Node *this_node, Node *item);
void insertList(List *this_list, char letter, int row, int col);
void addList(List *this_list, List *next_list);
void deleteList(List **lpp);

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

/* list initializers */

List *hor_obv(Board *this_board)
{
  int i, j;
  List *root, *current;
  root = (List *)malloc(sizeof(List));
  root->item = NULL;
  root->next = NULL;
  for (j = 0; j < this_board->width; ++j)
  {
    insertList(root, this_board->board[0][j], 0, j);
  }
  for (i = 1; i < this_board->height; ++i)
  {
    current = (List *)malloc(sizeof(List));
    current->item = NULL;
    current->next = NULL;
    for (j = 0; j < this_board->width; ++j)
    {
      insertList(current, this_board->board[i][j], i, j);
    }
    addList(root, current);
  }
  return root;
}

List *hor_rev(Board *this_board)
{
  int i, j;
  List *root, *current;
  root = (List *)malloc(sizeof(List));
  root->item = NULL;
  root->next = NULL;
  for (j = this_board->width - 1; j >= 0; --j)
  {
    insertList(root, this_board->board[0][j], 0, j);
  }
  for (i = 1; i < this_board->height; ++i)
  {
    current = (List *)malloc(sizeof(List));
    current->item = NULL;
    current->next = NULL;
    for (j = this_board->width - 1; j >= 0; --j)
    {
      insertList(current, this_board->board[i][j], i, j);
    }
    addList(root, current);
  }
  return root;
}

List *ver_obv(Board *this_board)
{
  int i, j;
  List *root, *current;
  root = (List *)malloc(sizeof(List));
  root->item = NULL;
  root->next = NULL;
  for (i = 0; i < this_board->height; ++i)
  {
    insertList(root, this_board->board[i][0], i, 0);
  }
  for (j = 1; j < this_board->width; ++j)
  {
    current = (List *)malloc(sizeof(List));
    current->item = NULL;
    current->next = NULL;
    for (i = 0; i < this_board->height; ++i)
    {
      insertList(current, this_board->board[i][j], i, j);
    }
    addList(root, current);
  }
  return root;
}

List *ver_rev(Board *this_board)
{
  int i, j;
  List *root, *current;
  root = (List *)malloc(sizeof(List));
  root->item = NULL;
  root->next = NULL;
  for (i = this_board->height - 1; i >= 0; --i)
  {
    insertList(root, this_board->board[i][0], i, 0);
  }
  for (j = 1; j < this_board->width; ++j)
  {
    current = (List *)malloc(sizeof(List));
    current->item = NULL;
    current->next = NULL;
    for (i = this_board->height - 1; i >= 0; --i)
    {
      insertList(current, this_board->board[i][j], i, j);
    }
    addList(root, current);
  }
  return root;
}

List *maj_obv(Board *this_board)
{
  int i, j, k, m, n;
  List *root, *current;

  root = (List *)malloc(sizeof(List));
  root->item = NULL;
  root->next = NULL;

  m = this_board->height;
  n = this_board->width;

  insertList(root, this_board->board[0][n - 1], 0, n - 1);
  for (k = 1; k < m + n - 1; ++k)
  {
    current = (List *)malloc(sizeof(List));
    current->item = NULL;
    current->next = NULL;

    for (i = 0; i <= k; ++i)
    {
      j = n - 1 - k + i;
      if (i >= m || j < 0)
      {
        continue;
      }
      insertList(current, this_board->board[i][j], i, j);
    }
    addList(root, current);
  }
  return root;
}

List *maj_rev(Board *this_board)
{
  int i, j, k, m, n;
  List *root, *current;

  root = (List *)malloc(sizeof(List));
  root->item = NULL;
  root->next = NULL;

  m = this_board->height;
  n = this_board->width;

  insertList(root, this_board->board[0][n - 1], 0, n - 1);
  for (k = 1; k < m + n - 1; ++k)
  {
    current = (List *)malloc(sizeof(List));
    current->item = NULL;
    current->next = NULL;

    for (i = k; i >= 0; --i)
    {
      j = n - 1 - k + i;
      if (i >= m || j < 0)
      {
        continue;
      }
      insertList(current, this_board->board[i][j], i, j);
    }
    addList(root, current);
  }
  return root;
}

List *min_obv(Board *this_board)
{
  int i, j, k, m, n;
  List *root, *current;

  root = (List *)malloc(sizeof(List));
  root->item = NULL;
  root->next = NULL;

  m = this_board->height;
  n = this_board->width;

  insertList(root, this_board->board[0][0], 0, 0);
  for (k = 1; k < m + n - 1; ++k)
  {
    current = (List *)malloc(sizeof(List));
    current->item = NULL;
    current->next = NULL;

    for (i = k; i >= 0; --i)
    {
      j = k - i;
      if (i >= m || j >= n)
      {
        continue;
      }
      insertList(current, this_board->board[i][j], i, j);
    }
    addList(root, current);
  }
  return root;
}

List *min_rev(Board *this_board)
{
  int i, j, k, m, n;
  List *root, *current;

  root = (List *)malloc(sizeof(List));
  root->item = NULL;
  root->next = NULL;

  m = this_board->height;
  n = this_board->width;

  insertList(root, this_board->board[0][0], 0, 0);
  for (k = 1; k < m + n - 1; ++k)
  {
    current = (List *)malloc(sizeof(List));
    current->item = NULL;
    current->next = NULL;

    for (i = 0; i <= k; ++i)
    {
      j = k - i;
      if (i >= m || j >= n)
      {
        continue;
      }
      insertList(current, this_board->board[i][j], i, j);
    }
    addList(root, current);
  }
  return root;
}

void searchWord(List *this_list, FILE *word_input, FILE *board_output)
{
  int found;
  int i, j, k, len, num_words;
  Node *starting, *working;
  List *current;
  char buf[BUFSIZ] = {0};

  if (this_list == NULL || word_input == NULL || board_output == NULL)
  {
    fprintf(stderr, "Null argument in searchWord().\n");
    return;
  }

  fscanf(word_input, "%d", &num_words);
  for (k = 0; k < num_words; ++k)
  {
    current = this_list;
    for (i = 0; i < BUFSIZ; ++i)
    {
      buf[i] = 0;
    }
    fscanf(word_input, "%s", buf);
    len = strlen(buf);
    while (current != NULL)
    {
      starting = current->item;
      while (starting != NULL)
      {
        found = 1;
        working = starting;
        for (i = 0; i < len; ++i)
        {
          if (working == NULL)
          {
            break;
          }
          found = found && (working->letter == buf[i]);
          working = working->next;
        }
        if (found && i == len)
        {
          working = starting;
          fprintf(board_output, "%s:", buf);
          for (j = 0; j < len; ++j)
          {
            fprintf(board_output, " (%d,%d)", working->row, working->col);
            working = working->next;
          }
          fputc('\n', board_output);
        }
        starting = starting->next;
      }
      current = current->next;
    }
  }
  rewind(word_input);
}

Node *newNode(char letter, int row, int col)
{
  Node *this_node;
  this_node = (Node *)malloc(sizeof(Node));
  this_node->letter = letter;
  this_node->row = row;
  this_node->col = col;
  this_node->next = NULL;
  return this_node;
}

void deleteNode(Node **npp)
{
  Node *this_node;
  if (npp == NULL || *npp == NULL)
  {
    return;
  }
  this_node = *npp;
  deleteNode(&this_node->next);
  free(this_node);
  *npp = NULL;
}

void insertNode(Node *this_node, Node *item)
{
  if (this_node == NULL || item == NULL)
  {
    fprintf(stderr, "Null argument in insertNode().\n");
    exit(1);
  }
  if (this_node->next == NULL)
  {
    this_node->next = item;
  }
  else
  {
    insertNode(this_node->next, item);
  }
}

void insertList(List *this_list, char letter, int row, int col)
{
  Node *data;
  data = newNode(letter, row, col);
  if (this_list->item == NULL)
  {
    this_list->item = data;
  }
  else
  {
    insertNode(this_list->item, data);
  }
}

void addList(List *this_list, List *next_list)
{
  List *current;
  if (this_list->next == NULL)
  {
    this_list->next = next_list;
  }
  else
  {
    current = this_list->next;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = next_list;
  }
}

void deleteList(List **lpp)
{
  List *this_list;
  if (lpp == NULL || *lpp == NULL)
  {
    return;
  }
  this_list = *lpp;
  deleteNode(&this_list->item);
  deleteList(&this_list->next);
  free(this_list);
  *lpp = NULL;
}

int main(int argc, char *argv[])
{
  int i, j;
  FILE *board_input, *word_input, *board_output;
  Board *board;
  List *hor_obv_list, *hor_rev_list;
  List *ver_obv_list, *ver_rev_list;
  List *maj_obv_list, *maj_rev_list;
  List *min_obv_list, *min_rev_list;

  if (argc < 4)
  {
    fprintf(stderr, "Usage: %s board_input word_input board_output\n", argv[0]);
    return EXIT_FAILURE;
  }
  board_input = fopen(argv[1], "r");
  word_input = fopen(argv[2], "r");
  board = readBoard(board_input);
  board_output = fopen(argv[3], "w");

  hor_obv_list = hor_obv(board);
  hor_rev_list = hor_rev(board);
  ver_obv_list = ver_obv(board);
  ver_rev_list = ver_rev(board);
  maj_obv_list = maj_obv(board);
  maj_rev_list = maj_rev(board);
  min_obv_list = min_obv(board);
  min_rev_list = min_rev(board);

  searchWord(hor_obv_list, word_input, board_output);
  searchWord(hor_rev_list, word_input, board_output);
  searchWord(ver_obv_list, word_input, board_output);
  searchWord(ver_rev_list, word_input, board_output);
  searchWord(maj_obv_list, word_input, board_output);
  searchWord(maj_rev_list, word_input, board_output);
  searchWord(min_obv_list, word_input, board_output);
  searchWord(min_rev_list, word_input, board_output);

  fclose(board_input);
  fclose(word_input);
  fclose(board_output);

  deleteBoard(&board);
  deleteList(&hor_obv_list);
  deleteList(&hor_rev_list);
  deleteList(&ver_obv_list);
  deleteList(&ver_rev_list);
  deleteList(&maj_obv_list);
  deleteList(&maj_rev_list);
  deleteList(&min_obv_list);
  deleteList(&min_rev_list);

  return EXIT_SUCCESS;
}
