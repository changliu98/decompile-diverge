int __cdecl stringmatchlen_fuzz_test()
{
  int j_0; // [rsp+8h] [rbp-58h]
  int j; // [rsp+Ch] [rbp-54h]
  int patlen; // [rsp+10h] [rbp-50h]
  int strlen; // [rsp+14h] [rbp-4Ch]
  int total_matches; // [rsp+18h] [rbp-48h]
  int cycles; // [rsp+1Ch] [rbp-44h]
  char pat[32]; // [rsp+20h] [rbp-40h] BYREF
  char str[32]; // [rsp+40h] [rbp-20h] BYREF

  cycles = 10000000;
  for ( total_matches = 0; cycles--; total_matches += stringmatchlen(pat, patlen, str, strlen, 0) )
  {
    strlen = rand() & 0x1F;
    patlen = rand() & 0x1F;
    for ( j = 0; j < strlen; ++j )
      str[j] = rand() % 128;
    for ( j_0 = 0; j_0 < patlen; ++j_0 )
      pat[j_0] = rand() % 128;
  }
  return total_matches;
}