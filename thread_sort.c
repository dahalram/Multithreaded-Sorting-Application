#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int low;
	int high;
} Array;

void merge(int arr[], int left, int right, int mid) {
	int first_half = mid - left +1;
	int second_half = right - mid;
	int first[first_half];
	int last[second_half];

	for (int i = 0; i < first_half; i++) {
		first[i] = arr[left+i];
	} 

	for (int j = 0; j < second_half; j++) {
		last[j] = arr[mid+1+j];
	}

	int i = 0; j = 0, k = left;
	while (i < first_half && j < second_half) {
		if (first[i] <= last[j]) {
			arr[k] = first[i];
			i++;		
		} else {
			arr[k] = second[j];
			j++;
		}
		k++;
	}

	while (i < first_half) {
		arr[k] = first[i];
		i++; k++;
	}

	while (j < second_half) {
		arr[k] = second[j];
		j++; k++;	
	}

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
	//file = fopen("input.txt", "r");

	char *f = argv[1];
	int *arr = readfile(f);

	pthread_t thread;
	pthread_create(&thread, NULL, mergesort, &arr);
	pthread_join(thread, NULL);
	return 0;
}
