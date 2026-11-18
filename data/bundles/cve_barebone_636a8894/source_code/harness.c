/*
 * Decompile-Diverge direct-call harness -- cve_636a8894 (vim, src/ex_docmd.c)
 *
 * TARGET FUNCTION (embedded VERBATIM below, unmodified): f_fullcommand
 *   src/ex_docmd.c, pre-fix (vulnerable) revision
 *   e0bfb7d3016ccd6c2186b9cd74cee6538eea9b5e.
 *
 * Bug (fixed by vim commit 4c6fe2e2ea62469642ed1d80b16d39e616b25cf5, patch
 * 8.2.xxxx "1846", upstream test comment: "this used to crash vim"):
 *   f_fullcommand implements the Vim script builtin fullcommand({name}).
 *   Its very first use of the argument reads the union member for the
 *   VAR_STRING case UNCONDITIONALLY, without first checking argvars[0]'s
 *   actual v_type:
 *       name = argvars[0].vval.v_string;
 *       if (name == NULL)
 *           return;
 *       ...
 *       while (*name == ':')
 *           name++;
 *   typval_T's "vval" member is a C union (v_number / v_string / v_list /
 *   ... all alias the same storage).  If the caller passes a NUMBER (e.g.
 *   the script `fullcommand(10)`), argvars[0].v_type == VAR_NUMBER and the
 *   union actually holds v_number == 10; reading vval.v_string reinterprets
 *   that integer as a char_u* -- "name" becomes the wild, essentially-NULL
 *   pointer (char_u *)10, which is neither NULL (so the NULL guard doesn't
 *   save it) nor a valid string. The very next statement,
 *   "while (*name == ':')", dereferences it and SIGSEGVs. The fix (upstream
 *   diff) replaces the raw union read with the type-aware accessor:
 *       name = tv_get_string(&argvars[0]);
 *   which coerces any typval to its string form instead of blindly reading
 *   the string union slot. The fault is entirely inside f_fullcommand's own
 *   body (its first dereference of the misinterpreted "name"), so
 *   f_fullcommand is always the top ASAN frame.
 *
 *   ASAN classifies this as SEGV on unknown address (wild/near-NULL pointer
 *   dereference) -> CWE-476 per this benchmark's crash-class mapping (see
 *   ddiv/cwe.py: "segv"/"segv on unknown address" -> CWE-476).
 *
 * Harness I/O contract (all attacker bytes live in a single HEAP buffer,
 * required so ASAN can catch the crash and so the input is fuzzable):
 *   argv[1] file layout:
 *     byte[0]   bit0: 1 => argvars[0] = { v_type = VAR_NUMBER,
 *                          vval.v_number = 1 + (small value derived from
 *                          byte[1..4], always in [1, 65535]) }
 *                          (TRIGGER: type confusion, "name" becomes a wild
 *                          pointer into the unmapped low-address guard
 *                          region -> SIGSEGV on the very first *name)
 *                     0 => argvars[0] = { v_type = VAR_STRING,
 *                          vval.v_string = <heap copy of byte[1..], NUL
 *                          terminated> }
 *                          (SAFE: a real string typval -- the exact case
 *                          f_fullcommand's own union read was written for --
 *                          runs the whole function body: the ':'/skip_range
 *                          prefix skip, the (stubbed) find_ex_command
 *                          lookup, and the "not found" theend cleanup, with
 *                          no fault)
 *     byte[1..] for the safe case: raw name bytes (copied to the heap
 *               as-is, NUL-terminated -- no filtering needed, an embedded
 *               NUL just truncates the C string early, which is a normal,
 *               in-bounds outcome for skip_range's byte-at-a-time scan).
 *
 *   argvars[1] is always { v_type = VAR_UNKNOWN } (the optional 2nd,
 *   boolean "vim9script" argument of fullcommand() is not part of this
 *   bug -- VAR_UNKNOWN makes f_fullcommand skip that branch entirely, the
 *   same as calling fullcommand() with a single argument).
 *
 *   main() reads argv[1] into a HEAP buffer, builds the argvars[] typval
 *   array as above, and calls f_fullcommand(argvars, &rettv) exactly once.
 *
 * Everything below other than main() and the small incidental-callee stubs
 * (marked as such) is copied verbatim (types with real field names, or the
 * target function byte-for-byte) from src/vim.h, src/ascii.h, src/macros.h,
 * src/structs.h, src/option.h, src/ex_cmds.h, src/globals.h, src/charset.c,
 * src/strings.c and src/ex_docmd.c of the vulnerable tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* ============================================================
 * Real typedefs / macros, copied from src/vim.h, src/ascii.h, src/macros.h
 * ============================================================ */

