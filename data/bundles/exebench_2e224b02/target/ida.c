void __cdecl prtl16(long num, char *str)
{
  int v2; // eax
  char v3; // cl
  char *v4; // rax
  char temp[9]; // [rsp+1h] [rbp-1Dh]
  int i; // [rsp+Ah] [rbp-14h]
  char *stra; // [rsp+Eh] [rbp-10h]
  long numa; // [rsp+16h] [rbp-8h]

  numa = num;
  stra = str;
  temp[0] = 0;
  for ( i = 1; i <= 8; ++i )
  {
    temp[i] = a0123456789abcd[numa & 0xF];
    numa >>= 4;
  }
  for ( i = 8; temp[i] == 48; --i )
    ;
  if ( !i )
    i = 1;
  while ( i >= 0 )
  {
    v2 = i--;
    v3 = temp[v2];
    v4 = stra++;
    *v4 = v3;
  }
}