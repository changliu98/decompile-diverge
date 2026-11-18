void swap(int *a, int *b)
{
 int temp = *a;
 if(*a < *b)
 {
  *a = *b;
  *b = temp;
 }
}