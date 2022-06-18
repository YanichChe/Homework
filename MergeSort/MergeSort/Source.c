#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void merge_sort(int* array, int left, int right);
void merge(int* array, int left, int middle, int right);  
void g(int n);
void c();
void s();
int main(int argc, char **argv) {
	/*if (strcmp(argv[1], "-s") == 0) {
		s();
	}*/
	s();
	return 1;
}

void g(int n) {
	FILE* fp;
	char name[] = "out.txt";
	fp = fopen(name, "a");
	for (int i = 0; i < n; i++) {
		fprintf(fp,"%d\n",rand());
	}
	fclose(fp);
}

void c() {
	FILE* fp;
	char name[] = "in.txt";
	fp = fopen(name, "r");
	int len;
	fscanf(fp,"%d",&len);
	int last;
	fscanf(fp, "%d", &last);
	for (int i = 1; i < len; i++) {
		int new;
		fscanf(fp, "%d", &new);
		if (new < last) {
			printf("%d", i + 1);
			break;
		}
		last = new;
	}
	fclose(fp);
}
void s() {
	FILE* fp, *fp1;
	char name[] = "in.txt";
	char name1[] = "out.txt";
	fp = fopen(name, "r");
	fp1 = fopen(name1, "a");
	int len;
	fscanf(fp, "%d", &len);
	int *array = (int*)malloc(len * sizeof(int));
	for (int i = 0; i < len; i++) {
		fscanf(fp, "%d", &array[i]);
	}
	merge_sort(array, 0, len-1);
	for (int i = 0; i < len; i++) {
		fprintf(fp1, "%d ", array[i]);
	}
	fclose(fp1);
	fclose(fp);
}

void merge_sort(int *array, int left, int right) {
	if (left < right) {
		int middle = left + (right - left) / 2;
		merge_sort(array, left, middle);
		merge_sort(array, middle + 1, right);
		merge(array, left, middle, right);
	}
}

void merge(int* array, int left, int middle, int right) {
	int len1 = middle - left + 1;
	int len2 = right - middle;
	int *first_array = (int*)malloc(len1 * sizeof(int));
	int *second_array = (int*)malloc(len2 * sizeof(int));
	for (int i = 0; i < len1; i++) {
		first_array[i] = array[left + i];
	}
	for (int j = 0; j < len2; j++) {
		second_array[j] = array[middle + 1 + j];
	}
	int i = 0;
	int k = left;
	int j = 0;
	while (i < len1 && j < len2) {
		if (first_array[i] <= second_array[j]) {
			array[k++] = first_array[i++];
		}
		else {
			array[k++] = second_array[j++];
		}
	}
	while (i < len1) {
		array[k++] = first_array[i++];
	}
	while (j < len2) {
		array[k++] = second_array[j++];
	}
}