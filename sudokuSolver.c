/* Header files */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/* Sudoku dimension */
const int rows = 9;
const int cols = 9;

/* Helper variables */
int count = 0;
bool isValidSudoku = false;

/* setting output colors and showing output */
void red () {
  printf("\033[0;31m");
}

void purple() {
  printf("\033[0;95m");
}

void green () {
	printf("\033[0;32m");
}

void blue () {
	printf("\033[0;34m");
}

void reset () {
  printf("\033[0m");
}

void newLine(){
	printf("\n");
}

void greet(){
	newLine();
	purple();
	printf("|-------------------------|\n");
	printf("|Welcome to sudoku solver |\n");
	printf("|-------------------------|\n");
	reset();
	newLine();
	
}

void printBoard(int board[rows][cols], int color){

	int i, j;

	if(color == 1){
		green();
		newLine();
		printf("The state of board after : ");
		newLine();
		newLine();
	}

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

	reset();
}

void byeMessage(){
	blue();
	newLine();
	printf("That was quick !, Hope to see you again with new problem :)");
}


/* Taking input and validating input  */
void takeInput(int board[rows][cols]){

	for (int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j){
			int x;
			scanf("%d", &x);
			
			board[i][j] = x;
		}
	}
}

bool validNumbers(int board[rows][cols]){

	for (int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j){
			
			if(board[i][j] > 9 || board[i][j] < 0){
				return false;
			} 

		}
	}

	return true;
}

void checkForValidInput(int board[rows][cols]){
	while(!validNumbers(board)){
		red();
		newLine();
		printf("Please make sure that each number is between 1 to 9, re-enter the sudoku... \n");
		newLine();
		reset();
		takeInput(board);
	}
}



/* Sudoku solver and its helper funtions   */
bool isPossibleNumber(int board[rows][cols], int x, int y, int val){
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

void sudokuSolver(int board[rows][cols], int i, int j){

	if(i == rows){
		isValidSudoku = true;
		printBoard(board, 1);
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
		sudokuSolver(board, nextI, nextJ);
	}else{

		for(int possibleAnswer = 1; possibleAnswer <= 9; possibleAnswer++)
		{
			if(isPossibleNumber(board, i , j , possibleAnswer)){
				board[i][j] = possibleAnswer;
				sudokuSolver(board, nextI, nextJ);
				board[i][j] = 0;
			}
		}

	}

}

void solveSudoku(int board[rows][cols]){
	newLine();
    printf("The state of board before : ");
	newLine();   
	newLine();   

  	printBoard(board, 0);

  	sudokuSolver(board, 0, 0);
}

/* Main funtion */
int main(){

	int board[rows][cols];

	greet();

	printf("Please enter the sudoku you want to solve (make sure there are 81 elements) \n");
	newLine();

	takeInput(board);

	checkForValidInput(board);

	solveSudoku(board);

  	if(!isValidSudoku){
		red();
  		printf("Please enter a valid sudoku next!, The program has ended");
		reset();
  	}

	byeMessage();

	return 0;
}