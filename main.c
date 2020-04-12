#include "moves.h"
#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
extern PlayerState player[2];

int main(int argc, char const *argv[]) {
  /* Your testing code here. */

  parse_board("rnbqkbnr/ppppp2p/5p11/6p1/4P3/2N5/PPPP1PPP/R1BQKBNR");
  display_board();

  
  Move *m;
  unsigned int pcount;
  legal_moves(&m, 1, &pcount);

  Move *m1=NULL;
  unsigned int pcount1 = 0;

  while(m!=NULL){
    make_move(m,1);
    pcount1=0;
    legal_moves(&m1, 0, &pcount1);
    if (pcount1 == 0) {
      printf("------------------------");
      display_board();
      print_move(m);
      printf("\n !!! CHECKMATE !!! \n");
      break;
    }
    else {
      free(m1);
      parse_board("rnbqkbnr/ppppp2p/5p11/6p1/4P3/2N5/PPPP1PPP/R1BQKBNR");
      m=m->next_move;
    }
  }
  return 0;
}