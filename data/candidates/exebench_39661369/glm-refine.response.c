void __cdecl copy(char *to, char *from)
{
  int i = 0;
  char c;

  do {
    c = from[i];
    to[i] = c;
    i++;
  } while (c != '\0');
}