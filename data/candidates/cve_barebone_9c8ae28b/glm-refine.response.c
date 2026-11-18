void __cdecl messageAddArgument(message *m, const char *arg)
{
  char *parsed_arg;
  char **new_args;
  char *current_arg;
  int offset;
  const char *trimmed_arg;

  if ( !m )
    __assert_fail("m != NULL", "/work/harness.c", 0x15AU, "void messageAddArgument(message *, const char *)");
    
  if ( arg )
  {
    // Skip leading whitespace
    trimmed_arg = arg;
    while ( ((*__ctype_b_loc())[(unsigned char)*trimmed_arg] & 0x2000) != 0 )
      ++trimmed_arg;

    if ( *trimmed_arg && usefulArg(trimmed_arg) )
    {
      // Check for duplicate arguments
      for ( offset = 0; offset < m->numberOfArguments && m->mimeArguments[offset]; ++offset )
      {
        if ( !strcasecmp(trimmed_arg, m->mimeArguments[offset]) )
          return;
      }

      // If we reached the end of the arguments array, reallocate to grow it
      if ( offset == m->numberOfArguments )
      {
        new_args = (char **)cli_realloc(m->mimeArguments, 8LL * ++m->numberOfArguments);
        if ( !new_args )
        {
          --m->numberOfArguments;
          return;
        }
        m->mimeArguments = new_args;
      }

      // Parse the argument using RFC 2231
      parsed_arg = rfc2231(trimmed_arg);
      m->mimeArguments[offset] = parsed_arg;
      current_arg = parsed_arg;

      if ( parsed_arg )
      {
        // If there is no '=' in the argument, check if it starts with `bytes`
        if ( !strchr(parsed_arg, 61) ) // 61 is ASCII for '='
        {
          if ( strncmp(current_arg, bytes, 8uLL) )
          {
            free(m->mimeArguments[offset]);
            m->mimeArguments[offset] = NULL;
            return;
          }
          current_arg[8] = '='; // Append '=' after "bytes"
        }

        // Check for specific MIME type prefixes and update message MIME type if necessary
        if ( (!strncasecmp(current_arg, qword_42A2, 9uLL) || !strncasecmp(current_arg, &qword_42A2[4], 5uLL))
          && messageGetMimeType(m) == NOMIME )
        {
          messageSetMimeType(m, "application");
        }
      }
    }
  }
}