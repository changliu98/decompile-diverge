/* cve_barebone direct-call harness for cve_65a35fce (rsyslog runtime/stream.c)
 * Target: strmReadMultiLine
 *
 * ================================================================================
 * DATASET METADATA CAVEAT (documented, not hidden)
 * ================================================================================
 * This bundle's attached CVE id (CVE-2017-12588) and fix_commit
 * (062d0c671a29f7c6f7dff4a2f1f35df375bbb30b) are a crawler mismatch: per the GitHub API and
 * OSV's own record, that commit/CVE is a format-string bug in contrib/imzmq3/imzmq3.c and
 * contrib/omzmq3/omzmq3.c ONLY (PR #1565, "Fix format security issue in zmq3 modules"). It
 * touches no file under runtime/ and has nothing to do with strmReadMultiLine or multi-line
 * log reading. Fetching that fix diff (as the task instructions call for) shows this
 * immediately -- it is not "the trigger condition" for anything in this function.
 *
 * What follows instead is a REAL, independently-confirmed memory-safety bug in
 * strmReadMultiLine's OWN body (verified below against upstream's own later hardening of the
 * identical computation), reproduced byte-for-byte from
 * data_cve/cve_65a35fce/target/original_function.c.
 *
 * ================================================================================
 * THE BUG -- CWE-125, heap-buffer-overflow READ, integer underflow -> negative pointer offset
 * ================================================================================
 * In the "message exceeds maxMsgSize" branch:
 *
 *     int currLineLen = cstrLen(thisLine);
 *     if(currLineLen > 0) {
 *         int len;
 *         if((len = cstrLen(pThis->prevMsgSegment) + currLineLen) < maxMsgSize) {
 *             CHKiRet(cstrAppendCStr(pThis->prevMsgSegment, thisLine));
 *         } else {
 *             len = currLineLen-(len-maxMsgSize);                                  <- (*)
 *             for(int z=0; z<len; z++)
 *                 cstrAppendChar(pThis->prevMsgSegment, thisLine->pBuf[z]);
 *             finished = 1;
 *             *ppCStr = pThis->prevMsgSegment;
 *             CHKiRet(rsCStrConstructFromszStr(&pThis->prevMsgSegment, thisLine->pBuf+len)); <- (**)
 *             ...
 *
 * Algebraically, (*) reduces to `len = maxMsgSize - cstrLen(pThis->prevMsgSegment)` -- with NO
 * check that cstrLen(pThis->prevMsgSegment) <= maxMsgSize. The SAME branch can itself leave
 * pThis->prevMsgSegment longer than maxMsgSize on exit: when a single incoming line is much
 * longer than maxMsgSize, the untruncated remainder written back via (**) can be arbitrarily
 * large. So one call that overflows maxMsgSize by a lot leaves prevMsgSegment *itself*
 * oversized; the VERY NEXT call to strmReadMultiLine on that stream then computes a NEGATIVE
 * `len` at (*), and thisLine->pBuf+len at (**) is a pointer BEFORE the start of thisLine's own
 * heap buffer -- passed straight into rsCStrConstructFromszStr(), which does
 * `strlen((char*)sz)` on it: an out-of-bounds heap READ.
 *
 * Reachable purely by calling strmReadMultiLine() directly, twice, on one harness-owned
 * strm_t, feeding attacker-controlled file bytes through strmReadChar() both times -- exactly
 * how the real caller (imfile's pollFileReal()) drives it across repeated polls of one open
 * stream:
 *   call 1: a short "start" line (matches start_preg) then one long non-matching line that
 *           overflows maxMsgSize -> an ORDINARY (non-negative) truncation, but the untruncated
 *           remainder written back to pThis->prevMsgSegment is ITSELF left longer than
 *           maxMsgSize (a big enough line guarantees this).
 *   call 2: one more short non-matching line -> cstrLen(pThis->prevMsgSegment) is already >
 *           maxMsgSize from call 1 -> len goes negative -> OOB read in
 *           rsCStrConstructFromszStr, called directly from inside strmReadMultiLine.
 *
 * CONFIRMATION this is a genuine bug, not a harness artifact: upstream rsyslog master (fetched
 * 2026-07-11, https://raw.githubusercontent.com/rsyslog/rsyslog/master/runtime/stream.c) still
 * has the identical shape but with an explicit guard added around the exact same computation:
 *
 *     if (cstrLen(pThis->prevMsgSegment) > maxMsgSize) {
 *         len = 0;
 *     } else {
 *         len = currLineLen - (len - maxMsgSize);
 *         ...
 *     }
 *
 * i.e. upstream itself now special-cases "prevMsgSegment already oversized" -- precisely the
 * precondition this harness constructs -- confirming the unguarded original (the exact bytes
 * in target/original_function.c, introduced by commit 8ceaddde352a "imfile: add posibility to
 * truncate msg", 2017-05-19, and unchanged through vul_commit fab2e391187c598ea1009122039e
 * 83b5894b826f, 2017-06-01) really did lack this check.
 *
 * ================================================================================
 * CWE CLASSIFICATION -- empirically stabilized to a single, reproducible ASAN diagnosis
 * ================================================================================
 * The underflowed pointer (thisLine->pBuf+len, len < 0) is, fundamentally, an out-of-bounds
 * READ (CWE-125) regardless of exactly what memory it lands on -- but WHICH ASAN diagnosis it
 * produces depends on how far back it walks, since that determines whether it lands in
 * thisLine's own left redzone, a differently-sized recently-freed chunk, or unmapped memory.
 * An `scripts/dc_try.py` sweep of the offset magnitude (see crafting notes) found:
 *     offset  -1 .. -57    -> heap-buffer-overflow READ   (CWE-125)   <- stable, chosen zone
 *     offset -87 .. -277   -> heap-use-after-free  READ   (CWE-416)
 *     offset -477 and out  -> bare SEGV (unmapped)         (no ASAN type)
 * All three are genuine manifestations of the identical root-cause defect (the missing
 * cstrLen(prevMsgSegment) <= maxMsgSize check) -- the offset magnitude alone decides which one
 * ASAN reports. build_trigger() below deliberately keeps l2 in a narrow range so the resulting
 * offset (124-l2-l1) always falls in the validated, stable [-32,-5] sub-window -> every
 * triggering input in this corpus reproduces the SAME CWE-125 heap-buffer-overflow READ.
 *
 * ================================================================================
 * FIDELITY NOTES
 * ================================================================================
 * Types/macros are the REAL rsyslog names (runtime/typedefs.h, runtime/rsyslog.h,
 * runtime/stringbuf.h), expanded exactly as they are in a real NON-debug (NDEBUG) rsyslog
 * build (BEGINfunc/ENDfuncIRet are empty in that mode; rsSETOBJTYPE/rsCHECKVALIDOBJECT are
 * no-ops; cstr_s drops its debug-only OID field) -- so cstr_t/DEFiRet/CHKiRet/RETiRet/RS_RET_*
 * behave exactly as in a real release build. cstrConstruct/rsCStrExtendBuf/cstrAppendChar/
 * rsCStrAppendStrWithLen/cstrAppendCStr/rsCStrConstructFromCStr/rsCStrConstructFromszStr/
 * rsCStrDestruct/cstrGetSzStrNoNULL are copied VERBATIM from runtime/stringbuf.c: thisLine->
 * pBuf really is the heap buffer cstrAppendChar/rsCStrExtendBuf grew via malloc/realloc, so
 * the OOB pointer arithmetic strmReadMultiLine computes hits a REAL ASAN-guarded heap
 * allocation, not a synthetic stand-in.
 *
 * strm_t here keeps only the 5 fields strmReadMultiLine's own body actually reads or writes
 * (readTimeout, lastRead, prevLineSegment, prevMsgSegment, ignoringMsg) -- verified by
 * grepping target/original_function.c for every `pThis->` access. The real struct.h strm_s
 * additionally carries pthread_mutex_t/pthread_cond_t, a zlib z_stream, cryprov_if_t
 * pointers, BEGINobjInstance generic-object bookkeeping, IO buffers, etc.; none of that is
 * read or written by strmReadMultiLine, so it is omitted rather than dragging in libz/
 * libpthread/the whole object system for fields that cannot affect this bug. Field
 * NAMES/TYPES that ARE used are verbatim.
 *
 * strmReadChar (real: pThis->pIOBuf-backed disk I/O + zlib decompression) and
 * glblGetMaxLine/getTime/errmsg.LogError/dbgprintf (global config + logging) are incidental to
 * the bug (never on its crash path) -- minimal faithful stand-ins:
 *   - strmReadChar reads sequentially from the attacker-controlled input file, matching the
 *     real function's one-byte-at-a-time contract (RS_RET_OK + *pC on a byte, RS_RET_EOF at
 *     end).
 *   - glblGetMaxLine returns a fixed $MaxMessageSize (a real, admin-configurable rsyslog
 *     setting) -- the bug is in the *comparison* against it, not any particular threshold, so
 *     it is held fixed small purely to keep corpus files a manageable size.
 *   - getTime/errmsg.LogError/dbgprintf: readTimeout is held 0 (disables the unrelated
 *     finalize_it timeout branch) and discardTruncatedMsg/msgDiscardingError are held 0 in the
 *     driver below, so none of these three is ever actually invoked by the crafted corpus;
 *     they exist purely so the verbatim function body compiles.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>
#include <regex.h>
#include <stdarg.h>

#define NDEBUG 1
#include <assert.h>

/* ---- runtime/typedefs.h (verbatim) ---- */
typedef unsigned char uchar;                 /* typedefs.h:49 */
typedef char sbool;                          /* typedefs.h:158 */
typedef int rsRetVal;                        /* typedefs.h:75 -- friendly type for enum rsRetVal_ */

