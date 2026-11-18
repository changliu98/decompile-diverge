rsRetVal
strmReadMultiLine(strm_t *pThis, cstr_t **ppCStr, regex_t *preg, const sbool bEscapeLF, const sbool discardTruncatedMsg, const sbool msgDiscardingError)
{
        uchar c;
	uchar finished = 0;
	cstr_t *thisLine = NULL;
	rsRetVal readCharRet;
	const time_t tCurr = pThis->readTimeout ? getTime(NULL) : 0;
	int maxMsgSize = glblGetMaxLine();
        DEFiRet;

	do {
		CHKiRet(strmReadChar(pThis, &c)); /* immediately exit on EOF */
		pThis->lastRead = tCurr;
		CHKiRet(cstrConstruct(&thisLine));
		/* append previous message to current message if necessary */
		if(pThis->prevLineSegment != NULL) {
			CHKiRet(cstrAppendCStr(thisLine, pThis->prevLineSegment));
			cstrDestruct(&pThis->prevLineSegment);
		}

		while(c != '\n') {
			CHKiRet(cstrAppendChar(thisLine, c));
			readCharRet = strmReadChar(pThis, &c);
			if(readCharRet == RS_RET_EOF) {/* end of file reached without \n? */
				CHKiRet(rsCStrConstructFromCStr(&pThis->prevLineSegment, thisLine));
			}
			CHKiRet(readCharRet);
		}
		cstrFinalize(thisLine);

		/* we have a line, now let's assemble the message */
		const int isMatch = !regexec(preg, (char*)rsCStrGetSzStrNoNULL(thisLine), 0, NULL, 0);

		if(isMatch) {
			/* in this case, the *previous* message is complete and we are
			 * at the start of a new one.
			 */
			if(pThis->ignoringMsg == 0) {
				if(pThis->prevMsgSegment != NULL) {
					/* may be NULL in initial poll! */
					finished = 1;
					*ppCStr = pThis->prevMsgSegment;
				}
			}
			CHKiRet(rsCStrConstructFromCStr(&pThis->prevMsgSegment, thisLine));
			pThis->ignoringMsg = 0;
		} else {
			if(pThis->ignoringMsg == 0) {
				if(pThis->prevMsgSegment == NULL) {
					/* may be NULL in initial poll or after timeout! */
					CHKiRet(rsCStrConstructFromCStr(&pThis->prevMsgSegment, thisLine));
				} else {
					if(bEscapeLF) {
						rsCStrAppendStrWithLen(pThis->prevMsgSegment, (uchar*)"\\n", 2);
					} else {
						cstrAppendChar(pThis->prevMsgSegment, '\n');
					}


					int currLineLen = cstrLen(thisLine);
					if(currLineLen > 0) {
						int len;
						if((len = cstrLen(pThis->prevMsgSegment) + currLineLen) < maxMsgSize) {
							CHKiRet(cstrAppendCStr(pThis->prevMsgSegment, thisLine));
							/* we could do this faster, but for now keep it simple */
						} else {
							len = currLineLen-(len-maxMsgSize);
							for(int z=0; z<len; z++) {
								cstrAppendChar(pThis->prevMsgSegment, thisLine->pBuf[z]);
							}
							finished = 1;
							*ppCStr = pThis->prevMsgSegment;
							CHKiRet(rsCStrConstructFromszStr(&pThis->prevMsgSegment, thisLine->pBuf+len));
							if(discardTruncatedMsg == 1) {
								pThis->ignoringMsg = 1;
							}
							if(msgDiscardingError == 1) {
								if(discardTruncatedMsg == 1) {
									errmsg.LogError(0, RS_RET_ERR, "imfile error: message received is "
											"larger than max msg size; rest of message "
											"will not be processed");
								} else {
									errmsg.LogError(0, RS_RET_ERR, "imfile error: message received is "
											"larger than max msg size; message will be "
											"split and processed as another message");
								}
							}
						}
					}
				}
			}
		}
		cstrDestruct(&thisLine);
	} while(finished == 0);

finalize_it:
	if(   pThis->readTimeout
	   && (iRet != RS_RET_OK)
	   && (pThis->prevMsgSegment != NULL)
	   && (tCurr > pThis->lastRead + pThis->readTimeout)) {
		CHKiRet(rsCStrConstructFromCStr(ppCStr, pThis->prevMsgSegment));
		cstrDestruct(&pThis->prevMsgSegment);
		pThis->lastRead = tCurr;
		dbgprintf("stream: generated msg based on timeout: %s\n", cstrGetSzStrNoNULL(*ppCStr));
			FINALIZE;
		iRet = RS_RET_OK;
	}
        RETiRet;
}