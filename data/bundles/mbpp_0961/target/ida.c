int __cdecl func0(char *s)
{
  int i; // [rsp+4h] [rbp-41Ch]
  int len; // [rsp+8h] [rbp-418h]
  int int_val; // [rsp+Ch] [rbp-414h]
  int rom_val[256]; // [rsp+10h] [rbp-410h] BYREF
  char *sa; // [rsp+418h] [rbp-8h]

  sa = s;
  memset(rom_val, 0, sizeof(rom_val));
  rom_val[73] = 1;
  rom_val[86] = 5;
  rom_val[88] = 10;
  rom_val[76] = 50;
  rom_val[67] = 100;
  rom_val[68] = 500;
  rom_val[77] = 1000;
  int_val = 0;
  len = strlen(sa);
  for ( i = 0; i < len; ++i )
  {
    if ( i <= 0 || rom_val[sa[i]] <= rom_val[sa[i - 1]] )
      int_val += rom_val[sa[i]];
    else
      int_val += rom_val[sa[i]] - 2 * rom_val[sa[i - 1]];
  }
  return int_val;
}