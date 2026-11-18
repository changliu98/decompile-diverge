static int
strmReadMultiLine(strm_t *pThis, cstr_t *pMsg, regex_t *pRegex, char escapeLF,
         char discardTruncatedMsg, char msgDiscardingError)
{
 unsigned char c;
 int iRet;
 int bIsMatch;
 int iMaxMsgSize;
 int iCurrLineLen;
 int iMsgLen;
 int iStartOfNewMsg;
 int i;
 cstr_t *pThisLine = NULL;
 cstr_t *pTmpMsg = NULL;
 time_t tNow;
 time_t tLastRead;
 unsigned char bFinished = 0;

 do { ; ; ; } while(0);;

 if(pThis->iTimeoutRead != 0) {
  tNow = getTime(NULL);
 } else {
  tNow = 0;
 }
 tLastRead = tNow;

 iMaxMsgSize = glblGetMaxLine();





 do {
  iRet = strmReadChar(pThis, &c);
  if(iRet != 0) {
   goto finalize_it;
  }

  pThis->tLastRead = tNow;

  iRet = cstrConstruct(&pThisLine);
  if(iRet != 0) {
   goto finalize_it;
  }

  if(pThis->pPrevMsg != NULL) {
   iRet = cstrAppendCStr(pThisLine, pThis->pPrevMsg);
   if(iRet != 0) {
    goto finalize_it;
   }
   rsCStrDestruct(&pThis->pPrevMsg);
  }

  while(c != '\n') {
   iRet = cstrAppendChar(pThisLine, c);
   if(iRet != 0) {
    goto finalize_it;
   }
   iRet = strmReadChar(pThis, &c);
   if(iRet == -2026) {

    iRet = rsCStrConstructFromCStr(&pThis->pPrevMsg, pThisLine);
    if(iRet != 0) {
     goto finalize_it;
    }
   } else if(iRet != 0) {
    goto finalize_it;
   }
  }

  if(pThisLine->len > 0) {
   pThisLine->szBuf[pThisLine->len] = '\0';
  }


  bIsMatch = (regexec(pRegex, cstrGetSzStrNoNULL(pThisLine), (size_t) 0, NULL, 0) == 0) ? 0 : 1;
  if(bIsMatch) {
   if(!pThis->bTruncationInProgress) {
    if(pThis->pMsg != NULL) {
     bFinished = 1;
     *pMsg = pThis->pMsg;
    }
   } else {
    iRet = rsCStrConstructFromCStr(&pThis->pMsg, pThisLine);
    if(iRet != 0) {
     goto finalize_it;
    }
    pThis->bTruncationInProgress = 0;
   }
  } else {
   if(!pThis->bTruncationInProgress) {
    if(pThis->pMsg == NULL) {
     iRet = rsCStrConstructFromCStr(&pThis->pMsg, pThisLine);
     if(iRet != 0) {
      goto finalize_it;
     }
    } else {
     if(escapeLF) {
      cstrAppendStrWithLen(pThis->pMsg, "\\n", sizeof("\\n") - 1);
     } else {
      cstrAppendChar(pThis->pMsg, '\n');
     }
     iCurrLineLen = pThisLine->len;
     if(iCurrLineLen > 0) {
      iMsgLen = pThis->pMsg->len + iCurrLineLen;
      if(iMsgLen < iMaxMsgSize) {
       iRet = cstrAppendCStr(pThis->pMsg, pThisLine);
       if(iRet != 0) {
        goto finalize_it;
       }
      } else {
       iMsgLen = iCurrLineLen - (iMsgLen - iMaxMsgSize);
       for(i = 0 ; i < iMsgLen ; ++i) {
        cstrAppendChar(pThis->pMsg, pThisLine->szBuf[i]);
       }
       bFinished = 1;
       *pMsg = pThis->pMsg;
       iRet = rsCStrConstructFromszStr(&pThis->pMsg, &pThisLine->szBuf[iMsgLen]);
       if(iRet != 0) {
        goto finalize_it;
       }
       if(discardTruncatedMsg == 1) {
        pThis->bTruncationInProgress = 1;
       }
       if(msgDiscardingError == 1) {
        if(discardTruncatedMsg == 1) {
         errmsg.LogError(0, "imfile error: message received is larger than max msg size; "
           "truncated message: %s", cstrGetSzStrNoNULL(*pMsg));
        } else {
         errmsg.LogError(0, "imfile error: message received is larger than max msg size; "
           "message: %s", cstrGetSzStrNoNULL(*pMsg));
        }
       }
      }
     }
    }
   }
  }
  rsCStrDestruct(&pThisLine);
 } while(!bFinished);

finalize_it:
 if(pThis->iTimeoutRead != 0 && iRet != 0 && pThis->pMsg != NULL &&
    tNow > pThis->tLastRead + pThis->iTimeoutRead) {
  iRet = rsCStrConstructFromCStr(pMsg, pThis->pMsg);
  if(iRet != 0) {
   goto finalize_it;
  }
  rsCStrDestruct(&pThis->pMsg);
  pThis->tLastRead = tNow;
  dbgprintf("stream: generated msg based on timeout: %s\n",
     cstrGetSzStrNoNULL(*pMsg));
 }

 do{ return iRet; }while(0);
}