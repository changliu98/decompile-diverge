void ToRNA(char *dna) {
  while (*dna) {
    if (*dna == 'T')
      *dna = 'U';
    else if (*dna == 't')
      *dna = 'u';
    dna++;
  }
}