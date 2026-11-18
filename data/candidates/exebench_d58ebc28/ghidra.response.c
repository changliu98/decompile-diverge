void dummyfunc(char *s)

{
  char ss [8];
  int e;
  char *s_local;
  
  ss = s_Goodbye_00102004;
  for (e = 0; s[e] != '\0'; e = e + 1) {
    s[e] = ss[e];
  }
  return;
}