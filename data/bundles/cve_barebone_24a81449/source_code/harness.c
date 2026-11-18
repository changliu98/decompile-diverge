/* cve_barebone harness -- libarchive CVE-2020-21674 /
 * archive_string_append_from_wcs heap-buffer-overflow WRITE (CWE-787).
 *
 * See the generator script (scripts/gen_dc_cve_24a81449.py) docstring for the full bug
 * writeup. In short: archive_string_append_from_wcs's mid-loop reallocation
 * (`archive_string_ensure(as, as->length + len*2+1)`) does not reserve MB_CUR_MAX bytes, so
 * when it happens to be a NO-OP against an already-tight buffer, the following wcrtomb() call
 * can write a multi-byte wide character straight past the allocation.
 *
 * TRIGGER: a `struct archive_string` whose buffer_length is exactly `as->length + 3` bytes
 *          (a 3-byte "room" -- deliberately < the 4 bytes UTF-8 needs for a supplementary-
 *          plane wide char) plus a single such wide char (len==1) -- both
 *          archive_string_ensure() calls become no-ops (3 >= 1*1+1 and 3 >= 1*2+1), so the
 *          loop writes a 4-byte UTF-8 sequence into that 3-byte room: 1 byte overflow, always,
 *          regardless of whether the platform's MB_CUR_MAX is 4 or 6 (glibc's UTF-8 wcrtomb()
 *          only ever emits up to 4 bytes for a valid Unicode scalar either way).
 * SAFE:    a generously-sized buffer (room >= 8*wlen+32) -- every archive_string_ensure()
 *          call (no-op or a genuine realloc()) leaves far more headroom than any wide char
 *          could need, so the loop always stays in-bounds.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <wchar.h>
#include <locale.h>

/* ---- struct archive_string: VERBATIM (libarchive/archive_string.h) ---- */
struct archive_string {
	char	*s;  /* Pointer to the storage */
	size_t	 length; /* Length of 's' in characters */
	size_t	 buffer_length; /* Length of malloc-ed storage in bytes. */
};

/* ---- archive_string_free: VERBATIM (libarchive/archive_string.c) -- called by
 * archive_string_ensure() on allocation failure. ---- */
void
archive_string_free(struct archive_string *as)
{
	as->length = 0;
	as->buffer_length = 0;
	free(as->s);
	as->s = NULL;
}

/* ---- archive_string_ensure: VERBATIM (libarchive/archive_string.c) -- the ONLY function
 * archive_string_append_from_wcs calls besides libc wcrtomb()/memset(). Its "return
 * immediately if the existing buffer_length already covers the request" fast path (the very
 * first `if`) is the mechanism the CVE exploits: a no-op "reallocation" that leaves the
 * too-small window open instead of growing it. ---- */
/* Returns NULL on any allocation failure. */
struct archive_string *
archive_string_ensure(struct archive_string *as, size_t s)
{
	char *p;
	size_t new_length;

	/* If buffer is already big enough, don't reallocate. */
	if (as->s && (s <= as->buffer_length))
		return (as);

	/*
	 * Growing the buffer at least exponentially ensures that
	 * append operations are always linear in the number of
	 * characters appended.  Using a smaller growth rate for
	 * larger buffers reduces memory waste somewhat at the cost of
	 * a larger constant factor.
	 */
	if (as->buffer_length < 32)
		/* Start with a minimum 32-character buffer. */
		new_length = 32;
	else if (as->buffer_length < 8192)
		/* Buffers under 8k are doubled for speed. */
		new_length = as->buffer_length + as->buffer_length;
	else {
		/* Buffers 8k and over grow by at least 25% each time. */
		new_length = as->buffer_length + as->buffer_length / 4;
		/* Be safe: If size wraps, fail. */
		if (new_length < as->buffer_length) {
			/* On failure, wipe the string and return NULL. */
			archive_string_free(as);
			errno = ENOMEM;/* Make sure errno has ENOMEM. */
			return (NULL);
		}
	}
	/*
	 * The computation above is a lower limit to how much we'll
	 * grow the buffer.  In any case, we have to grow it enough to
	 * hold the request.
	 */
	if (new_length < s)
		new_length = s;
	/* Now we can reallocate the buffer. */
	p = (char *)realloc(as->s, new_length);
	if (p == NULL) {
		/* On failure, wipe the string and return NULL. */
		archive_string_free(as);
		errno = ENOMEM;/* Make sure errno has ENOMEM. */
		return (NULL);
	}

	as->s = p;
	as->buffer_length = new_length;
	return (as);
}

