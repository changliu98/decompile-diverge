int __cdecl substitute(char *data, char from, char to)
{
  while ((data = strchr(data, from)) != NULL)
  {
    *data = to;
    data++; // Move past the replaced character to continue searching
  }
  return 1;
}