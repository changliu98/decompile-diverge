void escape(char *out, char *in)
{
  int i = 0; int j = 0;
  for (i = 0; in[i]; i++)
  {
    switch (in[i])
    {
      case '\a':
        out[j] = '\\';
        j++;
        out[j] = 'a';
        break;
      case '\b':
        out[j] = '\\';
        j++;
        out[j] = 'b';
        break;
      case '\t':
        out[j] = '\\';
        j++;
        out[j] = 't';
        break;
      case '\n':
        out[j] = '\\';
        j++;
        out[j] = 'n';
        break;
      case '\v':
        out[j] = '\\';
        j++;
        out[j] = 'v';
        break;
      case '\f':
        out[j] = '\\';
        j++;
        out[j] = 'f';
        break;
      case '\r':
        out[j] = '\\';
        j++;
        out[j] = 'r';
        break;
      case '\"':
        out[j] = '\\';
        j++;
        out[j] = '\"';
        break;
      case '\'':
        out[j] = '\\';
        j++;
        out[j] = '\'';
        break;
      case '\\':
        out[j] = '\\';
        j++;
        out[j] = '\\';
        break;
      case '?':
        out[j] = '\\';
        j++;
        out[j] = '?';
        break;
      default:
        out[j] = in[i];
    }
    j++;
  }
  out[j] = '\0';
}