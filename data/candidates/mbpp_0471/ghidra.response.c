int func0(int *arr,int lens,int n)

{
  int i;
  int mul;
  int n_local;
  int lens_local;
  int *arr_local;
  
  mul = 1;
  for (i = 0; i < lens; i = i + 1) {
    mul = (mul * (arr[i] % n)) % n;
  }
  return mul % n;
}