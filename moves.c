#include <stdio.h>
#include <stdlib.h>
#include "moves.h"

int fp_kingpos,sp_kingpos;

int add_move(PlayerColor c, Move** move, int fr, int t, Piece p, Piece choice) {
	Move* temp_move = (Move *) malloc(sizeof(Move));
	temp_move->from = fr;
	temp_move->to = t;
	temp_move->piece = p;
	temp_move->promotion_choice = choice;
    if (validate_and_move(temp_move,c)) {
		(*move)->next_move = temp_move; /* x->y->z->...->move->temp_move ===== we are at move */ 
		*move = (*move)->next_move;	
		return 1;    /* x->y->z->...->move->temp_move ===== now we moved forward, so we are at temp_move */ 
	}
	else return 0;
}

int king_thread(int j, int sp,PlayerColor c, PlayerColor enemy_c) {
	int k;
	if(RANK_OF(j) != '8'){
		k = NORTH_OF(j);
		while(UNOCCUPIED(k) && RANK_OF(k) != '8') k = NORTH_OF(k);
		if(OCCUPIED_SP(sp,k) && (get_piece_at(k, enemy_c) == QUEEN || get_piece_at(k, enemy_c) == ROOK)) return 1;
	}

	if(FILE_OF(j) != 'a'){
		k = WEST_OF(j);
		while(UNOCCUPIED(k) && FILE_OF(k) != 'a') k = WEST_OF(k);
		if(OCCUPIED_SP(sp,k) && (get_piece_at(k, enemy_c) == QUEEN || get_piece_at(k, enemy_c) == ROOK) ) return 1;
	}

	if(RANK_OF(j) != '1'){
		k = SOUTH_OF(j);
		while(UNOCCUPIED(k) && RANK_OF(k) != '1') k = SOUTH_OF(k);
		if(OCCUPIED_SP(sp,k) && (get_piece_at(k, enemy_c) == QUEEN || get_piece_at(k, enemy_c) == ROOK) ) return 1;
	}

	if(FILE_OF(j) != 'a'){
		k = EAST_OF(j);
		while(UNOCCUPIED(k) && FILE_OF(k) != 'h') k = EAST_OF(k);
		if(OCCUPIED_SP(sp,k) && (get_piece_at(k, enemy_c) == QUEEN || get_piece_at(k, enemy_c) == ROOK) ) return 1;
	}

	/* if there is an enemy_queen or enemy_bishop at cross then king cannot move to this square. */
	if(RANK_OF(j) != '8' && FILE_OF(j) != 'a'){
		k = NW_OF(j);
		while(UNOCCUPIED(k) && RANK_OF(k) != '8' && FILE_OF(k) != 'a') k = NW_OF(k);
		if(OCCUPIED_SP(sp,k) && (get_piece_at(k, enemy_c) == QUEEN || get_piece_at(k, enemy_c) == BISHOP) ) return 1;
	}

	if(RANK_OF(j) != '1' && FILE_OF(j) != 'a'){
		k = SW_OF(j);
		while(UNOCCUPIED(k) && RANK_OF(k) != '1' && FILE_OF(k) != 'a') k = SW_OF(k);
		if(OCCUPIED_SP(sp,k) && (get_piece_at(k, enemy_c) == QUEEN || get_piece_at(k, enemy_c) == BISHOP) ) return 1;
	}

	if(RANK_OF(j) != '8' && FILE_OF(j) != 'h'){
		k = NE_OF(j);
		while(UNOCCUPIED(k) && RANK_OF(k) != '8' && FILE_OF(k) != 'h') k = NE_OF(k);
		if(OCCUPIED_SP(sp,k) && (get_piece_at(k, enemy_c) == QUEEN || get_piece_at(k, enemy_c) == BISHOP) ) return 1;
	}

	if(RANK_OF(j) != '1' && FILE_OF(j) != 'h'){
		k = SE_OF(j);
		while(UNOCCUPIED(k) && RANK_OF(k) != '1' && FILE_OF(k) != 'h') k = SE_OF(k);
		if(OCCUPIED_SP(sp,k) && (get_piece_at(k, enemy_c) == QUEEN || get_piece_at(k, enemy_c) == BISHOP) ) return 1;
	}
	/* if there is an enemy_pawn at NW_OF(NORTH_OF(KING_POS)) then WHITE king cannot move to this square. */
	k = j;
	if(c == WHITE && RANK_OF(k) != '8' && OCCUPIED_SP(sp,NW_OF(k)) && get_piece_at(NW_OF(k), enemy_c) == PAWN) return 1;	
	k = j;
	if(c == WHITE && RANK_OF(k) != '8' && OCCUPIED_SP(sp,NE_OF(k)) && get_piece_at(NE_OF(k), enemy_c) == PAWN) return 1;	
	/* if there is an enemy_pawn at NW_OF(NORTH_OF(KING_POS)) then BLACK king cannot move to this square. */
	k = j;
	if(c == BLACK && RANK_OF(k) != '1' && OCCUPIED_SP(sp,SW_OF(k)) && get_piece_at(SW_OF(k), enemy_c) == PAWN) return 1;	
	k = j;
	if(c == BLACK && RANK_OF(k) != '1' && OCCUPIED_SP(sp,SE_OF(k)) && get_piece_at(SE_OF(k), enemy_c) == PAWN) return 1;	
	/* if there is an enemy_night at square NORTH_OF(WEST_OF(WEST_OF(i))), then king cannot move to this square */
	k = j;
	if(RANK_OF(k) != '8' && FILE_OF(k)  > 'c' && get_piece_at(NORTH_OF(WEST_OF(WEST_OF(k))), enemy_c) == NIGHT) return 1;
	k = j;
	if(RANK_OF(k)  < '6' && FILE_OF(k) != 'a' && get_piece_at(NORTH_OF(NORTH_OF(WEST_OF(k))), enemy_c) == NIGHT) return 1;
	k = j;
	if(RANK_OF(k)  < '6' && FILE_OF(k) != 'h' && get_piece_at(EAST_OF(NORTH_OF(NORTH_OF(k))), enemy_c) == NIGHT ) return 1;
	k = j;
	if(RANK_OF(k) != '8' && FILE_OF(k)  < 'f' && get_piece_at(EAST_OF(EAST_OF(NORTH_OF(k))), enemy_c) == NIGHT ) return 1;
	k = j;
	if(RANK_OF(k) != '1' && FILE_OF(k)  < 'f' && get_piece_at(SOUTH_OF(EAST_OF(EAST_OF(k))), enemy_c) == NIGHT ) return 1;
	k = j;
	if(RANK_OF(k)  > '3' && FILE_OF(k) != 'h' && get_piece_at(SOUTH_OF(SOUTH_OF(EAST_OF(k))), enemy_c) == NIGHT ) return 1;
	k = j;
	if(RANK_OF(k)  > '3' && FILE_OF(k) != 'a' && get_piece_at(WEST_OF(SOUTH_OF(SOUTH_OF(k))), enemy_c) == NIGHT ) return 1;
	k = j;
	if(RANK_OF(k) != '1' && FILE_OF(k)  > 'c' && get_piece_at(WEST_OF(WEST_OF(SOUTH_OF(k))), enemy_c) == NIGHT ) return 1;	
	/* if there is an enemy_king at square __ , then king cannot move to this square */
	k = j;
	if(RANK_OF(k) != '8' && get_piece_at(NORTH_OF(k), enemy_c) == KING) return 1;
	k = j;
	if(RANK_OF(k) != '1' && get_piece_at(SOUTH_OF(k), enemy_c) == KING) return 1;
	k = j;
	if(RANK_OF(k) != '8' && FILE_OF(k) != 'a' && get_piece_at(NW_OF(k), enemy_c) == KING) return 1;
	k = j;
	if(RANK_OF(k) != '8' && FILE_OF(k) != 'h' && get_piece_at(NE_OF(k), enemy_c) == KING) return 1;
	k = j;
	if(FILE_OF(k) != 'a' && get_piece_at(WEST_OF(k), enemy_c) == KING) return 1;
	k = j;
	if(FILE_OF(k) != 'h' && get_piece_at(EAST_OF(k), enemy_c) == KING) return 1;
	k = j;
	if(FILE_OF(k) != 'a' && RANK_OF(k) != '1' && get_piece_at(SW_OF(k), enemy_c) == KING) return 1;
	k = j;
	if(FILE_OF(k) != 'h' && RANK_OF(k) != '1' && get_piece_at(SE_OF(k), enemy_c) == KING) return 1;
	return 0;
}

