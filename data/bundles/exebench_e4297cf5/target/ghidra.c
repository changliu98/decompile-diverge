char * m_stpcpy(char *out,char *in)

{
  size_t i;
  char *in_local;
  char *out_local;
  
  for (i = 0; in[i] != '\0'; i = i + 1) {
    out[i] = in[i];
  }
  out[i] = '\0';
  return out + i;
}