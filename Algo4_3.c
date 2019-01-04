#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS

void Sorting(int *arr, int left, int right);
void quick_sort(int *arr, int left, int right);
int partition(int *arr, int left, int right);
int heap_size(int *arr);
void InsertSort(int *arr, int n);

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

	Sorting(arr, 0, heap_size(arr) - 1);

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

void Sorting(int *arr, int left, int right) {
	int n = 1000;

	InsertSort(arr, n);
	quick_sort(arr, 0, right);
}

void quick_sort(int *arr, int left, int right) {

	if (left < right) { //������ ������ �� �� �̻��̸� 
		int q = partition(arr, left, right); //pivot�� ���ؼ� ����, ������ ����
		quick_sort(arr, left, q - 1); //pivot�� ���� �� ��Ʈ
		quick_sort(arr, q + 1, right); //pivot�� ������ �� ��Ʈ
	}
}

int partition(int *arr, int left, int right) {
	int x, i, j, temp;
	int index;

	//index = left + rand() % (right - left + 1);

	x = arr[right];
	i = left - 1;

	for (j = left; j <= right - 1; j++) {
		if (arr[j] <= x) {
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	temp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = temp;

	return i + 1;
}

int heap_size(int *arr) { //arr�� ũ��
	return (_msize((void*)arr) / sizeof(int));
}

void InsertSort(int *arr, int n) {
	int i, j, k;
	int num;

	for (k = 0; k < n; k++) {
		for (i = 1; i < n; i++) {
			for (j = 0; j < i;j++) {
				if (arr[i] < arr[j]) {
					num = arr[i];
					arr[i] = arr[j];
					arr[j] = num;
					break;
				}
			}
		}
	}
}