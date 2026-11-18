char * func0(char **test_tup,int size)

{
  int i;
  char delim [2];
  int size_local;
  char **test_tup_local;
  
  strcpy(func0::res,"");
  delim[0] = DAT_00102004[0];
  delim[1] = DAT_00102004[1];
  for (i = 0; i < size; i = i + 1) {
    strcat(func0::res,test_tup[i]);
    if (i < size + -1) {
      strcat(func0::res,delim);
    }
  }
  return func0::res;
}