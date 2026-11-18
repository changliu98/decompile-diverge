int benchmark() {
  int n = 10000000;
  char string[32], pattern[32];
  int matches = 0;

  while(n--) {
    int stringLen = rand() & 31;
    int patternLen = rand() & 31;
    int j;

    for (j = 0; j < stringLen; j++) string[j] = rand() % 128;
    for (j = 0; j < patternLen; j++) pattern[j] = rand() % 128;

    matches += stringmatchlen(pattern, patternLen, string, stringLen, 0);
  }
  return matches;
}