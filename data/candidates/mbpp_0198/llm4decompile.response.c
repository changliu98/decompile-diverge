double func0(int a, int b)
{
 double area;

 if (a < 0 || b < 0)
  return -1;

 area = 3.14159265358979323846 * sqrt(3) * pow(a, 2) / (4 * b);

 return area;
}