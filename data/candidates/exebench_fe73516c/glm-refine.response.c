char *__cdecl strcpy(char *pDestination, const char *pSource)
{
  char *pDest = pDestination;

  while ((*pDest++ = *pSource++) != '\0')
    ;

  return pDestination;
}