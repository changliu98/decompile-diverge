void __cdecl encode_int(char *c, int i)
{
  char *v2; // rax
  int negative; // [rsp+0h] [rbp-10h]
  int ia; // [rsp+4h] [rbp-Ch]
  char *ca; // [rsp+8h] [rbp-8h]

  ca = c;
  LOBYTE(ia) = i;
  negative = 0;
  if ( i <= 0 )
  {
    ia = -i;
    negative = 1;
  }
  else
  {
    if ( (i & 0x7C00) != 0 )
    {
      ca = c + 1;
      *c = (i >> 10) & 0x1F | 0x40;
    }
    if ( (i & 0x3F0) != 0 )
    {
      v2 = ca++;
      *v2 = (i >> 4) & 0x3F | 0x40;
    }
  }
  if ( (ia & 0xF) != 0 )
    *ca = ia & 0xF | 0x20;
  else
    *ca = 32;
  if ( !negative )
    *ca |= 0x10u;
  ca[1] = 0;
}