int has_duplicates(int arraynums[], int length)
{
  int i;
  int j;
  int found_duplicate = 0;
  for (i = 0; i < length; i++)
  {
    for (j = i + 1; j < length; j++)
    {
      if (arraynums[i] == arraynums[j])
      {
        found_duplicate = 1;
        break;
      }
    }
    if (found_duplicate)
    {
      break;
    }
  }
  return found_duplicate;
}