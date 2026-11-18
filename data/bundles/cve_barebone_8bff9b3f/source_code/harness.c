#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* --- REAL type vocabulary from tcpdump (netdissect.h), verbatim names --- */
typedef unsigned int u_int;

struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

/* ==== TARGET FUNCTION (verbatim from target/original_function.c) ==== */
static char *
bittok2str_internal(register const struct tok *lp, register const char *fmt,
	   register u_int v, const char *sep)
{
        static char buf[256]; /* our stringbuffer */
        int buflen=0;
        register u_int rotbit; /* this is the bit we rotate through all bitpositions */
        register u_int tokval;
        const char * sepstr = "";

	while (lp != NULL && lp->s != NULL) {
            tokval=lp->v;   /* load our first value */
            rotbit=1;
            while (rotbit != 0) {
                /*
                 * lets AND the rotating bit with our token value
                 * and see if we have got a match
                 */
		if (tokval == (v&rotbit)) {
                    /* ok we have found something */
                    buflen+=snprintf(buf+buflen, sizeof(buf)-buflen, "%s%s",
                                     sepstr, lp->s);
                    sepstr = sep;
                    break;
                }
                rotbit=rotbit<<1; /* no match - lets shift and try again */
            }
            lp++;
	}

        if (buflen == 0)
            /* bummer - lets print the "unknown" message as advised in the fmt string if we got one */
            (void)snprintf(buf, sizeof(buf), fmt == NULL ? "#%08x" : fmt, v);
        return (buf);
}

/* ---- direct-call harness scaffolding ---- */
/* Call through a volatile function pointer so the -O1 optimizer cannot
   inline the static target into main() -- keeps bittok2str_internal a real
   frame in the ASAN backtrace. */
static char *(*volatile g_fn)(const struct tok *, const char *, u_int, const char *) = bittok2str_internal;

int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }
    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("fopen"); return 2; }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 2; }
    long ln = ftell(f);
    if (ln < 0) { fclose(f); return 2; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 2; }
    size_t n = (size_t)ln;

    /* Heap-allocate the input so any read/write is ASAN-guarded. */
    unsigned char *data = (unsigned char *)malloc(n ? n : 1);
    if (!data) { fclose(f); return 2; }
    size_t got = fread(data, 1, n, f);
    fclose(f);
    n = got;

    size_t off = 0;

    /* First byte -> v (the bitfield value). Any byte value is <= 255, hence
       never 0xffffffff, so value-0 tokens below always match. */
    u_int v = 0;
    if (off < n) { v = (u_int)data[off]; off++; }

    /* Build the struct tok array FDP-style from the rest: [len][len bytes]*.
       Each token gets value 0 (always matches) and a heap-copied string. */
    size_t cap = 8, ntok = 0;
    const size_t MAXTOK = 4096;
    struct tok *toks = (struct tok *)malloc((cap + 1) * sizeof(struct tok));
    if (!toks) { free(data); return 2; }

    while (off < n && ntok < MAXTOK) {
        size_t L = (size_t)data[off]; off++;
        size_t avail = n - off;
        size_t m = L < avail ? L : avail;
        char *s = (char *)malloc(m + 1);
        if (!s) break;
        memcpy(s, data + off, m);
        s[m] = '\0';
        off += m;
        if (ntok == cap) {
            cap *= 2;
            struct tok *nt = (struct tok *)realloc(toks, (cap + 1) * sizeof(struct tok));
            if (!nt) break;
            toks = nt;
        }
        toks[ntok].v = 0;
        toks[ntok].s = s;
        ntok++;
    }
    /* NULL-terminate the token table (as the real tcpdump tables are). */
    toks[ntok].v = 0;
    toks[ntok].s = NULL;

    const char *sep = ", ";
    char *r = g_fn(toks, NULL, v, sep);
    if (r) { volatile size_t sink = strlen(r); (void)sink; }
    return 0;
}
