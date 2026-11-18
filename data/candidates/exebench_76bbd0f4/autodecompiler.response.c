void assignops(int *a, int b)
{
 *a >>= b;
 *a <<= b;
 *a += b;
 *a *= b;
 *a /= b;
 *a ^= b;
 *a -= b;
 *a &= b;
 *a |= b;
 *a %= b;
 *a = b;
}