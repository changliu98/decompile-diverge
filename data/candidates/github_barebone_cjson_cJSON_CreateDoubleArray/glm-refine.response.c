cJSON *__cdecl cJSON_CreateDoubleArray(const double *numbers, int count)
{
  cJSON *array;
  cJSON *current;
  cJSON *prev = NULL;
  size_t i;

  if (count < 0 || !numbers)
    return NULL;

  array = cJSON_CreateArray();
  if (!array)
    return NULL;

  for (i = 0; i < (size_t)count; ++i)
  {
    current = cJSON_CreateNumber(numbers[i]);
    if (!current)
    {
      cJSON_Delete(array);
      return NULL;
    }

    if (i == 0)
      array->child = current;
    else
      suffix_object(prev, current);

    prev = current;
  }

  // In cJSON, the last element's `prev` pointer points back to the first element 
  // (or to itself if it's the only element) to form a circular doubly-linked list.
  if (array->child)
    array->child->prev = prev;

  return array;
}