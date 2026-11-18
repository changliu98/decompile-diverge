int __cdecl sdsull2str(char *s, unsigned __int64 v)
{
  char *start = s;
  char *end = s;

  // Convert the number to a string in reverse order
  do
  {
    *end++ = (v % 10) + '0';
    v /= 10;
  }
  while (v);

  int length = end - start;
  *end = '\0';

  // Reverse the string in place
  char *left = start;
  char *right = end - 1;
  while (left < right)
  {
    char temp = *left;
    *left = *right;
    *right = temp;
    
    left++;
    right--;
  }

  return length;
}