void __cdecl wdc_UtilsDeleteCharFromString(char *buffer, int buffSize, char charToRemove)
{
  int write_idx = 0;
  int i;

  if (buffer && buffSize)
  {
    for (i = 0; i < buffSize && buffer[i] != '\0'; ++i)
    {
      if (buffer[i] != charToRemove)
      {
        buffer[write_idx++] = buffer[i];
      }
    }
    buffer[write_idx] = '\0';
  }
}