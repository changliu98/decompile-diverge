char *func0(int a, int b, int n)
{
 int x, y;
 for (x = 0; x * a <= n; x++) {
  if ((n - x * a) % b == 0) {
   y = (n - x * a) / b;
   sprintf(func0.result, "x = %d, y = %d", x, y);
   return func0.result;
  }
 }
 return "No solution";
}