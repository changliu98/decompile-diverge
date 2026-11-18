void cenitPolarCrypt(char *str)
{
  int i; int j;
  for (i = 0; str[i]; i++)
    for (j = 0; aCenitcenitpola[j]; j++)
      if (str[i] == aCenitcenitpola[j])
      {
        str[i] = aPolarpolarceni[j];
        break;
      }
}