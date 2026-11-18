char *gf_text_get_utf8_line(char *line, unsigned int line_size, char *txt_in, int unicode_type)
{
  char *line_out;
  char *line_in = line;
  char line_conv[-1];
  unsigned int i; unsigned int j;
  unsigned int len;
  char tmp;
  char *end;
  int ret;
  clear_line(line, 0, line_size);
  line_out = get_line(line, line_size, txt_in);
  if (line_out == ((void *)0))
    return ((void *)0);
  if (unicode_type < 2)
  {
    for (j = 0, len = get_line_len(line_in); j < len; j++)
    {
      if (unicode_type == 0 && (line_in[j] & 0x80))
      {
        if ((line_in[j + 1] & 0xc0) != 0x80)
        {
          line_conv[j++] = (line_in[j] & 0xc0) | 0x80;
          line_in[j] = line_in[j] & ~0x40;
        }
        else
        {
          if ((line_in[j] & 0xe0) == 0xc0)
          {
            line_conv[j] = line_in[j];
            j++;
          }
          else if ((line_in[j] & 0xf0) == 0xe0)
          {
            line_conv[j] = line_in[j];
            j++;
            line_conv[j] = line_in[j];
            j++;
          }
          else if ((line_in[j] & 0xf8) == 0xf0)
          {
            line_conv[j] = line_in[j];
            j++;
            line_conv[j] = line_in[j];
            j++;
            line_conv[j] = line_in[j];
            j++;
          }
        }
      }
      line_conv[j] = line_in[j];
      if (j >= (unsigned int)(sizeof(line_conv) - 1))
        break;
    }
    line_conv[j] = '\0';
    convert_to_utf8(line_in, line_conv);
  }
  else if (unicode_type == 2)
  {
    for (i = 0; line_in[i] != '\0' && line_in[i + 1] != '\0'; i += 2)
    {
      tmp = line_in[i + 1];
      line_in[i + 1] = line_in[i];
      line_in[i] = tmp;
    }
  }
  end = (char *)line_in;
  ret = convert_to_utf16(line_conv, sizeof(line_conv), &end);
  if (ret == -1)
    ret = 0;
  line_conv[ret] = '\0';
  convert_to_utf8(line_in, line_conv);
  if (unicode_type == 3)
    convert_to_utf8_reverse(txt_in);
  return line_out;
}