/* ---- runtime/rsyslog.h (verbatim values / NDEBUG macro expansions) ---- */
#define RS_RET_OUT_OF_MEMORY   (-6)          /* rsyslog.h:185 */
#define RS_RET_ERR              (-3000)      /* rsyslog.h:193 */
#define RS_RET_EOF               (-2026)     /* rsyslog.h:241 */
#define RS_RET_OK                 0          /* rsyslog.h:492 */

#define RS_STRINGBUF_ALLOC_INCREMENT 128      /* rsyslog.h:56 */

/* DEFiRet/RETiRet/CHKiRet -- release-mode (NDEBUG) expansion: BEGINfunc/ENDfuncIRet are empty
 * in that build mode (debug.h), so they simply vanish here. */
#define DEFiRet rsRetVal iRet = RS_RET_OK
#define RETiRet do{ return iRet; }while(0)
#define CHKiRet(code) if((iRet = code) != RS_RET_OK) goto finalize_it
#define FINALIZE goto finalize_it;
#define ABORT_FINALIZE(errCode) do { iRet = errCode; goto finalize_it; } while(0)
#define CHKmalloc(operation) if((operation) == NULL) ABORT_FINALIZE(RS_RET_OUT_OF_MEMORY)

#define MALLOC(x) malloc(x)                   /* debug.h release-mode expansion */
#define RSFREEOBJ(x) free(x)                  /* rsyslog.h NDEBUG expansion */
#define rsSETOBJTYPE(pObj, type) ((void)0)    /* rsyslog.h NDEBUG expansion */
#define rsCHECKVALIDOBJECT(x, type) ((void)0) /* rsyslog.h NDEBUG expansion */

