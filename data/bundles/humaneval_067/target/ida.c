int __cdecl func0(const char *s, int n)
{
  int v2; // eax
  int v4; // [rsp+Ch] [rbp-34h]
  int v5; // [rsp+10h] [rbp-30h]
  int i; // [rsp+14h] [rbp-2Ch]
  int j; // [rsp+18h] [rbp-28h]
  int is12; // [rsp+1Ch] [rbp-24h]
  char num2[10]; // [rsp+20h] [rbp-20h] BYREF
  char num1[10]; // [rsp+2Ah] [rbp-16h] BYREF
  int na; // [rsp+34h] [rbp-Ch]
  const char *sa; // [rsp+38h] [rbp-8h]

  sa = s;
  na = n;
  memset(num1, 0, sizeof(num1));
  memset(num2, 0, sizeof(num2));
  is12 = 0;
  j = 0;
  for ( i = 0; sa[i]; ++i )
  {
    if ( ((*__ctype_b_loc())[sa[i]] & 0x800) != 0 )
    {
      v2 = j++;
      if ( is12 )
        num2[v2] = sa[i];
      else
        num1[v2] = sa[i];
    }
    else if ( !is12 && j > 0 )
    {
      is12 = 1;
      j = 0;
    }
  }
  v4 = na;
  v5 = v4 - atoi(num1);
  return v5 - atoi(num2);
}