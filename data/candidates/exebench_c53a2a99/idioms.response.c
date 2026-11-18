void unhide(char *text)
{
  int i = 0;
  int przesun = 0;
  int tab[] = {1, 0, 3};
  for (i = 0; text[i]; i++)
  {
    text[i] -= tab[przesun];
    przesun++;
    if (przesun == 3)
      przesun = 0;
  }
}