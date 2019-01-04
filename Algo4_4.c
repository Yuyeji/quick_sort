#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS

void quick_sort(int *arr, int left, int right);
int partition(int *arr, int left, int right, int mid);
int heap_size(int *arr);
int getMid(int *arr, int left, int right);
void generalSort(int *arr,int left,int right);

int main(void) {
	int *arr; // 파일의 데이터를 저장할 포인터 변수 선언.
	int size = 1;
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("test1.txt", "r");

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	arr = (int *)malloc(sizeof(int));

	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[size - 1]);
		size++;
	}

	startTime = clock();

	quick_sort(arr, 0, heap_size(arr) - 1);

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);


	for (int j = 0; j < heap_size(arr); j++) {
		printf("%d\t", arr[j]);
	}

	printf("측정 시간 : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // 테스트 보기 위해.

}

int heap_size(int *arr) { //arr의 크기
	return (_msize((void*)arr) / sizeof(int));
}

void quick_sort(int *arr, int left, int right) {
	int size = right - left + 1;

	if (size < 3) { 
		generalSort(arr, left, right); //크기가 3보다 작을 경우 일반적인 정렬.
	}else{ 
		int mid = getMid(arr, left, right); //중앙값을 pivot으로 설정
		int q = partition(arr, left, right, mid); //pivot을 구해서 왼쪽, 오른쪽 정렬
		quick_sort(arr, left, q - 1); //pivot의 왼쪽 퀵 소트
		quick_sort(arr, q + 1, right); //pivot의 오른쪽 퀵 소트
	}
}

int partition(int *arr, int left, int right, int mid) {
	int i, j, temp;
	int index;

	i = left - 1;

	for (j = left; j <= right - 1; j++) {
		if (arr[j] <= mid) { //mid보다 작으면
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//pivot을 중간으로 위치
	temp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = temp;

	return i + 1; //pivot의 위치 반환
}

void generalSort(int *arr, int left, int right) {
	int size = right - left + 1;
	int temp;

	if (size <= 1)
		return;
	if (size == 2) {
		if (arr[left] > arr[right]) {
			temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
		return;
	}
}

int getMid(int *arr, int left, int right) {
	int i = left;
	int j = (right - left) / 2;
	int k = right;
	int mid;

	if (i < j) {    //  i j     k
		if (j < k) {    // i j k 
			mid = j;
		}else {
			if (i < k) {   // i k j
				mid = k;
			}else {        // k i j
				mid = i;
			}
		}
	}else {        // j i    k 
		if (i < k) {    // j i k 
			mid = i;
		}else {
			if (j < k) {   // j k i
				mid = k;
			}else {        // k j i
				mid = j;
			}
		}
	}

	return mid;
}