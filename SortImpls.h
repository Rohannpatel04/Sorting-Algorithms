#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
#include <vector>
using namespace std;

void BubbleSort(vector<int>& v, int first, int last) {
  // nothing to sort when the last index of the vector is 0 because
  // there is only 1 integer in the vector
  if (last == 0) return;

  int i, j;
  for (i = 0; i < last; i++) {
    for (j = 0; j < last; j++)
      // If they are out of order swap the two elements
      if (v[j] > v[j + 1]) {
        int temp;
        temp = v[j];
        v[j] = v[j + 1];
        v[j + 1] = temp;
      }
  }
}

void InsertionSort(vector<int>& v, int first, int last) {
  for (int i = 1; i <= last; i++) {
    int temp = v[i];
    int j = i - 1;

    while (j >= 0 && v[j] > temp) {
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = temp;
  }
}

void QuickSort(vector<int>& v, int first, int last) {
  if (first >= last) {
    return;
  }

  int left = first;
  int right = last;
  int pivot = v[(first + last) / 2];

  while (left <= right) {
    while (left <= right && v[left] < pivot) {
      left++;
    }
    while (left <= right && v[right] > pivot) {
      right--;
    }

    if (left <= right) {
      swap(v[left], v[right]);
      left++;
      right--;
    }
  }

  QuickSort(v, first, right);
  QuickSort(v, left, last);
}

void ShellSort(vector<int>& v, int first, int last) {
  int gap = last / 2;

  while (gap > 0) {
    int j = 0;
    for (int i = gap; i <= last; i++) {
      int temp = v[i];
      for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
        v[j] = v[j - gap];
      }
      v[j] = temp;
    }
    gap = gap / 2;
  }
}

void merge(vector<int>& v, int first, int middle, int last) {
  int size = last - first + 1;
  int* temp;
  temp = new int[size];
  int f1 = first;
  int l1 = middle;
  int f2 = middle + 1;
  int l2 = last;
  int i = 0;

  while ((f1 <= l1) && (f2 <= l2)) {
    if (v[f1] < v[f2]) {
      temp[i] = v[f1];
      f1++;
    } else {
      temp[i] = v[f2];
      f2++;
    }
    i++;
  }

  while (f1 <= l1) {
    temp[i] = v[f1];
    f1++;
    i++;
  }

  while (f2 <= l2) {
    temp[i] = v[f2];
    f2++;
    i++;
  }

  for (i = 0; i < size; i++) {
    v[first] = temp[i];
    first++;
  }
  delete[] temp;
}

void MergeSort(vector<int>& v, int first, int last) {
  if (first < last) {
    int middle = (first + last) / 2;
    MergeSort(v, first, middle);
    MergeSort(v, middle + 1, last);
    merge(v, first, middle, last);
  }
}

void mergeI(vector<int>& v, vector<int>& temp, int first, int middle,
            int last) {
  int size = last - first + 1;
  int f1 = first;
  int l1 = middle;
  int f2 = middle + 1;
  int l2 = last;
  int i = first;

  while ((f1 <= l1) && (f2 <= l2)) {
    if (v[f1] < v[f2]) {
      temp[i] = v[f1];
      f1++;
    } else {
      temp[i] = v[f2];
      f2++;
    }
    i++;
  }

  while (f1 <= l1) {
    temp[i] = v[f1];
    f1++;
    i++;
  }

  while (f2 <= l2) {
    temp[i] = v[f2];
    f2++;
    i++;
  }
}

int min(int x, int y) { return (x < y) ? x : y; }

void IterativeMergeSort(vector<int>& v, int first, int last) {
  int p, i, low, mid, high;
  int size = (last - first) + 1;
  int counter = 1;
  vector<int> temp(size);
  for (p = 1; p <= last; p = p * 2) {
    for (i = first; i < last; i += p * 2) {
      low = i;
      high = min(i + (2 * p) - 1, last);
      mid = min((i + p) - 1, last);

      if (counter % 2 != 0) {
        mergeI(v, temp, low, mid, high);
      }

      if (counter % 2 == 0) {
        mergeI(temp, v, low, mid, high);
      }
    }
    counter++;
  }

  if (p / 2 < last) {
    mergeI(v, temp, 0, p / 2, size - 1);
  }

  if (counter % 2 != 0) {
    for (i = 0; i < size; i++) {
      v[first] = temp[i];
      first++;
    }
  }
}
#endif
