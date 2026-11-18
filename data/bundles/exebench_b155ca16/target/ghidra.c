char * object_desc_chr(char *t,char c)

{
  char c_local;
  char *t_local;
  
  *t = c;
  t[1] = '\0';
  return t + 1;
}