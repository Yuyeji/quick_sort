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
	int *arr; // ������ �����͸� ������ ������ ���� ����.
	int size = 1;
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("test1.txt", "r");

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
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

	printf("���� �ð� : %f\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // �׽�Ʈ ���� ����.

}

int heap_size(int *arr) { //arr�� ũ��
	return (_msize((void*)arr) / sizeof(int));
}

void quick_sort(int *arr, int left, int right) {
	int size = right - left + 1;

	if (size < 3) { 
		generalSort(arr, left, right); //ũ�Ⱑ 3���� ���� ��� �Ϲ����� ����.
	}else{ 
		int mid = getMid(arr, left, right); //�߾Ӱ��� pivot���� ����
		int q = partition(arr, left, right, mid); //pivot�� ���ؼ� ����, ������ ����
		quick_sort(arr, left, q - 1); //pivot�� ���� �� ��Ʈ
		quick_sort(arr, q + 1, right); //pivot�� ������ �� ��Ʈ
	}
}

int partition(int *arr, int left, int right, int mid) {
	int i, j, temp;
	int index;

	i = left - 1;

	for (j = left; j <= right - 1; j++) {
		if (arr[j] <= mid) { //mid���� ������
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//pivot�� �߰����� ��ġ
	temp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = temp;

	return i + 1; //pivot�� ��ġ ��ȯ
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