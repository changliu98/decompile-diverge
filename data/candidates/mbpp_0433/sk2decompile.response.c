void func0(int *a, int n, int num) {
  int i, j, temp;
  for (j = 0; j < n - 1; j++) {
    for (i = 0; i < n - j - 1; i++) {
      if (a[i] > a[i + 1]) {
        temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
      }
    }
  }
  if (num > a[n - 1])
    printf("Yes, the entered number is greater than those in the array\n");
  else
    printf("No, entered number is less than those in the array\n");
}