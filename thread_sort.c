#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int low;
	int high;
} Array;

void merge(int arr[], int left, int right, int mid) {

}

void mergesort(int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + (right -1))/2;
		mergesort(arr, left, mid);
		mergesort(arr, mid+1, right);
	}
}

int *readfile(char *filename) {
	FILE *file;
	file = fopen(filename, "rt");
	char line[80];
	int len = 0;
	while (fgets(line, 80, file) != NULL) {
		len += 1;
	}
	
	int i = 0, j;
	int *inp = malloc(len*sizeof(int));

	while (fgets(line, 80, file) != NULL) {
		sscanf(line, "%d", &j);
		inp[i] = j;
		i++;
	}
	fclose(file);

	return inp;
	
}

int main(int argc, char *argv[]) {
	// Create threads
	FILE *file;
	file = fopen("input.txt", "r");

	char *f = argv[1];
	int *arr = readfile(f);

	pthread_t thread;
	pthread_create(&thread, NULL, mergesort, &arr);
	pthread_join(thread, NULL);
	return 0;
}