/* ---- runtime/stringbuf.h (verbatim struct + macros; NDEBUG layout drops the debug-only OID
 * field) ---- */
typedef struct cstr_s {
	uchar *pBuf;        /**< pointer to the string buffer, may be NULL if string is empty */
	size_t iBufSize;     /**< current maximum size of the string buffer */
	size_t iStrLen;       /**< length of the string in characters. */
} cstr_t;

#define cstrLen(x) ((int)((x)->iStrLen))
#define cstrFinalize(pThis) { \
	if((pThis)->iStrLen > 0) \
		(pThis)->pBuf[(pThis)->iStrLen] = '\0'; \
}
#define cstrDestruct(x) rsCStrDestruct((x))
#define rsCStrGetSzStrNoNULL(x) cstrGetSzStrNoNULL(x)

/* ---- runtime/stringbuf.c (VERBATIM, the subset strmReadMultiLine's call graph needs) ---- */

rsRetVal
cstrConstruct(cstr_t **ppThis)
{
	DEFiRet;
	cstr_t *pThis;

	CHKmalloc(pThis = (cstr_t*) malloc(sizeof(cstr_t)));
	rsSETOBJTYPE(pThis, OIDrsCStr);
	pThis->pBuf = NULL;
	pThis->iBufSize = 0;
	pThis->iStrLen = 0;
	*ppThis = pThis;

finalize_it:
	RETiRet;
}


rsRetVal
rsCStrConstructFromszStr(cstr_t **ppThis, const uchar *sz)
{
	DEFiRet;
	cstr_t *pThis;

	CHKiRet(cstrConstruct(&pThis));

	pThis->iStrLen = strlen((char *) sz);
	pThis->iBufSize = strlen((char *) sz) + 1;
	if((pThis->pBuf = (uchar*) MALLOC(pThis->iBufSize)) == NULL) {
		RSFREEOBJ(pThis);
		ABORT_FINALIZE(RS_RET_OUT_OF_MEMORY);
	}

	/* we do NOT need to copy the \0! */
	memcpy(pThis->pBuf, sz, pThis->iStrLen);

	*ppThis = pThis;

finalize_it:
	RETiRet;
}


