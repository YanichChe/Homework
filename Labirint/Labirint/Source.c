#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/////////////////////// INPUT ///////////////////////

int input_len(FILE* file_input)
{
	int len;

	if (fscanf(file_input, "%d", &len) != 1) {
		return -1;
	}

	return len;
}

int** input_matrix(FILE* file_input, int len)
{
	int** matrix = (int**)malloc(len * sizeof(int*));

	for (int i = 0; i < len; i++) {
		matrix[i] = malloc(len * sizeof(int));

		for (int j = 0; j < len; j++) {
			if (fscanf(file_input, "%d", &matrix[i][j]) != 1) {
				return NULL;
			}
		}
	}

	return matrix;
}

int** create_solution_table(int n)
{
	int** solution = (int**)calloc(n, sizeof(int));

	for (int i = 0; i < n; i++) {
		solution[i] = (int*)calloc(n, sizeof(int));
	}

	return solution;
}

/////////////////////// CHECK_INPUT ///////////////////////

bool check_len(int len) 
{
	if (len <= 1) {
		return false;
	}

	return true;
}

bool check_matrix(int** matrix, int len) 
{
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (matrix[i][j] != 0 && matrix[i][j] != 1) {
				return false;
			}
		}
	}

	return true;
}


/////////////////////// STRUCTUR DATA ///////////////////////

typedef struct _data Data;
struct _data 
{
	int** matrix;
	int** solution;
	int n;
	FILE* file_output;
};

Data* create_data(FILE* file_input, FILE* file_output) 
{
	Data* data = malloc(sizeof(Data));
	data->file_output = file_output;

	int len = input_len(file_input);
	data->n = len;

	int** matrix = input_matrix(file_input, len);
	data->matrix = matrix;

	int** solution = create_solution_table(len);
	data->solution = solution;

	return data;
}

/////////////////////// OUTPPUT ///////////////////////

void print_solution(Data* data) 
{
	for (int i = 0; i < data->n; i++) {
		for (int j = 0; j < data->n; j++) {
			if (data->solution[i][j] == 1) {
				fprintf(data->file_output, "* ");
			}
			else {
				fprintf(data->file_output, "%d ", data->solution[i][j]);
			}
		}
		fprintf(data->file_output, "\n");
	}
}

void print_error(Data* data) {
	fprintf(data->file_output, "WRONG INPUT");
}

///////////////////// SOLUTION ///////////////////////

bool is_safe(Data* data, int x, int y)
{
	if (x >= 0 && x < data->n && y >= 0 && y < data->n && data->matrix[x][y] == 0 && data->solution[x][y] == 0) {
		return true;
	}
	return false;
}

bool find_way(Data* data, int x, int y)
{
	int n = data->n;

	if (x == n - 1 && y == n - 1) {
		data->solution[x][y] = 1;
		print_solution(data);
		return true;
	}

	if (is_safe(data, x, y)) {
		data->solution[x][y] = 1;

		if (find_way(data, x + 1, y))
			return true;
		if (find_way(data, x - 1, y))
			return true;
		if (find_way(data, x, y - 1))
			return true;
		if (find_way(data, x, y + 1))
			return true;

		data->solution[x][y] = 0;

		return false;
	}

	return false; 
}

void solve_maze(Data* data)
{
	if (!find_way(data, 0, 0)) {
		fprintf(data->file_output, "NO SOLUTIONS");
		return;
	}
}

////////////////////// FREE MEMORY ///////////////////////

void free_two_dimensional_array(int** array, int n) 
{
	for (int i = 0; i < n; i++) {
		free(array[i]);
	}
	free(array);

}

void free_data(Data* data) 
{
	free_two_dimensional_array(data->matrix, data->n);
	free_two_dimensional_array(data->solution, data->n);
	free(data);
}

/////////////////////// MAIN ///////////////////////

int main(int argc, char** argv)
{
	char* file_input_name = argv[1];
	char* file_output_name = argv[2];

	FILE* file_input;
	FILE* file_output;

	if ((file_input = fopen(file_input_name, "r")) == NULL)
		return EXIT_SUCCESS;

	if ((file_output = fopen(file_output_name, "w")) == NULL)
		return EXIT_SUCCESS;

	Data* data = create_data(file_input, file_output);
	
	if (!check_len(data->n) || !check_matrix(data->matrix, data->n))
	{
		print_error(data);
		free_data(data);
		return EXIT_SUCCESS;
	}

	solve_maze(data);

	fclose(file_input);
	fclose(file_output);

	free_data(data);

	return EXIT_SUCCESS;
}
