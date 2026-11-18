int calcola(char **operato, int *operand, int operato_size, int operand_size)
{
  int *num = (int*)malloc(operand_size*sizeof(int));
  int *posto = (int*)malloc(operand_size*sizeof(int));
  int i;
  for(i=0; i<operand_size; i++)
  {
    num[i]=operand[i];
    posto[i]=i;
  }
  for(i=0; i<operato_size; i++)
  {
    if(!strcmp(operato[i], "**"))
    {
      while(posto[posto[i]]!=posto[i])
        posto[i]=posto[posto[i]];
      while(posto[posto[i]+1]!=posto[i]+1)
        posto[i+1]=posto[posto[i]+1];
      num[posto[i]]=pow(num[posto[i]],num[posto[i]+1]);
      posto[i+1]=posto[i];
    }
  }
  for(i=0; i<operato_size; i++)
  {
    if(!strcmp(operato[i], "*") || !strcmp(operato[i], "//"))
    {
      while(posto[posto[i]]!=posto[i])
        posto[i]=posto[posto[i]];
      while(posto[posto[i]+1]!=posto[i]+1)
        posto[i+1]=posto[posto[i]+1];
      if(!strcmp(operato[i], "*"))
        num[posto[i]]=num[posto[i]]*num[posto[i]+1];
      else
        num[posto[i]]=num[posto[i]]/num[posto[i]+1];
      posto[i+1]=posto[i];
    }
  }
  for(i=0; i<operato_size; i++)
  {
    if(!strcmp(operato[i], "+") || !strcmp(operato[i], "-"))
    {
      while(posto[posto[i]]!=posto[i])
        posto[i]=posto[posto[i]];
      while(posto[posto[i]+1]!=posto[i]+1)
        posto[i+1]=posto[posto[i]+1];
      if(!strcmp(operato[i], "+"))
        num[posto[i]]=num[posto[i]]+num[posto[i]+1];
      else
        num[posto[i]]=num[posto[i]]-num[posto[i]+1];
      posto[i+1]=posto[i];
    }
  }
  int ris = num[0];
  free(num);
  free(posto);
  return ris;
}