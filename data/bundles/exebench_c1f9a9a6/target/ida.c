int __cdecl parse_uuid(char *str, int *uuid)
{
  char *v2; // rax
  int n; // [rsp+18h] [rbp-28h]
  char c; // [rsp+1Fh] [rbp-21h]
  int i; // [rsp+20h] [rbp-20h]
  int hit; // [rsp+24h] [rbp-1Ch]

  hit = 0;
  for ( i = 0; i < 4; ++i )
    uuid[i] = 0;
  while ( 1 )
  {
    v2 = str++;
    c = *v2;
    if ( !*v2 )
      return hit == 32;
    if ( c >= 48 && c <= 57 )
    {
      n = c - 48;
      goto LABEL_16;
    }
    if ( c >= 97 && c <= 102 )
    {
      n = c - 87;
      goto LABEL_16;
    }
    if ( c < 65 || c > 70 )
    {
      if ( !strchr(":. -", c) )
        return 0;
    }
    else
    {
      n = c - 55;
LABEL_16:
      if ( hit < 32 )
      {
        uuid[hit / 8] *= 16;
        uuid[hit / 8] += n;
      }
      ++hit;
    }
  }
}