/*
 * cve_barebone direct-call harness for CVE-2018-16452 (tcpdump smb_fdata()).
 *
 * Bug (CWE-674, Uncontrolled Recursion): smb_fdata() interprets a "*<sub-fmt>"
 * format token by recursively re-invoking itself on the remainder of the
 * format string, once per element, with NO depth limit. The upstream fix
 * (commit 24182d959f661327525a20d9a94c98a8ec016778) adds `if (depth == 10)`
 * to cap the recursion. Feeding smb_fdata() a format string consisting of
 * many '*' characters back-to-back drives unbounded recursion (one stack
 * frame per '*') until the process stack is exhausted -> SIGSEGV against the
 * guard page, reported by ASAN as "stack-overflow", with smb_fdata itself
 * on every frame of the crash stack.
 *
 * smb_fdata() below is pasted byte-for-byte from
 * data_cve/cve_7aa71e51/target/original_function.c.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>   /* u_char, u_int (glibc BSD compat typedefs) */

/* ---- real type definitions smb_fdata needs (names match netdissect.h / smb.h) ---- */

typedef struct netdissect_options netdissect_options;

/* Minimal netdissect_options: smb_fdata only ever touches ndo->ndo_printf,
 * via the ND_PRINT macro below. The real struct (netdissect.h) carries many
 * more unrelated fields (ndo_bflag, ndo_snapend, ...); none of them are
 * referenced by smb_fdata's own body, so only the field it actually uses is
 * reproduced here, under its real name. */
struct netdissect_options {
    int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h:321 */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* smb.h:119 */
#define PTR_DIFF(p1, p2) ((size_t)(((const char *)(p1)) - (const char *)(p2)))

/* Incidental callees reachable from smb_fdata's body but NOT on the
 * recursion-exhaustion crash path exercised here (that path only ever hits
 * the '*' case, consuming '*' characters until the format string is empty).
 * Faithful minimal stubs so the file links standalone. */
static const u_char *
smb_fdata1(netdissect_options *ndo, const u_char *buf, const char *fmt,
           const u_char *maxbuf, int unicodestr)
{
    (void)ndo; (void)fmt; (void)unicodestr;
    return buf < maxbuf ? buf + 1 : buf;
}

static void
smb_print_data(netdissect_options *ndo, const unsigned char *buf, int len)
{
    (void)ndo; (void)buf; (void)len;
}

/* ---- smb_fdata, pasted verbatim from target/original_function.c ---- */

const u_char *
smb_fdata(netdissect_options *ndo,
          const u_char *buf, const char *fmt, const u_char *maxbuf,
          int unicodestr)
{
    static int depth = 0;
    char s[128];
    char *p;

    while (*fmt) {
	switch (*fmt) {
	case '*':
	    fmt++;
	    while (buf < maxbuf) {
		const u_char *buf2;
		depth++;
		buf2 = smb_fdata(ndo, buf, fmt, maxbuf, unicodestr);
		depth--;
		if (buf2 == NULL)
		    return(NULL);
		if (buf2 == buf)
		    return(buf);
		buf = buf2;
	    }
	    return(buf);

	case '|':
	    fmt++;
	    if (buf >= maxbuf)
		return(buf);
	    break;

	case '%':
	    fmt++;
	    buf = maxbuf;
	    break;

	case '#':
	    fmt++;
	    return(buf);
	    break;

	case '[':
	    fmt++;
	    if (buf >= maxbuf)
		return(buf);
	    memset(s, 0, sizeof(s));
	    p = strchr(fmt, ']');
	    if ((size_t)(p - fmt + 1) > sizeof(s)) {
		/* overrun */
		return(buf);
	    }
	    strncpy(s, fmt, p - fmt);
	    s[p - fmt] = '\0';
	    fmt = p + 1;
	    buf = smb_fdata1(ndo, buf, s, maxbuf, unicodestr);
	    if (buf == NULL)
		return(NULL);
	    break;

	default:
	    ND_PRINT((ndo, "%c", *fmt));
	    fmt++;
	    break;
	}
    }
    if (!depth && buf < maxbuf) {
	size_t len = PTR_DIFF(maxbuf, buf);
	ND_PRINT((ndo, "Data: (%lu bytes)\n", (unsigned long)len));
	smb_print_data(ndo, buf, len);
	return(buf + len);
    }
    return(buf);
}

/* ---- driver ---- */

static int
fake_printf(netdissect_options *ndo, const char *fmt, ...)
{
    (void)ndo;
    va_list ap;
    int r;
    va_start(ap, fmt);
    r = vfprintf(stderr, fmt, ap);
    va_end(ap);
    return r;
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 1;
    }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 1; }
    long sz = ftell(fp);
    if (sz < 0) { fclose(fp); return 1; }
    rewind(fp);

    /* Heap-allocate the format-string input (ASAN-guarded), as the
     * attacker-controlled fmt argument to smb_fdata(). */
    char *fmt = (char *)malloc((size_t)sz + 1);
    if (!fmt) { fclose(fp); return 1; }
    size_t rd = fread(fmt, 1, (size_t)sz, fp);
    fclose(fp);
    fmt[rd] = '\0';

    /* Heap-allocate a small SMB "packet" buffer for buf/maxbuf. The '*'
     * recursion path never advances buf, so any non-empty region keeps
     * `buf < maxbuf` true across every recursion level -- exactly like the
     * real caller's `buf`..`maxbuf` window over one attacker-controlled SMB
     * packet. */
    u_char *data = (u_char *)malloc(16);
    if (!data) { free(fmt); return 1; }
    memset(data, 0x41, 16);

    netdissect_options ndo_storage;
    ndo_storage.ndo_printf = fake_printf;

    const u_char *result = smb_fdata(&ndo_storage, data, fmt, data + 16, 0);
    (void)result;

    free(data);
    free(fmt);
    return 0;
}
