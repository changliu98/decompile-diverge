char *__cdecl strcpy(char *pDestination, const char *pSource)
{
  char v2; // al
  char *pDestinationa; // [rsp+10h] [rbp-8h]

  for ( pDestinationa = pDestination; ; ++pDestinationa )
  {
    v2 = *pSource;
    *pDestinationa = *pSource;
    if ( !v2 )
      break;
    ++pSource;
  }
  return pDestination;
}