typedef unsigned char char_u;
typedef unsigned long long_u;                 /* vim.h, generic 64-bit branch */

#define NUL   '\000'                          /* ascii.h */
#define FAIL  0                                /* vim.h */
#define OK    1                                /* vim.h */
#define FALSE 0                                /* vim.h: note this is an int, not a long! */
#define TRUE  1                                /* vim.h */

#define VIM_ISWHITE(x)      ((x) == ' ' || (x) == '\t')       /* macros.h */

/* ============================================================
 * Real typedefs / structs, copied from src/structs.h
 * ============================================================ */

typedef long linenr_T;                         /* structs.h, generic branch */
typedef long varnumber_T;                      /* structs.h, generic branch */
typedef double float_T;                        /* structs.h */

/* Opaque types f_fullcommand only ever touches through a pointer (never
 * dereferenced on any path this harness exercises -- the type-confusion
 * crash happens before any of them are even constructed, and the safe path
 * never allocates one) -- kept as real forward-declared names, left
 * incomplete rather than pulling in their full (large, unrelated) struct
 * bodies. */
typedef struct listvar_S list_T;
typedef struct dictvar_S dict_T;
typedef struct partial_S partial_T;
typedef struct jobvar_S job_T;
typedef struct channel_S channel_T;
typedef struct instr_S instr_T;
typedef struct class_S class_T;
typedef struct object_S object_T;

typedef enum                                    /* structs.h, verbatim */
{
    VAR_UNKNOWN = 0,	// not set, any type or "void" allowed
    VAR_ANY,		// used for "any" type
    VAR_VOID,		// no value (function not returning anything)
    VAR_BOOL,		// "v_number" is used: VVAL_TRUE or VVAL_FALSE
    VAR_SPECIAL,	// "v_number" is used: VVAL_NULL or VVAL_NONE
    VAR_NUMBER,		// "v_number" is used
    VAR_FLOAT,		// "v_float" is used
    VAR_STRING,		// "v_string" is used
    VAR_BLOB,		// "v_blob" is used
    VAR_FUNC,		// "v_string" is function name
    VAR_PARTIAL,	// "v_partial" is used
    VAR_LIST,		// "v_list" is used
    VAR_DICT,		// "v_dict" is used
    VAR_JOB,		// "v_job" is used
    VAR_CHANNEL,	// "v_channel" is used
    VAR_INSTR,		// "v_instr" is used
    VAR_CLASS,		// "v_class" is used (also used for interface)
    VAR_OBJECT,		// "v_object" is used
} vartype_T;

/* Structure to hold an internal variable without a name (structs.h,
 * verbatim). */
typedef struct typval_S typval_T;
struct typval_S
{
    vartype_T	v_type;
    char	v_lock;		// see below: VAR_LOCKED, VAR_FIXED
    union
    {
	varnumber_T	v_number;	// number value
	float_T		v_float;	// floating point number value
	char_u		*v_string;	// string value (can be NULL)
	list_T		*v_list;	// list value (can be NULL)
	dict_T		*v_dict;	// dict value (can be NULL)
	partial_T	*v_partial;	// closure: function with args
	job_T		*v_job;		// job value (can be NULL)
	channel_T	*v_channel;	// channel value (can be NULL)
	instr_T		*v_instr;	// instructions to execute
	class_T		*v_class;	// class value (can be NULL)
	object_T	*v_object;	// object value (can be NULL)
    }		vval;
};

/* SCript ConteXt (structs.h) -- trimmed to the one field in_vim9script()
 * actually reads (sc_sid/sc_seq/sc_lnum are FEAT_EVAL script-position
 * bookkeeping, never touched on any path here). Real field name/type kept. */
typedef struct {
    int	sc_version;	// :scriptversion
} sctx_T;

