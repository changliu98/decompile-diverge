static int atomic_fetch_xor(int *a, int b)
{
 int t = *a;
 *a ^= b;
 return t;
}