int minmax(int *array, int n, int *min, int *max)
{
  int i;
  if (n % 2 == 0) {
    if (array[0] < array[1]) {
      *min = array[0];
      *max = array[1];
    } else {
      *min = array[1];
      *max = array[0];
    }
    i = 2;
  } else {
    *min = *max = array[0];
    i = 1;
  }
  return i;
}