/* The pasted target below needs HAVE_WCRTOMB so it takes the (thread-safe) wcrtomb() branch --
 * exactly like every real build of libarchive on a HAVE_WCRTOMB platform (glibc always has
 * it). A build-time #define, not an edit to the function's own bytes. */
#define HAVE_WCRTOMB 1

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash keeps its own stack frame (dc_batch requires the target function
 * name in the ASAN backtrace); ordinary (non-static) linkage already makes clang unlikely to
 * inline it at -O1, this just forbids it outright. */
__attribute__((noinline))
int
archive_string_append_from_wcs(struct archive_string *as,
    const wchar_t *w, size_t len)
{
	/* We cannot use the standard wcstombs() here because it
	 * cannot tell us how big the output buffer should be.  So
	 * I've built a loop around wcrtomb() or wctomb() that
	 * converts a character at a time and resizes the string as
	 * needed.  We prefer wcrtomb() when it's available because
	 * it's thread-safe. */
	int n, ret_val = 0;
	char *p;
	char *end;
#if HAVE_WCRTOMB
	mbstate_t shift_state;

	memset(&shift_state, 0, sizeof(shift_state));
#else
	/* Clear the shift state before starting. */
	wctomb(NULL, L'\0');
#endif
	/*
	 * Allocate buffer for MBS.
	 * We need this allocation here since it is possible that
	 * as->s is still NULL.
	 */
	if (archive_string_ensure(as, as->length + len + 1) == NULL)
		return (-1);

	p = as->s + as->length;
	end = as->s + as->buffer_length - MB_CUR_MAX -1;
	while (*w != L'\0' && len > 0) {
		if (p >= end) {
			as->length = p - as->s;
			as->s[as->length] = '\0';
			/* Re-allocate buffer for MBS. */
			if (archive_string_ensure(as,
			    as->length + len * 2 + 1) == NULL)
				return (-1);
			p = as->s + as->length;
			end = as->s + as->buffer_length - MB_CUR_MAX -1;
		}
#if HAVE_WCRTOMB
		n = wcrtomb(p, *w++, &shift_state);
#else
		n = wctomb(p, *w++);
#endif
		if (n == -1) {
			if (errno == EILSEQ) {
				/* Skip an illegal wide char. */
				*p++ = '?';
				ret_val = -1;
			} else {
				ret_val = -1;
				break;
			}
		} else
			p += n;
		len--;
	}
	as->length = p - as->s;
	as->s[as->length] = '\0';
	return (ret_val);
}
/* ==== end verbatim target function ==== */

/* Eight Unicode supplementary-plane scalar values: EVERY one of them needs EXACTLY 4 bytes to
 * encode in UTF-8 (the definition of a 4-byte UTF-8 sequence is U+10000..U+10FFFF, and glibc's
 * wcrtomb() never emits more than that for a valid scalar), so the TRIGGER construction below
 * is exact regardless of whether the platform reports MB_CUR_MAX==4 or MB_CUR_MAX==6 for its
 * UTF-8 locale (glibc's UTF-8 charmap historically advertises 6, for pre-RFC3629 compat) --
 * the overflow amount is pinned at n(4) - room(3) == 1 byte either way. */
static const uint32_t VB_CODEPOINTS[] = {
    0x10000, 0x1F600, 0x1F4A9, 0x20000, 0x2F800, 0x10FFFD, 0x1F914, 0x2A700,
};
#define VB_N_CODEPOINTS (sizeof(VB_CODEPOINTS) / sizeof(VB_CODEPOINTS[0]))

