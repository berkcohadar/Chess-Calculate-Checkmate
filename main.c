#include "moves.h"
#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

extern PlayerState player[2];

int main(int argc, char const *argv[]) {
  printf("\nOUR CODES DOES NOT INCKUDE CASTLE MOVEMENT AND EP-SQUARE IN THE LEGAL MOVEMENTS.\n\nLOADING THE RESULTS PLEASE WAIT...\n\n");
  /* Your testing code here. */
  char board[512]; int c;

  FILE *fr = fopen(argv[1], "r");                                   /* open file to read */
  FILE *fa = fopen(argv[2], "a");                                   /* open file to append */
  char const mode = *(argv[3]);

  if(fr == NULL) {
    printf("Error loading file.");                                  /* give error message and return 0, if file cannot be read */
    fclose(fr);
    fclose(fa);
    return 0;
  }

  switch (mode)
  {
  case '1':
    printf("\n\nFIRST CASE COMES\n\n");
    while(fgets(board, sizeof(board), fr) != NULL) {                  /* read the file line by line, and print the result to another file line by line */
      char real_board[512] = {0}; int i; int j=0;                     /* board is the whole line, but we need the first part to create the board */ 
      if (strlen(board) < 16) fgets(board, sizeof(board), fr);
      for (i = 0; board[i] != ' '; i++) real_board[i] = board[i];     /* the board resides until ' ', the playerColor comes after the space -> ' ' */

      i+=1;                                                           /* goes one forward because of 'space' */
      char currentp = board[i];                                       /* sets the currentp as 'w' or 'b' */
      if (currentp == 'w') c = 1;                                     /* sets 1 if white */
      else if (currentp == 'b') c = 0;                                /* sets 0 if black */

      i+=2;                                                           /* goes two times forward because of 'space' and 'playerColor' */
      while(board[i] != ' ') {                                        /* creates castling string ex. "Kq" */
        castling[j] = board[i];                                       /* castling is global */
        i++; j++;
      }

      parse_board(real_board);                                        /* create the board */


      Move *m;
      unsigned int pcount;
      legal_moves(&m, c, &pcount);                                    /* let's find what are the possible moves for FIRST PLAYER */

      Move *m1=NULL;
      unsigned int pcount1 = 0;
      while(m!=NULL){                                                 /* m -> first player's possible moves */
        make_move(m,c);                                               /* make the FIRST PLAYER's move */ /* tries every possible moves again and again, in the FIRST BOARD POSITION */

        pcount1=0;                                                    /* pcount1 must be re-initialized to 0 everytime; in order to find SECOND PLAYER's possible moves correctly */
        legal_moves(&m1, 1-c, &pcount1);                              /* find SECOND PLAYER's possible moves, after the move 'm' has been played by FIRST PLAYER */
        if (pcount1 == 0) {                                           /* pcount1 is 0 if there is no possible moves for SECOND PLAYER */
         char result[8] = {FILE_OF(m->from),RANK_OF(m->from),'-',
                                    FILE_OF(m->to), RANK_OF(m->to)};  /* the string of movement */
         fprintf(fa,"%s\n",result);                                   /* appends the movement to the solutions.txt file */
         break;                                                       /* break if there is a possible checkmate movement */
       }
       else {
         free(m1);                                                    /* frees the memory */
         parse_board(real_board);                                     /* returns back to board's first position; in other words, reverse the FIRST PLAYER's current move */
         m=m->next_move;                                              /* goes to the next element in the FIRST PLAYER'S LEGAL MOVE LIST */
       }
      }
      if (pcount1 != 0) fprintf(fa,"Not found\n");                   /* writes "-----" if there is no possible checkmate movements */
      /*free(m); free(m1);*/
    }
    break;
  case '2':
    printf("\n\nSECOND CASE COMES\n\n");
    while(fgets(board, sizeof(board), fr) != NULL){
      char real_board[512] = {0}; int i; int j = 0;                   /* board is the whole line, but we need the first part to create the board */ 
      if (strlen(board) < 16) fgets(board, sizeof(board), fr);
      for (i = 0; board[i] != ' '; i++) real_board[i] = board[i];     /* the board resides until ' ', the playerColor comes after the space -> ' ' */

      i+=1;
      char currentp = board[i];                                       /* sets the currentp as 'w' or 'b' */
      if (currentp == 'w') c = 1;                                     /* sets 1 if white */
      else if (currentp == 'b') c = 0;                                /* sets 0 if black */

      i+=2;                                                           /* goes two times forward because of 'space' and 'playerColor' */
      while(board[i] != ' ') {                                        /* creates castling string ex. "Kq" */
        castling[j] = board[i];                                       /* castling is global */
        i++; j++;
      }

      parse_board(real_board);

      Move *m;
      unsigned int pcount;
      legal_moves(&m, c, &pcount);    
      Move *m1=NULL;
      unsigned int pcount1 = 0;      
      Move *m2=NULL;
      unsigned int pcount2 = 0;      
      Move *m3=NULL;
      unsigned int pcount3 = 0;
      while(m!=NULL){
        make_move(m,c);
        legal_moves(&m1, 1-c, &pcount1);
        while(m1!=NULL){
            char tmp_brd1[512]={0};
            char* temp_board1 = board_to_string();
            strcpy(tmp_brd1, temp_board1);
            
            make_move(m1,1-c);
            legal_moves(&m2,1,&pcount2);
            while(m2!=NULL){
                char tmp_brd2[512]={0};
                char* temp_board2 = board_to_string();
                strcpy(tmp_brd2, temp_board2);
                make_move(m2,c);
                legal_moves(&m3,1-c,&pcount3);
                if(pcount3 == 0) {
                  printf("FIRST PLAYERS MOVE; "); print_move(m);
                  printf("SECOND PLAYERS MOVE; "); print_move(m1);
                  printf("FIRST PLAYERS MOVE; "); print_move(m2);
                  printf("\n\n--------------------\n\n");
                  char result[8] = {FILE_OF(m->from),RANK_OF(m->from),'-',
                                  FILE_OF(m->to), RANK_OF(m->to)};
                  fprintf(fa,"%s\n",result);
                  break;
                }
                else {
                  parse_board(tmp_brd2);
                  m2=m2->next_move;
                }
              }
              if(pcount3 == 0) break;
              parse_board(tmp_brd1);
              m1=m1->next_move;
          }
          if(pcount3 == 0) break;
          parse_board(real_board);
          m=m->next_move;
      }
      if(pcount3 != 0) fprintf(fa,"Not found\n");
    }
    break;

  default:
    printf("Error! mode is not correct.\n\nSample Inputs -> ./chess in.txt out.txt 1 & ./chess in.txt out.txt 2\n\n");
    break;
  }

  fclose(fa);
  fclose(fr);
  return 0;
}
