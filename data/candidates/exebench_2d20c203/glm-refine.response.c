char *__cdecl str_rev(char *s)
{
  char temp;
  char *tail;
  char *head = s;

  // Find the null terminator of the string
  tail = s;
  while (*tail)
    tail++;

  // Set tail to point to the last character of the string
  tail -= 2;

  // Swap characters from the outside in
  while (head < tail)
  {
    temp = *head;
    *head = *tail;
    *tail = temp;
    
    head++;
    tail--;
  }

  return s;
}