static void descending2(int *a, int *b)
{
 int temp = *a;
 if (*a < *b)
 {
  *a = *b;
  *b = temp;
 }
}