#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "moves.h"

extern PlayerState player[2]; 

void display_board() {
    unsigned int i = 0 , j = 0 ;
	char currentPiece;
	printf("\n  −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n") ;
	for (i=0; i<8 ;i++){ /* Rank */
		printf("%d | " , 8-i);
		for(j=0;j<8;j++) { /* File */
			if(get_piece_at (i*8+j, WHITE) == KING) currentPiece = 'K';
			else if(get_piece_at (i*8+j, WHITE) == QUEEN) currentPiece = 'Q';
			else if(get_piece_at (i*8+j, WHITE) == BISHOP) currentPiece = 'B';
			else if(get_piece_at (i*8+j, WHITE) == NIGHT) currentPiece = 'N';
			else if(get_piece_at (i*8+j, WHITE) == ROOK) currentPiece = 'R';
			else if(get_piece_at (i*8+j, WHITE) == PAWN) currentPiece = 'P';
			else if(get_piece_at (i*8+j, BLACK) == KING) currentPiece = 'k';
			else if(get_piece_at (i*8+j, BLACK) == QUEEN) currentPiece = 'q';
			else if(get_piece_at (i*8+j, BLACK) == BISHOP) currentPiece = 'b';
			else if(get_piece_at (i*8+j, BLACK) == NIGHT) currentPiece = 'n';
			else if(get_piece_at (i*8+j, BLACK) == ROOK) currentPiece = 'r';
			else if(get_piece_at (i*8+j, BLACK) == PAWN) currentPiece = 'p';
			else currentPiece = ' ';
			printf("%c | ", currentPiece);
		}
		printf("\n  −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
	}
	printf("    a   b   c   d   e   f   g   h\n" ) ;
	printf("\n");
}

Bool parse_board(char *board) {
    /* Your implementation */
	int i;
	int c=0;
	while(c<64){
		RESET_BIT(player[BLACK].q,c);RESET_BIT(player[BLACK].k,c);RESET_BIT(player[BLACK].b,c);RESET_BIT(player[BLACK].r,c);RESET_BIT(player[BLACK].n,c);RESET_BIT(player[BLACK].p,c);
		RESET_BIT(player[WHITE].q,c);RESET_BIT(player[WHITE].k,c);RESET_BIT(player[WHITE].b,c);RESET_BIT(player[WHITE].r,c);RESET_BIT(player[WHITE].n,c);RESET_BIT(player[WHITE].p,c);
		c++;
	}
	c=0;
	for( i = 0; board[i] != '\0'; i++ ) 
	{
		if (board[i] >= '1' && board[i] <= '8') c+=board[i]-'1';
		if (board[i] == 'q') SET_BIT(player[BLACK].q,c);
		if (board[i] == 'k') SET_BIT(player[BLACK].k,c);
		if (board[i] == 'b') SET_BIT(player[BLACK].b,c);
		if (board[i] == 'n') SET_BIT(player[BLACK].n,c);
		if (board[i] == 'p') SET_BIT(player[BLACK].p,c);
		if (board[i] == 'r') SET_BIT(player[BLACK].r,c);
		if (board[i] == 'Q') SET_BIT(player[WHITE].q,c);
		if (board[i] == 'K') SET_BIT(player[WHITE].k,c);
		if (board[i] == 'B') SET_BIT(player[WHITE].b,c);
		if (board[i] == 'N') SET_BIT(player[WHITE].n,c);
		if (board[i] == 'R') SET_BIT(player[WHITE].r,c);
		if (board[i] == 'P') SET_BIT(player[WHITE].p,c);
		if (board[i] != '/') c++;
	}
	return TRUE;
}

void stradd(char str[], char c){
    for (;*str;str++);
    *str++ = c; 
    *str++ = 0;
}

char* board_to_string(){
	char result[330]= {0};/* under 330, gives invalid board  */
	int i, counter = 0;
	for(i=0;i<64;i++){
		if(counter != 0 && counter%8==0) stradd(result,'/');
		if(IS_SET(player[WHITE].p,i)) {stradd(result,'P'); counter++;}
		else if(IS_SET(player[WHITE].q,i)) {stradd(result,'Q'); counter++;}
		else if(IS_SET(player[WHITE].r,i)) {stradd(result,'R'); counter++;}
		else if(IS_SET(player[WHITE].b,i)) {stradd(result,'B'); counter++;}
		else if(IS_SET(player[WHITE].n,i)) {stradd(result,'N'); counter++;}
		else if(IS_SET(player[WHITE].k,i)) {stradd(result,'K'); counter++;}
		else if(IS_SET(player[BLACK].p,i)) {stradd(result,'p'); counter++;}
		else if(IS_SET(player[BLACK].q,i)) {stradd(result,'q'); counter++;}
		else if(IS_SET(player[BLACK].r,i)) {stradd(result,'r'); counter++;}
		else if(IS_SET(player[BLACK].b,i)) {stradd(result,'b'); counter++;}
		else if(IS_SET(player[BLACK].n,i)) {stradd(result,'n'); counter++;}
		else if(IS_SET(player[BLACK].k,i)) {stradd(result,'k'); counter++;}
		else {stradd(result,'1'); counter++;}
	}
	char* ret = result;
	return ret;
}

void print_move(Move* m) { 
	if(get_piece_at(m->from, 1) == QUEEN) printf("QUEEN ");
	if(get_piece_at(m->from, 1) == KING) printf("KING ");
	if(get_piece_at(m->from, 1) == BISHOP) printf("BISHOP ");
	if(get_piece_at(m->from, 1) == PAWN) printf("PAWN ");
	if(get_piece_at(m->from, 1) == ROOK) printf("ROOK ");
	if(get_piece_at(m->from, 1) == NIGHT) printf("NIGHT ");
	if(get_piece_at(m->from, 0) == QUEEN) printf("QUEEN ");
	if(get_piece_at(m->from, 0) == KING) printf("KING ");
	if(get_piece_at(m->from, 0) == BISHOP) printf("BISHOP ");
	if(get_piece_at(m->from, 0) == PAWN) printf("PAWN ");
	if(get_piece_at(m->from, 0) == ROOK) printf("ROOK ");
	if(get_piece_at(m->from, 0) == NIGHT) printf("NIGHT ");
	printf("%c%c-%c%c\n", FILE_OF(m->from), RANK_OF(m->from), FILE_OF(m->to), RANK_OF(m->to));
} 