Bool legal_moves(Move **m, PlayerColor c, unsigned int *pcount) {
	/* Your implementation */

	/* Initialize the players */
	int fp,sp,total_moves=0,i,j,k;

	if (c == WHITE) {fp = 1; sp = 0;}
	if (c == BLACK) {fp = 0; sp = 1;}

	/* initialize first movement */
	Move* first_move = (Move*) malloc(sizeof(Move));
	*m = first_move;

	/* loop that will check all squares */
	for(i = 0; i <=63; i++) { /* we have 64 squares, 0-63 */
		if(IS_SET(player[fp].p,i)){
			if(c == WHITE){
				if( RANK_OF(i) != '8' ){
					if( UNOCCUPIED(NORTH_OF(i)) ){
						if(RANK_OF(i) != '7') {
							j = NORTH_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,UNKNOWN);
							
						}
						else{
							j = NORTH_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,QUEEN);
							total_moves += add_move(c,m,i,j,PAWN,ROOK);
							total_moves += add_move(c,m,i,j,PAWN,NIGHT);
							total_moves += add_move(c,m,i,j,PAWN,BISHOP);
							
						}
					}
					if( UNOCCUPIED(NORTH_OF(NORTH_OF(i))) ){
						if(RANK_OF(i) == '2') {
							j = NORTH_OF(NORTH_OF(i));
							total_moves += add_move(c,m,i,j,PAWN,UNKNOWN);
							
						}
					}
					if(FILE_OF(i) != 'a') if( (!(OCCUPIED_FP(fp, NW_OF(i)))) && OCCUPIED_SP(sp, NW_OF(i)) ){
						if(RANK_OF(i) != '7') {
							j = NW_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,UNKNOWN);
							
						}
						else{
							j = NW_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,QUEEN);
							total_moves += add_move(c,m,i,j,PAWN,ROOK);
							total_moves += add_move(c,m,i,j,PAWN,NIGHT);
							total_moves += add_move(c,m,i,j,PAWN,BISHOP);
							
						}
					}
					if(FILE_OF(i) != 'h') if( (!(OCCUPIED_FP(fp, NE_OF(i)))) && OCCUPIED_SP(sp, NE_OF(i)) ){
						if(RANK_OF(i) != '7') {
							j = NE_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,UNKNOWN);
							
						}
						else{
							j = NE_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,QUEEN);
							total_moves += add_move(c,m,i,j,PAWN,ROOK);
							total_moves += add_move(c,m,i,j,PAWN,NIGHT);
							total_moves += add_move(c,m,i,j,PAWN,BISHOP);
							
						}
					}
				}
			}
			if(c == BLACK){
				if(RANK_OF(i) != '1'){
					if(UNOCCUPIED(SOUTH_OF(i))){
						if(RANK_OF(i) != '2') {
							j = SOUTH_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,UNKNOWN);
							
						}
						else{
							j = SOUTH_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,QUEEN);
							total_moves += add_move(c,m,i,j,PAWN,ROOK);
							total_moves += add_move(c,m,i,j,PAWN,NIGHT);
							total_moves += add_move(c,m,i,j,PAWN,BISHOP);
							
						}
					}
					if( UNOCCUPIED(SOUTH_OF(SOUTH_OF(i))) ){
						if(RANK_OF(i) == '7') {
							j = SOUTH_OF(SOUTH_OF(i));
							total_moves += add_move(c,m,i,j,PAWN,UNKNOWN);
							
						}
					}
					if(FILE_OF(i) != 'a') if( (!(OCCUPIED_FP(fp, SW_OF(i)))) && OCCUPIED_SP(sp, SW_OF(i)) ){
						if(RANK_OF(i) != '2') {
							j = SW_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,UNKNOWN);
							
						}
						else{
							j = SW_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,QUEEN);
							total_moves += add_move(c,m,i,j,PAWN,ROOK);
							total_moves += add_move(c,m,i,j,PAWN,NIGHT);
							total_moves += add_move(c,m,i,j,PAWN,BISHOP);
							
						}
					}
					if(FILE_OF(i) != 'h') if( (!(OCCUPIED_FP(fp, SE_OF(i)))) && OCCUPIED_SP(sp, SE_OF(i)) ){
						if(RANK_OF(i) != '2') {
							j = SE_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,UNKNOWN);
							
						}
						else{
							j = SE_OF(i);
							total_moves += add_move(c,m,i,j,PAWN,QUEEN);
							total_moves += add_move(c,m,i,j,PAWN,ROOK);
							total_moves += add_move(c,m,i,j,PAWN,NIGHT);
							total_moves += add_move(c,m,i,j,PAWN,BISHOP);
							
						}
					}
				}
			}
		}
		if(IS_SET(player[fp].b,i)){
			k=i;
			/* NW_OF */
			while(RANK_OF(k) != '8' && FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, NW_OF(k)))) )
			{
				j = NW_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, BISHOP, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, BISHOP, UNKNOWN);
				k = NW_OF(k);
			}
			k=i;
			/* NE_OF */
			while(RANK_OF(k) != '8' && FILE_OF(k) != 'h'  && (!(OCCUPIED_FP(fp, NE_OF(k)))) )
			{
				j = NE_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, BISHOP, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, BISHOP, UNKNOWN);
				k = NE_OF(k);
			}
			k=i;
			/* SW_OF */
			while(RANK_OF(k) != '1' && FILE_OF(k) != 'a'  && (!(OCCUPIED_FP(fp, SW_OF(k)))) )
			{
				j = SW_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, BISHOP, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, BISHOP, UNKNOWN);
				k = SW_OF(k);
			}
			k=i;
			/* SE_OF */
			while(RANK_OF(k) != '1' && FILE_OF(k) != 'h'  && (!(OCCUPIED_FP(fp, SE_OF(k)))) )
			{
				j = SE_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, BISHOP, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, BISHOP, UNKNOWN);
				k = SE_OF(k);
			}
		}
		if(IS_SET(player[fp].r,i)){
			k=i;
			/* NORTH_OF */
			while(RANK_OF(k) != '8' && (!(OCCUPIED_FP(fp, NORTH_OF(k)))) )
			{
				j = NORTH_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, ROOK, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, ROOK, UNKNOWN);
				k = NORTH_OF(k);
			}
			k=i;
			/* SOUTH_OF */
			while(RANK_OF(k) != '1' && (!(OCCUPIED_FP(fp, SOUTH_OF(k)))) )
			{
				j = SOUTH_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, ROOK, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, ROOK, UNKNOWN);
				k = SOUTH_OF(k);
			}
			k=i;
			/* WEST_OF */
			while(FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, WEST_OF(k)))) )
			{
				j = WEST_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, ROOK, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, ROOK, UNKNOWN);
				k = WEST_OF(k);
			}
			k=i;
			/* EAST_OF */
			while(FILE_OF(k) != 'h' && (!(OCCUPIED_FP(fp, EAST_OF(k)))) )
			{
				j = EAST_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, ROOK, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, ROOK, UNKNOWN);
				k = EAST_OF(k);
			}
		}
		if(IS_SET(player[fp].n,i)){
			if(RANK_OF(i) != '8' && FILE_OF(i) != 'a' && FILE_OF(i) != 'b') 
			{
				j=NORTH_OF(WEST_OF(WEST_OF(i))); /* A B 8 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					
					total_moves += add_move(c,m,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != '7' && RANK_OF(i) != '8' && FILE_OF(i) != 'a') 
			{
				j=NORTH_OF(NORTH_OF(WEST_OF(i))); /* A 7 8 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					
					total_moves += add_move(c,m,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != '7' && RANK_OF(i) != '8' && FILE_OF(i) != 'h') 
			{
				j=EAST_OF(NORTH_OF(NORTH_OF(i))); /* H 7 8 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					
					total_moves += add_move(c,m,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != '8' && FILE_OF(i) != 'g' && FILE_OF(i) != 'h') 
			{
				j=EAST_OF(EAST_OF(NORTH_OF(i))); /* G H 8 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					
					total_moves += add_move(c,m,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != '1' && FILE_OF(i) != 'g' && FILE_OF(i) != 'h')
			{
				j=SOUTH_OF(EAST_OF(EAST_OF(i))); /* G H 1 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					
					total_moves += add_move(c,m,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != '1' && RANK_OF(i) != '2' && FILE_OF(i) != 'h')
			{
				j=SOUTH_OF(SOUTH_OF(EAST_OF(i))); /* H 1 2 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					
					total_moves += add_move(c,m,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != '1' && RANK_OF(i) != '2' && FILE_OF(i) != 'a')
			{
				j=WEST_OF(SOUTH_OF(SOUTH_OF(i))); /* A 1 2 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					
					total_moves += add_move(c,m,i,j,NIGHT,UNKNOWN);
				}
			}
			if(RANK_OF(i) != '1' && FILE_OF(i) != 'a' && FILE_OF(i) != 'b')
			{
				j=WEST_OF(WEST_OF(SOUTH_OF(i))); /* A B 1 */
				if(!(OCCUPIED_FP(fp, j)))
				{
					
					total_moves += add_move(c,m,i,j,NIGHT,UNKNOWN);
				}
			}
		}
		if(IS_SET(player[fp].q,i)){
			k=i;
			/* NORTH_OF */
			while(RANK_OF(k) != '8' && (!(OCCUPIED_FP(fp, NORTH_OF(k)))) )
			{
				j = NORTH_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
				k = NORTH_OF(k);
			}
			k=i;
			/* SOUTH_OF */
			while(RANK_OF(k) != '1' && (!(OCCUPIED_FP(fp, SOUTH_OF(k)))) )
			{
				j = SOUTH_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
				k = SOUTH_OF(k);
			}
			k=i;
			/* WEST_OF */
			while(FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, WEST_OF(k)))) )
			{
				j = WEST_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
				k = WEST_OF(k);
			}
			k=i;
			/* EAST_OF */
			while(FILE_OF(k) != 'h' && (!(OCCUPIED_FP(fp, EAST_OF(k)))) )
			{
				j = EAST_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
				k = EAST_OF(k);
			}
			k=i;
			/* NW_OF */
			while(RANK_OF(k) != '8' && FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, NW_OF(k)))) )
			{
				j = NW_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
				k = NW_OF(k);
			}
			k=i;
			/* NE_OF */
			while(RANK_OF(k) != '8' && FILE_OF(k) != 'h' && (!(OCCUPIED_FP(fp, NE_OF(k)))) )
			{
				j = NE_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
				k = NE_OF(k);
			}
			k=i;
			/* SW_OF */
			while(RANK_OF(k) != '1' && FILE_OF(k) != 'a' && (!(OCCUPIED_FP(fp, SW_OF(k)))) )
			{
				j = SW_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
				k = SW_OF(k);
			}
			k=i;
			/* SE_OF */
			while(RANK_OF(k) != '1' && FILE_OF(k) != 'h' && (!(OCCUPIED_FP(fp, SE_OF(k)))) )
			{
				j = SE_OF(k);
				
				if (OCCUPIED_SP(sp, j))
				{
					total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
					break;
				}
				else total_moves += add_move(c,m, i, j, QUEEN, UNKNOWN);
				k = SE_OF(k);
			}
		}
		if(IS_SET(player[fp].k,i)){
			int thread = 0;
			if(RANK_OF(i) != '8' && (!(OCCUPIED_FP(fp, NORTH_OF(i)))) )
			{
				j = NORTH_OF(i);
				/*thread = king_thread(j,sp,c,enemy_c);*/

				if(thread == 0) {  total_moves += add_move(c,m,i,j,KING,UNKNOWN);}
			}
			if(RANK_OF(i) != '1' && (!(OCCUPIED_FP(fp, SOUTH_OF(i)))) )
			{
				j = SOUTH_OF(i);
				/*thread = king_thread(j,sp,c,enemy_c);*/

				if(thread == 0) {  total_moves += add_move(c,m,i,SOUTH_OF(i),KING,UNKNOWN);}
			}
			if(FILE_OF(i) != 'a' && (!(OCCUPIED_FP(fp, WEST_OF(i)))) )
			{
				j = WEST_OF(i);
				/*thread = king_thread(j,sp,c,enemy_c);*/

				if(thread == 0) {  total_moves += add_move(c,m,i,WEST_OF(i),KING,UNKNOWN);}
			}
			if(FILE_OF(i) != 'h' && (!(OCCUPIED_FP(fp, EAST_OF(i)))) )
			{
				j = EAST_OF(i);
				/*thread = king_thread(j,sp,c,enemy_c);*/

				if(thread == 0) {  total_moves += add_move(c,m,i,EAST_OF(i),KING,UNKNOWN);}
			}
			if(RANK_OF(i) != '8' && FILE_OF(i) != 'a' && (!(OCCUPIED_FP(fp, NW_OF(i)))) )
			{
				j = NW_OF(i);
				/*thread = king_thread(j,sp,c,enemy_c);*/

				if(thread == 0) {  total_moves += add_move(c,m,i,NW_OF(i),KING,UNKNOWN);}
			}
			if(RANK_OF(i) != '1' && FILE_OF(i) != 'h' && (!(OCCUPIED_FP(fp, SE_OF(i)))) )
			{
				j = SE_OF(i);
				/*thread = king_thread(j,sp,c,enemy_c);*/

				if(thread == 0) {  total_moves += add_move(c,m,i,SE_OF(i),KING,UNKNOWN);}
			}
			if(FILE_OF(i) != 'a' && RANK_OF(i) != '1' && (!(OCCUPIED_FP(fp, SW_OF(i)))) )
			{
				j = SW_OF(i);
				/*thread = king_thread(j,sp,c,enemy_c);*/

				if(thread == 0) {  total_moves += add_move(c,m,i,SW_OF(i),KING,UNKNOWN);}
			}
			if(FILE_OF(i) != 'h' && RANK_OF(i) != '8' && (!(OCCUPIED_FP(fp, NE_OF(i)))) )
			{
				j = NE_OF(i);
				/*thread = king_thread(j,sp,c,enemy_c);*/

				if(thread == 0) {  total_moves += add_move(c,m,i,NE_OF(i),KING,UNKNOWN);}
			}
			
		}
	}
	first_move = first_move->next_move;
	*m = first_move;
	*pcount = total_moves; /* amount of possible movements */
	if (*pcount > 0) return TRUE; /* total_moves > 0 */ /* if there are possible movements, return TRUE  */
	else return FALSE; /* if there is no possible movements return FALSE */
}

