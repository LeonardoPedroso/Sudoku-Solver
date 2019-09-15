#include "sudoku.h"

int main(){
	byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH];
	init_table(table);
	printf("Input table:\n");
	print_table(table, 0);
	check_posssible_numbers(table);
	if(fill_sudoku(table))
		printf("Solution found:\n");
	else
		printf("No solutions found\n");
	print_table(table, 0);

	printf("Done\n");
	return 0;
}

void init_table(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]){
	byte sample[TABLE_LENGTH][TABLE_HEIGHT] = SUDOKU;
	for (byte j = 0; j < TABLE_HEIGHT; ++j){
		for (byte i = 0; i < TABLE_LENGTH; ++i){
			table[i][j][0] = sample[j][i];
			for (byte k = 1; k < TABLE_DEPTH; k++){
				table[i][j][k] = EMPTY;
			}
		}
	}
}

void print_table(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH], byte k){
	for (byte j = 0; j < TABLE_HEIGHT; ++j){
		printf("\n");
		if(j%3 == 0)
			printf("\n");
		for (byte i = 0; i < TABLE_LENGTH; ++i){
			if(i%3==0)
				printf(" ");
			if(table[i][j][k] != 0)
				printf("%d ", table[i][j][k]);
			else
				printf(". ");
		}
	}
	printf("\n\n");
}

void check_posssible_numbers(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]){
	for (byte i = 0; i < TABLE_LENGTH; ++i){
		for (byte j = 0; j < TABLE_HEIGHT; ++j){
			if(table[i][j][0] != 0)
				continue;
			for(byte k = 1; k< TABLE_DEPTH; ++k){
				byte break_for = FALSE;
				//linhas
				for(byte n = 0; n < TABLE_LENGTH; ++n){
					if(table[n][j][0] == k){
						table[i][j][k] = NOT_POSSIBLE;
						break_for = TRUE;
						break;
					}
				}
				if(break_for) continue;
				for(byte n = 0; n < TABLE_HEIGHT; ++n){
					if(table[i][n][0] == k){
						table[i][j][k] = NOT_POSSIBLE;
						break_for = TRUE;
						break;
					}
				}
				if(break_for) continue;
				check_square(table, i, j, k, start_square(i), start_square(j));
			}
		}
	}
}

byte start_square(byte x){
	if(x<3)
		return 0;
	else if(x>=3 && x<6)
		return 3;
	else
		return 6;
}

void check_square(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH], byte i, byte j, byte k, byte start_square_i, byte start_square_j){
	for(byte n = 0; n<3; n++){
		for(byte m = 0; m<3; m++){
			if(table[start_square_i+n][start_square_j+m][0]==k){
				table[i][j][k] = NOT_POSSIBLE;
				return;
			}
		}
	}
	table[i][j][k] = POSSIBLE;
}

byte fill_sudoku(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]){
	byte control = reset_possible_numbers(table);
	if(control == FULL)
		return FULL;
	else if(control == INVALID)
		return INVALID;
	check_posssible_numbers(table);
	byte filled = FALSE;
	for (byte i = 0; i < TABLE_LENGTH; ++i){
		for (byte j = 0; j < TABLE_HEIGHT; ++j){
			byte single_alternative = FALSE;
			if(table[i][j][0] != EMPTY)
				continue;
			for(byte k = 1; k < TABLE_DEPTH; ++k){
				if(table[i][j][k] == POSSIBLE && single_alternative == FALSE){
					single_alternative = k;
				}
				else  if(table[i][j][k] == POSSIBLE && single_alternative != FALSE){
					single_alternative = FALSE;
					break;
				}
			}
			if(single_alternative){
				filled = TRUE;
				table[i][j][0] = single_alternative;
			}
		}
	}
	if(filled)
		return fill_sudoku(table);

	for(byte i = 0; i< TABLE_LENGTH; i++){
		for(byte k = 1; k < TABLE_DEPTH; k++){
			byte break_for = FALSE;
			for(byte j = 0; j < TABLE_HEIGHT; j++){
				if(table[i][j][0] == k){
					break_for = TRUE;
					break;
				}
			}
			if(break_for)
				continue;
			//k not in column
			byte single_alternative = FALSE;
			for(byte j = 0; j< TABLE_HEIGHT; j++){
				if(table[i][j][0] != EMPTY)
					continue;
				if(table[i][j][k] == POSSIBLE && !single_alternative){
					single_alternative = j+1;
				}else if(table[i][j][k] == POSSIBLE && single_alternative){
					single_alternative = FALSE;
					break;
				}
			}
			if(single_alternative){
				table[i][single_alternative-1][0] = k;
				filled = TRUE;
			}
		}
	}
	if(filled)
		return fill_sudoku(table);
	for(byte j = 0; j< TABLE_HEIGHT; j++){
		for(byte k = 1; k < TABLE_DEPTH; k++){
			byte break_for = FALSE;
			for(byte i = 0; i < TABLE_LENGTH; i++){
				if(table[i][j][0] == k){
					break_for = TRUE;
					break;
				}
			}
			if(break_for)
				continue;
			//k not in column
			byte single_alternative = FALSE;
			for(byte i = 0; i< TABLE_LENGTH; i++){
				if(table[i][j][0] != EMPTY)
					continue;
				if(table[i][j][k] == POSSIBLE && !single_alternative){
					single_alternative = i+1;
				}else if(table[i][j][k] == POSSIBLE && single_alternative){
					single_alternative = FALSE;
					break;
				}
			}
			if(single_alternative){
				table[single_alternative-1][j][0] = k;
				filled = TRUE;
			}
		}
	}
	if(filled)
		return fill_sudoku(table);
	for(byte start_square_i = 0; start_square_i < 7; start_square_i +=3){
		for(byte start_square_j = 0; start_square_j < 7; start_square_j += 3){
			for(byte k = 1; k< TABLE_DEPTH; k++){
				byte break_for = FALSE;
				for(byte i = 0; i< 3; i++){
					for(byte j = 0; j<3; j++){
						if(table[i][j][0] == k){
							break_for = TRUE;
							break;
						}
					}
					if(break_for)
						break;
				}
				if(break_for)
					break;
				//k not in square
				byte single_alternative = FALSE;
				break_for = FALSE;
				for(byte i = 0; i< 3; i++){
					for(byte j = 0; j<3; j++){
						if(table[i][j][0] == EMPTY){
							if(table[i][j][k] == POSSIBLE && !single_alternative){
								single_alternative = i + j*TABLE_LENGTH+1;
							}else if(table[i][j][k] == POSSIBLE && single_alternative){
								single_alternative = FALSE;
								break_for = TRUE;
								break;
							}
						}
					}
					if(break_for)
						break;
				}
				if(single_alternative){
					table[(single_alternative-1)%TABLE_LENGTH][(single_alternative-1) / TABLE_LENGTH][0] = k;
					filled = TRUE;
				}
			}
		}
	}
	if(filled)
		return fill_sudoku(table);
	else
		return clone_sudoku(table);
}

