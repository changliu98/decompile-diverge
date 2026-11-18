/*
 * cve_barebone direct-call harness for vim get_tagfname() (src/tag.c).
 *
 * CVE-2026 (vim patch 9.1.2132): in the b_help branch, when the runtimepath
 * search found nothing new (tnp->tn_hf_idx >= tag_fnames.ga_len) the function
 * does
 *     STRCPY(buf, p_hf);           // <-- unbounded strcpy of 'helpfile'
 * into a caller-supplied buffer that is documented ("pointer to buffer of
 * MAXPATHL chars") and in real Vim IS exactly MAXPATHL bytes.  'helpfile'
 * (p_hf) is a normal Vim string option fully controllable via
 * `:set helpfile=...` with no length limit, so an overlong helpfile value
 * overflows `buf`.  The fix replaces the STRCPY with
 * `vim_strncpy(buf, p_hf, MAXPATHL - 1)`.
 *
 * This harness calls get_tagfname() directly and in isolation:
 *   - curbuf->b_help = TRUE           (take the help-file branch)
 *   - first = TRUE                    (CLEAR_POINTER(tnp) -> tn_hf_idx == 0)
 *   - tag_fnames stays empty (ga_len == 0, do_in_runtimepath stubbed to find
 *     nothing -- a legitimate real-world outcome when 'runtimepath' has no
 *     doc/tags files, which is exactly the environment here)
 *   - p_hf is the attacker-controlled input file content (argv[1])
 *   - buf is a heap buffer of exactly MAXPATHL bytes (ASAN-guarded), matching
 *     the real caller's contract, so an overlong p_hf triggers a heap-buffer-
 *     overflow WRITE (CWE-787) at the exact vulnerable STRCPY line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal vim.h primitives (real names/values, src/vim.h + src/os_unix.h) ---- */

typedef unsigned char char_u;

#define NUL   '\000'
#define OK    1
#define FAIL  0
#define TRUE  1
#define FALSE 0

/* src/os_unix.h: MAXPATHL is PATH_MAX on Linux (> 1000), else 1024 */
#define MAXPATHL 4096

#define STRLEN(s)        strlen((char *)(s))
#define STRCPY(d, s)     strcpy((char *)(d), (char *)(s))
#define STRNCPY(d, s, n) strncpy((char *)(d), (char *)(s), (size_t)(n))
#define STRCMP(d, s)     strcmp((char *)(d), (char *)(s))
#define STRMOVE(d, s)    memmove((d), (s), STRLEN(s) + 1)
#define vim_memset(ptr, c, size) memset((ptr), (c), (size))
#define CLEAR_POINTER(ptr) vim_memset((ptr), 0, sizeof(*(ptr)))

#define DIP_ALL        0x01
#define FINDFILE_FILE  0

/* ---- minimal structs.h (real field names, src/structs.h) ---- */

typedef struct growarray
{
    int     ga_len;
    int     ga_maxlen;
    int     ga_itemsize;
    int     ga_growsize;
    void    *ga_data;
} garray_T;
#define GA_EMPTY  {0, 0, 0, 0, NULL}

/* Structure used for get_tagfname() (src/structs.h, verbatim field set). */
typedef struct
{
    char_u  *tn_tags;
    char_u  *tn_np;
    int     tn_did_filefind_init;
    int     tn_hf_idx;
    void    *tn_search_ctx;
} tagname_T;

/*
 * Minimal buf_T stub: real vim's buf_T is a huge structure (hundreds of
 * fields). get_tagfname() only ever touches these three fields on curbuf,
 * so only these are modeled (real field names, src/structs.h).
 */
typedef struct
{
    int     b_help;      // TRUE for help file buffer
    char_u  *b_p_tags;   // 'tags' local value
    char_u  *b_ffname;   // full path file name
} buf_T;

/* ---- globals get_tagfname() references (real names, src/globals.h / option.h) ---- */

