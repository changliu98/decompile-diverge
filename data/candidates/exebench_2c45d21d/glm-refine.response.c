char __cdecl last_char(char *str)
{
  if (!str || !*str)
    return 0;

  char *end = str;
  while (*end)
    ++end;

  char *last = end - 1;
  char c = *last;
  *last = 0;
  
  return c;
}