Bool is_checkmate() {
    /* Your implementation */
	return TRUE;
}

Bool validate_and_move(Move *move, PlayerColor c) {
	/*Bool validate_and_move(Move *move, char **msg, PlayerColor c, Pos *ep_sq) {*/
	
    /* Your implementation */
	char* temp = board_to_string();
	int i = move->from;
	int j = move->to;
	if(get_piece_at(j,1-c) != KING) {
		if(move->piece == QUEEN) { RESET_BIT(player[c].q, i); SET_BIT(player[c].q, j); }
		else if(move->piece == KING) { RESET_BIT(player[c].k, i); SET_BIT(player[c].k, j); }
		else if(move->piece == BISHOP) { RESET_BIT(player[c].b, i); SET_BIT(player[c].b, j); }
		else if(move->piece == NIGHT) { RESET_BIT(player[c].n, i); SET_BIT(player[c].n, j); }
		else if(move->piece == ROOK) { RESET_BIT(player[c].r, i); SET_BIT(player[c].r, j); }
		else if(move->piece == PAWN) { RESET_BIT(player[c].p, i); SET_BIT(player[c].p, j); }
		RESET_BIT(player[1-c].q ,j); RESET_BIT(player[1-c].b ,j); RESET_BIT(player[1-c].r ,j); RESET_BIT(player[1-c].p ,j); RESET_BIT(player[1-c].n ,j);RESET_BIT(player[1-c].k ,j);
			/* loop that will find KING positions */
		int a;
		for(a = 0; a <=63; a++) {
			if(IS_SET(player[c].k,a)) fp_kingpos = a;
			else if(IS_SET(player[1-c].k,a)) sp_kingpos = a;
		}
			/* returns TRUE if move is valid && reverses the movement*/
		if(king_thread(fp_kingpos, 1-c, c, 1-c) == 0 ) { parse_board(temp); return TRUE; }
		else { parse_board(temp); return FALSE; }
	}
	else { parse_board(temp); return FALSE; }
}
void make_move(Move *move, PlayerColor c){
	int i = move->from;
	int j = move->to;
	if(move->piece == QUEEN) { RESET_BIT(player[c].q, i); SET_BIT(player[c].q, j); }
	else if(move->piece == KING) { RESET_BIT(player[c].k, i); SET_BIT(player[c].k, j); }
	else if(move->piece == BISHOP) { RESET_BIT(player[c].b, i); SET_BIT(player[c].b, j); }
	else if(move->piece == NIGHT) { RESET_BIT(player[c].n, i); SET_BIT(player[c].n, j); }
	else if(move->piece == ROOK) { RESET_BIT(player[c].r, i); SET_BIT(player[c].r, j); }
	else if(move->piece == PAWN) { RESET_BIT(player[c].p, i); SET_BIT(player[c].p, j); }
	RESET_BIT(player[1-c].q ,j); RESET_BIT(player[1-c].b ,j); RESET_BIT(player[1-c].r ,j); RESET_BIT(player[1-c].p ,j); RESET_BIT(player[1-c].n ,j);RESET_BIT(player[1-c].k ,j);
}
Bool is_draw() {
    /* Your implementation */
	return TRUE;
}

Piece get_piece_at(Board pos, PlayerColor c) {
    /* Your implementation */
	if(IS_SET(player[c].p, pos)) return PAWN;
	if(IS_SET(player[c].k, pos)) return KING;
	if(IS_SET(player[c].q, pos)) return QUEEN;
	if(IS_SET(player[c].r, pos)) return ROOK;
	if(IS_SET(player[c].n, pos)) return NIGHT;
	if(IS_SET(player[c].b, pos)) return BISHOP;
	return UNKNOWN;
}

unsigned int detect_castle_move(Move move, PlayerColor c) {
    /* Your implementation */
	return 1;
}

void perform_castle(unsigned int castle, PlayerColor c) {
    /* Your implementation */
}