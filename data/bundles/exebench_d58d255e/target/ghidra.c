char * smtp_stpcpy(char *s1,char *s2)

{
  size_t sVar1;
  size_t i;
  char *s2_local;
  char *s1_local;
  
  i = 0;
  sVar1 = i;
  do {
    i = sVar1;
    s1[i] = s2[i];
    sVar1 = i + 1;
  } while (s2[i] != '\0');
  return s1 + i;
}