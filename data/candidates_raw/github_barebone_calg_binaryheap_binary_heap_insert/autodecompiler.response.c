int binary_heap_push(binary_heap_t *binary_heap, void *item)
{
 unsigned int i, j;
 int ret;

 if (binary_heap->nitems >= binary_heap->capacity) {
  unsigned int new_capacity;
  void **new_values;

  new_capacity = binary_heap->capacity * 2;
  new_values = realloc(binary_heap->values, new_capacity * sizeof(void *));
  if (!new_values) {
   ret = 0;
   goto out;
  }

  binary_heap->capacity = new_capacity;
  binary_heap->values = new_values;
 }

 i = binary_heap->nitems;
 binary_heap->nitems++;

 while (i > 0) {
  j = (i - 1) / 2;
  if (binary_heap_cmp(binary_heap, binary_heap->values[j], item) < 0)
   break;

  binary_heap->values[i] = binary_heap->values[j];
  i = j;
 }
 binary_heap->values[i] = item;

 ret = 1;
out:
 return ret;
}