char *__cdecl jstrescapecpy(char *pt, const char *spt)
{
  int v2; // ecx
  char v3; // dl
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  char v8; // dl
  int v9; // ecx
  int v11; // [rsp+0h] [rbp-24h]
  int j; // [rsp+4h] [rbp-20h]
  int i; // [rsp+8h] [rbp-1Ch]

  i = 0;
  j = 0;
  if ( spt )
  {
    while ( spt[i] )
    {
      v11 = spt[i];
      if ( v11 == 37 )
      {
        v6 = j++;
        pt[v6] = 95;
        ++i;
      }
      else if ( v11 == 39 )
      {
        pt[j] = 92;
        v2 = i++;
        v3 = spt[v2];
        v4 = j + 1;
        j += 2;
        pt[v4] = v3;
      }
      else
      {
        if ( v11 == 92 )
        {
          pt[j] = 92;
          v5 = i++;
          v8 = spt[v5];
          v9 = j + 1;
          j += 2;
        }
        else
        {
          v7 = i++;
          v8 = spt[v7];
          v9 = j++;
        }
        pt[v9] = v8;
      }
    }
    pt[j] = 0;
    return pt;
  }
  else
  {
    *pt = 0;
    return pt;
  }
}