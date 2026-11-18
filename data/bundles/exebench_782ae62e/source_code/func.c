
void tosuper(char *a)
{
  int i = 0;
  while (*(a + i) != '\0')
  {
    if (*(a + i) >= 'a' && *(a + i) <= 'z')
    {
      *(a + i) = *(a + i) - 32;
    }
    i++;
  }
}