byte reset_possible_numbers(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]){
	if(!check_sudoku_validity(table))
		return INVALID;

	byte full = FULL; 
	for (byte j = 0; j < TABLE_HEIGHT; ++j){
		for (byte i = 0; i < TABLE_LENGTH; ++i){
			for (byte k = 0; k < TABLE_DEPTH; k++){
				if(k==0){
					if(table[i][j][k] == EMPTY)
						full = FALSE;
				}else
					table[i][j][k] = EMPTY;
			}
		}
	}

	return full;
}


byte clone_sudoku(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]){

	byte break_for = FALSE;
	byte table_alternative[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH];
	for (byte i = 0; i < TABLE_LENGTH; ++i){
		for (byte j = 0; j < TABLE_HEIGHT; ++j){
			byte num_alternatives = 0;

			if(table[i][j][0] != EMPTY)
				continue;

			for(byte k = 1; k < TABLE_DEPTH; ++k){
				if(table[i][j][k] == POSSIBLE)
					num_alternatives++;
			}

			if(num_alternatives == 2){
				copy_table(table_alternative, table);

				byte oneIn = FALSE;
				for(byte k = 1; k< TABLE_DEPTH; k++){
					if(table[i][j][k] == POSSIBLE && !oneIn){
						oneIn = TRUE;
						table_alternative[i][j][0] = k;
					}
					else if(table[i][j][k] == POSSIBLE && oneIn)
						table[i][j][0] = k;
					
				}

				break_for = TRUE;
				break;
			}	
		}

		if(break_for)
			break;
	}


	if(fill_sudoku(table) == FULL)
		return FULL;
		
	if(fill_sudoku(table_alternative) == FULL){
		copy_table(table, table_alternative);
		return FULL;
	}

	return FALSE;
}

void copy_table(byte table_to[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH], byte table_from[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]){

	for(byte i = 0; i< TABLE_LENGTH; i++){
		for(byte j = 0; j< TABLE_HEIGHT; j++){
			for(byte k= 0; k< TABLE_DEPTH; k++){
				table_to[i][j][k] = table_from[i][j][k];
			}
		}
	}
}

byte check_sudoku_validity(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]){

	for (byte i = 0; i < TABLE_LENGTH; ++i){
		for (byte k = 1; k < TABLE_DEPTH; ++k){
			
			byte found = FALSE;
			for (byte j = 0; j < TABLE_HEIGHT; ++j){
				if(table[i][j][0] == EMPTY)
					continue;

				if(table[i][j][0] == k && !found){
					found = TRUE;
					continue;
				}

				if(table[i][j][0] == k && found)
					return FALSE;
			}

		}
	}


	for (byte j = 0; j < TABLE_LENGTH; ++j){
		for (byte k = 1; k < TABLE_DEPTH; ++k){
			
			byte found = FALSE;
			for (byte i = 0; i < TABLE_HEIGHT; ++i){
				if(table[i][j][0] == EMPTY)
					continue;

				if(table[i][j][0] == k && !found){
					found = TRUE;
					continue;
				}

				if(table[i][j][0] == k && found)
					return FALSE;
			}

		}
	}

	for (byte li = 0; li < TABLE_LENGTH; li+=3){
		for (byte lj = 0; lj < TABLE_HEIGHT; lj+=3){
			
			for (byte k = 1; k < TABLE_DEPTH; ++k){
				byte found = FALSE;
				for(byte i = li; i < li+3; i++){
					for(byte j = lj; j < lj+3; j++){

						if(table[i][j][0] == EMPTY)
							continue;

						
						if(table[i][j][0] == k && !found){
							found = TRUE;
							continue;
						}

						if(table[i][j][0] == k && found)
							return FALSE;
					}
				}
			}

		}
	}

	return TRUE;

}

