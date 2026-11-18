int __cdecl stringmatchlen_fuzz_test()
{
  char pat[32];
  char str[32];
  int total_matches = 0;
  int cycles = 10000000;

  while (cycles--) 
  {
    int str_len = rand() & 0x1F;
    int pat_len = rand() & 0x1F;

    for (int i = 0; i < str_len; ++i)
      str[i] = rand() % 128;

    for (int i = 0; i < pat_len; ++i)
      pat[i] = rand() % 128;

    total_matches += stringmatchlen(pat, pat_len, str, str_len, 0);
  }
  
  return total_matches;
}