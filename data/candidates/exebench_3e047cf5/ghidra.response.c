void ToRNA(char *seq)

{
  char *seq_local;
  
  for (seq_local = seq; *seq_local != '\0'; seq_local = seq_local + 1) {
    if (*seq_local == 'T') {
      *seq_local = 'U';
    }
    else if (*seq_local == 't') {
      *seq_local = 'u';
    }
  }
  return;
}