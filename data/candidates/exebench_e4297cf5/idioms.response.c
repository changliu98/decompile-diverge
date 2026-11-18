char *m_stpcpy(char *out, char *in)
{
  unsigned long i;
  for (i = 0; in[i]; i++)
    out[i] = in[i];
  out[i] = '\0';
  return out + i;
}