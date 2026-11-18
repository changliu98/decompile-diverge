char *__cdecl m_stpcpy(char *out, const char *in)
{
  size_t i; // [rsp+0h] [rbp-18h]

  for ( i = 0LL; in[i]; ++i )
    out[i] = in[i];
  out[i] = 0;
  return &out[i];
}