int in_list(char **list, char *str, int size){
  int i;
  for (i = 0; i < size; i++)
    if (strstr(list[i], str))
      return 1;
  return 0;
}