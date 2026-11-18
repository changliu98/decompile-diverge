void func0(char* Tekst)
{
  int i;
  for (i = 0; ; i++)
  {
    if (Tekst[i] == '\0') break;
    if (Tekst[i] == ' ') Tekst[i] = '_';
  }
}