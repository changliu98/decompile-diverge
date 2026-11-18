void func0(int *numbers,int size,int *result)

{
  int i;
  int product;
  int sum;
  int *result_local;
  int size_local;
  int *numbers_local;
  
  sum = 0;
  product = 1;
  for (i = 0; i < size; i = i + 1) {
    sum = numbers[i] + sum;
    product = numbers[i] * product;
  }
  *result = sum;
  result[1] = product;
  return;
}