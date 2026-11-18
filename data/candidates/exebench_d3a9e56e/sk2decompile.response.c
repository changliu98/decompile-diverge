void reverseInt(int *a) {
  int i, temp;
  for (i = 0; i < 5; i++) {
    temp = a[i];
    a[i] = a[10 - i - 1];
    a[10 - i - 1] = temp;
  }
}