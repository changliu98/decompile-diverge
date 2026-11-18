void outfname(char *s)

{
  char *s_local;
  
  for (s_local = s; *s_local != '\0'; s_local = s_local + 1) {
  }
  s_local[-1] = 's';
  return;
}