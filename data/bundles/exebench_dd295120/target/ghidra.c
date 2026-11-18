char * ft_strcpy(char *s1,char *s2)

{
  char *keep;
  char *s2_local;
  char *s1_local;
  
  s2_local = s2;
  s1_local = s1;
  while (*s2_local != '\0') {
    *s1_local = *s2_local;
    s2_local = s2_local + 1;
    s1_local = s1_local + 1;
  }
  *s1_local = '\0';
  return s1;
}