#include <stdlib.h>
#include "wordsearch.h"

Node *newNode(char letter, int row, int col) {
  Node *this_node;
  this_node = (Node *)malloc(sizeof(Node));
  this_node->letter = letter;
  this_node->row = row;
  this_node->col = col;
  this_node->next = NULL;
  return this_node;
}

void insertNode(Node *this_node, Node *item) {
  if (this_node == NULL || item == NULL) {
    fprintf(stderr, "Null argument in insertNode().\n");
    return;
  }
  if (this_node->next == NULL) {
    this_node->next = item;
  }
  else {
    insertNode(this_node->next, item);
  }
}

void deleteNode(Node **npp) {
  Node *this_node;
  if (npp == NULL || *npp == NULL) {
    return;
  }
  this_node = *npp;
  deleteNode(&this_node->next);
  free(this_node);
  *npp = NULL;
}
