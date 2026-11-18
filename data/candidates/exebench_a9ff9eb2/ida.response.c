void __cdecl ltox(unsigned int value, char *str)
{
  char tab[16]; // [rsp+0h] [rbp-30h] BYREF
  int i; // [rsp+1Ch] [rbp-14h]
  char *stra; // [rsp+20h] [rbp-10h]
  unsigned int valuea; // [rsp+2Ch] [rbp-4h]

  valuea = value;
  stra = str;
  qmemcpy(tab, "0123456789ABCDEF", sizeof(tab));
  for ( i = 0; i < 8; ++i )
  {
    stra[9 - i] = tab[valuea & 0xF];
    valuea >>= 4;
  }
  *stra = 48;
  stra[1] = 120;
  stra[10] = 10;
  stra[11] = 0;
}