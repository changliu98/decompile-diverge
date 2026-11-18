void __cdecl dummyfunc(char *s)
{
  char ss_0[8]; 
  int e; 
  char *sa; 

  sa = s;
  e = 0;
  strcpy(ss_0, "Goodbye");
  while ( sa[e] )
  {
    sa[e] = ss_0[e];
    ++e;
  }
}