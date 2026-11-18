int strmReadMultiLine(struct strm *pThis, struct cstr **ppCStr, struct regex *preg, _Bool bEscapeLF, _Bool discardTruncatedMsg, _Bool msgDiscardingError)
{
  struct cstr *pThisLine = ((void *)0);
  char c;
  _Bool finished = 0;
  int iRet;
  int maxMsgSize;
  int currLineLen;
  int len;
  int i;
  char *lineNoNull;
  long now;
  if (pThis->readTimeout != 0)
    now = strm_get_time(((void *)0));
  else
    now = 0;
  maxMsgSize = strm_get_max_msg_size();
  do
  {
    iRet = strm_get_char(pThis, &c);
    if (iRet != 0)
      break;
    pThis->lastRead = now;
    iRet = strm_alloc_line(&pThisLine);
    if (iRet != 0)
      break;
    if (pThis->prevLineSegment == ((void *)0))
      goto add_to_msg;
    iRet = strm_append_line(pThisLine, pThis->prevLineSegment);
    if (iRet != 0)
      break;
    strm_free_line(&pThis->prevLineSegment);
  add_to_msg:
    while (c != '\n')
    {
      iRet = strm_append_char(pThisLine, c);
      if (iRet != 0)
        goto finalize_it;
      iRet = strm_get_char(pThis, &c);
      if (iRet == -2026)
      {
        if (strm_free_line(&pThis->prevLineSegment) == 0)
        {
          iRet = strm_get_char(pThis, &c);
          if (iRet == 0)
            continue;
        }
      }
      break;
    }
    if (pThisLine->iStrLen > 0)
      pThisLine->pBuf[pThisLine->iStrLen] = '\0';
    if (regexec(preg, strm_get_cstr(pThisLine), 0, ((void *)0), 0))
    {
      if (pThis->ignoringMsg == 0)
      {
        if (pThis->prevMsgSegment == ((void *)0))
        {
          iRet = strm_append_line(&pThis->prevMsgSegment, pThisLine);
          if (iRet != 0)
            break;
        }
        else
        {
          if (bEscapeLF)
            strm_append_str(pThis->prevMsgSegment, "$$", 2);
          else
            strm_append_char(pThis->prevMsgSegment, '\n');
          currLineLen = pThisLine->iStrLen;
          if (currLineLen > 0)
          {
            if (currLineLen + pThis->prevMsgSegment->iStrLen < maxMsgSize)
            {
              iRet = strm_append_line(pThis->prevMsgSegment, pThisLine);
              if (iRet != 0)
                break;
            }
            else
            {
              len = maxMsgSize - pThis->prevMsgSegment->iStrLen;
              for (i = 0; i < len; i++)
                strm_append_char(pThis->prevMsgSegment, pThisLine->pBuf[i]);
              finished = 1;
              *ppCStr = pThis->prevMsgSegment;
              iRet = strm_append_line(&pThis->prevMsgSegment, pThisLine->pBuf + len);
              if (iRet != 0)
                break;
              if (discardTruncatedMsg == 1)
                pThis->ignoringMsg = 1;
              if (msgDiscardingError == 1)
              {
                if (discardTruncatedMsg == 1)
                  errmsg(((void *)0), -1000, "imfile error: message received is larger than max msg size; rest of message will not be processed");
                else
                  errmsg(((void *)0), -1000, "imfile error: message received is larger than max msg size; message will be split and processed as another message");
              }
            }
          }
        }
      }
    }
    else
    {
      if (pThis->ignoringMsg == 0 && pThis->prevMsgSegment != ((void *)0))
      {
        finished = 1;
        *ppCStr = pThis->prevMsgSegment;
      }
      iRet = strm_append_line(&pThis->prevMsgSegment, pThisLine);
      if (iRet != 0)
        break;
      pThis->ignoringMsg = 0;
    }
    strm_free_line(&pThisLine);
  }
  while (finished == 0);
finalize_it:
  while (pThis->readTimeout != 0 && iRet != 0 && pThis->prevMsgSegment != ((void *)0) &&
         pThis->lastRead + pThis->readTimeout < now)
  {
    iRet = strm_append_line(ppCStr, pThis->prevMsgSegment);
    if (iRet == 0)
    {
      strm_free_line(&pThis->prevMsgSegment);
      pThis->lastRead = now;
      lineNoNull = strm_get_cstr(*ppCStr);
      strm_log("stream: generated msg based on timeout: %s\n", lineNoNull);
    }
  }
  return iRet;
}