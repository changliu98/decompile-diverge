char *get_line(struct _STREAM *stream, char *line)
{
  char *ret = ((void *)0);
  ret = get_line_ex(line, 1024, stream);
  if (ret == ((void *)0))
    return ((void *)0);
  if (line[get_line_len(line)-1] == '\n')
    line[get_line_len(line)-1] = '\0';
  return ret;
}