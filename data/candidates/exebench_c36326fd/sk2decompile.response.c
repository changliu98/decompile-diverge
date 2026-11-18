void initialize_temp(int *a, int *temp) {
  int i = 9;
  int j = 14;
  while (i >= 0) {
    temp[j] = a[i];
    j--;
    i--;
  }
  while (j != -1) {
    temp[j--] = 0;
  }
}