void __cdecl bo_backoff(int *bwait, int cap)
{
  int v2; // [rsp+0h] [rbp-14h]
  int i; // [rsp+4h] [rbp-10h]

  for ( i = *bwait; i; --i )
    ;
  if ( 2 * *bwait >= cap )
    v2 = cap;
  else
    v2 = 2 * *bwait;
  *bwait = v2;
}