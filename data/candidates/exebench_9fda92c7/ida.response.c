void __cdecl reverse(char *s)
{
  char *v1; // rax
  char buf; // [rsp+0h] [rbp-1Ah]
  char *end; // [rsp+2h] [rbp-18h]
  char *enda; // [rsp+2h] [rbp-18h]
  char *start; // [rsp+Ah] [rbp-10h]

  end = s;
  start = s;
  do
    v1 = end++;
  while ( *v1 );
  for ( enda = end - 2; start < enda; --enda )
  {
    buf = *start;
    *start = *enda;
    *enda = buf;
    ++start;
  }
}