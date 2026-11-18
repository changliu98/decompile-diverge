int *
func0(int *numbers, int size)
{
 int i;
 int max;
 int *result;

 if (size < 1) {
  return NULL;
 }

 result = malloc((size_t)size * sizeof(int));
 if (result == NULL) {
  return NULL;
 }

 max = numbers[0];
 for (i = 0; i < size; i++) {
  if (numbers[i] > max) {
   max = numbers[i];
  }
  result[i] = max;
 }

 return result;
}