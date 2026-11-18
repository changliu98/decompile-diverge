

#include <stdio.h>

#include <assert.h>

#include <stdlib.h>



void heapify(int heap[], int n, int i) {

    int smallest = i;

    int l = 2 * i + 1;

    int r = 2 * i + 2;



    if (l < n && heap[l] < heap[smallest])

        smallest = l;



    if (r < n && heap[r] < heap[smallest])

        smallest = r;



    if (smallest != i) {

        int temp = heap[i];

        heap[i] = heap[smallest];

        heap[smallest] = temp;

        heapify(heap, n, smallest);

    }

}



void buildHeap(int heap[], int n) {

    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--) {

        heapify(heap, n, i);

    }

}



void func0(int heap[], int n, int a, int* outHeap) {
  buildHeap(heap, n);
  if (a < heap[0]) return;
  heap[0] = a;
  heapify(heap, n, 0);
  for (int i = 0; i < n; i++) {
    outHeap[i] = heap[i];
  }
}
