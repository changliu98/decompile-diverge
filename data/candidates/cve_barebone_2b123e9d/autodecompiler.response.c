int
writefile( char *pcFilename, tBuf *ptBuffer )
{
  FILE *fFile;
  int iResult;

  fFile = fopen( pcFilename, "w" );
  if ( fFile == NULL )
  {
    vLoggingPrintf( "open %s:", pcFilename );
    iResult = -1;
  }
  else
  {
    int iError = 0;
    if ( fwrite( &ptBuffer->pcBuf[0], sizeof(char),
                 ptBuffer->iLength, fFile ) != ptBuffer->iLength
         || fflush( fFile ) != 0 )
    {
      vLoggingPrintf( "write %s:", pcFilename );
      iError = -1;
    }
    fclose( fFile );
    iResult = iError;
  }
  return iResult;
}