/* cmdmod_T (structs.h) -- trimmed to the one field in_vim9script() /
 * f_fullcommand actually read/write (cmod_flags); the ~15 other real
 * fields (cmod_split, cmod_verbose, cmod_save_ei, ...) are UI/undo-command
 * bookkeeping never touched here. Real field name/type kept. */
typedef struct {
    int		cmod_flags;		// CMOD_ flags
#define CMOD_VIM9CMD	    0x4000	// ":vim9cmd"                (structs.h)
#define CMOD_LEGACY	    0x8000	// ":legacy"                  (structs.h)
} cmdmod_T;

#define SCRIPT_VERSION_VIM9 999999             /* structs.h */

/* ============================================================
 * Real typedefs / structs / macros, copied from src/ex_cmds.h,
 * src/option.h, src/macros.h
 * ============================================================ */

/* Compile-context type used only in find_ex_command's prototype on this
 * (dead, never-taken) call; kept opaque with its real name. */
typedef struct cctx_S cctx_T;

/*
 * cmdidx_T (ex_cmds.h) is really "enum CMD_index", the ~650-entry list of
 * every ":" Ex command (CMD_append, CMD_abbreviate, ..., CMD_decrement,
 * CMD_SIZE, CMD_USER = -1, CMD_USER_BUF = -2) generated by repeating the
 * EXCMD() macro over ex_cmds.h's command table. f_fullcommand only ever
 * compares ea.cmdidx against CMD_SIZE and (in dead code below, unreachable
 * because find_ex_command here always returns NULL first) indexes cmdnames[]
 * with it -- the identity of the other ~648 real command indices carries no
 * signal for this bug, so they are elided; CMD_SIZE (the one real value
 * f_fullcommand's own logic reads) is kept under its real name. */
typedef enum { CMD_SIZE } cmdidx_T;

typedef void (*ex_func_T) (void *eap);         /* ex_cmds.h, "eap" is really
						 * exarg_T*; the exact pointee
						 * type is irrelevant -- this
						 * typedef is only used to give
						 * "struct cmdname" (below) its
						 * real cmd_func field type,
						 * which is never called. */

typedef enum { ADDR_NONE } cmd_addr_T;         /* ex_cmds.h -- trimmed the
						 * same way as cmdidx_T: only
						 * cmdnames[]'s field type is
						 * needed, the value is never
						 * read (dead code below). */

/* struct exarg / exarg_T (ex_cmds.h) -- trimmed to the 4 fields
 * f_fullcommand's own body actually reads/writes (cmd, cmdidx, addr_count,
 * useridx); the ~25 other real fields (arg, nextcmd, line1/line2, cstack,
 * getline, ...) are Ex-command-execution state never touched by
 * f_fullcommand (it only ever fills in a local exarg_T to hand to
 * find_ex_command / not_in_vim9, both stubbed below). Real field
 * names/types kept. */
typedef struct exarg
{
    char_u	*cmd;		// the name of the command
    cmdidx_T	cmdidx;		// the index for the command
    int		addr_count;	// the number of addresses given
    int		useridx;	// user command index
} exarg_T;

#define IS_USER_CMDIDX(idx) ((int)(idx) < 0)   /* macros.h, verbatim */

/* struct cmdname / "cmdnames[]" (ex_cmds.h) -- the real global is the full
 * ~650-row EXCMD() command table. f_fullcommand only ever reads
 * cmdnames[ea.cmdidx].cmd_name, and only on the "found a real (non-user)
 * command" path -- which this harness's stubbed find_ex_command (always
 * returns NULL) never reaches, so that line is dead code that only needs to
 * type-check/link. A single dummy real-shaped row is kept under the real
 * struct/array name instead of the full table. */
static struct cmdname
{
    char_u	*cmd_name;	// name of the command
    ex_func_T   cmd_func;	// function for this command
    long_u	cmd_argt;	// flags declared above
    cmd_addr_T	cmd_addr_type;	// flag for address type
} cmdnames[1] = { { (char_u *) "", NULL, 0, ADDR_NONE } };

/* ============================================================
 * Real globals, copied from src/globals.h (verbatim names/types).
 * ============================================================ */

