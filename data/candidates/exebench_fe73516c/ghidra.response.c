char * strcpy(char *pDestination,char *pSource)

{
  char cVar1;
  char *pSaveDest;
  char *pSource_local;
  char *pDestination_local;
  
  pDestination_local = pDestination;
  for (pSource_local = pSource; cVar1 = *pSource_local, *pDestination_local = cVar1, cVar1 != '\0';
      pSource_local = pSource_local + 1) {
    pDestination_local = pDestination_local + 1;
  }
  return pDestination;
}