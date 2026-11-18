char *gf_text_get_utf8_line(char *line, unsigned int line_size, struct _STREAM *stream, int unicode_type)
{
  char *line_conv = (char *)line;
  char *line_in = (char *)line;
  char *line_out = (char *)line;
  text_clear(line, 0, line_size);
  char *line_end = text_gets(line, line_size, stream);
  if (line_end == ((void *)0))
    return ((void *)0);
  if (unicode_type < 2)
  {
    unsigned long i; unsigned long j = 0; unsigned long len = text_getlen(line_in);
    for (i = 0; i < len; i++)
    {
      if (unicode_type == 0 && (line_in[i] & 0x80) != 0 && (line_in[i + 1] & 0xc0) == 0x80)
      {
        if ((line_in[i] & 0xe0) == 0xc0)
        {
          if (j < 2048 - 1)
          {
            line_conv[j] = (line_in[i] & 0x1f) | 0x80;
            line_in[i] &= ~0x40;
            i++;
          }
          else
          {
            line_conv[2048 - 1] = '\0';
            text_copy(line_in, line_conv);
            return line_end;
          }
        }
        else if ((line_in[i] & 0xf0) == 0xe0)
        {
          if (j + 1 < 2048 - 1)
          {
            line_conv[j] = (line_in[i] & 0x0f) | 0x80;
            line_in[i] &= ~0x40;
            i++;
            line_conv[++j] = (line_in[i] & 0x3f) | 0x80;
            line_in[i] &= ~0x40;
            i++;
            j++;
          }
          else
          {
            line_conv[2048 - 1] = '\0';
            text_copy(line_in, line_conv);
            return line_end;
          }
        }
        else if ((line_in[i] & 0xf8) == 0xf0)
        {
          if (j + 2 < 2048 - 1)
          {
            line_conv[j] = (line_in[i] & 0x07) | 0x80;
            line_in[i] &= ~0x40;
            i++;
            line_conv[++j] = (line_in[i] & 0x3f) | 0x80;
            line_in[i] &= ~0x40;
            i++;
            line_conv[++j] = (line_in[i] & 0x3f) | 0x80;
            line_in[i] &= ~0x40;
            i++;
            j++;
          }
          else
          {
            line_conv[2048 - 1] = '\0';
            text_copy(line_in, line_conv);
            return line_end;
          }
        }
        else
        {
          i++;
          continue;
        }
      }
      if (j < 2048 - 1)
      {
        line_conv[j] = line_in[i];
        j++;
      }
      else
      {
        line_conv[2048 - 1] = '\0';
        text_copy(line_in, line_conv);
        return line_end;
      }
    }
    if (j < 2048 - 1)
      line_conv[j] = '\0';
    else
      line_conv[2048 - 1] = '\0';
    text_copy(line_in, line_conv);
  }
  else if (unicode_type == 2)
  {
    unsigned long i;
    for (i = 0; line_in[i] != '\0' && line_in[i + 1] != '\0'; i += 2)
    {
      char tmp = line_in[i + 1];
      line_in[i + 1] = line_in[i];
      line_in[i] = tmp;
    }
  }
  unsigned long len = text_getlen(line_conv);
  unsigned long i = text_to_utf8(line_out, 2048 - 1, (unsigned short *)line_in);
  if (i == (unsigned long)-1)
    i = 0;
  line_conv[i] = '\0';
  text_copy(line_in, line_conv);
  if (unicode_type == 3)
    text_to_utf16(stream);
  return line_end;
}