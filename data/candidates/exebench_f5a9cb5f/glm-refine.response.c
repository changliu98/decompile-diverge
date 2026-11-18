void __cdecl reverse(char *s)
{
  int length = 0;
  int left = 0;
  int right;
  char temp;

  // Calculate the length of the string
  while (s[length])
    ++length;

  // Reverse the string in-place
  for (right = length - 1; left < right; --right)
  {
    temp = s[left];
    s[left] = s[right];
    s[right] = temp;
    ++left;
  }
}