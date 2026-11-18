char *__cdecl strncpy2(char *target, char *source, int n)
{
  int v3; // ecx
  char *v4; // rax
  char v5; // cl
  char *v6; // rax
  bool v8; // [rsp+1h] [rbp-2Dh]
  char *tp; // [rsp+6h] [rbp-28h]

  for ( tp = target; ; ++tp )
  {
    v3 = n--;
    v8 = 0;
    if ( v3 > 0 )
      v8 = *source != 0;
    if ( !v8 )
      break;
    v4 = source++;
    v5 = *v4;
    v6 = tp;
    *v6 = v5;
  }
  *tp = 0;
  return target;
}