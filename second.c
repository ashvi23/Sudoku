#include<stdio.h>
#include<stdlib.h>
int inrow(int**, int, int); // num to check, row 
int incol(int**, int, int); // num to check, col
int insub(int**, int, int, int); // num to check, row start, col start
int islegal(int**, int, int, int); // num to check, row start, column start
int inrow(int** sudoku, int target, int row){
	int exists = 0;
		for(int j =0; j< 9; j++){
			if (sudoku[row][j] == target){
				exists = 1;
			}
		}
	return exists;
}
int incol(int** sudoku, int target, int col){
	int exists = 0;
		for(int i =0; i< 9; i++){
			if (sudoku[i][col] == target){
				exists = 1;
			}
		}
	return exists;

}
int insub(int** sudoku, int target, int rowstart, int colstart){
	int exists = 0;
	for (int i = rowstart; i< rowstart+3; i++){
		for(int j =colstart; j< colstart+3; j++){
			if (sudoku[i][j] == target){
				exists = 1;
			}
		}
	}
	return exists;
}

int islegal(int** sudoku, int target, int row, int col){
	int legality = 0;
	int rowexist = inrow(sudoku, target, row);
	int colexist = incol(sudoku, target, col);
int trow = row%3;
int tcol = col%3;
int subrow = row- trow;
int subcol = col - tcol;
	int subexist = insub(sudoku, target, subrow, subcol);
//printf("row:%d, col:%d, sub:%d \n", rowexist, colexist, subexist);
	if(rowexist == 0 && colexist == 0 && subexist == 0){
	legality = 1;
	}
	return legality;
}

int main (int argc, char**argv){
FILE* fp;
int** sudoku;
char input;
int enterval; 
sudoku = (int**) malloc(9 * sizeof(int*));
	for (int i=0; i< 9; i++){
		sudoku[i] = (int*) malloc(9 * sizeof(int));
	}
	for(int i =0; i< 9; i++){
			for(int j =0; j< 9; j++){
			sudoku[i][j] = 0;
			}
	}

		if (argc!= 2){
		//printf("not enough arguments");
		return 0;
		}
		fp = fopen(argv[1], "r");
		if(fp == NULL){
			//printf("Error, no input");
			return 0;
		}
		
for (int i=0; i< 9; i++){
	for (int j=0;j< 9; j++){
		fscanf(fp, "%c\t\n", &input);
		if(input == '-'){
			enterval = 0;				
			sudoku[i][j] = enterval;
		}
		else if(input == '1' ||input == '2' ||input == '3' ||input == '4' ||input == '5' ||input == '6' ||input == '7' ||input == '8' ||input == '9') {
			enterval = input-'0';
			sudoku[i][j] = enterval;
		}			
	}
}

int possibilities=0;
int possibleinp =0;
int inputted=1;
int legal=0;
int dashesexist; 
	for (int i = 0; i< 9; i++){
		for(int j =0; j< 9; j++){
			if (sudoku[i][j] == 0){
				dashesexist = 1;
			}
		}
	}
while(dashesexist == 1 && inputted ==1){
inputted = 0;
for (int i = 0; i< 9; i++){
		for(int j = 0; j< 9; j++){
			possibilities = 0;
			possibleinp = 0;
			if (sudoku[i][j] == 0){
				for(int trynum =1; trynum<=9; trynum++){
					legal = islegal(sudoku, trynum, i, j);
					if(legal ==1){
						possibilities++;
						possibleinp = trynum;

					}
				}
				if (possibilities == 1){ // input the number no guessing needed
				sudoku[i][j] = possibleinp;
				inputted =1;
				}
				
			}// if sudoku ij ==0
		}//for j
	} // for i 
}

dashesexist =0;
	for (int i = 0; i< 9; i++){
		for(int j =0; j< 9; j++){
			if (sudoku[i][j] == 0){
				//printf("i:%d j:%d \n", i, j );
				dashesexist = 1;
			}
		}
	}

if(dashesexist == 1){
printf("no-solution");
return 0;
}

int* countarr;
countarr = (int*)malloc(9*sizeof(int));
for(int n = 0; n<9;n++){
countarr[n] = 0;
}
for (int i = 0; i< 9; i++){
	for(int j =0; j< 9; j++){
		int val = sudoku[i][j];
		val = val-1;
		int curcount = countarr[val];
		countarr[val]= curcount +1;
	}

}

for (int i = 0; i< 9; i++){
	if(countarr[i] != 9){
	printf("no-solution");
	return 0;
	}
}

if(dashesexist == 0){
for (int i = 0; i< 9; i++){
		for(int j =0; j< 9; j++){
			
			if(j+1 !=9){
				printf("%d\t", sudoku[i][j]);
			}
			else if (j+1 == 9){
				printf("%d", sudoku[i][j]);
			}
		}
		if(i+1 !=9){
		printf("\n");
		}
	}
} //else if dashes = 0
for(int i=0; i< 9; i++){
	free(sudoku[i]);
}
free(sudoku);
free(countarr);
fclose(fp);
return 0;
}
