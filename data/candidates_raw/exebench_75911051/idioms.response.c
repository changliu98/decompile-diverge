int divmod(int a, int b, int *remainder)
{
  *remainder = a % b;
  return a / b;
}