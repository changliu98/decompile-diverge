int strmReadMultiLine(strm_t *pThis, rsCStr_t **ppCStr, regex_t *pReg, unsigned char bEscapeLF, unsigned char bTrimLine, unsigned char discardTrailingLF) {
    int r = 0;
    unsigned char bEscapeLFs = 0;
    long long ttStart = 0;
    int iMaxLine;
    int localRet;
    char c;
    cstr_t *pCStr = NULL;
    rsCStr_t *pUnreadCStr = NULL;
    int lenCstr;
    int i;
    int newLen;
    int localRet2;
    int finalRet;

    if (pThis->bIsUsed) {
        ttStart = getTime();
    } else {
        ttStart = 0;
    }
    pThis->ttStart = ttStart;

    iMaxLine = glblGetMaxLine();

    do {
        localRet = strmReadChar(pThis, &c);
        if (localRet != 0) {
            break;
        }

        pThis->ttStart = ttStart;
        localRet = cstrConstruct(&pCStr);
        if (localRet != 0) {
            break;
        }

        if (pThis->pUnread != NULL) {
            localRet = cstrAppendCStr(pCStr, pThis->pUnread);
            if (localRet != 0) {
                break;
            }
            rsCStrDestruct(&pThis->pUnread);
        }

        while (c != '\n') {
            localRet = cstrAppendChar(pCStr, c);
            if (localRet != 0) {
                break;
            }

            localRet = strmReadChar(pThis, &c);
            if (localRet == -2000) { // 0xfffff816
                localRet = rsCStrConstructFromCStr(&pThis->pUnread, pCStr);
                if (localRet != 0) {
                    break;
                }
            }

            if (localRet != 0) {
                break;
            }
        }

        if (localRet != 0) {
            break;
        }

        if (pCStr->len > 0) {
            pCStr->pBuf[pCStr->len] = '\0';
        }

        if (regexec(pReg, cstrGetSzStrNoNULL(pCStr), 0, NULL, 0) == 0) {
            if (pThis->bPrevLineWasIncomplete == 0) {
                if (pThis->pCurrLine != NULL) {
                    bEscapeLFs = 1;
                    *ppCStr = pThis->pCurrLine;
                }
            } else {
                localRet = rsCStrConstructFromCStr(&pThis->pCurrLine, pCStr);
                if (localRet != 0) {
                    break;
                }
                pThis->bPrevLineWasIncomplete = 0;
            }
        } else {
            if (pThis->bPrevLineWasIncomplete == 0) {
                if (pThis->pCurrLine == NULL) {
                    localRet = rsCStrConstructFromCStr(&pThis->pCurrLine, pCStr);
                    if (localRet != 0) {
                        break;
                    }
                } else {
                    if (bEscapeLF) {
                        rsCStrAppendStrWithLen(pThis->pCurrLine, "\\n", 2);
                    } else {
                        cstrAppendChar(pThis->pCurrLine, '\n');
                    }

                    lenCstr = pCStr->len;
                    if (lenCstr > 0) {
                        newLen = pThis->pCurrLine->len + lenCstr;
                        if (newLen < iMaxLine) {
                            localRet = cstrAppendCStr(pThis->pCurrLine, pCStr);
                            if (localRet != 0) {
                                break;
                            }
                        } else {
                            newLen = lenCstr - (newLen - iMaxLine);
                            for (i = 0; i < newLen; i++) {
                                localRet = cstrAppendChar(pThis->pCurrLine, pCStr->pBuf[i]);
                                if (localRet != 0) {
                                    break;
                                }
                            }
                            if (localRet != 0) {
                                break;
                            }

                            bEscapeLFs = 1;
                            *ppCStr = pThis->pCurrLine;
                            localRet = rsCStrConstructFromszStr(&pThis->pCurrLine, pCStr->pBuf + newLen);
                            if (localRet != 0) {
                                break;
                            }

                            if (bTrimLine == 1) {
                                pThis->bPrevLineWasIncomplete = 1;
                            }

                            if (discardTrailingLF == 1) {
                                if (bTrimLine == 1) {
                                    errmsg(0, -3000, "error: discardTrailingLF is set but bTrimLine is also set - discarding is disabled");
                                } else {
                                    errmsg(0, -3000, "error: discardTrailingLF is set but bTrimLine is not set - discarding is disabled");
                                }
                            }
                        }
                    }
                }
            }
        }

        rsCStrDestruct(&pCStr);

        if (bEscapeLFs != 0) {
            break;
        }

    } while (bEscapeLFs == 0);

    if (pThis->bIsUsed && localRet != 0 && pThis->pCurrLine != NULL && ttStart > pThis->ttStart + pThis->bIsUsed) {
        localRet = rsCStrConstructFromCStr(ppCStr, pThis->pCurrLine);
        if (localRet != 0) {
            goto end;
        }
        rsCStrDestruct(&pThis->pCurrLine);
        pThis->ttStart = ttStart;
        dbgprintf("strmReadMultiLine: unexpectedly reached end of stream, returning partial line: '%s'\n", cstrGetSzStrNoNULL(*ppCStr));
    }

end:
    finalRet = localRet;
    return finalRet;
}