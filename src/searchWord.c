#include <string.h>
#include "wordsearch.h"

void searchWord(List *this_list, FILE *word_input, FILE *board_output) {
  int found;
  int i, j, k, len, num_words;
  Node *starting, *working;
  List *current;
  char buf[BUFSIZ] = {0};

  if (this_list == NULL || word_input == NULL || board_output == NULL) {
    fprintf(stderr, "Null argument in searchWord().\n");
    return;
  }

  fscanf(word_input, "%d", &num_words);
  for (k = 0; k < num_words; ++k) {
    current = this_list;
    for (i = 0; i < BUFSIZ; ++i) {
      buf[i] = 0;
    }
    fscanf(word_input, "%s", buf);
    len = strlen(buf);
    while (current != NULL) {
      starting = current->item;
      while (starting != NULL) {
        found = 1;
        working = starting;
        for (i = 0; i < len; ++i) {
          if (working == NULL) {
            break;
          }
          found = found && (working->letter == buf[i]);
          working = working->next;
        }
        if (found && i == len) {
          working = starting;
          fprintf(board_output, "%s:", buf);
          for (j = 0; j < len; ++j) {
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
