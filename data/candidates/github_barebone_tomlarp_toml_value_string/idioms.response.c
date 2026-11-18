int toml_value_string(char *in, char **out, int *outlen)
{
  char *inend;
  char *instart = in;
  int quote;
  int multiline = 0;
  *out = ((void *)0);
  if (in == ((void *)0))
    return -1;
  quote = *instart;
  inend = in + strlen(in);
  if (quote != '\'' && quote != '"')
    return -1;
  if (instart[1] == quote &&
      instart[2] == quote)
  {
    multiline = 1;
    instart += 3;
    inend -= 3;
    if (instart > inend ||
        inend[0] != quote ||
        inend[1] != quote ||
        inend[2] != quote)
      return -1;
    if (instart[0] == '\n')
      instart += 1;
    else if (instart[0] == '\r' &&
             instart[1] == '\n')
      instart += 2;
  }
  else
  {
    instart += 1;
    inend -= 1;
    if (instart > inend ||
        inend[0] != quote)
      return -1;
  }
  if (quote == '\'')
    *out = norm_lit_str(instart, inend - instart,
                        outlen, multiline, ((void *)0), ((void *)0));
  else
    *out = norm_basic_str(instart, inend - instart,
                          outlen, multiline, ((void *)0), ((void *)0));
  if (*out == ((void *)0))
    return -1;
  return 0;
}