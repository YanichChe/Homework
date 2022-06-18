#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

bool input_array(int* array, int array_len)
{
	for (int i = 0; i < array_len; i++) {
		if (scanf("%d", &array[i]) != 1) {
			return false;
		}
	}
	return true;
}

bool input_len(int* array_len)
{
	if (scanf("%d", array_len) != 1) {
		return false;
	}
	return true;
}

void swap(unsigned int* a, unsigned int* b) {
	unsigned int tmp = *a;
	*a = *b;
	*b = tmp;
}

void unsigned_radix_sort(unsigned int* from, unsigned int* to, unsigned int bit)
{
	if (!bit || to < from + 1)
		return;

	unsigned int* right = to - 1;
	unsigned int* left = from;

	while (1) {
		while (left < right && !(*left & bit)) left++;
		while (left < right && (*right & bit)) right--;
		if (left >= right)
			break;
		swap(left, right);
	}

	if (!(bit & *left) && left < to) left++;
	bit >>= 1;

	unsigned_radix_sort(from, left, bit);
	unsigned_radix_sort(left, to, bit);
}

void inversion(unsigned int* new_array, int len) {
	for (size_t i = 0; i < len; i++)
		new_array[i] ^= INT_MIN;
}

void radix_sort(int* array, int len)
{
	unsigned* new_array = (unsigned*)array;
	inversion(new_array, len);
	unsigned_radix_sort(new_array, new_array + len, INT_MIN);
	inversion(new_array, len);
}

void print_array(int* array, int array_len) {
	FILE* file = fopen("out.txt", "w");

	for (int i = 0; i < array_len; i++) {
		fprintf(file, "%d ", array[i]);
	}
	fclose(file);
}

int main(void)
{
	int array_len = 20000000;
	if (!input_len(&array_len)) return EXIT_SUCCESS;

	int* array = (int*)malloc(array_len * sizeof(int));
	if (!input_array(array, array_len)) return EXIT_SUCCESS;

	radix_sort(array, array_len);
	print_array(array, array_len);

	free(array);
	return EXIT_SUCCESS;
}