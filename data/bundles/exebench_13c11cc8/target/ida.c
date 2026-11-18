void __cdecl sort_three(int *v1, int *v2, int *v3)
{
  int tmp; // [rsp+0h] [rbp-1Ch]
  int tmpa; // [rsp+0h] [rbp-1Ch]
  int tmpb; // [rsp+0h] [rbp-1Ch]

  if ( *v1 > *v2 )
  {
    tmp = *v2;
    *v2 = *v1;
    *v1 = tmp;
  }
  if ( *v1 > *v3 )
  {
    tmpa = *v3;
    *v3 = *v1;
    *v1 = tmpa;
  }
  if ( *v2 > *v3 )
  {
    tmpb = *v2;
    *v2 = *v3;
    *v3 = tmpb;
  }
}