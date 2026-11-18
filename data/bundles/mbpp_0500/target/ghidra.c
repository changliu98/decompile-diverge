char * func0(char **arr,int size)

{
  int i;
  int size_local;
  char **arr_local;
  
  strcpy(func0::ans," ");
  for (i = 0; i < size; i = i + 1) {
    strcat(func0::ans," ");
    strcat(func0::ans,arr[i]);
  }
  return func0::ans;
}