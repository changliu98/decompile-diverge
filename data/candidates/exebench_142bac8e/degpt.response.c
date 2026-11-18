void wordstore(char *buffer, int word)
{
  *buffer = (char)word;
  buffer[1] = (char)((uint)word >> 8);
}