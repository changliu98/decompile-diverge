int func0(int *param1, int param2) {
  int i = 0x80000000;
  int j;
  for (j = 0; j < param2; j++) {
    if (param1[j] > i) {
      i = param1[j];
    }
  }
  return i;
}