int popPriorityQueue(int* queue, short* heap) {
    queue[0] -= 1;
    return heap[queue[0] * 2];
}