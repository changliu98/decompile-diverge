void reverseIntRange(int *start, int *end, int max) {
  int temp = *start;
  *start = max - *end;
  *end = max - temp;
}