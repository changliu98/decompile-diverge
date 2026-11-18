char *__cdecl gdb_to_rz_profile(const char *gdb)
{
  int v1; // eax
  const char *v2; // rdx
  bool v4; // [rsp+27h] [rbp-119h]
  char *ptr; // [rsp+28h] [rbp-118h]
  char *ptra; // [rsp+28h] [rbp-118h]
  int ret; // [rsp+34h] [rbp-10Ch]
  int type_bits; // [rsp+38h] [rbp-108h]
  int size; // [rsp+3Ch] [rbp-104h]
  unsigned int offset; // [rsp+40h] [rbp-100h]
  char type; // [rsp+70h] [rbp-D0h]
  char groups[128]; // [rsp+80h] [rbp-C0h] BYREF
  char name[16]; // [rsp+100h] [rbp-40h] BYREF
  char *gptr1; // [rsp+110h] [rbp-30h]
  char *gptr; // [rsp+118h] [rbp-28h]
  char *ptr1; // [rsp+120h] [rbp-20h]
  RzStrBuf *sb; // [rsp+128h] [rbp-18h]
  const char *gdba; // [rsp+130h] [rbp-10h]

  gdba = gdb;
  if ( !gdb )
    return 0LL;
  sb = rz_strbuf_new("");
  if ( !sb )
    return 0LL;
  ptr = (char *)rz_str_trim_head_ro(gdba);
  if ( !rz_str_startswith(ptr, "Name") )
    goto LABEL_9;
  ptra = strchr(ptr, 10);
  if ( ptra )
  {
    ptr = ptra + 1;
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
      v1 = __isoc99_sscanf();
      ret = v1;
      if ( v1 >= 6 )
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
            v4 = 1;
            if ( (type_bits & 0x100) == 0 )
            {
              v4 = 1;
              if ( (type_bits & 0x10) == 0 )
                v4 = (type_bits & 0x20) != 0;
            }
            v2 = "gpr";
            if ( v4 )
              v2 = "fpu";
            rz_strbuf_appendf(sb, "%s\t%s\t.%d\t%d\t0\n", v2, name, (unsigned int)(8 * size), offset);
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
  else
  {
    rz_strbuf_free(sb);
    return 0LL;
  }
}