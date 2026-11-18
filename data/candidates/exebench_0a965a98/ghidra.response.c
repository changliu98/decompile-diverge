int new_strcpy(char *s,char *t,int num)

{
  int i;
  int num_local;
  char *t_local;
  char *s_local;
  
  for (i = 0; t[i] != '\0' && i < num; i = i + 1) {
    s[i] = t[i];
  }
  s[i] = '\0';
  return 0;
}