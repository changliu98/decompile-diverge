void __cdecl reverse(char *str)
{
  // Calculate the length of the string
  int len = 0;
  while (str[len]) 
  {
    len++;
  }

  // Ignore the trailing newline character if present
  int end = len - 1;
  if (str[end] == '\n') 
  {
    end--;
  }

  // Reverse the string in-place
  for (int start = 0; start < end; start++, end--) 
  {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
  }
}