#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>


struct arrnum{
	int low;
	int high;
	int is_st;
};

int *arr;
void merge(int left, int right, int mid) {
	int first_half = mid - left +1;
	int second_half = right - mid;
	int first[first_half];
	int last[second_half];
	
	int i, j;
	for (i = 0; i < first_half; i++) {
		first[i] = arr[left+i];
	} 

	for (j = 0; j < second_half; j++) {
		last[j] = arr[mid+1+j];
	}

	i = 0; j = 0;
	int k;
	k = left;
	while (i < first_half && j < second_half) {
		if (first[i] <= last[j]) {
			arr[k] = first[i];
			i++;		
		} else {
			arr[k] = last[j];
			j++;
		}
		k++;
	}

	while (i < first_half) {
		arr[k] = first[i];
		i++; k++;
	}

	while (j < second_half) {
		arr[k] = last[j];
		j++; k++;	
	}

}

void mergesort(int left, int right) {
	if (left < right) {
		int mid = (left + (right -1))/2;
		mergesort(left, mid);
		mergesort(mid+1, right);
		merge(left, mid, right);
	}
}


/*
int print_contents(int arr[]) {
	int i = 0;
	int n = sizeof(arr)/sizeof(arr[0]);
	for (i; i < n; i++) {
		printf("%d ", arr[i]);
	}
	return 0;	
}
*/

void *helper(void *param) {
	struct arrnum *tmp = param;
	if (tmp->is_st == 1) {
		mergesort(tmp->low, tmp->high);
	} else {
		int mid = (tmp->low + tmp->high)/2;
		merge(tmp->low, mid, tmp->high);
	}
	//pthread_exit(0);
	//return 0;

}


int main(int argc, char *argv[]) {
	// Create threads
	FILE *file;
	//file = fopen("input.txt", "r");

	//char *f = argv[1];
	file = fopen(argv[1], "r");
	char *nums = NULL;
	size_t len = 0;
	int n = -1;
	ssize_t line;
	while ((line = getline(&nums, &len, file)) != -1) {
		n++;
	}
	
	arr = malloc(n*sizeof(int));
	file = fopen(argv[1], "r");
	printf("The original input numbers are: \n");
	int i = 0;
	while ((line = getline(&nums, &len, file)) != -1) {
		arr[i] = atoi(nums);
		i++;
		printf("%s", nums);
	}


	pthread_t thread_a;
	pthread_t thread_b;
	pthread_t thread_ab;

	struct arrnum t_a;
	t_a.low = 0;
	t_a.high = (n/2);
	t_a.is_st = 1;
	printf("\nFirst thread has the following numbers: \n");
	for (i = 0; i <= t_a.high; i++) {
		printf("%d ", arr[i]);
	}

	struct arrnum t_b;
	t_b.low = (n/2) + 1;
	t_b.high = n;
	t_b.is_st = 1;
	printf("\nSecond thread has the following numbers: \n");
	for (i = t_b.low; i <= t_b.high; i++) {
		printf("%d ", arr[i]);
	}

	struct arrnum t_ab;
	t_ab.low = 0;
	t_ab.high = n;
	t_ab.is_st = 0;

	pthread_create(&thread_a, NULL, helper, &t_a);
	pthread_create(&thread_b, NULL, helper, &t_b);
	
	//pthread_create(&thread, NULL, mergesort, &arr);
	pthread_join(thread_a, NULL);
	pthread_join(thread_b, NULL);

	pthread_create(&thread_ab, NULL, helper, &t_ab);
	pthread_join(thread_ab, NULL);

	printf("\nThe final sorted array is: \n");
	for (i = 0; i <= n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	pthread_exit(0);

	return 0;
}