cmdmod_T cmdmod;                 // Ex command modifiers -- zero-initialized
				  // (static storage), matching Vim's own
				  // startup state (no ":vim9cmd"/":legacy"
				  // modifier active).
sctx_T current_sctx;             // zero-initialized -> sc_version == 0,
				  // i.e. not Vim9 script, matching Vim's own
				  // startup state.
int emsg_silent;                 // don't print error messages

/* ============================================================
 * Incidental-callee stubs / small real helpers.
 *
 * in_vim9script() is copied VERBATIM (src/vim9script.c) -- it is cheap and
 * its result gates the very first "if" in f_fullcommand's body, so it is
 * worth getting exactly right rather than stubbing: with the zero-
 * initialized cmdmod/current_sctx above it deterministically returns FALSE,
 * so f_fullcommand always falls straight through to
 * "name = argvars[0].vval.v_string" without ever calling
 * check_for_string_arg/check_for_opt_bool_arg -- exactly Vim's own
 * startup-time behaviour (no vim9script active), which is also exactly the
 * scenario the upstream regression test (`fullcommand(10)`) crashes in.
 *
 * check_for_string_arg / check_for_opt_bool_arg / tv_get_bool / not_in_vim9
 * / get_user_command_name / vim_strsave are all called ONLY inside branches
 * that are unreachable given the above (either guarded by "in_vim9script()"
 * being TRUE, which it never is here, or guarded by
 * "find_ex_command() != NULL", and find_ex_command is stubbed below to
 * always return NULL) -- i.e. every one of this harness's corpus inputs is
 * dead-code-safe past those lines. They are given real signatures (copied
 * from src/proto/typval.pro, src/proto/vim9script.pro,
 * src/proto/usercmd.pro, src/proto/strings.pro) purely so f_fullcommand's
 * own unmodified body still type-checks and links; their bodies are never
 * executed by any input this harness generates.
 * ============================================================ */

    int
in_vim9script(void)                                       /* vim9script.c, verbatim */
{
    return (current_sctx.sc_version == SCRIPT_VERSION_VIM9
					 || (cmdmod.cmod_flags & CMOD_VIM9CMD))
		&& !(cmdmod.cmod_flags & CMOD_LEGACY);
}

int check_for_string_arg(typval_T *args, int idx)          /* proto/typval.pro */
{ (void) args; (void) idx; return OK; }

int check_for_opt_bool_arg(typval_T *args, int idx)        /* proto/typval.pro */
{ (void) args; (void) idx; return OK; }

varnumber_T tv_get_bool(typval_T *varp)                    /* proto/typval.pro */
{ (void) varp; return 0; }

int not_in_vim9(exarg_T *eap)                               /* proto/vim9script.pro */
{ (void) eap; return OK; }

char_u *get_user_command_name(int idx, int cmdidx)          /* proto/usercmd.pro */
{ (void) idx; (void) cmdidx; return NULL; }

char_u *vim_strsave(char_u *string)                          /* proto/strings.pro */
{ (void) string; return NULL; }

/*
 * find_ex_command (src/ex_docmd.c) is a long (~150 line) linear/binary
 * lookup against the full real cmdnames[] table (elided above) plus
 * user-command matching -- none of that machinery is on this bug's crash
 * path (the crash is f_fullcommand's own *very first* dereference of
 * "name", strictly before find_ex_command is ever called). This is a
 * minimal faithful stub that always returns NULL, which is one of the real
 * function's two documented return values ("Returns NULL for an ambiguous
 * user command", per its own header comment) -- i.e. it is not inventing a
 * new behaviour, just always taking that one real branch. Consequently
 * f_fullcommand's own "if (p == NULL || ...) goto theend;" is always taken
 * for every safe (VAR_STRING) input, and the (dead) cmdnames[]/
 * get_user_command_name/not_in_vim9/vim_strsave lines below it are never
 * reached by anything this harness generates. */
char_u *
find_ex_command(
	exarg_T *eap,
	int	*full,
	int	(*lookup)(char_u *, size_t, int, cctx_T *),
	cctx_T	*cctx)
{
    (void) eap; (void) full; (void) lookup; (void) cctx;
    return NULL;
}

/*
 * skipwhite (src/charset.c, verbatim) -- tiny, real dependency of
 * skip_range() below.
 */
    char_u *