/* Driver: reads argv[1] into a HEAP buffer (malloc, ASAN-guarded) and derives every argument
 * to archive_string_append_from_wcs from those bytes. */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    if (!setlocale(LC_ALL, "C.UTF-8") && !setlocale(LC_ALL, "en_US.UTF-8")) {
        fprintf(stderr, "no UTF-8 locale available\n");
        return 2;
    }
    if (MB_CUR_MAX < 4) {
        fprintf(stderr, "MB_CUR_MAX=%d: locale is not multibyte, this PoC needs UTF-8\n",
            (int)MB_CUR_MAX);
        return 2;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    fseek(fp, 0, SEEK_END);
    long ln = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (ln < 0) ln = 0;
    size_t n = (size_t)ln;
    unsigned char *data = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
    if (!data) { fclose(fp); return 2; }
    size_t got = fread(data, 1, n, fp);
    fclose(fp);
    if (got < 20) { free(data); return 0; }   /* too small -> clean exit */

    /* ---- construct archive_string_append_from_wcs's arguments from the input bytes ----
     * byte0   : mode  -- even => TRIGGER, odd => SAFE
     * byte1   : codepoint index into VB_CODEPOINTS
     * byte2   : wlen selector (SAFE only: 1..8 wide chars; TRIGGER always uses wlen==1)
     * byte3   : init_len perturbation (0..63) -- varies the "already-used" prefix length
     * byte4.. : filler bytes driving SAFE wide-char content
     */
    unsigned mode   = data[0];
    unsigned cp_idx = data[1] % VB_N_CODEPOINTS;
    unsigned wsel   = 1u + (data[2] % 8u);
    unsigned initp  = data[3] % 64u;
    int trigger = (mode & 1u) == 0u;

    unsigned init_len, room, wlen;
    wchar_t w[10];

    if (trigger) {
        /* room==3: BOTH archive_string_ensure() calls inside archive_string_append_from_wcs
         * become no-ops against this pre-sized buffer_length (3 >= wlen*1+1 and
         * 3 >= wlen*2+1 for wlen==1), yet a supplementary-plane wide char needs exactly 4
         * bytes to encode -- 1 byte short, guaranteed. */
        wlen = 1;
        room = 3;
        init_len = 32 + initp;             /* varies the file across the 25 trigger inputs */
        w[0] = (wchar_t)VB_CODEPOINTS[cp_idx];
        w[1] = L'\0';
    } else {
        /* room generous: every archive_string_ensure() call -- no-op or a genuine realloc()
         * -- leaves comfortably more than any wide char could need, so the loop always stays
         * in-bounds; a mix of ASCII and (safely-margined) multi-byte filler content exercises
         * the same code paths without ever approaching the buffer edge. */
        wlen = wsel;
        room = 8u * wlen + 32u;
        init_len = initp;
        unsigned i;
        for (i = 0; i < wlen && i < 9; i++) {
            unsigned char b = data[4 + (i % (got - 4))];
            w[i] = (b & 1) ? (wchar_t)('a' + (b % 26))
                            : (wchar_t)VB_CODEPOINTS[(b + i) % VB_N_CODEPOINTS];
        }
        w[i] = L'\0';
        wlen = i;
    }

    unsigned buf_size = init_len + room;
    struct archive_string as;
    as.s = (char *)malloc(buf_size);       /* HEAP, ASAN-guarded; buffer_length below matches
                                               the ACTUAL allocation size exactly */
    if (!as.s) { free(data); return 2; }
    memset(as.s, 'A', buf_size);
    as.length = init_len;
    as.buffer_length = buf_size;

    free(data);

    /* volatile function pointer: forbid the compiler from proving the call away. */
    int (* volatile fn)(struct archive_string *, const wchar_t *, size_t) =
        archive_string_append_from_wcs;

    int rv = fn(&as, w, (size_t)wlen);
    (void)rv;

    /* Only reached on a SAFE run (a triggering run aborts inside the call above). */
    free(as.s);
    return 0;
}
