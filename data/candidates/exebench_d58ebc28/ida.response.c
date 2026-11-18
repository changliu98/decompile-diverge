void __cdecl dummyfunc(char *s)
{
  char ss_0[8]; // [rsp+0h] [rbp-14h] BYREF
  int e; // [rsp+8h] [rbp-Ch]
  char *sa; // [rsp+Ch] [rbp-8h]

  sa = s;
  e = 0;
  strcpy(ss_0, "Goodbye");
  while ( sa[e] )
  {
    sa[e] = ss_0[e];
    ++e;
  }
}