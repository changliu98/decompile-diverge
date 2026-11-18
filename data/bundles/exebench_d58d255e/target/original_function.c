static char *
smtp_stpcpy(char *s1,
            const char *s2){
  size_t i;

  i = 0;
  do{
    s1[i] = s2[i];
  } while(s2[i++] != '\0');
  return &s1[i-1];
}