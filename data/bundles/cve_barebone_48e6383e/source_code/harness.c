/* cve_barebone direct-call harness for vim's get_number() integer-overflow bug
 * (CVE-2023-48236, fixed by vim/vim@73b2d3790cad5694fc0ed0db2926e4220c48d968).
 * Target: get_number  (src/misc1.c)
 * Bug class: signed-integer-overflow (CWE-190) at `n = n * 10 + c - '0';`
 *   get_number() accumulates a decimal count one keystroke at a time into a
 *   plain `int`, with no overflow guard. Typing enough digits (the upstream
 *   regression test is `0z=337203685477580`, i.e. >=10 digits at the "z="
 *   count prompt) makes `n * 10 + c - '0'` overflow a 32-bit signed int ->
 *   undefined behaviour, trapped here by UBSan's signed-integer-overflow
 *   check. The fix adds `if (n > INT_MAX / 10) return 0;` before the multiply.
 *
 * get_number's own body performs no memory access beyond this arithmetic and
 * the char <-> key-code comparisons; its only "input" is safe_vgetc(), which
 * in real vim pulls the next key from the terminal/typeahead queue. That
 * whole event-loop/typeahead machinery is out of scope for a direct-call
 * harness, so safe_vgetc() here is a faithful stand-in that returns the next
 * byte of the attacker-controlled input file -- exactly what a user's
 * keystrokes are, one byte per digit typed -- and CAR (as if Enter were hit)
 * once the input is exhausted. This mirrors the real "type digits, overflow"
 * exploit path verbatim (single-byte ASCII keystrokes; termcap decoding into
 * the multi-byte K_SPECIAL codes is out of scope and untouched by the bug).
 * windgoto/msg_putchar/msg_puts/stuffcharReadbuff are cursor/echo/stuff-
 * buffer side effects that do not touch `n`; they are faithful no-op stubs
 * (real prototypes, from src/proto/{screen,message,getchar}.pro).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 *   + harness.flags: -fsanitize=signed-integer-overflow -fno-sanitize-recover=signed-integer-overflow
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- real vim constants, verbatim from src/ascii.h / src/vim.h / src/macros.h / src/keymap.h ---- */
#define NL		'\012'			/* src/ascii.h */
#define CAR		'\015'			/* src/ascii.h: CR is used by Mac OS X */
#define ESC		'\033'			/* src/ascii.h */
#define Ctrl_C		3			/* src/ascii.h */
#define Ctrl_H		8			/* src/ascii.h */

#ifndef TRUE
# define FALSE	0				/* src/vim.h: note: this is an int, not a long! */
# define TRUE	1
#endif

#define VIM_ISDIGIT(c) ((unsigned)(c) - '0' < 10)	/* src/macros.h */

#define KS_EXTRA		253		/* src/keymap.h */
#define TERMCAP2KEY(a, b)	(-((a) + ((int)(b) << 8)))	/* src/keymap.h */
#define K_BS		TERMCAP2KEY('k', 'b')		/* src/keymap.h */
#define K_DEL		TERMCAP2KEY('k', 'D')		/* src/keymap.h */
#define KE_KDEL		80				/* src/keymap.h: keypad Delete key */
#define K_KDEL		TERMCAP2KEY(KS_EXTRA, KE_KDEL)	/* src/keymap.h */
#define KE_LEFTMOUSE	44				/* src/keymap.h: Left mouse button click */
#define K_LEFTMOUSE	TERMCAP2KEY(KS_EXTRA, KE_LEFTMOUSE)	/* src/keymap.h */

/* ---- real vim globals get_number reads/writes verbatim (src/globals.h, EXTERN ... INIT(...)) ---- */
int	msg_silent = 0;		/* src/globals.h: don't print messages */
int	no_mapping = FALSE;	/* src/globals.h: currently no mapping allowed */
int	allow_keys = FALSE;	/* src/globals.h: allow key codes when no_mapping */
int	msg_row = 0;		/* src/globals.h */
int	msg_col = 0;		/* src/globals.h */
int	exmode_active = 0;	/* src/globals.h: zero, EXMODE_NORMAL or EXMODE_VIM */
int	cmdline_row = 0;	/* src/globals.h */
int	skip_redraw = FALSE;	/* src/globals.h: skip redraw once */
int	do_redraw = FALSE;	/* src/globals.h: extra redraw once */
int	mouse_row = 0;		/* src/globals.h */

