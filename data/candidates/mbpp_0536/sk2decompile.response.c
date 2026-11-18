void _get_every_nth_element(int *array, int size, int n, int *result,
                            int *result_size) {
  int i, j = 0;
  for (i = 0; i < size; i += n) {
    result[j++] = array[i];
  }
  *result_size = j;
}