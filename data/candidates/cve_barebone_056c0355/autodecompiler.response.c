void xmlrpc_char_encode(char *dest, char *src)
{
  mowgli_string_t *str = mowgli_string_create();
  size_t i;
  char buf[16] = { 0 };

  *dest = '\0';

  if (!src || !*src)
    return;

  for (i = 0;; i++)
  {
    unsigned int c;

    if (!src[i])
      break;

    c = (unsigned int)src[i];

    if (c >= 128)
    {
      snprintf(buf, sizeof(buf) - 1, "&#%d;", c);
      str->append(str, buf, strlen(buf));
    }
    else if (c == '&')
      str->append(str, "&amp;", 5);
    else if (c == '<')
      str->append(str, "&lt;", 4);
    else if (c == '>')
      str->append(str, "&gt;", 4);
    else if (c == '"')
      str->append(str, "&quot;", 6);
    else
      str->append_char(str, (char)c);
  }

  memcpy(dest, str->string, 4096);
}