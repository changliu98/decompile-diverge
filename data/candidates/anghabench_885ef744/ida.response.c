void __cdecl ui2a(unsigned int num, unsigned int base, int uc, char *bf)
{
  char v4; // al
  char *v5; // rax
  char v6; // [rsp+0h] [rbp-2Ch]
  int dgt; // [rsp+8h] [rbp-24h]
  unsigned int d; // [rsp+Ch] [rbp-20h]
  int n; // [rsp+10h] [rbp-1Ch]
  unsigned int numa; // [rsp+28h] [rbp-4h]

  numa = num;
  n = 0;
  for ( d = 1; num / d >= base; d *= base )
    ;
  while ( d )
  {
    dgt = numa / d;
    numa %= d;
    d /= base;
    if ( n || dgt > 0 || !d )
    {
      if ( dgt >= 10 )
      {
        v4 = 97;
        if ( uc )
          v4 = 65;
        v6 = v4 - 10;
      }
      else
      {
        v6 = 48;
      }
      v5 = bf++;
      *v5 = v6 + dgt;
      ++n;
    }
  }
  *bf = 0;
}