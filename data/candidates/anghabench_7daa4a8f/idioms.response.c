char *stb_skipnewline(char *line)
{
  if (line[0] == '\r' || line[0] == '\n')
  {
    if (line[0] + line[1] == '\r'+'\n')
    {
      line++;
    }
    line++;
  }
  return (line);
}