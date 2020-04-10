#include <stdio.h>
#include <stdlib.h>
#include "moves.h"

/* Given a color, this function returns a singly linked list of all legal Moves with the head at *m. 
 * The function returns TRUE if at least 1 legal move is available. 
 * The total number of moves found is stored in the address pointed to by pcount. */


void add_move(Move* move, int fr, int t, Piece p, Piece choice)
{
	Move* temp_move = (Move *) malloc(sizeof(Move));
	temp_move->from = fr;
	temp_move->to = t;
	temp_move->piece = p;
	temp_move->promotion_choice = choice;
	move->next_move = temp_move; /* x->y->z->...->move->temp_move ===== we are at move */ 
	move = temp_move; 	    /* x->y->z->...->move->temp_move ===== now we moved forward, so we are at temp_move */ 
}

Bool legal_moves(Move **m, PlayerColor c, unsigned int *pcount) 
{
	/* Your implementation */

	/* Initialize the players */
	int fp,sp,total_moves=0,i,j,k;
	if (c == WHITE) {fp = 1; sp = 0;}
	if (c == BLACK) {fp = 0; sp = 1;}
	/*PlayerState player[2];*/
	PlayerState first_player = player[fp]; PlayerState second_player = player[sp];

	/* Initialize the pieces */
	Board pawn1 = first_player.p, bishop1 = first_player.b , knight1= first_player.n , king1 = first_player.k , queen1 = first_player.q , rook1 = first_player.r;
	Board pawn2 = second_player.p, bishop2 = second_player.b , knight2= second_player.n , king2 = second_player.k , queen2 = second_player.q , rook2 = second_player.r;

	/* initialize first movement as linked list - classic linked list initialization */
	Move* first_move = (Move*) malloc(sizeof(Move));
	first_move->from = 0;
	first_move->to = 0;
	first_move->piece = UNKNOWN;
	first_move->promotion_choice = UNKNOWN;
	Move* move = first_move;

	/* loop that will check all squares */
	for(i = 0; i <=63; i++) { /* we have 64 squares, 0-63 */
		if(IS_SET(pawn1,i)){
			if(c == WHITE){
				if( RANK_OF(i) != 8 ){
					if( UNOCCUPIED(NORTH_OF(i)) ){
						if(RANK_OF(i) != 7) {
							j = NORTH_OF(i);
							add_move(move,i,j,PAWN,UNKNOWN);
							total_moves++;
						}
						else{
							j = NORTH_OF(i);
							add_move(move,i,j,PAWN,QUEEN);
							add_move(move,i,j,PAWN,ROOK);
							add_move(move,i,j,PAWN,NIGHT);
							add_move(move,i,j,PAWN,BISHOP);
							total_moves+=4;
						}
					}
					if(FILE_OF(i) != 'a') if( (!(OCCUPIED_FP(fp, NW_OF(i)))) && OCCUPIED_SP(sp, NW_OF(i)) ){
						if(RANK_OF(i) != 7) {
							j = NW_OF(i);
							add_move(move,i,j,PAWN,UNKNOWN);
							total_moves++;
						}
						else{
							j = NW_OF(i);
							add_move(move,i,j,PAWN,QUEEN);
							add_move(move,i,j,PAWN,ROOK);
							add_move(move,i,j,PAWN,NIGHT);
							add_move(move,i,j,PAWN,BISHOP);
							total_moves+=4;
						}
					}
					if(FILE_OF(i) != 'h') if( (!(OCCUPIED_FP(fp, NE_OF(i)))) && OCCUPIED_SP(sp, NE_OF(i)) ){
						if(RANK_OF(i) != 7) {
							j = NE_OF(i);
							add_move(move,i,j,PAWN,UNKNOWN);
							total_moves++;
						}
						else{
							j = NE_OF(i);
							add_move(move,i,j,PAWN,QUEEN);
							add_move(move,i,j,PAWN,ROOK);
							add_move(move,i,j,PAWN,NIGHT);
							add_move(move,i,j,PAWN,BISHOP);
							total_moves+=4;
						}
					}
				}
			}
			if(c == BLACK){
				if(RANK_OF(i) != 1){
					if(UNOCCUPIED(SOUTH_OF(i))){
						if(RANK_OF(i) != 2) {
							j = SOUTH_OF(i);
							add_move(move,i,j,PAWN,UNKNOWN);
							total_moves++;
						}
						else{
							j = SOUTH_OF(i);
							add_move(move,i,j,PAWN,QUEEN);
							add_move(move,i,j,PAWN,ROOK);
							add_move(move,i,j,PAWN,NIGHT);
							add_move(move,i,j,PAWN,BISHOP);
							total_moves+=4;
						}
					}
					if(FILE_OF(i) != 'a') if( (!(OCCUPIED_FP(fp, SW_OF(i)))) && OCCUPIED_SP(sp, SW_OF(i)) ){
						if(RANK_OF(i) != 2) {
							j = SW_OF(i);
							add_move(move,i,j,PAWN,UNKNOWN);
							total_moves++;
						}
						else{
							j = SW_OF(i);
							add_move(move,i,j,PAWN,QUEEN);
							add_move(move,i,j,PAWN,ROOK);
							add_move(move,i,j,PAWN,NIGHT);
							add_move(move,i,j,PAWN,BISHOP);
							total_moves+=4;
						}
					}
					if(FILE_OF(i) != 'h') if( (!(OCCUPIED_FP(fp, SE_OF(i)))) && OCCUPIED_SP(sp, SE_OF(i)) ){
						if(RANK_OF(i) != 2) {
							j = SE_OF(i);
							add_move(move,i,j,PAWN,UNKNOWN);
							total_moves++;
						}
						else{
							j = SE_OF(i);
							add_move(move,i,j,PAWN,QUEEN);
							add_move(move,i,j,PAWN,ROOK);
							add_move(move,i,j,PAWN,NIGHT);
							add_move(move,i,j,PAWN,BISHOP);
							total_moves+=4;
						}
					}
				}
			}
		}
		if(IS_SET(bishop1,i)){
			k=i;
			/* NW_OF */
			while(RANK_OF(k) != 8 && FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, NW_OF(k)))) )
			{
				j = NW_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, BISHOP, UNKNOWN);
					break;
				}
				else add_move(move, i, j, BISHOP, UNKNOWN);
				k = NW_OF(k);
			}
			k=i;
			/* NE_OF */
			while(RANK_OF(k) != 8 && FILE_OF(k) != 'h'  && (!(OCCUPIED_FP(fp, NE_OF(k)))) )
			{
				j = NE_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, BISHOP, UNKNOWN);
					break;
				}
				else add_move(move, i, j, BISHOP, UNKNOWN);
				k = NE_OF(k);
			}
			k=i;
			/* SW_OF */
			while(RANK_OF(k) != 1 && FILE_OF(k) != 'a'  && (!(OCCUPIED_FP(fp, SW_OF(k)))) )
			{
				j = SW_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, BISHOP, UNKNOWN);
					break;
				}
				else add_move(move, i, j, BISHOP, UNKNOWN);
				k = SW_OF(k);
			}
			k=i;
			/* SE_OF */
			while(RANK_OF(k) != 1 && FILE_OF(k) != 'h'  && (!(OCCUPIED_FP(fp, SE_OF(k)))) )
			{
				j = SE_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, BISHOP, UNKNOWN);
					break;
				}
				else add_move(move, i, j, BISHOP, UNKNOWN);
				k = SE_OF(k);
			}
		}
		if(IS_SET(rook1,i)){
			k=i;
			/* NORTH_OF */
			while(RANK_OF(k) != 8 && (!(OCCUPIED_FP(fp, NORTH_OF(k)))) )
			{
				j = NORTH_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, ROOK, UNKNOWN);
					break;
				}
				else add_move(move, i, j, ROOK, UNKNOWN);
				k = NORTH_OF(k);
			}
			k=i;
			/* SOUTH_OF */
			while(RANK_OF(k) != 1 && (!(OCCUPIED_FP(fp, SOUTH_OF(k)))) )
			{
				j = SOUTH_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, ROOK, UNKNOWN);
					break;
				}
				else add_move(move, i, j, ROOK, UNKNOWN);
				k = SOUTH_OF(k);
			}
			k=i;
			/* WEST_OF */
			while(FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, WEST_OF(k)))) )
			{
				j = WEST_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, ROOK, UNKNOWN);
					break;
				}
				else add_move(move, i, j, ROOK, UNKNOWN);
				k = WEST_OF(k);
			}
			k=i;
			/* EAST_OF */
			while(FILE_OF(k) != 'h' && (!(OCCUPIED_FP(fp, EAST_OF(k)))) )
			{
				j = EAST_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, ROOK, UNKNOWN);
					break;
				}
				else add_move(move, i, j, ROOK, UNKNOWN);
				k = EAST_OF(k);
			}
		}
		if(IS_SET(knight1,i)){
			if(RANK_OF(i) != 8 && FILE_OF(i) != 'a' && FILE_OF(i) != 'b') 
			{
				j=NORTH_OF(WEST_OF(WEST_OF(i))); /* A B 8 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					total_moves++;
					add_move(move,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != 7 && RANK_OF(i) != 8 && FILE_OF(i) != 'a') 
			{
				j=NORTH_OF(NORTH_OF(WEST_OF(i))); /* A 7 8 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					total_moves++;
					add_move(move,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != 7 && RANK_OF(i) != 8 && FILE_OF(i) != 'h') 
			{
				j=EAST_OF(NORTH_OF(NORTH_OF(i))); /* H 7 8 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					total_moves++;
					add_move(move,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != 8 && FILE_OF(i) != 'g' && FILE_OF(i) != 'h') 
			{
				j=EAST_OF(EAST_OF(NORTH_OF(i))); /* G H 8 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					total_moves++;
					add_move(move,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != 1 && FILE_OF(i) != 'g' && FILE_OF(i) != 'h')
			{
				j=SOUTH_OF(EAST_OF(EAST_OF(i))); /* G H 1 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					total_moves++;
					add_move(move,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != 1 && RANK_OF(i) != 2 && FILE_OF(i) != 'h')
			{
				j=SOUTH_OF(SOUTH_OF(EAST_OF(i))); /* H 1 2 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					total_moves++;
					add_move(move,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != 1 && RANK_OF(i) != 2 && FILE_OF(i) != 'a')
			{
				j=WEST_OF(SOUTH_OF(SOUTH_OF(i))); /* A 1 2 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					total_moves++;
					add_move(move,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != 1 && FILE_OF(i) != 'a' && FILE_OF(i) != 'b')
			{
				j=WEST_OF(WEST_OF(SOUTH_OF(i))); /* A B 1 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					total_moves++;
					add_move(move,i,j,NIGHT,UNKNOWN);
				}
			}
		}
		if(IS_SET(queen1,i)){
			k=i;
			/* NORTH_OF */
			while(RANK_OF(k) != 8 && (!(OCCUPIED_FP(fp, NORTH_OF(k)))) )
			{
				j = NORTH_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, QUEEN, UNKNOWN);
					break;
				}
				else add_move(move, i, j, QUEEN, UNKNOWN);
				k = NORTH_OF(k);
			}
			k=i;
			/* SOUTH_OF */
			while(RANK_OF(k) != 1 && (!(OCCUPIED_FP(fp, SOUTH_OF(k)))) )
			{
				j = SOUTH_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, QUEEN, UNKNOWN);
					break;
				}
				else add_move(move, i, j, QUEEN, UNKNOWN);
				k = SOUTH_OF(k);
			}
			k=i;
			/* WEST_OF */
			while(FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, WEST_OF(k)))) )
			{
				j = WEST_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, QUEEN, UNKNOWN);
					break;
				}
				else add_move(move, i, j, QUEEN, UNKNOWN);
				k = WEST_OF(k);
			}
			k=i;
			/* EAST_OF */
			while(FILE_OF(k) != 'h' && (!(OCCUPIED_FP(fp, EAST_OF(k)))) )
			{
				j = EAST_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, QUEEN, UNKNOWN);
					break;
				}
				else add_move(move, i, j, QUEEN, UNKNOWN);
				k = EAST_OF(k);
			}
			k=i;
			/* NW_OF */
			while(RANK_OF(k) != 8 && FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, NW_OF(k)))) )
			{
				j = NW_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, QUEEN, UNKNOWN);
					break;
				}
				else add_move(move, i, j, QUEEN, UNKNOWN);
				k = NW_OF(k);
			}
			k=i;
			/* NE_OF */
			while(RANK_OF(k) != 8 && FILE_OF(k) != 'h' && (!(OCCUPIED_FP(fp, NE_OF(k)))) )
			{
				j = NE_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, QUEEN, UNKNOWN);
					break;
				}
				else add_move(move, i, j, QUEEN, UNKNOWN);
				k = NE_OF(k);
			}
			k=i;
			/* SW_OF */
			while(RANK_OF(k) != 1 && FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, SW_OF(k)))) )
			{
				j = SW_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, QUEEN, UNKNOWN);
					break;
				}
				else add_move(move, i, j, QUEEN, UNKNOWN);
				k = SW_OF(k);
			}
			k=i;
			/* SE_OF */
			while(RANK_OF(k) != 1 && FILE_OF(k) != 'h' && (!(OCCUPIED_FP(fp, SE_OF(k)))) )
			{
				j = SE_OF(k);
				total_moves++;
				if (OCCUPIED_SP(sp, j))
				{
					add_move(move, i, j, QUEEN, UNKNOWN);
					break;
				}
				else add_move(move, i, j, QUEEN, UNKNOWN);
				k = SE_OF(k);
			}
		}
		if(IS_SET(king1,i)){
			if(RANK_OF(i) != 8 && (!(OCCUPIED_FP(fp, NORTH_OF(i)))) )
			{

			}
			if(RANK_OF(i) != 1 && (!(OCCUPIED_FP(fp, SOUTH_OF(i)))) )
			{

			}
			if(FILE_OF(i) != 'a' && (!(OCCUPIED_FP(fp, WEST_OF(i)))) )
			{

			}
			if(FILE_OF(i) != 'h' && (!(OCCUPIED_FP(fp, EAST_OF(i)))) )
			{

			}
			if(RANK_OF(i) != 8 && FILE_OF(i) != 'a' && (!(OCCUPIED_FP(fp, NW_OF(i)))) )
			{

			}
			if(RANK_OF(i) != 1 && FILE_OF(i) != 'h' && (!(OCCUPIED_FP(fp, SE_OF(i)))) )
			{

			}
			if(FILE_OF(i) != 'a' && RANK_OF(i) != 1 && (!(OCCUPIED_FP(fp, SW_OF(i)))) )
			{

			}
			if(FILE_OF(i) != 'h' && RANK_OF(i) != 8 && (!(OCCUPIED_FP(fp, NE_OF(i)))) )
			{

			}
			
		}
	}

	move->next_move = NULL; /* finish the movements list by connecting it to NULL */
	first_move = first_move->next_move; /* we initialized first_move to zero at the beginning, so we have to move forward */
	m[0] = first_move; /* all of the possible movements */
	*pcount = total_moves; /* amount of possible movements */
	if (*pcount > 0) return TRUE; /* total_moves > 0 */ /* if there are possible movements, return TRUE  */
	else return FALSE; /* if there is no possible movements return FALSE */
}

