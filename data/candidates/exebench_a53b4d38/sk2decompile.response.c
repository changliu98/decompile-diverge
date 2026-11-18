void foo(int *a, int *b) {
  int i;
  for (i = 0; i < 8; i++) {
    if (b[i] != i + 2) break;
  }
  if (i == 8 && *a == 1) {
    *a = 8;
    for (i = 0; i < 8; i++) b[i] = i + 9;
  } else {
    *a = 6;
  }
}