rsRetVal strmReadMultiLine(strm_t *pThis, cstr_t **ppCStr, regex_t *preg, sbool bEscapeLF, sbool discardTruncatedMsg, sbool msgDiscardingError)
{
 rsRetVal iRet = 0;
 cstr_t *thisLine = NULL;
 uchar c;
 uchar finished = 0;
 int isMatch;
 int currLineLen;
 int maxMsgSize;
 time_t tCurr;
 rsRetVal readCharRet;


 if(pThis->readTimeout)
  tCurr = getTime(NULL);
 else
  tCurr = 0;

 maxMsgSize = glblGetMaxLine();

 do {
  iRet = strmReadChar(pThis, &c);
  if(iRet != 0)
   break;

  pThis->lastRead = tCurr;

  iRet = cstrConstruct(&thisLine);
  if(iRet != 0)
   break;





  if(pThis->prevLineSegment != NULL) {
   iRet = cstrAppendCStr(thisLine, pThis->prevLineSegment);
   if(iRet != 0)
    break;
   rsCStrDestruct(&pThis->prevLineSegment);
  }

  while(c != '\n') {
   iRet = cstrAppendChar(thisLine, c);
   if(iRet != 0)
    break;

   readCharRet = strmReadChar(pThis, &c);
   if(readCharRet == -2026) {
    iRet = rsCStrConstructFromCStr(&pThis->prevLineSegment, thisLine);
    if(iRet != 0)
     break;
   } else if(readCharRet != 0) {
    iRet = readCharRet;
    break;
   }
  }

  if(iRet != 0)
   break;





  if(thisLine->iStrLen != 0)
   thisLine->pBuf[thisLine->iStrLen] = '\0';

  isMatch = regexec(preg, (char*) cstrGetSzStrNoNULL(thisLine), (size_t) 0, NULL, 0);
  if(isMatch == 0) {






   if(!pThis->ignoringMsg && pThis->prevMsgSegment != NULL) {
    finished = 1;
    *ppCStr = pThis->prevMsgSegment;
   }

   iRet = rsCStrConstructFromCStr(&pThis->prevMsgSegment, thisLine);
   if(iRet != 0)
    break;

   pThis->ignoringMsg = 0;
  } else {






   if(!pThis->ignoringMsg) {
    if(pThis->prevMsgSegment == NULL) {
     iRet = rsCStrConstructFromCStr(&pThis->prevMsgSegment, thisLine);
     if(iRet != 0)
      break;
    } else {






     if(bEscapeLF)
      rsCStrAppendStrWithLen(pThis->prevMsgSegment, "\\n", 2);
     else
      cstrAppendChar(pThis->prevMsgSegment, '\n');

     currLineLen = thisLine->iStrLen;
     if(currLineLen > 0) {
      if(pThis->prevMsgSegment->iStrLen + currLineLen < maxMsgSize) {
       iRet = cstrAppendCStr(pThis->prevMsgSegment, thisLine);
       if(iRet != 0)
        break;
      } else {
       int i;
       int missingChars;

       missingChars = (pThis->prevMsgSegment->iStrLen + currLineLen) - maxMsgSize;
       currLineLen -= missingChars;

       for(i = 0 ; i < currLineLen ; ++i)
        cstrAppendChar(pThis->prevMsgSegment, thisLine->pBuf[i]);

       finished = 1;
       *ppCStr = pThis->prevMsgSegment;

       iRet = rsCStrConstructFromszStr(&pThis->prevMsgSegment, thisLine->pBuf + currLineLen);
       if(iRet != 0)
        break;

       if(discardTruncatedMsg == 1)
        pThis->ignoringMsg = 1;

       if(msgDiscardingError == 1) {
        if(discardTruncatedMsg == 1) {
         errmsg.LogError(0, -3000, "imfile error: message received is larger than max msg size; rest of message will not be processed");
        } else {
         errmsg.LogError(0, -3000, "imfile error: message received is larger than max msg size; message will be split and processed as another message");
        }
       }
      }
     }
    }
   }
  }

  rsCStrDestruct(&thisLine);
 } while(finished == 0);





 if(pThis->readTimeout && iRet != 0 && pThis->prevMsgSegment != NULL && pThis->lastRead + pThis->readTimeout < tCurr) {
  iRet = rsCStrConstructFromCStr(ppCStr, pThis->prevMsgSegment);
  if(iRet == 0) {
   rsCStrDestruct(&pThis->prevMsgSegment);
   pThis->lastRead = tCurr;
   dbgprintf("stream: generated msg based on timeout: %s\n", cstrGetSzStrNoNULL(*ppCStr));
  }
 }

 do{ return iRet; }while(0);
}