/* Returns TRUE if the CurrentPlayer is under checkmate, FALSE otherwise. */
Bool is_checkmate() {
    /* Your implementation */
	return TRUE;
}

/* Validate a move and make it. Returns TRUE if successful, FALSE if not. 
 *  Error message if any, are stored in *msg. 
 * ep_square (if any) is stored in *ep_sq
 */
Bool validate_and_move(Move *move, char **msg, PlayerColor c, Pos *ep_sq) {
    /* Your implementation */
	return TRUE;
}

/* Function to decide whether the current position is a draw */
/* Draw can be due to insufficient material, 3 move repetition or stalemate */
	/* 3 move repetition also covers perpetual check */
Bool is_draw() {
    /* Your implementation */
	return TRUE;
}

/* Returns the piece on a square belonging to player color c. 
 * If there is no piece with color c, UNKNOWN is returned. */
Piece get_piece_at(Board pos, PlayerColor c) {
    /* Your implementation */
	return TRUE;
}

/* Check if this move is trying to castle */
unsigned int detect_castle_move(Move move, PlayerColor c) {
    /* Your implementation */;
	return 1;
}

/* Perform castling. Moves king and rook and resets castle flags */
void perform_castle(unsigned int castle, PlayerColor c) {
    /* Your implementation */
	return;
}
