int mobi_search_links_kf7( TS_PLAY_LIST *pTSPlayList, char* pStart, char* pEnd )
{
 int found = 0;
 char *p, *p1, *p2;
 unsigned long len, len1, len2, len_min;
 char border, tag_open, tag_close;
 int i;
 if ( pTSPlayList == NULL )
  return 2;

 pTSPlayList->ts_file_pos = 0;
 pTSPlayList->ts_rec_index = 0;
 pTSPlayList->filename[0] = '\0';
 if ( pStart == NULL || pEnd == NULL )
 {
  return 2;
 }

 p1 = "filepos=";
 p2 = "recindex=";
 len1 = strlen(p1);
 len2 = strlen(p2);
 if ( len1 > len2 )
  len_min = len1;
 else
  len_min = len2;

 if ( pStart + len_min > pEnd )
 {
  return 0;
 }

 p = pStart;
 tag_open = '<';
 tag_close = '>';
 border = '<';

 while( !found )
 {
  if ( p > pEnd )
   break;

  switch(*p)
  {
  case '<':
  case '>':
   border = *p;
   break;
  default:
   if ( p + len_min <= pEnd )
   {
    if ( memcmp( p, p1, len1 ) == 0 ||
      memcmp( p, p2, len2 ) == 0 )
    {
     if ( border == '<' )
     {
      while(1)
      {
       if ( p < pStart || (((unsigned short)___ctype_b_loc()[(unsigned char)(*p)] & (unsigned short)(0x2000)) != (unsigned short)(0x2000)) || (*p == '<') )
        break;
       p--;
      }
      pTSPlayList->ts_file_pos = ++p;
      for ( i=0; i<151; )
      {
       if ( p > pEnd || (((unsigned short)___ctype_b_loc()[(unsigned char)(*p)] & (unsigned short)(0x2000)) != (unsigned short)(0x2000)) || (*p == '>') || ( i >= 151 ) )
        break;
       pTSPlayList->filename[i++] = *p++;
      }
      if ( *(p-1) == '/' && *p == '>' )
      {
       p--;
       i--;
      }
      pTSPlayList->ts_rec_index = p;
      pTSPlayList->filename[i] = '\0';
      found = 1;
     }
     else
      p += len_min;
    }
   }
   break;
  }
  if ( !found )
   p++;
 }

 return found;
}