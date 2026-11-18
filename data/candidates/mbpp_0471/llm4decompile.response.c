int func0(int *arr, int lens, int n)
{
 int i;
 int mul = 1;
 for (i = 0; i < lens; i++)
  mul = (mul * (arr[i] % n)) % n;
 return mul % n;
}