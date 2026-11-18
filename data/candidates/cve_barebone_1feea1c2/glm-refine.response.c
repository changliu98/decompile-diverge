char *__cdecl build_ustar_entry_name(char *dest, const char *src, size_t src_length, const char *insert)
{
  bool need_slash = false;
  size_t suffix_length = 99;
  size_t insert_length = insert ? (strlen(insert) + 2) : 0;

  // If the source path is too long or an insertion string is provided, 
  // we must split it into a USTAR prefix and suffix.
  if (src_length >= 100 || insert)
  {
    const char *filename_end = &src[src_length];

    // Strip trailing slashes from the end of the path
    while (filename_end > src && *(filename_end - 1) == '/')
    {
      --filename_end;
      need_slash = true;
    }

    // Strip trailing "/." or "/.." sequences
    while (filename_end > src + 1 && *(filename_end - 1) == '.' && *(filename_end - 2) == '/')
    {
      filename_end -= 2;
      need_slash = true;
    }

    if (need_slash)
      suffix_length = 98;

    // Find the start of the final path component (filename)
    const char *filename = filename_end - 1;
    while (filename > src && *filename != '/')
    {
      --filename;
    }
    if (*filename == '/' && filename < filename_end - 1)
      ++filename;

    // Truncate filename if it exceeds the available suffix space
    size_t max_suffix_len = suffix_length - insert_length;
    if (filename_end > &filename[max_suffix_len])
      filename_end = &filename[max_suffix_len];

    // Determine the end of the prefix (limited to 155 characters)
    const char *prefix_end = (src + 155 > filename) ? filename : (src + 155);
    while (prefix_end > src && *prefix_end != '/')
    {
      --prefix_end;
    }
    if (prefix_end < filename && *prefix_end == '/')
      ++prefix_end;

    // Determine the end of the suffix
    size_t remaining_suffix_len = max_suffix_len - (filename_end - filename);
    const char *suffix_end = &prefix_end[remaining_suffix_len];
    if (suffix_end > filename)
      suffix_end = filename;
    if (suffix_end < prefix_end)
      suffix_end = prefix_end;

    while (suffix_end > prefix_end && *suffix_end != '/')
    {
      --suffix_end;
    }
    if (suffix_end < filename && *suffix_end == '/')
      ++suffix_end;

    // Build the final string in dest
    char *p = dest;

    // Copy prefix
    if (prefix_end > src)
    {
      size_t prefix_len = prefix_end - src;
      strncpy(p, src, prefix_len);
      p += prefix_len;
    }

    // Copy suffix
    if (suffix_end > prefix_end)
    {
      size_t suffix_len = suffix_end - prefix_end;
      strncpy(p, prefix_end, suffix_len);
      p += suffix_len;
    }

    // Insert the extra string (if any) followed by a slash
    if (insert)
    {
      strcpy(p, insert);
      p += strlen(insert);
      *p++ = '/';
    }

    // Copy the filename component
    size_t filename_len = filename_end - filename;
    strncpy(p, filename, filename_len);
    p += filename_len;

    // Append trailing slash if it was stripped earlier
    if (need_slash)
      *p++ = '/';

    *p = '\0';
    return dest;
  }
  else
  {
    // Path is short enough and no insertion is needed; just copy it directly
    strncpy(dest, src, src_length);
    dest[src_length] = '\0';
    return dest;
  }
}