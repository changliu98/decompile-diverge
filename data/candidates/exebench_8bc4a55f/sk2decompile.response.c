short popPriorityQueue(int *size, short queue[][2]) {
  (*size)--;
  return queue[*size][0];
}