bool __cdecl ExtractRnick(char *Rnick, char *incoming_msg)
{
  char *p = incoming_msg;
  int k = 0;

  // Skip the leading ':' character if present
  if (*p == ':')
    p++;

  // Copy characters until '!' or null-terminator is encountered
  while (*p != '!' && *p != '\0')
  {
    Rnick[k++] = *p++;
  }
  Rnick[k] = '\0';

  // Return true if the first character of Rnick is a digit ('0' - '9')
  return Rnick[0] >= '0' && Rnick[0] <= '9';
}