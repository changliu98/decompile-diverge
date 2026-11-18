int div(int *a, int *b)
{
 int c = *a / *b;
 *b = *a - c * *b;
 return c;
}