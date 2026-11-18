char *func0(int a, int b, int c)
{
 int d = b * b - 4 * a * c;
 return (d > 0) ? "2 solutions" : (d < 0) ? "No solutions" : "1 solution";
}