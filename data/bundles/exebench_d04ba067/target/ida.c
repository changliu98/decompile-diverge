int __cdecl itochar(int num, char *strb)
{
  unsigned __int8 v2; // al
  char stra[16]; // [rsp+0h] [rbp-30h]
  unsigned __int8 j; // [rsp+1Eh] [rbp-12h]
  unsigned __int8 i; // [rsp+1Fh] [rbp-11h]
  char *strba; // [rsp+20h] [rbp-10h]
  int numa; // [rsp+2Ch] [rbp-4h]

  numa = num;
  strba = strb;
  i = 0;
  j = 0;
  do
  {
    v2 = i++;
    stra[v2] = numa % 10 + 48;
    numa /= 10;
  }
  while ( numa );
  do
  {
    strba[j] = stra[i - j - 1];
    ++j;
  }
  while ( j < (int)i );
  return j;
}