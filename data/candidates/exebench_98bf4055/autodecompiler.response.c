void reverseIntRange(int *a, int *b, int n)
{
 int t = *a;
 *a = n - *b;
 *b = n - t;
}