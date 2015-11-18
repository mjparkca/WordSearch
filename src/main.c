#include <stdlib.h>
#include "wordsearch.h"

int main(int argc, char *argv[]) {
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
    return -1;
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

  return 0;
}
