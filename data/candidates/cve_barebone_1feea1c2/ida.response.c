char *__cdecl build_ustar_entry_name(char *dest, const char *src, size_t src_length, const char *insert)
{
  char *v4; // rax
  char *v5; // rax
  bool v7; // [rsp+5h] [rbp-7Bh]
  bool v8; // [rsp+6h] [rbp-7Ah]
  bool v9; // [rsp+7h] [rbp-79h]
  size_t insert_length; // [rsp+8h] [rbp-78h]
  size_t suffix_length; // [rsp+10h] [rbp-70h]
  size_t suffix_lengtha; // [rsp+10h] [rbp-70h]
  size_t suffix_lengthb; // [rsp+10h] [rbp-70h]
  int need_slash; // [rsp+1Ch] [rbp-64h]
  char *p; // [rsp+20h] [rbp-60h]
  char *pa; // [rsp+20h] [rbp-60h]
  const char *filename_end; // [rsp+28h] [rbp-58h]
  const char *filename; // [rsp+30h] [rbp-50h]
  const char *suffix_end; // [rsp+38h] [rbp-48h]
  const char *prefix_end; // [rsp+48h] [rbp-38h]

  need_slash = 0;
  suffix_length = 99LL;
  if ( insert )
    insert_length = strlen(insert) + 2;
  else
    insert_length = 0LL;
  if ( src_length >= 0x64 || insert )
  {
    for ( filename_end = &src[src_length]; ; filename_end -= 2 )
    {
      while ( filename_end > src && *(filename_end - 1) == 47 )
      {
        --filename_end;
        need_slash = 1;
      }
      if ( filename_end <= src + 1 || *(filename_end - 1) != 46 || *(filename_end - 2) != 47 )
        break;
      need_slash = 1;
    }
    if ( need_slash )
      suffix_length = 98LL;
    for ( filename = filename_end - 1; ; --filename )
    {
      v9 = 0;
      if ( filename > src )
        v9 = *filename != 47;
      if ( !v9 )
        break;
    }
    if ( *filename == 47 && filename < filename_end - 1 )
      ++filename;
    suffix_lengtha = suffix_length - insert_length;
    if ( filename_end > &filename[suffix_lengtha] )
      filename_end = &filename[suffix_lengtha];
    suffix_lengthb = suffix_lengtha - (filename_end - filename);
    prefix_end = src + 155;
    if ( src + 155 > filename )
      prefix_end = filename;
    while ( 1 )
    {
      v8 = 0;
      if ( prefix_end > src )
        v8 = *prefix_end != 47;
      if ( !v8 )
        break;
      --prefix_end;
    }
    if ( prefix_end < filename && *prefix_end == 47 )
      ++prefix_end;
    suffix_end = &prefix_end[suffix_lengthb];
    if ( &prefix_end[suffix_lengthb] > filename )
      suffix_end = filename;
    if ( suffix_end < prefix_end )
      suffix_end = prefix_end;
    while ( 1 )
    {
      v7 = 0;
      if ( suffix_end > prefix_end )
        v7 = *suffix_end != 47;
      if ( !v7 )
        break;
      --suffix_end;
    }
    if ( suffix_end < filename && *suffix_end == 47 )
      ++suffix_end;
    p = dest;
    if ( prefix_end > src )
    {
      strncpy(dest, src, prefix_end - src);
      p = &dest[prefix_end - src];
    }
    if ( suffix_end > prefix_end )
    {
      strncpy(p, prefix_end, suffix_end - prefix_end);
      p += suffix_end - prefix_end;
    }
    if ( insert )
    {
      strcpy(p, insert);
      v4 = &p[strlen(insert)];
      p = v4 + 1;
      *v4 = 47;
    }
    strncpy(p, filename, filename_end - filename);
    pa = &p[filename_end - filename];
    if ( need_slash )
    {
      v5 = pa++;
      *v5 = 47;
    }
    *pa = 0;
    return dest;
  }
  else
  {
    strncpy(dest, src, src_length);
    dest[src_length] = 0;
    return dest;
  }
}