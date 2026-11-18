static void arraylist_sort_internal(ArrayListValue *array, unsigned int length,
                                    ArrayListCompareFunc compare) {
  if (length > 1) {
    ArrayListValue pivot = array[length - 1];
    unsigned int i = 0;
    unsigned int j;
    for (j = 0; j < length - 1; j++) {
      if (compare(array[j], pivot) < 0) {
        ArrayListValue tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
        i++;
      }
    }
    array[length - 1] = array[i];
    array[i] = pivot;
    arraylist_sort_internal(array, i, compare);
    arraylist_sort_internal(array + i + 1, length - i - 1, compare);
  }
}