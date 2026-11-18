int __cdecl reverse(char *s)
{
  char *p = s;
  char *q = s;

  // Find the null terminator to get the end of the string
  do {
    q++;
  } while (*(q - 1));

  // Set qa to the last character of the string
  char *qa = q - 2;

  // Swap characters from the outside in
  while (p < qa) {
    // XOR swap algorithm
    *p ^= *qa;
    *qa ^= *p;
    *p ^= *qa;

    p++;
    qa--;
  }

  return 0;
}