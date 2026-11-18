rsRetVal __cdecl strmReadMultiLine(
        strm_t *pThis,
        cstr_t **ppCStr,
        regex_t *preg,
        const sbool bEscapeLF,
        const sbool discardTruncatedMsg,
        const sbool msgDiscardingError)
{
  uchar *SzStrNoNULL; // rax
  uchar *v7; // rax
  const regex_t *v9; // [rsp+8h] [rbp-78h]
  time_t Time; // [rsp+10h] [rbp-70h]
  int z; // [rsp+30h] [rbp-50h]
  int len; // [rsp+34h] [rbp-4Ch]
  int currLineLen; // [rsp+38h] [rbp-48h]
  rsRetVal iRet; // [rsp+40h] [rbp-40h]
  signed int maxMsgSize; // [rsp+44h] [rbp-3Ch]
  rsRetVal readCharRet; // [rsp+54h] [rbp-2Ch]
  cstr_t *thisLine; // [rsp+58h] [rbp-28h] BYREF
  uchar finished; // [rsp+63h] [rbp-1Dh]
  uchar c; // [rsp+64h] [rbp-1Ch] BYREF
  sbool msgDiscardingErrora; // [rsp+65h] [rbp-1Bh]
  sbool discardTruncatedMsga; // [rsp+66h] [rbp-1Ah]
  sbool bEscapeLFa; // [rsp+67h] [rbp-19h]
  regex_t *prega; // [rsp+68h] [rbp-18h]
  cstr_t **ppCStra; // [rsp+70h] [rbp-10h]
  strm_t *pThisa; // [rsp+78h] [rbp-8h]

  pThisa = pThis;
  ppCStra = ppCStr;
  prega = preg;
  bEscapeLFa = bEscapeLF;
  discardTruncatedMsga = discardTruncatedMsg;
  msgDiscardingErrora = msgDiscardingError;
  finished = 0;
  thisLine = 0LL;
  if ( pThis->readTimeout )
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
    if ( !pThisa->prevLineSegment )
      goto LABEL_10;
    iRet = cstrAppendCStr(thisLine, pThisa->prevLineSegment);
    if ( iRet )
      break;
    rsCStrDestruct(&pThisa->prevLineSegment);
LABEL_10:
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
    SzStrNoNULL = cstrGetSzStrNoNULL(thisLine);
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
      v7 = cstrGetSzStrNoNULL(*ppCStra);
      dbgprintf("stream: generated msg based on timeout: %s\n", (const char *)v7);
    }
  }
  return iRet;
}