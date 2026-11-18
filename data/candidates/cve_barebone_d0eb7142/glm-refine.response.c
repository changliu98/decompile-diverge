MOBI_RET __cdecl mobi_search_links_kf7(
        MOBIResult *result,
        const unsigned __int8 *data_start,
        const unsigned __int8 *data_end)
{
  const unsigned __int8 *data;
  const unsigned __int8 *link_start;
  size_t max_needle_len;
  size_t needle1_len;
  size_t needle2_len;
  unsigned __int8 last_border;
  int i;

  // Sanity check for the output structure
  if (!result)
    return 2;
  
  result->end = 0LL;
  result->start = 0LL;
  result->value[0] = 0;
  
  // Sanity check for input boundaries
  if (!data_start || !data_end)
    return 2;

  // Determine the length of the longest search needle
  needle1_len = strlen("filepos=");
  needle2_len = strlen("recindex=");
  max_needle_len = (needle1_len > needle2_len) ? needle1_len : needle2_len;

  // If the remaining data is shorter than the longest needle, no match is possible
  if (&data_start[max_needle_len] > data_end)
    return 0;

  data = data_start;
  last_border = '<'; // ASCII 60

  // 1. Search for "filepos=" or "recindex=" preceded by '<'
  while (1)
  {
    // Advance until we find a needle or go out of bounds
    while (1)
    {
      if (data > data_end)
        return 0;

      // Track the last encountered '<' (60) or '>' (62)
      if (*data == '<' || *data == '>')
        last_border = *data;

      // Check if the current position matches either needle
      if (&data[max_needle_len] <= data_end &&
          (!memcmp(data, "filepos=", needle1_len) || !memcmp(data, "recindex=", needle2_len)))
      {
        break;
      }
      ++data;
    }

    // If the needle was found inside a tag (last char seen was '<'), proceed
    if (last_border == '<')
      break;

    // Otherwise, skip past this false match and keep searching
    data += max_needle_len;
  }

  // 2. Walk backward to find the beginning of the attribute (non-space, non-'<')
  while (1)
  {
    bool is_valid_char = false;
    if (data >= data_start)
    {
      // Equivalent to !isspace(*data) && *data != '<'
      if (((*__ctype_b_loc())[*data] & _ISspace) == 0)
        is_valid_char = (*data != '<');
    }
    
    if (!is_valid_char)
      break;
      
    --data;
  }

  // The actual link value starts at the next character
  link_start = data + 1;
  result->start = link_start;

  // 3. Walk forward to extract the link value (up to 150 chars, stopping at '>' or space)
  for (i = 0; ; ++i)
  {
    bool is_valid_char = false;
    if (link_start <= data_end)
    {
      // Equivalent to !isspace(*link_start) && *link_start != '>' && i < 150
      if (((*__ctype_b_loc())[*link_start] & _ISspace) == 0)
      {
        if (*link_start != '>')
          is_valid_char = (i < 150);
      }
    }
    
    if (!is_valid_char)
      break;

    result->value[i] = *link_start;
    ++link_start;
  }

  // 4. Handle self-closing tags (e.g., strip the trailing '/' in "/>")
  if (*(link_start - 1) == '/' && *link_start == '>')
  {
    --link_start;
    --i;
  }

  // 5. Finalize the result structure
  result->end = link_start;
  result->value[i] = 0;

  return 0;
}