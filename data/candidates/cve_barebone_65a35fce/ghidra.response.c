rsRetVal strmReadMultiLine(strm_t *pThis,cstr_t **ppCStr,regex_t *preg,sbool bEscapeLF,
                          sbool discardTruncatedMsg,sbool msgDiscardingError)

{
  regex_t *__preg;
  int iVar1;
  rsRetVal rVar2;
  int iVar3;
  int iVar4;
  uchar *puVar5;
  long local_78;
  int z;
  int len;
  int currLineLen;
  int isMatch;
  rsRetVal iRet;
  int maxMsgSize;
  time_t tCurr;
  rsRetVal readCharRet;
  cstr_t *thisLine;
  uchar finished;
  uchar c;
  sbool msgDiscardingError_local;
  sbool discardTruncatedMsg_local;
  sbool bEscapeLF_local;
  regex_t *preg_local;
  cstr_t **ppCStr_local;
  strm_t *pThis_local;
  
  finished = '\0';
  thisLine = (cstr_t *)0x0;
  msgDiscardingError_local = msgDiscardingError;
  discardTruncatedMsg_local = discardTruncatedMsg;
  bEscapeLF_local = bEscapeLF;
  preg_local = preg;
  ppCStr_local = ppCStr;
  pThis_local = pThis;
  if (pThis->readTimeout == 0) {
    local_78 = 0;
  }
  else {
    local_78 = getTime((time_t *)0x0);
  }
  iVar1 = glblGetMaxLine();
  do {
    iRet = strmReadChar(pThis_local,&c);
    if (iRet != 0) break;
    pThis_local->lastRead = local_78;
    iRet = cstrConstruct(&thisLine);
    if (iRet != 0) break;
    if (pThis_local->prevLineSegment != (cstr_t *)0x0) {
      iRet = cstrAppendCStr(thisLine,pThis_local->prevLineSegment);
      if (iRet != 0) break;
      rsCStrDestruct(&pThis_local->prevLineSegment);
    }
    while (__preg = preg_local, c != '\n') {
      iRet = cstrAppendChar(thisLine,c);
      if ((iRet != 0) ||
         (((rVar2 = strmReadChar(pThis_local,&c), rVar2 == -0x7ea &&
           (iRet = rsCStrConstructFromCStr(&pThis_local->prevLineSegment,thisLine), iRet != 0)) ||
          (iRet = rVar2, rVar2 != 0)))) goto LAB_00101b6c;
    }
    if (thisLine->iStrLen != 0) {
      thisLine->pBuf[thisLine->iStrLen] = '\0';
    }
    puVar5 = cstrGetSzStrNoNULL(thisLine);
    iVar3 = regexec((regex_t *)__preg,(char *)puVar5,0,(regmatch_t *)0x0,0);
    if (iVar3 == 0) {
      if ((pThis_local->ignoringMsg == 0) && (pThis_local->prevMsgSegment != (cstr_t *)0x0)) {
        finished = '\x01';
        *ppCStr_local = pThis_local->prevMsgSegment;
      }
      iRet = rsCStrConstructFromCStr(&pThis_local->prevMsgSegment,thisLine);
      if (iRet != 0) break;
      pThis_local->ignoringMsg = 0;
    }
    else if (pThis_local->ignoringMsg == 0) {
      if (pThis_local->prevMsgSegment == (cstr_t *)0x0) {
        iRet = rsCStrConstructFromCStr(&pThis_local->prevMsgSegment,thisLine);
joined_r0x00101a36:
        if (iRet != 0) break;
      }
      else {
        if (bEscapeLF_local == '\0') {
          cstrAppendChar(pThis_local->prevMsgSegment,'\n');
        }
        else {
          rsCStrAppendStrWithLen(pThis_local->prevMsgSegment,"\\n",2);
        }
        iVar3 = (int)thisLine->iStrLen;
        if (0 < iVar3) {
          iVar4 = (int)pThis_local->prevMsgSegment->iStrLen + iVar3;
          if (iVar4 < iVar1) {
            iRet = cstrAppendCStr(pThis_local->prevMsgSegment,thisLine);
            goto joined_r0x00101a36;
          }
          iVar3 = iVar3 - (iVar4 - iVar1);
          for (z = 0; z < iVar3; z = z + 1) {
            cstrAppendChar(pThis_local->prevMsgSegment,thisLine->pBuf[z]);
          }
          finished = '\x01';
          *ppCStr_local = pThis_local->prevMsgSegment;
          iRet = rsCStrConstructFromszStr(&pThis_local->prevMsgSegment,thisLine->pBuf + iVar3);
          if (iRet != 0) break;
          if (discardTruncatedMsg_local == '\x01') {
            pThis_local->ignoringMsg = 1;
          }
          if (msgDiscardingError_local == '\x01') {
            if (discardTruncatedMsg_local == '\x01') {
              (*errmsg.LogError)(0,-3000,
                                 "imfile error: message received is larger than max msg size; rest of message will not be processed"
                                );
            }
            else {
              (*errmsg.LogError)(0,-3000,
                                 "imfile error: message received is larger than max msg size; message will be split and processed as another message"
                                );
            }
          }
        }
      }
    }
    rsCStrDestruct(&thisLine);
  } while (finished == '\0');
LAB_00101b6c:
  while (((pThis_local->readTimeout != 0 && (iRet != 0)) &&
         ((pThis_local->prevMsgSegment != (cstr_t *)0x0 &&
          (pThis_local->lastRead + (long)pThis_local->readTimeout < local_78))))) {
    iRet = rsCStrConstructFromCStr(ppCStr_local,pThis_local->prevMsgSegment);
    if (iRet == 0) {
      rsCStrDestruct(&pThis_local->prevMsgSegment);
      pThis_local->lastRead = local_78;
      puVar5 = cstrGetSzStrNoNULL(*ppCStr_local);
      dbgprintf("stream: generated msg based on timeout: %s\n",puVar5);
    }
  }
  return iRet;
}