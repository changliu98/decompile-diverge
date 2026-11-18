void ToRNA(char *seq)
{
  char c;

  for ( ; *seq ; seq++) {
    c = *seq;
    if (c == 'T') *seq = 'U';
    else if (c == 't') *seq = 'u';
  }
}