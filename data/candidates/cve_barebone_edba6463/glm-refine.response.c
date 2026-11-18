void __cdecl process_COM(const uchar *Data, int length)
{
  char Comment[16001]; 
  int nch = 0;
  int max_len = length;

  // Clamp the maximum processed length to 16000
  if (max_len > 16000)
    max_len = 16000;

  // Start processing from offset 2 (skipping the 2-byte marker length)
  for (int i = 2; i < max_len; ++i)
  {
    int ch = Data[i];

    // Skip CRLF (0x0D 0x0A) sequences
    if (ch == 13 && Data[i + 1] == 10)
      continue;

    // Store printable characters, tab (0x09), and newline (0x0A)
    if (ch >= 32 || ch == 10 || ch == 9)
    {
      Comment[nch++] = ch;
    }
    else
    {
      // Replace other control characters with '?' (0x3F)
      Comment[nch++] = 63;
    }
  }

  // Null-terminate the sanitized comment string
  Comment[nch] = 0;

  if (ShowTags)
    printf("COM marker comment: %s\n", Comment);

  // Copy the extracted comment into the global image info buffer
  strcpy(ImageInfo, Comment);
}