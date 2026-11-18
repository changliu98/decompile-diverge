char **__cdecl func0(const char *planet1, const char *planet2, int *returnSize)
{
  char **out; // [rsp+8h] [rbp-78h]
  int temp; // [rsp+10h] [rbp-70h]
  int m; // [rsp+14h] [rbp-6Ch]
  int ma; // [rsp+14h] [rbp-6Ch]
  int pos2; // [rsp+18h] [rbp-68h]
  int pos1; // [rsp+1Ch] [rbp-64h]
  const char *planets[8]; // [rsp+20h] [rbp-60h] BYREF
  int *returnSizea; // [rsp+60h] [rbp-20h]
  const char *planet2a; // [rsp+68h] [rbp-18h]
  const char *planet1a; // [rsp+70h] [rbp-10h]

  planet1a = planet1;
  planet2a = planet2;
  returnSizea = returnSize;
  memcpy(planets, &off_3D60, sizeof(planets));
  pos1 = -1;
  pos2 = -1;
  for ( m = 0; m < 8; ++m )
  {
    if ( !strcmp(planets[m], planet1a) )
      pos1 = m;
    if ( !strcmp(planets[m], planet2a) )
      pos2 = m;
  }
  if ( pos1 == -1 || pos2 == -1 || pos1 == pos2 )
  {
    *returnSizea = 0;
    return 0LL;
  }
  else
  {
    if ( pos1 > pos2 )
    {
      temp = pos1;
      pos1 = pos2;
      pos2 = temp;
    }
    *returnSizea = pos2 - pos1 - 1;
    if ( *returnSizea > 0 )
    {
      out = (char **)malloc(8LL * *returnSizea);
      for ( ma = pos1 + 1; ma < pos2; ++ma )
        out[ma - pos1 - 1] = (char *)planets[ma];
      return out;
    }
    else
    {
      *returnSizea = 0;
      return 0LL;
    }
  }
}