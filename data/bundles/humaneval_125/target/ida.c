char **__cdecl func0(const char *txt, int *returnSize)
{
  char *v2; // rax
  char v3; // cl
  int v4; // eax
  char current[101]; // [rsp+0h] [rbp-A0h] BYREF
  char **out; // [rsp+70h] [rbp-30h]
  int len; // [rsp+7Ch] [rbp-24h]
  int count; // [rsp+80h] [rbp-20h]
  int num; // [rsp+84h] [rbp-1Ch]
  int j; // [rsp+88h] [rbp-18h]
  int i; // [rsp+8Ch] [rbp-14h]
  int *returnSizea; // [rsp+90h] [rbp-10h]
  const char *txta; // [rsp+98h] [rbp-8h]

  txta = txt;
  returnSizea = returnSize;
  j = 0;
  num = 0;
  count = 0;
  len = strlen(txt);
  out = 0LL;
  memset(current, 0, sizeof(current));
  if ( strchr(txta, 32) || strchr(txta, 44) )
  {
    out = (char **)malloc(8LL * (len + 1));
    for ( i = 0; i <= len; ++i )
    {
      if ( txta[i] == 32 || txta[i] == 44 || !txta[i] )
      {
        if ( j > 0 )
        {
          current[j] = 0;
          v2 = strdup(current);
          out[count++] = v2;
          j = 0;
        }
      }
      else
      {
        v3 = txta[i];
        v4 = j++;
        current[v4] = v3;
      }
    }
  }
  else
  {
    for ( i = 0; i < len; ++i )
    {
      if ( ((*__ctype_b_loc())[txta[i]] & 0x200) != 0 && (txta[i] - 97) % 2 == 1 )
        ++num;
    }
    out = (char **)malloc(8uLL);
    *out = (char *)malloc(0xCuLL);
    sprintf(*out, "%d", (unsigned int)num);
    count = 1;
  }
  *returnSizea = count;
  return out;
}