#include <stdlib.h>
#include "wordsearch.h"

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
