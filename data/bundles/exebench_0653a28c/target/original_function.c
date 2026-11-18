void reverse(char li[])
{
 char *left, *right;
 left = right = li;
 while (*right++) ;
 right -= 2;

 while (left < right) {
  char t = *left;
  *left = *right;
  *right = t;

  ++left;
  --right;
 }
}