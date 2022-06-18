#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/////////////////////// CHECK_ERRORS ///////////////////////

bool check_conditions(int row, int column, int row_queen, int column_queen) 
{
	if (row == row_queen)
		return true;
	else if (row + column == row_queen + column_queen)
		return true;
	else if (row_queen - column_queen == row - column)
		return true;
	return false;
}

bool check_place(int* board, int row, int column, int n) 
{
	for (int i = 0; i < n; i++) {
		if (board[i] != 0 && check_conditions(row, column, board[i], i + 1)) {
			return false;
		}
	}
	return true;
}

bool check_len(int n) {
	if (n <= 0) {
		return true;
	}
	return false;
}

/////////////////////// OUTPUT ///////////////////////

void print_solution(int* board, int n, FILE* solution_data)
{
	for (int i = 0; i < n; i++) {
		fprintf(solution_data, "%d ", board[i]);
	}
	fprintf(solution_data, "\n");
}

void print_board(int* solution, int n, FILE* file_output) 
{
	for (int i = 0; i < n; i++) {
		int index = solution[i] - 1;
		for (int j = 0; j < index; j++) {
			fprintf(file_output, "0 ");
		}
		fprintf(file_output, "1 ");
		for (int j = index + 1; j < n; j++) {
			fprintf(file_output, "0 ");
		}
		fprintf(file_output, "\n");
	}
	fprintf(file_output, "------------------------\n");
}

/////////////////////// BACKTRACKING ///////////////////////

void back_tracking(int* board, int n, int position, FILE* solution_data, int* count) 
{
	if (position == n) {
		*count += 1;
		print_solution(board, n, solution_data);
		return;
	}
	for (int k = 1; k < n + 1; k++) {
		if (check_place(board, k, position + 1, n)) {
			board[position] = k;
			back_tracking(board, n, position + 1, solution_data, count);
			board[position] = 0;
		}
	}
}

//////////////////////////////////////////////

int* create_board(int n) 
{
	int* board = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		board[i] = 0;
	}
	return board;
}

 int* create_solution(int n, FILE* solution_data) 
{
	int* solution = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		fscanf(solution_data, "%d", &solution[i]);
	}
	return solution;
}

void fill_output(FILE* file_output, int count, FILE* solution_data, int n)
{
	fprintf(file_output, "%d\n", count);

	for (int j = 0; j < count; j++) {
		int* solution = create_solution(n, solution_data);
		print_board(solution, n, file_output);
		free(solution);
	}
}
//////////////////////////////////////////////

int main(int argc, char** argv)
{
	int n = atoi(argv[1]);
	char* file_name = argv[2];

	FILE* file_output;
	FILE* solution_data;

	if ((file_output = fopen(file_name, "w")) == NULL)
		return EXIT_SUCCESS;

	if ((solution_data= fopen("solutionData.txt", "w")) == NULL)
		return EXIT_SUCCESS;

	if (check_len(n)) {
		fprintf(file_output, "No solutions");
		return EXIT_SUCCESS;
	}

	int* board = create_board(n);
	int count = 0;

	back_tracking(board, n, 0, solution_data, &count);
	fclose(solution_data);

	if ((solution_data = fopen("solutionData.txt", "r")) == NULL)
		return EXIT_SUCCESS;

	if (count == 0) {
		fprintf(file_output, "No solutions");
		return EXIT_SUCCESS;
	}

	fill_output(file_output, count, solution_data, n);

	fclose(solution_data);
	fclose(file_output);

	free(board);
	return EXIT_SUCCESS;
}