rsRetVal rsCStrConstructFromCStr(cstr_t **ppThis, cstr_t *pFrom)
{
	DEFiRet;
	cstr_t *pThis;

	rsCHECKVALIDOBJECT(pFrom, OIDrsCStr);

	CHKiRet(cstrConstruct(&pThis));

	pThis->iStrLen = pFrom->iStrLen;
	pThis->iBufSize = pFrom->iStrLen + 1;
	if((pThis->pBuf = (uchar*) MALLOC(pThis->iBufSize)) == NULL) {
		RSFREEOBJ(pThis);
		ABORT_FINALIZE(RS_RET_OUT_OF_MEMORY);
	}

	/* copy properties */
	memcpy(pThis->pBuf, pFrom->pBuf, pThis->iStrLen);

	*ppThis = pThis;
finalize_it:
	RETiRet;
}


void rsCStrDestruct(cstr_t **ppThis)
{
	cstr_t *pThis = *ppThis;

	free(pThis->pBuf);
	RSFREEOBJ(pThis);
	*ppThis = NULL;
}


static rsRetVal
rsCStrExtendBuf(cstr_t *const __restrict__ pThis, const size_t iMinNeeded)
{
	uchar *pNewBuf;
	size_t iNewSize;
	DEFiRet;

	if(iMinNeeded > RS_STRINGBUF_ALLOC_INCREMENT) {
		iNewSize = (iMinNeeded / RS_STRINGBUF_ALLOC_INCREMENT + 1) * RS_STRINGBUF_ALLOC_INCREMENT;
	} else {
		iNewSize = pThis->iBufSize + RS_STRINGBUF_ALLOC_INCREMENT;
	}
	iNewSize += pThis->iBufSize; /* add current size */

	CHKmalloc(pNewBuf = (uchar*) realloc(pThis->pBuf, iNewSize));
	pThis->iBufSize = iNewSize;
	pThis->pBuf = pNewBuf;

finalize_it:
	RETiRet;
}

rsRetVal cstrAppendChar(cstr_t *const __restrict__ pThis, const uchar c)
{
	rsRetVal iRet = RS_RET_OK;

	if(pThis->iStrLen+1 >= pThis->iBufSize) {
		CHKiRet(rsCStrExtendBuf(pThis, 1)); /* need more memory! */
	}

	*(pThis->pBuf + pThis->iStrLen++) = c;

finalize_it:
	return iRet;
}

rsRetVal rsCStrAppendStrWithLen(cstr_t *pThis, const uchar* psz, size_t iStrLen)
{
	DEFiRet;

	rsCHECKVALIDOBJECT(pThis, OIDrsCStr);
	assert(psz != NULL);

	if(pThis->iStrLen + iStrLen >= pThis->iBufSize) {
		CHKiRet(rsCStrExtendBuf(pThis, iStrLen)); /* need more memory! */
	}

	memcpy(pThis->pBuf + pThis->iStrLen, psz, iStrLen);
	pThis->iStrLen += iStrLen;

finalize_it:
	RETiRet;
}

rsRetVal cstrAppendCStr(cstr_t *pThis, cstr_t *pstrAppend)
{
	return rsCStrAppendStrWithLen(pThis, pstrAppend->pBuf, pstrAppend->iStrLen);
}

uchar*
cstrGetSzStrNoNULL(cstr_t *const __restrict__ pThis)
{
	rsCHECKVALIDOBJECT(pThis, OIDrsCStr);

	if(pThis->pBuf == NULL)
		return (uchar*) "";

	pThis->pBuf[pThis->iStrLen] = '\0'; /* space for this is reserved */
	return(pThis->pBuf);
}

/* ---- runtime/stream.h (verbatim SUBSET -- only the fields strmReadMultiLine's own body
 * touches; see FIDELITY NOTES above) ---- */
typedef struct strm_s {
	int readTimeout;             /* stream.h:122 */
	time_t lastRead;              /* stream.h:123 */
	cstr_t *prevLineSegment;      /* stream.h:161 */
	cstr_t *prevMsgSegment;       /* stream.h:162 */
	int ignoringMsg;               /* stream.h:165 */
} strm_t;

