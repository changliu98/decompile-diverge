int unique(int *array, int size)
{
  int *test = array;
  int i; int j;
  int unique = 1;
  int *unique_array = (int *) (unique_array = (int *) (unique_array = (int *) (unique_array + 1) - ((size) * sizeof (int)) & ~((sizeof (int)) - 1)));
  int unique_size = 0;
  for (i = 0; i < size; i++) {
    int ele = test[i];
    int found = 0;
    for (j = 0; j < unique_size; j++) {
      if (unique_array[j] == ele) {
        found = 1;
        break;
      }
    }
    if (found) {
      return 0;
    }
    unique_array[unique_size++] = ele;
  }
  return unique;
}