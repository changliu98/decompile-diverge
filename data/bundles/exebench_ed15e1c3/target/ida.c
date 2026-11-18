void __cdecl reverse(char *s)
{
  char tmp; // [rsp+1h] [rbp-11h]
  unsigned int max; // [rsp+2h] [rbp-10h]
  unsigned int e; // [rsp+6h] [rbp-Ch]
  unsigned int ea; // [rsp+6h] [rbp-Ch]

  for ( e = 0; s[e]; ++e )
    ;
  max = e;
  for ( ea = 0; ea < max >> 1; ++ea )
  {
    tmp = s[ea];
    s[ea] = s[max - (ea + 1)];
    s[max - (ea + 1)] = tmp;
  }
}