buf_T   *curbuf = NULL;
char_u  *p_hf = NULL;     // 'helpfile'
char_u  *p_tags = NULL;   // 'tags'
static garray_T tag_fnames = GA_EMPTY;
static int really_exiting = 0;

/* ---- real callees (verbatim ports of the actual, tiny implementations) ---- */

/* src/alloc.c:vim_free */
void vim_free(void *x)
{
    if (x != NULL && !really_exiting)
        free(x);
}

/* src/alloc.c:ga_init */
static void ga_init(garray_T *gap)
{
    gap->ga_data = NULL;
    gap->ga_maxlen = 0;
    gap->ga_len = 0;
}

/* src/alloc.c:ga_init2 */
void ga_init2(garray_T *gap, size_t itemsize, int growsize)
{
    ga_init(gap);
    gap->ga_itemsize = (int)itemsize;
    gap->ga_growsize = growsize;
}

/* src/alloc.c:ga_clear */
static void ga_clear(garray_T *gap)
{
    vim_free(gap->ga_data);
    ga_init(gap);
}

/* src/alloc.c:ga_clear_strings */
void ga_clear_strings(garray_T *gap)
{
    int i;
    if (gap->ga_data != NULL)
        for (i = 0; i < gap->ga_len; ++i)
            vim_free(((char_u **)(gap->ga_data))[i]);
    ga_clear(gap);
}

/* src/strings.c:vim_strncpy (real impl -- this IS the fixed function, kept
 * verbatim so the "else" branch of get_tagfname still compiles/behaves like
 * upstream; it is not on the crash path we exercise here). */
void vim_strncpy(char_u *to, char_u *from, size_t len)
{
    STRNCPY(to, from, len);
    to[len] = NUL;
}

/* src/strings.c:vim_strsave (real impl, trivial). Only used on the
 * non-help-buffer branch, which this harness never takes (curbuf->b_help is
 * always TRUE), but is provided so get_tagfname compiles unmodified. */
char_u *vim_strsave(char_u *string)
{
    char_u *p;
    size_t len = STRLEN(string) + 1;
    p = (char_u *)malloc(len);
    if (p != NULL)
        memcpy(p, string, len);
    return p;
}

/*
 * src/filepath.c:gettail, simplified for a plain-ASCII harness: real
 * gettail() additionally special-cases multibyte encodings and "c:" drive
 * letters (MSWIN) via get_past_head()/MB_PTR_ADV, which is a no-op on the
 * Unix code path this harness models. On Unix, get_past_head() is the
 * identity function, so this is a faithful minimal port for the corpus data
 * used here (single-byte ASCII strings).
 */
char_u *gettail(char_u *fname)
{
    char_u *p1, *p2;
    if (fname == NULL)
        return (char_u *)"";
    for (p1 = p2 = fname; *p2; ++p2)
        if (*p2 == '/')
            p1 = p2 + 1;
    return p1;
}

/*
 * src/findfile.c:simplify_filename does cosmetic "." / ".." / duplicate "/"
 * removal in-place. It is purely a path-string normalization step, not part
 * of the vulnerable mechanism (the bug is the unbounded STRCPY that already
 * happened by the time this runs), so it is stubbed as a no-op -- a minimal
 * faithful stub for an incidental callee.
 */
size_t simplify_filename(char_u *filename)
{
    return STRLEN(filename);
}

/*
 * src/tag.c:found_tagfile_cb -- callback do_in_runtimepath() invokes per
 * match. Never actually invoked here (do_in_runtimepath is stubbed to find
 * nothing), kept only so its address can be passed / it still typechecks.
 */
static void found_tagfile_cb(char_u *fname, void *cookie)
{
    (void)fname;
    (void)cookie;
}

/*
 * src/scriptfile.c:do_in_runtimepath -- incidental filesystem-search
 * callee, not part of the vulnerable mechanism. Minimal faithful stub:
 * finds nothing, matching the real behaviour of an environment whose
 * 'runtimepath' has no doc/tags[-??] files (exactly the case here, there is
 * no real vim runtime tree). This leaves tag_fnames.ga_len == 0, which is
 * what drives execution into the vulnerable STRCPY branch.
 */
