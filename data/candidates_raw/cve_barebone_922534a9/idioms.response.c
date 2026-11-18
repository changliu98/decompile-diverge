enum MOBIResult mobi_parse_tag(struct MOBIResult *result, unsigned char *start, unsigned char *end)
{
  if ( !result )
    return MOBI_RES_NULL;
  result->end = ((void *)0);
  result->start = ((void *)0);
  result->value[0] = '\0';
  if ( !start || !end )
    return MOBI_RES_NULL;
  unsigned long needle1_len = mobi_strlen("filepos=");
  unsigned long needle2_len = mobi_strlen("recindex=");
  unsigned long needle_len = ( needle1_len > needle2_len ? needle1_len : needle2_len );
  if ( start + needle_len > end )
    return MOBI_RES_END;
  unsigned char *p = start;
  unsigned char last_border = '<';
  while ( 1 )
  {
    if ( p > end )
      return MOBI_RES_END;
    if ( *p == '<' || *p == '>' )
      last_border = *p;
    if ( p + needle_len <= end )
    {
      if (
        mobi_str_find( p, "filepos=", needle1_len )
        && mobi_str_find( p, "recindex=", needle2_len )
      )
        continue;
    }
    if ( last_border == '<' )
      break;
    p += needle_len;
  }
  while ( 1 )
  {
    int is_start = 0;
    if ( p >= start )
    {
      is_start =
        ( !mobi_is_space( *p ) )
        && ( *p != '<' );
    }
    if ( !is_start )
      break;
    --p;
  }
  ++p;
  result->start = p;
  int i = 0;
  while ( 1 )
  {
    int is_end = 0;
    if ( p <= end )
    {
      is_end =
        ( !mobi_is_space( *p ) )
        && ( *p != '>' )
        && ( i < 150 );
    }
    if ( !is_end )
      break;
    result->value[ i++ ] = *p++;
  }
  if ( p[-1] == '/' && p[0] == '>' )
  {
    --p;
    --i;
  }
  result->end = p;
  result->value[ i ] = '\0';
  return MOBI_RES_OK;
}