#pragma once

#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;

void printArr(int a[], int N) {
	cout << endl;
	for (int i = 0; i < N; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
void swap(int a[], int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
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
void quickSort(int a[], int i, int j) {//主函数
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

//堆排序 O(NlogN)
void heapify(int a[], int p, int n) {
	if (p < 0 || p >= n) {
		return;
	}

	//2个孩子节点的下标
	int c1 = p * 2 + 1;
	int c2 = p * 2 + 2;

	int maxDx = p;
	if (c1 < n && a[c1] > a[maxDx]) {
		maxDx = c1;
	}
	if (c2 < n && a[c2] > a[maxDx]) {
		maxDx = c2;
	}

	if (maxDx != p) {
		swap(a, maxDx, p);
		heapify(a, maxDx, n);//对更改下标的子节点递归调整堆
	}
}
void buildHeap(int a[], int length) {//主函数
	int end_node_dx = length - 1;
	int parent_dx = (end_node_dx - 1) / 2;
	for (int p = parent_dx; p >= 0; p--) {
		heapify(a, p, length);
	}
}
void heapSort(int a[], int N) {
	for (int k = N; k >= 1; k--) {
		buildHeap(a, k);
		swap(a, 0, k - 1);
	}
}

//归并排序 O(NlogN)
void merge(int a[], int L, int mid, int R) {//合并2个有序数组 

	//[L,mid] [mid+1,R]
	int i = L;
	int j = mid + 1;

	//存储结果的数组
	int N = R - L + 1;
	vector<int> r;
	r.reserve(N);

	while (i <= mid && j <= R) { 
		if (a[i] <= a[j]) {
			r.push_back(a[i++]);
		}
		else {
			r.push_back(a[j++]);
		}
	}
	while (i <= mid) {
		r.push_back(a[i++]);
	}
	while (j <= R) {
		r.push_back(a[j++]);
	}

	//覆盖原数组
	/*for (int i = 0; i < N; i++) {//错误做法
		a[i] = r[i];
	}*/
	int d = 0;
	for (int i = L; i <= R; i++) {//肯定是需要在当前排序的实际位置(L,R)上赋最终的值
		a[i] = r[d++];
	}
}
void mergeSort(int a[], int L, int R) {//主函数
	if (L < R)
	{
		int mid = L + (R - L) / 2;
		mergeSort(a, L, mid);
		mergeSort(a, mid + 1, R);
		merge(a, L, mid, R);
	}
}

//int main() {
//	int a[10] = { 9,8,7,6,5,4,3,2,1,0 };
//	// 2 4 5 1 8
//	//
//	printArr(a, 10);
//	//selectSort(a, 5);
//	//insertSort(a, 5);
//	//quickSort(a, 0, 4);
//	//heapSort(a, 10);
//	mergeSort(a, 0, 9);
//	printArr(a, 10);
//}