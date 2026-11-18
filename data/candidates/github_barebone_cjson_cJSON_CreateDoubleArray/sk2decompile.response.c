cJSON *cJSON_CreateDoubleArray(const double *numbers, int count) {
  cJSON *array = 0, *n = 0, *prev = 0;
  int i;
  if (count < 0 || !numbers) {
    return 0;
  }
  array = cJSON_CreateArray();
  for (i = 0; array && i < count; i++) {
    n = cJSON_CreateNumber(numbers[i]);
    if (!n) {
      cJSON_Delete(array);
      return 0;
    }
    if (!i) {
      array->child = n;
    } else {
      suffix_object(prev, n);
    }
    prev = n;
  }
  if (array && array->child) {
    array->child->prev = n;
  }
  return array;
}