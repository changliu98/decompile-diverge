static void arraylist_sort_internal(ArrayListValue *list_data,
                                     unsigned int list_length,
                                     ArrayListCompareFunc compare_func) {
  ArrayListValue pivot;
  ArrayListValue temp;
  unsigned int list1_length, list2_length;
  unsigned int i;

  if (list_length <= 1) return;

  pivot = list_data[list_length - 1];

  list1_length = 0;
  for (i = 0;; i++) {
    while (i < list_length - 1 &&
           compare_func(list_data[i], pivot) >= 0) {
      i++;
    }
    if (i >= list_length - 1) break;

    temp = list_data[i];
    list_data[i] = list_data[list1_length];
    list_data[list1_length] = temp;
    list1_length++;
  }

  list2_length = list_length - list1_length - 1;

  list_data[list_length - 1] = list_data[list1_length];
  list_data[list1_length] = pivot;

  arraylist_sort_internal(list_data, list1_length, compare_func);
  arraylist_sort_internal(&list_data[list1_length + 1],
                          list2_length, compare_func);
}