skipwhite(char_u *q)
{
    char_u	*p = q;

    while (VIM_ISWHITE(*p))
	++p;
    return p;
}

/*
 * vim_strchr (src/strings.c) -- the real implementation branches on global
 * multibyte encoding state (enc_utf8 / enc_dbcs / has_mbyte) that is
 * unrelated to this bug; skip_range() below only ever calls it with a
 * single-byte ASCII needle (CPO_STAR == '*'). This minimal faithful stub
 * implements the real function's documented contract ("search for first
 * occurrence of c in string") for that single-byte case -- it is exactly
 * the real function's own single-byte tail loop
 * ("while ((b = *p) != NUL) { if (b == c) return p; ... }"), just without
 * the preceding multibyte branches that never trigger for our ASCII needle.
 */
    char_u *
vim_strchr(char_u *string, int c)
{
    char_u	*p;

    for (p = string; *p != NUL; ++p)
	if (*p == (char_u) c)
	    return p;
    return NULL;
}

#define CPO_STAR    '*'                        /* option.h, verbatim */
char_u *p_cpo = (char_u *) "";                  /* globals.h real name
						  * 'cpoptions'; Vim's real
						  * compiled-in default is a
						  * short fixed letter set that
						  * (in every released version)
						  * does not include '*', so an
						  * empty string reproduces the
						  * same "CPO_STAR not present"
						  * outcome for skip_range()'s
						  * one use of it below,
						  * without pulling in the
						  * whole options.c default
						  * table. */

/*
 * skip_range (src/ex_docmd.c, verbatim) -- a real, small dependency of
 * f_fullcommand, included in full (not stubbed) since it is cheap and its
 * real behaviour is worth exercising on the safe corpus.
 */
    char_u *
skip_range(
    char_u	*cmd_start,
    int		skip_star,	// skip "*" used for Visual range
    int		*ctx)		// pointer to xp_context or NULL
{
    char_u	*cmd = cmd_start;
    unsigned	delim;

    while (vim_strchr((char_u *)" \t0123456789.$%'/?-+,;\\", *cmd) != NULL)
    {
	if (*cmd == '\\')
	{
	    if (cmd[1] == '?' || cmd[1] == '/' || cmd[1] == '&')
		++cmd;
	    else
		break;
	}
	else if (*cmd == '\'')
	{
	    char_u *p = cmd;

	    // a quote is only valid at the start or after a separator
	    while (p > cmd_start)
	    {
		--p;
		if (!VIM_ISWHITE(*p))
		    break;
	    }
	    if (cmd > cmd_start && !VIM_ISWHITE(*p) && *p != ',' && *p != ';')
		break;
	}
	else if (*cmd == '/' || *cmd == '?')
	{
	    delim = *cmd++;
	    while (*cmd != NUL && *cmd != delim)
		if (*cmd++ == '\\' && *cmd != NUL)
		    ++cmd;
	}
	if (*cmd != NUL)
	    ++cmd;
    }
    (void) ctx;

    // Skip ":" and white space.
    while (*cmd == ':')
	cmd = skipwhite(cmd + 1);

    // Skip "*" used for Visual range.
    if (skip_star && *cmd == '*' && vim_strchr(p_cpo, CPO_STAR) == NULL)
	cmd = skipwhite(cmd + 1);

    return cmd;
}

/* ============================================================
 * TARGET FUNCTION, embedded VERBATIM (byte-for-byte from
 * target/original_function.c): src/ex_docmd.c f_fullcommand()
 * ============================================================ */

