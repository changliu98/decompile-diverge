void html_escape(char *outbuffer, char *inbuffer)
{
  char *out = outbuffer;
  char *in = inbuffer;
  struct mowgli_string *str = mowgli_string_new();
  char buf[15];
  char c;
  unsigned long i;
  buf[0] = '\0';
  out[0] = '\0';
  if (in && *in)
  {
    for (i = 0; in[i]; i++)
    {
      c = in[i];
      if (c > 127)
      {
        html_int2str(buf, sizeof(buf), "&#%d;", c);
        str->append = str->append;
        str->append(str, buf, html_strlen(buf));
      }
      else
      {
        switch (c)
        {
          case '&':
            str->append(str, "&amp;", 5);
            break;
          case '<':
            str->append(str, "&lt;", 4);
            break;
          case '>':
            str->append(str, "&gt;", 4);
            break;
          case '\"':
            str->append(str, "&quot;", 6);
            break;
          default:
            str->append_char(str, c);
            break;
        }
      }
    }
    str->tostring(out, str->str, sizeof(out));
  }
}