/* ---- incidental stand-ins (never on the crash path -- see FIDELITY NOTES) ---- */
static void dbgprintf(const char *fmt, ...) { (void)fmt; }

static time_t getTime(time_t *ttSeconds)
{
	time_t t = time(NULL);
	if(ttSeconds != NULL)
		*ttSeconds = t;
	return t;
}

/* fixed $MaxMessageSize -- a real, admin-configurable rsyslog setting (runtime/glbl.c
 * glblGetMaxLine); the bug is in the *comparison* against it, not any particular value. */
static int glblGetMaxLine(void) { return 64; }

typedef struct { void (*LogError)(int, int, const char*, ...); } errmsg_if_t;
static void vb_LogError(int iErrno, int iErrCode, const char *fmt, ...)
{
	(void)iErrno; (void)iErrCode; (void)fmt;
}
static errmsg_if_t errmsg = { vb_LogError };

/* strmReadChar -- real one is disk I/O + zlib via pThis->pIOBuf; this minimal stand-in reads
 * sequentially from the attacker-controlled input file, matching the real function's exact
 * one-byte-at-a-time contract. */
static const uchar *g_src;
static size_t g_src_len;
static size_t g_src_pos;

static rsRetVal strmReadChar(strm_t *pThis, uchar *pC)
{
	(void)pThis;
	if(g_src_pos >= g_src_len)
		return RS_RET_EOF;
	*pC = g_src[g_src_pos++];
	return RS_RET_OK;
}

/* ============================================================================================ */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_65a35fce/target/original_function.c */
/* ============================================================================================ */
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
/* ==== end verbatim target function ==== */

/* ---- driver --------------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded) -- the whole "stream" file -- and
 * feeds it to strmReadMultiLine() one byte at a time via strmReadChar(). Calls
 * strmReadMultiLine() in a loop on ONE strm_t, exactly like the real caller (imfile's
 * pollFileReal()) drives repeated polls of a single open stream: state (prevMsgSegment/
 * prevLineSegment/ignoringMsg) legitimately persists call to call, entirely through the
 * target function's own logic -- the driver never pokes strm_t fields mid-run.
 *
 * Stops on the first non-RS_RET_OK return (EOF, or any other terminal condition -- matches the
 * real poller's own loop-exit test) or after a generous iteration cap (safety net; never
 * reached by any crafted input here). A triggering input crashes inside strmReadMultiLine's own
 * call to rsCStrConstructFromszStr() well before either of those.
 */
int main(int argc, char **argv)
{
	if(argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
	FILE *fp = fopen(argv[1], "rb");
	if(!fp) { perror("fopen"); return 64; }
	if(fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
	long fsz = ftell(fp);
	if(fsz < 0) { fclose(fp); return 64; }
	if(fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

	size_t n = (size_t) fsz;
	uchar *buf = (uchar*) malloc(n ? n : 1);   /* HEAP, ASAN-guarded */
	if(!buf) { fclose(fp); return 64; }
	size_t rd = n ? fread(buf, 1, n, fp) : 0;
	fclose(fp);

	g_src = buf;
	g_src_len = rd;
	g_src_pos = 0;

	strm_t strm;
	memset(&strm, 0, sizeof(strm));
	strm.readTimeout = 0;           /* disable the finalize_it timeout branch -- unrelated to this bug */
	strm.prevLineSegment = NULL;
	strm.prevMsgSegment = NULL;
	strm.ignoringMsg = 0;

	regex_t preg;
	if(regcomp(&preg, "^X", 0) != 0) { free(buf); return 64; }

	const sbool bEscapeLF = 1;
	const sbool discardTruncatedMsg = 0;
	const sbool msgDiscardingError = 0;

	for(int calls = 0; calls < 64; calls++) {
		cstr_t *out = NULL;
		rsRetVal r = strmReadMultiLine(&strm, &out, &preg, bEscapeLF, discardTruncatedMsg, msgDiscardingError);
		if(out != NULL)
			cstrDestruct(&out);
		if(r != RS_RET_OK)
			break;   /* EOF (or another terminal condition) -- matches the real poller's exit test */
	}

	/* Only reached on a SAFE run (a triggering run aborts inside strmReadMultiLine). */
	regfree(&preg);
	if(strm.prevLineSegment != NULL) cstrDestruct(&strm.prevLineSegment);
	if(strm.prevMsgSegment != NULL) cstrDestruct(&strm.prevMsgSegment);
	free(buf);
	return 0;
}
