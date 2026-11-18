int stringmatchlen_rand_rand()
{
  int cycles = 10000000;
  int total_matches = 0;
  char str[-1];
  char pat[-1];
  int strlen; int patlen; int i;
  while (cycles--) {
    strlen = rand() & 31;
    patlen = rand() & 31;
    for (i = 0; i < strlen; i++)
      str[i] = rand() % 128;
    for (i = 0; i < patlen; i++)
      pat[i] = rand() % 128;
    total_matches += stringmatchlen(pat, patlen, str, strlen, 0);
  }
  return total_matches;
}