int get_line_len(char *line)
{
  int len = 0;
  int i;
  for (; *line == ' '; line++)
    continue;
  for (i = 0; i < strlen(line); i++) {
    if (line[i] == ' ')
      len = 0;
    else
      len++;
  }
  return len;
}