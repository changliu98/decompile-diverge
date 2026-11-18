int func0(int items[], int length) {
  int tot = 1;
  for (int i = 0; i < length; i++) {
    tot *= items[i];
  }
  return tot;
}