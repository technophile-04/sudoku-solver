#include<stdio.h>
#include<stdlib.h>

const int rows = 9;
const int cols = 9;

void printBoard(int board[rows][cols]){

	int i, j;

	printf("-------------------------------\n");

	for (i = 0; i < rows; ++i)
	{
		printf("|");

		for(j = 0; j < cols; ++j){
			printf(" %d ",board[i][j]);
			if((j+1) % 3 == 0){
				printf("|");
			}
		}
		printf("\n");

		if((i+1) % 3 == 0){
			printf("-------------------------------\n");
		}
	}
}

bool isValid(int board[rows][cols], int x, int y, int val){
	for(int j = 0; j < cols; j++){
		if(board[x][j] == val){
			return false;
		}
	}

	for(int i = 0; i < rows; i++){
		if(board[i][y] == val){
			return false;
		}
	}

	int smI = (x / 3) * 3;
	int smJ = (y / 3) * 3;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[smI + i][smJ + j] == val){
				return false;
			}
		}
	}

	return true;
}

void sudokuSolver(int board[rows][cols], int i, int j,bool &isValidSudoku){

	if(i == rows){
		isValidSudoku = true;
		printf("The state of board after : \n");
		printBoard(board);
		return;
	}

	int nextI= 0,nextJ = 0;

	if(j == cols - 1){
		nextI = i + 1;
		nextJ = 0;
	}else {
		nextI = i;
		nextJ = j + 1;
	}

	if(board[i][j] != 0){
		sudokuSolver(board, nextI, nextJ,isValidSudoku);
	}else{

		for(int possibleAnswer = 1; possibleAnswer <= 9; possibleAnswer++)
		{
			if(isValid(board, i , j , possibleAnswer)){
				board[i][j] = possibleAnswer;
				sudokuSolver(board, nextI, nextJ, isValidSudoku);
				board[i][j] = 0;
			}
		}

	}

}

int main(){

	int board[rows][cols];
	bool isValidSudoku = false;


	for (int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j){
			scanf("%d", &board[i][j]);
		}
	}

    printf("The state of board before : \n");   

  	printBoard(board);

  	sudokuSolver(board, 0, 0, isValidSudoku);

  	if(!isValidSudoku){
  		printf("Please enter a valid sudoku!");
	
  	}

  	

	return 0;
}