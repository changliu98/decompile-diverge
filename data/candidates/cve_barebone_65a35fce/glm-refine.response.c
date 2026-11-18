rsRetVal __cdecl strmReadMultiLine(
        strm_t *pThis,
        cstr_t **ppCStr,
        regex_t *preg,
        const sbool bEscapeLF,
        const sbool discardTruncatedMsg,
        const sbool msgDiscardingError)
{
  const regex_t *v9;
  time_t Time;
  int z;
  int len;
  int currLineLen;
  rsRetVal iRet;
  signed int maxMsgSize;
  rsRetVal readCharRet;
  cstr_t *thisLine;
  uchar finished;
  uchar c;
  sbool msgDiscardingErrora;
  sbool discardTruncatedMsga;
  sbool bEscapeLFa;
  regex_t *prega;
  cstr_t **ppCStra;
  strm_t *pThisa;

  pThisa = pThis;
  ppCStra = ppCStr;
  prega = preg;
  bEscapeLFa = bEscapeLF;
  discardTruncatedMsga = discardTruncatedMsg;
  msgDiscardingErrora = msgDiscardingError;
  finished = 0;
  thisLine = 0LL;
  if ( pThisa->readTimeout )
    Time = getTime(0LL);
  else
    Time = 0LL;
  maxMsgSize = glblGetMaxLine();
  
  do
  {
    iRet = strmReadChar(pThisa, &c);
    if ( iRet )
      break;
      
    pThisa->lastRead = Time;
    iRet = cstrConstruct(&thisLine);
    if ( iRet )
      break;
      
    if ( pThisa->prevLineSegment )
    {
      iRet = cstrAppendCStr(thisLine, pThisa->prevLineSegment);
      if ( iRet )
        break;
      rsCStrDestruct(&pThisa->prevLineSegment);
    }
    
    while ( c != 10 )
    {
      iRet = cstrAppendChar(thisLine, c);
      if ( !iRet )
      {
        readCharRet = strmReadChar(pThisa, &c);
        if ( readCharRet != -2026 || (iRet = rsCStrConstructFromCStr(&pThisa->prevLineSegment, thisLine)) == 0 )
        {
          iRet = readCharRet;
          if ( !readCharRet )
            continue;
        }
      }
      goto finalize_it;
    }
    
    if ( thisLine->iStrLen )
      thisLine->pBuf[thisLine->iStrLen] = 0;
      
    v9 = prega;
    uchar *SzStrNoNULL = cstrGetSzStrNoNULL(thisLine);
    
    if ( regexec(v9, (const char *)SzStrNoNULL, 0LL, 0LL, 0) )
    {
      if ( !pThisa->ignoringMsg )
      {
        if ( pThisa->prevMsgSegment )
        {
          if ( bEscapeLFa )
            rsCStrAppendStrWithLen(pThisa->prevMsgSegment, &psz, 2uLL);
          else
            cstrAppendChar(pThisa->prevMsgSegment, 0xAu);
            
          currLineLen = thisLine->iStrLen;
          if ( currLineLen > 0 )
          {
            if ( (int)(currLineLen + pThisa->prevMsgSegment->iStrLen) >= maxMsgSize )
            {
              len = maxMsgSize - pThisa->prevMsgSegment->iStrLen;
              for ( z = 0; z < len; ++z )
                cstrAppendChar(pThisa->prevMsgSegment, thisLine->pBuf[z]);
                
              finished = 1;
              *ppCStra = pThisa->prevMsgSegment;
              iRet = rsCStrConstructFromszStr(&pThisa->prevMsgSegment, &thisLine->pBuf[len]);
              if ( iRet )
                break;
                
              if ( discardTruncatedMsga == 1 )
                pThisa->ignoringMsg = 1;
                
              if ( msgDiscardingErrora == 1 )
              {
                if ( discardTruncatedMsga == 1 )
                  errmsg(
                    0LL,
                    4294964296LL,
                    "imfile error: message received is larger than max msg size; rest of message will not be processed");
                else
                  errmsg(
                    0LL,
                    4294964296LL,
                    "imfile error: message received is larger than max msg size; message will be split and processed as another message");
              }
            }
            else
            {
              iRet = cstrAppendCStr(pThisa->prevMsgSegment, thisLine);
              if ( iRet )
                break;
            }
          }
        }
        else
        {
          iRet = rsCStrConstructFromCStr(&pThisa->prevMsgSegment, thisLine);
          if ( iRet )
            break;
        }
      }
    }
    else
    {
      if ( !pThisa->ignoringMsg && pThisa->prevMsgSegment )
      {
        finished = 1;
        *ppCStra = pThisa->prevMsgSegment;
      }
      iRet = rsCStrConstructFromCStr(&pThisa->prevMsgSegment, thisLine);
      if ( iRet )
        break;
      pThisa->ignoringMsg = 0;
    }
    rsCStrDestruct(&thisLine);
  }
  while ( !finished );
  
finalize_it:
  while ( pThisa->readTimeout && iRet && pThisa->prevMsgSegment && Time > pThisa->readTimeout + pThisa->lastRead )
  {
    iRet = rsCStrConstructFromCStr(ppCStra, pThisa->prevMsgSegment);
    if ( !iRet )
    {
      rsCStrDestruct(&pThisa->prevMsgSegment);
      pThisa->lastRead = Time;
      uchar *v7 = cstrGetSzStrNoNULL(*ppCStra);
      dbgprintf("stream: generated msg based on timeout: %s\n", (const char *)v7);
    }
  }
  return iRet;
}