void __cdecl reverse(char *s)
{
  char *v1; // rax
  char *v2; // rax
  char temp; // [rsp+1h] [rbp-11h]
  char *end; // [rsp+2h] [rbp-10h]
  char *enda; // [rsp+2h] [rbp-10h]
  char *sa; // [rsp+Ah] [rbp-8h]

  sa = s;
  end = s;
  if ( s )
  {
    while ( *end )
      ++end;
    enda = end - 1;
    while ( sa < enda )
    {
      temp = *enda;
      v1 = enda--;
      *v1 = *sa;
      v2 = sa++;
      *v2 = temp;
    }
  }
}