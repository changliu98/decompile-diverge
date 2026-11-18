int func0(int n)
{
  char num[11];
  char z[11];
  int i;
  int na = n;
  int len;
  int zlen;
  char min;
  char tmp;
  sprintf(num,"%d",na);
  len = strlen(num);
  for(i = len - 2; i >= 0; i--)
  {
    if(num[i]<num[i+1])
    {
      strcpy(z,&num[i]);
      zlen = strlen(z);
      min = z[1];
      for(i = 1; i < zlen; i++)
      {
        if((z[i]>z[0])&&(z[i]<min))
        {
          min = z[i];
        }
      }
      for(i = 0; i < zlen; i++)
      {
        if(z[i]==min)
        {
          for(i = i; i < zlen - 1; i++)
          {
            z[i] = z[i+1];
          }
          z[zlen - 1] = '\0';
          break;
        }
      }
      qsort(z,strlen(z),sizeof(char),strcmp);
      num[i] = min;
      strcpy(&num[i+1],z);
      return (atoi(num));
    }
  }
  return (0);
}