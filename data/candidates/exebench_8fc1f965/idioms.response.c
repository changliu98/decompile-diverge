void murcielagoCrypt(char *str)
{
  int i; int j;
  for (i = 0; str[i]; i++)
  {
    for (j = 0; aMurcielagomurc[j]; j++)
    {
      if (str[i] == aMurcielagomurc[j])
      {
        str[i] = a01234567890123[j];
        break;
      }
    }
  }
}