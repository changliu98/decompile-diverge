rsRetVal strmReadMultiLine(strm_t *pThis, cstr_t **ppMsg, regex_t *pRegex,
                           rsUInt8 bAddNewLine, rsUInt8 bSplitMsg,
                           rsUInt8 bWarnOnSplit) {
  rsRetVal iRet;
  unsigned char c;
  unsigned char bDone = 0;
  cstr_t *pLine = NULL;
  time_t tNow;
  int iMaxLine;
  int iLineLen;
  int iMaxLineLen;
  int i;
  if (pThis->iTimeout)
    tNow = getTime(NULL);
  else
    tNow = 0;
  iMaxLine = glblGetMaxLine();
  do {
    iRet = strmReadChar(pThis, &c);
    if (iRet) break;
    pThis->tLastRead = tNow;
    iRet = cstrConstruct(&pLine);
    if (iRet) break;
    if (pThis->pMsg) {
      iRet = cstrAppendCStr(pLine, pThis->pMsg);
      if (iRet) break;
      rsCStrDestruct(&pThis->pMsg);
    }
    while (c != '\n') {
      iRet = cstrAppendChar(pLine, c);
      if (iRet) goto finalize_it;
      iRet = strmReadChar(pThis, &c);
      if (iRet == -2026) {
        iRet = rsCStrConstructFromCStr(&pThis->pMsg, pLine);
        if (iRet) break;
      }
      if (iRet) goto finalize_it;
    }
    if (pLine->iLen) pLine->szBuf[pLine->iLen] = '\0';
    if (!regexec(pRegex, cstrGetSzStrNoNULL(pLine), 0, NULL, 0)) {
      if (!pThis->bMsgSplit && pThis->pMsgBuf) {
        bDone = 1;
        *ppMsg = pThis->pMsgBuf;
      }
      iRet = rsCStrConstructFromCStr(&pThis->pMsgBuf, pLine);
      if (iRet) break;
      pThis->bMsgSplit = 0;
    } else {
      if (!pThis->bMsgSplit) {
        if (pThis->pMsgBuf) {
          if (bAddNewLine)
            rsCStrAppendStrWithLen(pThis->pMsgBuf, "\r\n", 2);
          else
            cstrAppendChar(pThis->pMsgBuf, '\n');
          iLineLen = pLine->iLen;
          if (iLineLen > 0) {
            if (pThis->pMsgBuf->iLen + iLineLen < iMaxLine) {
              iRet = cstrAppendCStr(pThis->pMsgBuf, pLine);
              if (iRet) break;
            } else {
              iMaxLineLen = iMaxLine - pThis->pMsgBuf->iLen;
              for (i = 0; i < iMaxLineLen; i++)
                cstrAppendChar(pThis->pMsgBuf, pLine->szBuf[i]);
              bDone = 1;
              *ppMsg = pThis->pMsgBuf;
              iRet = rsCStrConstructFromszStr(&pThis->pMsgBuf,
                                              pLine->szBuf + iMaxLineLen);
              if (iRet) break;
              if (bSplitMsg == 1) pThis->bMsgSplit = 1;
              if (bWarnOnSplit == 1) {
                if (bSplitMsg == 1)
                  errmsg(0, -2020,
                         "imfile error: message received is larger than max msg "
                         "size; rest of message will not be processed");
                else
                  errmsg(0, -2020,
                         "imfile error: message received is larger than max msg "
                         "size; message will be split and processed as another "
                         "message");
              }
            }
          }
        } else {
          iRet = rsCStrConstructFromCStr(&pThis->pMsgBuf, pLine);
          if (iRet) break;
        }
      }
    }
    rsCStrDestruct(&pLine);
  } while (!bDone);
finalize_it:
  while (pThis->iTimeout && iRet && pThis->pMsgBuf &&
         pThis->tLastRead > pThis->iTimeout + pThis->tLastRead) {
    iRet = rsCStrConstructFromCStr(ppMsg, pThis->pMsgBuf);
    if (!iRet) {
      rsCStrDestruct(&pThis->pMsgBuf);
      pThis->tLastRead = tNow;
      dbgprintf("stream: generated msg based on timeout: %s\n",
                cstrGetSzStrNoNULL(*ppMsg));
    }
  }
  return iRet;
}