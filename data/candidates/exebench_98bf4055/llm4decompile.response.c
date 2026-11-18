void reverseIntRange(int *pStart, int *pEnd, int size) {
    *pStart = size - *pEnd;
    *pEnd = size - *pStart;
}