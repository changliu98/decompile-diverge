static int _swap(int *a, int b)
{
 int t = *a;
 *a ^= b;
 return t;
}