void
f_fullcommand(typval_T *argvars, typval_T *rettv)
{
    exarg_T	ea;
    char_u	*name;
    char_u	*p;
    int		vim9script = in_vim9script();
    int		save_cmod_flags = cmdmod.cmod_flags;

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

    if (in_vim9script()
	    && (check_for_string_arg(argvars, 0) == FAIL
		|| check_for_opt_bool_arg(argvars, 1) == FAIL))
	return;

    name = argvars[0].vval.v_string;
    if (name == NULL)
	return;

    if (argvars[1].v_type != VAR_UNKNOWN)
    {
	vim9script = tv_get_bool(&argvars[1]);
	cmdmod.cmod_flags &= ~(CMOD_VIM9CMD | CMOD_LEGACY);
	cmdmod.cmod_flags |= vim9script ? CMOD_VIM9CMD : CMOD_LEGACY;
    }

    while (*name == ':')
	name++;
    name = skip_range(name, TRUE, NULL);

    ea.cmd = (*name == '2' || *name == '3') ? name + 1 : name;
    ea.cmdidx = (cmdidx_T)0;
    ea.addr_count = 0;
    ++emsg_silent;  // don't complain about using "en" in Vim9 script
    p = find_ex_command(&ea, NULL, NULL, NULL);
    --emsg_silent;
    if (p == NULL || ea.cmdidx == CMD_SIZE)
	goto theend;

    if (vim9script)
    {
	int	     res;

	++emsg_silent;
	res = not_in_vim9(&ea);
	--emsg_silent;

	if (res == FAIL)
	    goto theend;
    }

    rettv->vval.v_string = vim_strsave(IS_USER_CMDIDX(ea.cmdidx)
				 ? get_user_command_name(ea.useridx, ea.cmdidx)
				 : cmdnames[ea.cmdidx].cmd_name);
theend:
    cmdmod.cmod_flags = save_cmod_flags;
}

/* ============================================================
 * main() -- reads argv[1] into a HEAP buffer and calls f_fullcommand()
 * exactly once, with argvars[0] built as either a VAR_NUMBER (trigger) or
 * a VAR_STRING (safe) typval per the I/O contract described above.
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
	perror("fopen");
	return 1;
    }
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    if (fsz < 0)
	fsz = 0;
    fseek(f, 0, SEEK_SET);

    /* Attacker-controlled data MUST live on the heap so ASAN redzones bound
     * it. */
    size_t alloc_len = (size_t) fsz > 0 ? (size_t) fsz : 1;
    unsigned char *raw = (unsigned char *) malloc(alloc_len);
    if (!raw)
    {
	fclose(f);
	return 1;
    }
    size_t raw_len = fsz > 0 ? fread(raw, 1, (size_t) fsz, f) : 0;
    fclose(f);

    int trigger = (raw_len > 0) ? (raw[0] & 1) : 1;

    typval_T argvars[2];
    memset(argvars, 0, sizeof(argvars));
    argvars[1].v_type = VAR_UNKNOWN;   // fullcommand()'s optional 2nd arg
					// not exercised (not part of the bug)

    char_u *heap_name = NULL;

    if (trigger)
    {
	/* Derive a small, always-nonzero varnumber_T from the remaining
	 * bytes (bytes 1..4, big-endian fold) so different inputs pick
	 * different-but-still-guaranteed-unmapped low addresses -- any
	 * value < 65536 (Linux's default mmap_min_addr) is reliably never
	 * mapped into this process, so "*name" always SIGSEGVs. */
	unsigned long v = 0;
	for (size_t i = 1; i < raw_len && i < 5; i++)
	    v = (v << 8) | raw[i];
	varnumber_T num = (varnumber_T) (1 + (v % 65535));

	argvars[0].v_type = VAR_NUMBER;
	argvars[0].vval.v_number = num;
    }
    else
    {
	/* A real string typval: heap copy of byte[1..], NUL terminated.
	 * Embedded NULs just truncate the C string early -- still fully
	 * in-bounds. */
	size_t namelen = raw_len > 0 ? raw_len - 1 : 0;
	heap_name = (char_u *) malloc(namelen + 1);
	if (!heap_name)
	{
	    free(raw);
	    return 1;
	}
	if (namelen > 0)
	    memcpy(heap_name, raw + 1, namelen);
	heap_name[namelen] = NUL;

	argvars[0].v_type = VAR_STRING;
	argvars[0].vval.v_string = heap_name;
    }

    free(raw);

    typval_T rettv;
    memset(&rettv, 0, sizeof(rettv));

    f_fullcommand(argvars, &rettv);

    fprintf(stderr, "f_fullcommand: trigger=%d rettv.v_type=%d rettv.v_string=%s\n",
	    trigger, rettv.v_type,
	    rettv.vval.v_string ? (char *) rettv.vval.v_string : "(null)");

    free(heap_name);
    return 0;
}
