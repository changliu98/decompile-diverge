void numericCrypt(char *str)
{
  int i; int j;
  for (i = 0; str[i]; i++)
  {
    for (j = 0; oizeasgtbq[j]; j++)
    {
      if (str[i] == oizeasgtbq[j])
      {
        str[i] = "01234567890"[j];
        break;
      }
    }
  }
}