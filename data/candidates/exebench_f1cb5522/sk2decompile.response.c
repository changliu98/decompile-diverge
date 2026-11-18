void argorder(int a, int b, int *amin, int *amax) {
  int min, max;
  min = a;
  max = b;
  if (min > max) {
    int temp;
    temp = min;
    min = max;
    max = temp;
  }
  *amin = min;
  *amax = max;
}