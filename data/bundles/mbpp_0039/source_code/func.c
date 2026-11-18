#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>



typedef struct {

    int freq;

    char ch;

} HeapNode;



void swap(HeapNode *a, HeapNode *b) {

    HeapNode temp = *a;

    *a = *b;

    *b = temp;

}



int compare(HeapNode a, HeapNode b) {

    // Higher frequency has higher priority.

    // If frequency equal, smaller char (lexicographically) has higher priority.

    if(a.freq != b.freq)

        return a.freq - b.freq; // positive if a.freq > b.freq.

    else

        return (b.ch - a.ch);  // if a.ch < b.ch then priority: a

}



void heapify_down(HeapNode heap[], int n, int idx) {

    int largest = idx;

    int left = 2*idx + 1;

    int right = 2*idx + 2;

    if(left < n && (compare(heap[left], heap[largest]) > 0))

        largest = left;

    if(right < n && (compare(heap[right], heap[largest]) > 0))

        largest = right;

    if(largest != idx) {

        swap(&heap[idx], &heap[largest]);

        heapify_down(heap, n, largest);

    }

}



void heapify_up(HeapNode heap[], int idx) {

    while(idx > 0) {

        int parent = (idx - 1)/2;

        if(compare(heap[idx], heap[parent]) > 0) {

            swap(&heap[idx], &heap[parent]);

            idx = parent;

        } else {

            break;

        }

    }

}



void heap_push(HeapNode heap[], int *n, HeapNode node) {

    heap[*n] = node;

    (*n)++;

    heapify_up(heap, (*n)-1);

}



HeapNode heap_pop(HeapNode heap[], int *n) {

    HeapNode top = heap[0];

    heap[0] = heap[(*n)-1];

    (*n)--;

    heapify_down(heap, *n, 0);

    return top;

}



char *func0(const char *S) {
  int len = strlen(S);
  if (len == 0) {
    char *empty = malloc(1);
    if (empty) empty[0] = '\0';
    return empty;
  }
  int freq[256] = {0};
  for (int i = 0; i < len; i++) {
    freq[(unsigned char)S[i]]++;
  }
  HeapNode heap[256];
  int heapSize = 0;
  for (int i = 0; i < 256; i++) {
    if (freq[i] > 0) {
      HeapNode node;
      node.freq = freq[i];
      node.ch = (char)i;
      heap[heapSize++] = node;
    }
  }
  for (int i = (heapSize / 2) - 1; i >= 0; i--) {
    heapify_down(heap, heapSize, i);
  }
  if (heapSize > 0 && heap[0].freq * 2 > len + 1) {
    char *empty = malloc(1);
    if (empty) empty[0] = '\0';
    return empty;
  }
  char *result = malloc(len + 1);
  int pos = 0;
  while (heapSize >= 2) {
    HeapNode first = heap_pop(heap, &heapSize);
    HeapNode second = heap_pop(heap, &heapSize);
    result[pos++] = first.ch;
    result[pos++] = second.ch;
    first.freq--;
    second.freq--;
    if (first.freq > 0) {
      heap_push(heap, &heapSize, first);
    }
    if (second.freq > 0) {
      heap_push(heap, &heapSize, second);
    }
  }
  if (heapSize > 0) {
    HeapNode last = heap_pop(heap, &heapSize);
    result[pos++] = last.ch;
  }
  result[pos] = '\0';
  return result;
}
