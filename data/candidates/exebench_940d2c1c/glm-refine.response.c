void __cdecl escape(char *dst, char *src)
{
  int j = 0;

  for (int i = 0; src[i]; ++i)
  {
    switch (src[i])
    {
      case '\t':       // 9
        dst[j++] = '\\';
        dst[j] = 't';
        break;
      case '\n':       // 10
        dst[j++] = '\\';
        dst[j] = 'n';
        break;
      case '\"':       // 34
        dst[j++] = '\\';
        dst[j] = '\"';
        break;
      case '\\':       // 92
        dst[j++] = '\\';
        dst[j] = '\\';
        break;
      default:
        dst[j] = src[i];
        break;
    }
    ++j;
  }
  dst[j] = src[i]; // src[i] is '\0' here, acting as the null-terminator
}