int mobi_search_links_kf7( TS_PLAY_LIST *pTSPlayList, char* pStart, char* pEnd )
{
 int found = 0;
 char *p, *p1, *p2;
 unsigned long len, len1, len2, len_min;
 char border, tag_open, tag_close;
 int i;

 if ( pTSPlayList == NULL )
  return 2;

 pTSPlayList->filename_len = 0;
 pTSPlayList->filename_ptr = NULL;
 pTSPlayList->url[0] = '\0';

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

 while(1)
 {
  if ( p > pEnd )
   break;

  if ( *p == '<' || *p == '>' )
   border = *p;

  if ( p + len_min <= pEnd && ( memcmp(p,p1,len1) == 0 || memcmp(p,p2,len2) == 0 ) )
  {
   if ( border == '<' )
   {
    while(1)
    {
     if ( p < pStart || (((unsigned char) (*___ctype_b_loc ())[(int) ((*(char *)p))] & (unsigned short int) 0x2000)) != 0 || *p == '<' )
      break;
     p--;
    }
    pTSPlayList->filename_ptr = ++p;

    for ( i = 0; i<150; i++ )
    {
     if ( p > pEnd || (((unsigned char) (*___ctype_b_loc ())[(int) ((*(char *)p))] & (unsigned short int) 0x2000)) != 0 || *p == '>' )
      break;
     pTSPlayList->url[i++] = *p++;
    }

    if ( *(p-1) == '/' && *p == '>' )
    {
     p--;
     i--;
    }
    pTSPlayList->filename_len = i;
    pTSPlayList->url[i] = '\0';
    found = 1;
   }
   else
   {
    p += len_min;
   }
  }
  else
  {
   p++;
  }
 }

 return found;
}