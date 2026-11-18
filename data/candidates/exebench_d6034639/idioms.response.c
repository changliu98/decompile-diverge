int fatfs_get_sfn_display_name(char *out, char *in)
{
  int len = 0;
  for ( ; (in[0] != '\0') && (len < 12); ) {
    char c = *in++;
    if (c == ' ')
      continue;
    if (c >= 'A' && c <= 'Z')
      c += 'a'-'A';
    *out++ = c;
    len++;
  }
  *out = '\0';
  return 1;
}