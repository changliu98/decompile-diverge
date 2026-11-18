char *__cdecl m_stpcpy(char *out, const char *in)
{
  while ( (*out++ = *in++) != '\0' )
    ;
  return out - 1;
}