void __cdecl copy(char *longest, char *line)
{
  int i;

  for (i = 0; ; ++i)
  {
    longest[i] = line[i];
    if (line[i] == '\0')
      break;
  }
}