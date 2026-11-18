void count_down(int *time, int *countdown) {
  int i;
  if (*time > 0) {
    *time -= 1;
  }
  for (i = 0; i < 4; i++) {
    if (countdown[i] > 0) {
      countdown[i] -= 1;
    }
  }
}