char *__cdecl gdb_to_rz_profile(const char *gdb)
{
  char *ptr;
  char *ptr1;
  int ret;
  int type_bits;
  int size;
  unsigned int offset;
  char type;
  char groups[128];
  char name[16];
  char *gptr1;
  char *gptr;
  RzStrBuf *sb;

  if ( !gdb )
    return 0LL;
  sb = rz_strbuf_new("");
  if ( !sb )
    return 0LL;
  ptr = (char *)rz_str_trim_head_ro(gdb);
  if ( !rz_str_startswith(ptr, "Name") )
    goto LABEL_9;
  ptr = strchr(ptr, 10);
  if ( !ptr )
  {
    rz_strbuf_free(sb);
    return 0LL;
  }
  ++ptr;

  while ( 1 )
  {
LABEL_9:
    while ( ((*__ctype_b_loc())[(unsigned __int8)*ptr] & 0x2000) != 0 )
      ++ptr;
    if ( !*ptr )
      break;
    ptr1 = strchr(ptr, 10);
    if ( !ptr1 )
    {
      fprintf(stderr, "Could not parse line: %s (missing \\n)\n", ptr);
      rz_strbuf_free(sb);
      return 0LL;
    }
    *ptr1 = 0;
    ret = __isoc99_sscanf(ptr, "%15s %c %d %d %127s %d", name, &type, &size, &offset, groups, &type_bits);
    if ( ret >= 6 )
    {
      if ( rz_str_startswith(name, "''") )
      {
        if ( !ptr1 )
          return rz_strbuf_drain(sb);
        ptr = ptr1 + 1;
      }
      else if ( size )
      {
        type_bits = 0;
        if ( ret >= 7 )
        {
          for ( gptr = groups; ; gptr = gptr1 + 1 )
          {
            gptr1 = strchr(gptr, 44);
            if ( gptr1 )
              *gptr1 = 0;
            if ( rz_str_startswith(gptr, "general") )
            {
              type_bits |= 2u;
            }
            else if ( rz_str_startswith(gptr, "all") )
            {
              type_bits |= 1u;
            }
            else if ( rz_str_startswith(gptr, "save") )
            {
              type_bits |= 4u;
            }
            else if ( rz_str_startswith(gptr, "restore") )
            {
              type_bits |= 8u;
            }
            else if ( rz_str_startswith(gptr, "float") )
            {
              type_bits |= 0x10u;
            }
            else if ( rz_str_startswith(gptr, "sse") )
            {
              type_bits |= 0x20u;
            }
            else if ( rz_str_startswith(gptr, "mmx") )
            {
              type_bits |= 0x100u;
            }
            else if ( rz_str_startswith(gptr, "vector") )
            {
              type_bits |= 0x40u;
            }
            else if ( rz_str_startswith(gptr, "system") )
            {
              type_bits |= 0x80u;
            }
            if ( !gptr1 )
              break;
          }
        }
        if ( type )
        {
          if ( (type_bits & 0x20) == 0 && (type_bits & 0x10) == 0 )
            LOWORD(type_bits) = type_bits | 2;
          bool is_fpu = 1;
          if ( (type_bits & 0x100) == 0 )
          {
            is_fpu = 1;
            if ( (type_bits & 0x10) == 0 )
              is_fpu = (type_bits & 0x20) != 0;
          }
          const char *reg_type = "gpr";
          if ( is_fpu )
            reg_type = "fpu";
          rz_strbuf_appendf(sb, "%s\t%s\t.%d\t%d\t0\n", reg_type, name, (unsigned int)(8 * size), offset);
          if ( !ptr1 )
            return rz_strbuf_drain(sb);
          ptr = ptr1 + 1;
        }
        else
        {
          if ( !ptr1 )
            return rz_strbuf_drain(sb);
          ptr = ptr1 + 1;
        }
      }
      else
      {
        if ( !ptr1 )
          return rz_strbuf_drain(sb);
        ptr = ptr1 + 1;
      }
    }
    else
    {
      if ( *ptr != 42 )
      {
        fprintf(stderr, "Could not parse line: %s\n", ptr);
        rz_strbuf_free(sb);
        return 0LL;
      }
      ptr = ptr1 + 1;
    }
  }
  return rz_strbuf_drain(sb);
}