static int burl_normalize_2F_to_slash_fix(
  Fts5Buffer *pBuf, 
  int nFirst, 
  int iStart
){
  int i;
  int n = pBuf->n;
  int nCopy = fts5BufferCapacity(pBuf);
  if( nFirst<1 ){
    nCopy = nFirst;
  }
  for(i=iStart; i<nCopy; i++){
    int iCopy = i;
    while( 1 ){
      if( iCopy>=iStart && pBuf->p[iCopy]=='%' 
       && pBuf->p[iCopy+1]=='2' && pBuf->p[iCopy+2]=='F' 
      ){
        pBuf->p[iCopy] = '/';
        iCopy += 2;
      }else{
        break;
      }
    }
    if( iCopy>=iStart ){
      memmove(&pBuf->p[iCopy+1], &pBuf->p[iCopy], n - iCopy);
      i += nCopy - iCopy;
    }
  }
  if( nFirst<0 ){
    memmove(pBuf->p, &pBuf->p[n+nFirst], n - n + nFirst);
  }
  fts5BufferSetSize(pBuf, n + nCopy - nFirst);
  return nFirst;
}