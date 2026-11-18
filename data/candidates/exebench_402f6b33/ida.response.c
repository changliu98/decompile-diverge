void __cdecl itoa(int num, char *str, int base)
{
  int v3; // eax
  char v4; // cl
  int v5; // eax
  int v6; // eax
  char v8; // cl
  char *v9; // rax
  char tmp[16]; // [rsp+10h] [rbp-30h]
  int sign; // [rsp+24h] [rbp-1Ch]
  int i; // [rsp+28h] [rbp-18h]
  int basea; // [rsp+2Ch] [rbp-14h]
  char *stra; // [rsp+30h] [rbp-10h]
  int numa; // [rsp+3Ch] [rbp-4h]

  numa = num;
  stra = str;
  basea = base;
  sign = num;
  if ( num < 0 )
    numa = -numa;
  i = 0;
  if ( numa )
  {
    while ( numa )
    {
      v4 = a0123456789abcd[numa % basea];
      v5 = i++;
      tmp[v5] = v4;
      numa /= basea;
    }
  }
  else
  {
    v3 = i++;
    tmp[v3] = 48;
  }
  if ( sign < 0 )
  {
    v6 = i++;
    tmp[v6] = 45;
  }
  while ( i-- )
  {
    v8 = tmp[i];
    v9 = stra++;
    *v9 = v8;
  }
  *stra = 0;
}