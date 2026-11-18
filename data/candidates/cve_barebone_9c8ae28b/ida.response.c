void __cdecl messageAddArgument(message *m, const char *arg)
{
  char *v2; // rax
  char **q; // [rsp+8h] [rbp-28h]
  char *p; // [rsp+10h] [rbp-20h]
  int offset; // [rsp+1Ch] [rbp-14h]
  const char *arga; // [rsp+20h] [rbp-10h]

  arga = arg;
  if ( !m )
    __assert_fail("m != NULL", "/work/harness.c", 0x15Au, "void messageAddArgument(message *, const char *)");
  if ( arg )
  {
    while ( ((*__ctype_b_loc())[*arga] & 0x2000) != 0 )
      ++arga;
    if ( *arga && usefulArg(arga) )
    {
      for ( offset = 0; offset < m->numberOfArguments && m->mimeArguments[offset]; ++offset )
      {
        if ( !strcasecmp(arga, m->mimeArguments[offset]) )
          return;
      }
      if ( offset == m->numberOfArguments )
      {
        q = (char **)cli_realloc(m->mimeArguments, 8LL * ++m->numberOfArguments);
        if ( !q )
        {
          --m->numberOfArguments;
          return;
        }
        m->mimeArguments = q;
      }
      v2 = rfc2231(arga);
      m->mimeArguments[offset] = v2;
      p = v2;
      if ( v2 )
      {
        if ( !strchr(v2, 61) )
        {
          if ( strncmp(p, bytes, 8uLL) )
          {
            free(m->mimeArguments[offset]);
            m->mimeArguments[offset] = 0LL;
            return;
          }
          p[8] = 61;
        }
        if ( (!strncasecmp(p, qword_42A2, 9uLL) || !strncasecmp(p, &qword_42A2[4], 5uLL))
          && messageGetMimeType(m) == NOMIME )
        {
          messageSetMimeType(m, "application");
        }
      }
    }
  }
}