int do_in_runtimepath(char_u *name, int flags,
        void (*callback)(char_u *fname, void *ck), void *cookie)
{
    (void)name; (void)flags; (void)callback; (void)cookie;
    return FAIL;
}

/* ---- dead-code-only stubs: only reachable when curbuf->b_help == FALSE,
 * which this harness never sets, but get_tagfname() references them so they
 * must exist to link. Minimal faithful stubs for incidental callees. ---- */

int copy_option_part(char_u **option, char_u *buf, int maxlen, char *sep_chars)
{
    (void)option; (void)maxlen; (void)sep_chars;
    buf[0] = NUL;
    return FAIL;
}

char_u *vim_findfile_stopdir(char_u *buf)
{
    (void)buf;
    return NULL;
}

void *vim_findfile_init(char_u *path, char_u *filename, size_t filenamelen,
        char_u *stopdirs, int level, int free_visited, int find_what,
        void *search_ctx_arg, int tagfile, char_u *rel_fname)
{
    (void)path; (void)filename; (void)filenamelen; (void)stopdirs;
    (void)level; (void)free_visited; (void)find_what; (void)search_ctx_arg;
    (void)tagfile; (void)rel_fname;
    return NULL;
}

char_u *vim_findfile(void *search_ctx_arg)
{
    (void)search_ctx_arg;
    return NULL;
}

void vim_findfile_cleanup(void *ctx)
{
    (void)ctx;
}

/* ============================================================
 * get_tagfname() -- pasted BYTE-FOR-BYTE from
 * data_cve/cve_4dd33f4c/target/original_function.c
 * ============================================================ */

