int isSubset(int *set1, int size1, int *set2, int size2)
{
  int exist = 1;
  int i; int j;
  for(i = 0; i < size2; i++)
  {
    int found = 0;
    for(j = 0; j < size1; j++)
    {
      if(set2[i] == set1[j])
      {
        found = 1;
        break;
      }
    }
    if(!found)
    {
      exist = 0;
      break;
    }
  }
  return exist;
}