void __cdecl combain_sorted_array(int *p, int *q, int *s)
{
  bool v3; // [rsp+1h] [rbp-29h]
  int *q_end; // [rsp+2h] [rbp-28h]
  int *p_end; // [rsp+Ah] [rbp-20h]
  int *sb; // [rsp+12h] [rbp-18h]
  int *qa; // [rsp+1Ah] [rbp-10h]
  int *pa; // [rsp+22h] [rbp-8h]

  pa = p;
  qa = q;
  p_end = p + 5;
  q_end = q + 5;
  while ( 1 )
  {
    v3 = 0;
    if ( pa < p_end )
      v3 = qa < q_end;
    if ( !v3 )
      break;
    if ( *pa > *qa )
    {
      if ( qa == q + 4 )
      {
        *s++ = *qa;
        while ( pa < p_end )
          *s++ = *pa++;
      }
      *s++ = *qa++;
    }
    else
    {
      if ( pa == p + 4 )
      {
        *s = *pa;
        sb = s + 1;
        while ( qa < q_end )
          *sb++ = *qa++;
        return;
      }
      *s++ = *pa++;
    }
  }
}