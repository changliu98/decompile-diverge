MOBI_RET __cdecl mobi_search_links_kf7(
        MOBIResult *result,
        const unsigned char *data_start,
        const unsigned char *data_end)
{
  size_t needle1_length, needle2_length, max_needle_length;
  unsigned char *data;
  unsigned char *dataa;
  unsigned char last_border;
  int i;

  if ( !result )
    return 2;
    
  result->end = NULL;
  result->start = NULL;
  result->value[0] = '\0';
  
  if ( !data_start || !data_end )
    return 2;

  needle1_length = strlen("filepos=");
  needle2_length = strlen("recindex=");
  
  max_needle_length = (needle1_length > needle2_length) ? needle1_length : needle2_length;

  if ( &data_start[max_needle_length] > data_end )
    return 0;

  data = (unsigned char *)data_start;
  last_border = '>'; // 60 is '<', 62 is '>'

  // Find the next occurrence of "filepos=" or "recindex=" preceded by '<'
  while ( 1 )
  {
    while ( 1 )
    {
      if ( data > data_end )
        return 0;
        
      if ( *data == '<' || *data == '>' )
        last_border = *data;
        
      if ( &data[max_needle_length] <= data_end
        && (!memcmp(data, "filepos=", needle1_length) || !memcmp(data, "recindex=", needle2_length)) )
      {
        break;
      }
      ++data;
    }
    
    if ( last_border == '<' )
      break;
      
    data += max_needle_length;
  }

  // Walk backwards to find the start of the tag (skipping whitespace)
  while ( 1 )
  {
    bool is_non_space = false;
    if ( data >= data_start )
    {
      is_non_space = (!isspace(*data) && *data != '<');
    }
    if ( !is_non_space )
      break;
    --data;
  }

  dataa = data + 1;
  result->start = dataa;

  // Extract the attribute value (up to 150 chars, stopping at whitespace or '>')
  for ( i = 0; ; ++i )
  {
    bool keep_going = false;
    if ( dataa <= data_end )
    {
      keep_going = (!isspace(*dataa) && *dataa != '>' && i < 150);
    }
    if ( !keep_going )
      break;
      
    result->value[i] = *dataa++;
  }

  // Handle self-closing tags like "/>"
  if ( *(dataa - 1) == '/' && *dataa == '>' )
  {
    --dataa;
    --i;
  }

  result->end = dataa;
  result->value[i] = '\0';
  
  return 0;
}