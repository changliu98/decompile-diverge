short popPriorityQueue(int *size, short (*queue)[2]) {
    return queue[--*size][0];
}