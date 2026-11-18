int func0(int *param1, int param2, int param3) {
  int i;
  for (i = 0; i < param2; i++) {
    if (param1[i] > param3) {
      break;
    }
  }
  return i;
}