/* ---- attacker-controlled input feed for the safe_vgetc() stand-in below ---- */
static unsigned char *g_buf;
static size_t g_len;
static size_t g_pos;

/* ---- faithful minimal stubs for the incidental (non-overflow-path) callees ----
 * Real prototypes (src/proto/screen.pro, src/proto/message.pro, src/proto/getchar.pro):
 *   void windgoto(int row, int col);
 *   void msg_putchar(int c);
 *   void msg_puts(char *s);
 *   void stuffcharReadbuff(int c);
 * None of these feed back into `n` -- they only move the cursor, echo the
 * typed character, or push a character onto the stuff-buffer for later
 * replay -- so no-op bodies are faithful to the overflow path. */
void
windgoto(int row, int col)
{
    (void)row; (void)col;
}

void
msg_putchar(int c)
{
    (void)c;
}

void
msg_puts(char *s)
{
    (void)s;
}

void
stuffcharReadbuff(int c)
{
    (void)c;
}

/* safe_vgetc(): get_number's ONLY source of input. Real safe_vgetc() (src/getchar.c)
 * calls vgetc()/get_keystroke() to pull the next key from vim's terminal/typeahead
 * queue. Here it hands back the next byte of the attacker-controlled input file --
 * the direct-call analogue of "the user's next keystroke" -- and CAR (as if Enter
 * were hit) once the file is exhausted, so the loop always terminates instead of
 * reading past the buffer or spinning. */
int
safe_vgetc(void)
{
    if (g_pos >= g_len)
	return CAR;
    return (int)g_buf[g_pos++];
}

/* ==== VERBATIM from data_cve/cve_48e6383e/target/original_function.c ==== */
int
get_number(
    int	    colon,			// allow colon to abort
    int	    *mouse_used)
{
    int	n = 0;
    int	c;
    int typed = 0;

    if (mouse_used != NULL)
	*mouse_used = FALSE;

    // When not printing messages, the user won't know what to type, return a
    // zero (as if CR was hit).
    if (msg_silent != 0)
	return 0;

#ifdef USE_ON_FLY_SCROLL
    dont_scroll = TRUE;		// disallow scrolling here
#endif
    ++no_mapping;
    ++allow_keys;		// no mapping here, but recognize keys
    for (;;)
    {
	windgoto(msg_row, msg_col);
	c = safe_vgetc();
	if (VIM_ISDIGIT(c))
	{
	    n = n * 10 + c - '0';
	    msg_putchar(c);
	    ++typed;
	}
	else if (c == K_DEL || c == K_KDEL || c == K_BS || c == Ctrl_H)
	{
	    if (typed > 0)
	    {
		msg_puts("\b \b");
		--typed;
	    }
	    n /= 10;
	}
	else if (mouse_used != NULL && c == K_LEFTMOUSE)
	{
	    *mouse_used = TRUE;
	    n = mouse_row + 1;
	    break;
	}
	else if (n == 0 && c == ':' && colon)
	{
	    stuffcharReadbuff(':');
	    if (!exmode_active)
		cmdline_row = msg_row;
	    skip_redraw = TRUE;	    // skip redraw once
	    do_redraw = FALSE;
	    break;
	}
	else if (c == Ctrl_C || c == ESC || c == 'q')
	{
	    n = 0;
	    break;
	}
	else if (c == CAR || c == NL )
	    break;
    }
    --no_mapping;
    --allow_keys;
    return n;
}

/* ==== end verbatim ==== */

int
main(int argc, char **argv)
{
    unsigned char *buf;
    size_t cap, n;
    long sz;
    FILE *f;
    int mouse_used;
    int r;

    if (argc < 2)
	return 0;
    f = fopen(argv[1], "rb");
    if (!f)
	return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    sz = ftell(f);
    if (sz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the input so ASAN guards it. At least 1 byte so malloc(0)
     * is never taken. */
    cap = (size_t)sz > 0 ? (size_t)sz : 1;
    buf = (unsigned char *)malloc(cap);
    if (!buf) { fclose(f); return 0; }
    n = fread(buf, 1, (size_t)sz, f);
    fclose(f);

    g_buf = buf;
    g_len = n;
    g_pos = 0;

    mouse_used = 0;
    r = get_number(/* colon = */ 1, &mouse_used);

    free(buf);

    fprintf(stderr, "ok n=%d mouse_used=%d consumed=%zu/%zu\n", r, mouse_used, g_pos, g_len);
    return 0;
}
