char * func0(char **test_list,int size)

{
  double dVar1;
  double dVar2;
  double second;
  double first;
  char temp [100];
  int i;
  int size_local;
  char **test_list_local;
  
  strcpy(func0::res,"[");
  for (i = 0; i < size; i = i + 2) {
    dVar1 = atof(test_list[i]);
    dVar2 = atof(test_list[i + 1]);
    snprintf(temp,100,"(%.2f, %.2f)",dVar1,dVar2);
    strcat(func0::res,temp);
    if (i < size + -2) {
      strcat(func0::res,", ");
    }
  }
  strcat(func0::res,"]");
  return func0::res;
}