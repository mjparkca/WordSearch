#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#include <stdio.h>

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

struct Board *readBoard(FILE *board_input);
void deleteBoard(struct Board ** bpp);
struct List *hor_obv(struct Board *this_board);
struct List *hor_rev(struct Board *this_board);
struct List *ver_obv(struct Board *this_board);
struct List *ver_rev(struct Board *this_board);
struct List *maj_obv(struct Board *this_board);
struct List *maj_rev(struct Board *this_board);
struct List *min_obv(struct Board *this_board);
struct List *min_rev(struct Board *this_board);
void searchWord(struct List *str_set, FILE *word_input, FILE *board_output);
struct Node *newNode(char letter, int row, int col);
void deleteNode(struct Node **npp);
void insertNode(struct Node *this_node, struct Node *item);
void insertList(struct List *this_list, char letter, int row, int col);
void addList(struct List *this_list, struct List *next_list);
void deleteList(struct List **lpp);

#endif /* WORDSEARCH_H */
