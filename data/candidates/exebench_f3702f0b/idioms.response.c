void escape(char *out, char *in)
{
  int i = 0; int j = 0;
  int c;
  while (in[i]) {
    c = in[i];
    switch (c) {
    case ' ':
      out[j++] = '\\';
      out[j++] = 'b';
      break;
    case '\n':
      out[j++] = '\\';
      out[j++] = 'n';
      break;
    case '\t':
      out[j++] = '\\';
      out[j++] = 't';
      break;
    default:
      out[j++] = c;
    }
    i++;
  }
  out[j] = '\0';
}