int
get_tagfname(
    tagname_T	*tnp,	// holds status info
    int		first,	// TRUE when first file name is wanted
    char_u	*buf)	// pointer to buffer of MAXPATHL chars
{
    char_u		*fname = NULL;
    char_u		*r_ptr;
    int			i;

    if (first)
	CLEAR_POINTER(tnp);

    if (curbuf->b_help)
    {
	/*
	 * For help files it's done in a completely different way:
	 * Find "doc/tags" and "doc/tags-??" in all directories in
	 * 'runtimepath'.
	 */
	if (first)
	{
	    ga_clear_strings(&tag_fnames);
	    ga_init2(&tag_fnames, sizeof(char_u *), 10);
	    do_in_runtimepath((char_u *)
#ifdef FEAT_MULTI_LANG
# ifdef VMS
		    // Functions decc$to_vms() and decc$translate_vms() crash
		    // on some VMS systems with wildcards "??".  Seems ECO
		    // patches do fix the problem in C RTL, but we can't use
		    // an #ifdef for that.
		    "doc/tags doc/tags-*"
# else
		    "doc/tags doc/tags-??"
# endif
#else
		    "doc/tags"
#endif
					   , DIP_ALL, found_tagfile_cb, NULL);
	}

	if (tnp->tn_hf_idx >= tag_fnames.ga_len)
	{
	    // Not found in 'runtimepath', use 'helpfile', if it exists and
	    // wasn't used yet, replacing "help.txt" with "tags".
	    if (tnp->tn_hf_idx > tag_fnames.ga_len || *p_hf == NUL)
		return FAIL;
	    ++tnp->tn_hf_idx;
	    STRCPY(buf, p_hf);
	    STRCPY(gettail(buf), "tags");
#ifdef BACKSLASH_IN_FILENAME
	    slash_adjust(buf);
#endif
	    simplify_filename(buf);

	    for (i = 0; i < tag_fnames.ga_len; ++i)
		if (STRCMP(buf, ((char_u **)(tag_fnames.ga_data))[i]) == 0)
		    return FAIL; // avoid duplicate file names
	}
	else
	    vim_strncpy(buf, ((char_u **)(tag_fnames.ga_data))[
					     tnp->tn_hf_idx++], MAXPATHL - 1);
	return OK;
    }

    if (first)
    {
	// Init.  We make a copy of 'tags', because autocommands may change
	// the value without notifying us.
	tnp->tn_tags = vim_strsave((*curbuf->b_p_tags != NUL)
						 ? curbuf->b_p_tags : p_tags);
	if (tnp->tn_tags == NULL)
	    return FAIL;
	tnp->tn_np = tnp->tn_tags;
    }

    /*
     * Loop until we have found a file name that can be used.
     * There are two states:
     * tnp->tn_did_filefind_init == FALSE: setup for next part in 'tags'.
     * tnp->tn_did_filefind_init == TRUE: find next file in this part.
     */
    for (;;)
    {
	if (tnp->tn_did_filefind_init)
	{
	    fname = vim_findfile(tnp->tn_search_ctx);
	    if (fname != NULL)
		break;

	    tnp->tn_did_filefind_init = FALSE;
	}
	else
	{
	    char_u  *filename = NULL;

	    // Stop when used all parts of 'tags'.
	    if (*tnp->tn_np == NUL)
	    {
		vim_findfile_cleanup(tnp->tn_search_ctx);
		tnp->tn_search_ctx = NULL;
		return FAIL;
	    }

	    /*
	     * Copy next file name into buf.
	     */
	    buf[0] = NUL;
	    (void)copy_option_part(&tnp->tn_np, buf, MAXPATHL - 1, " ,");

	    r_ptr = vim_findfile_stopdir(buf);
	    // move the filename one char forward and truncate the
	    // filepath with a NUL
	    filename = gettail(buf);
	    if (r_ptr != NULL)
	    {
		STRMOVE(r_ptr + 1, r_ptr);
		++r_ptr;
	    }
	    STRMOVE(filename + 1, filename);
	    *filename++ = NUL;

	    tnp->tn_search_ctx = vim_findfile_init(buf, filename,
		    STRLEN(filename),
		    r_ptr, 100,
		    FALSE,	   // don't free visited list
		    FINDFILE_FILE, // we search for a file
		    tnp->tn_search_ctx, TRUE, curbuf->b_ffname);
	    if (tnp->tn_search_ctx != NULL)
		tnp->tn_did_filefind_init = TRUE;
	}
    }

    STRCPY(buf, fname);
    vim_free(fname);
    return OK;
}

/* ============================================================
 * harness main(): read argv[1] into a heap buffer, wire it up as the
 * 'helpfile' option value, and call get_tagfname() directly.
 * ============================================================ */

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f)
    {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 0)
    {
        fclose(f);
        return 1;
    }

    /* Heap-allocate the attacker-controlled buffer, ASAN-guarded. */
    char_u *data = (char_u *)malloc((size_t)sz + 1);
    if (!data)
    {
        fclose(f);
        return 1;
    }
    size_t rd = fread(data, 1, (size_t)sz, f);
    fclose(f);
    data[rd] = NUL;

    /* Attacker-controlled 'helpfile' option value (real Vim option, no
     * built-in length cap -- settable via `:set helpfile=...`). */
    p_hf = data;
    p_tags = (char_u *)"";

    buf_T bufstub;
    memset(&bufstub, 0, sizeof(bufstub));
    bufstub.b_help = TRUE;
    bufstub.b_p_tags = (char_u *)"";
    bufstub.b_ffname = NULL;
    curbuf = &bufstub;

    tagname_T *tnp = (tagname_T *)malloc(sizeof(tagname_T));
    if (!tnp)
    {
        free(data);
        return 1;
    }

    /* The real caller's contract: "buf: pointer to buffer of MAXPATHL
     * chars". Heap-allocate exactly that size so ASAN catches any write
     * past it. */
    char_u *buf = (char_u *)malloc(MAXPATHL);
    if (!buf)
    {
        free(tnp);
        free(data);
        return 1;
    }

    int rc = get_tagfname(tnp, TRUE, buf);
    (void)rc;

    free(buf);
    free(tnp);
    free(data);
    return 0;
}
