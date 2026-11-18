int divide(int a, int b, int *remainder)
{
 int quot;

 *remainder = a % b;
 quot = a / b;
 return quot;
}