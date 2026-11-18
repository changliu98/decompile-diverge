char *to_snake(char *in, char *out)
{
  int i = 0;
  int o = 0;
  int cap = 1;
  while (in[i])
  {
    if (in[i] == '_')
    {
      cap = 1;
    }
    else if (cap)
    {
      out[o++] = toupper(in[i]);
      cap = 0;
    }
    else
    {
      out[o++] = in[i];
    }
    i++;
  }
  out[o] = '\0';
  return out;
}