int set_bit(int *n, int b)
{
 int temp;
 temp = *n;
 *n |= (1 << b);
 return *n;
}