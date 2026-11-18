char *func0(char *array[], int size)
{
  static char ans[100];
  strcpy(ans," ");
  int i;
  for(i=0;i<size;i++)
  {
    strcat(ans," ");
    strcat(ans,array[i]);
  }
  return ans;
}