#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct {
	int low;
	int high;
} Array;

void merge(int a, int b) {

}

void *mergesort(void *arr) {

}

int main() {
	// Create threads
	FILE *file;
	file = fopen("input.txt", "r");

	pthread_t thread;
	pthread_create(&thread, NULL, mergesort, &arr);
	pthread_join(thread, NULL);
	return 0;
}
