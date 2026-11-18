void strcpy4(char *s, char *t)
{
  int i;

  i = 0;
  do {
    *(s + i) = *(t + i);
    i++;
  } while (*(t + i - 1) != 0);
}