#pragma once

#include<iostream>
using std::cout;
using std::endl;

void printArr(int a[], int N) {
	cout << endl;
	for (int i = 0; i < N; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
//选择排序 O(N²)
void selectSort(int a[], int N) {
	for (int i = 0; i < N; i++) {
		int minDx = i;
		for (int j = i; j < N; j++) {
			if (a[j] < a[minDx]) {
				minDx = j;
			}
		}
		int tmp = a[i];
		a[i] = a[minDx];
		a[minDx] = tmp;
	}
}
//插入排序 O(N²)
void insertSort(int a[], int N) {
	for (int i = 0; i < N; i++) {
		int cur = a[i];
		int j = i - 1;
		for (; j >= 0 && a[j] >= cur; j--) {
			a[j + 1] = a[j];
		}
		a[j + 1] = cur;
	}
}
//冒泡排序 O(N²)
void bubbleSort(int a[], int N) {
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (a[j] < a[j + 1]) {
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}
//快速排序 O(NlogN)
int find(int a[], int i, int j) {
	int val = a[i];
	int L = i;
	int R = j;
	while (L < R)
	{
		while (L<R && a[R] > val) {
			R--;
		}
		a[L] = a[R];
		while (L < R && a[L] < val) {
			L++;
		}
		a[R] = a[L];
	}
	a[L] = val;
	cout << "val = " << val << " , L = " << L << endl;
	return L;
}
void quickSort(int a[], int i, int j) {
	if (i < j)
	{
		int mid = find(a, i, j);
		quickSort(a, i, mid - 1);
		quickSort(a, mid + 1, j);
	}
	/*
	这里应该用if，while是错的，如果是while，那么主递归(i,j)是满足执行，子递归经历mid后，
	子递归执行(i,j)不满足，
	子递归可以退出，但是主递归的(i,j)不会被修改，还是满足继续死循环，所以应该用if。例如：
	int a[] =  {3,1,9,2,5} ;
	主递归：（即当前执行的 {3,1}小块的递归）：
	quickSort(0,1)
		int mid = find(0,1); //mid = 1
		quickSort(0,0);
		quickSort(2,1);
		//这里2个子递归直接退出，因为不满足i<j，但是主递归(i,j)仍是(0,1)，若是while(0<1)则继续循环
		//若是if，则子递归退出执行完毕，主递归也退出完毕
	*/
}
//int main() {
//	int a[5] = { 3,1,9,2,5 };
//	// 2 4 5 1 8
//	//
//	printArr(a, 5);
//	//selectSort(a, 5);
//	//insertSort(a, 5);
//	quickSort(a, 0, 4);
//	printArr(a, 5);
//}