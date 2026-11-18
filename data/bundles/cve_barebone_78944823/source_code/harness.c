/*
 * cve_78944823 - haproxy sample_conv_regsub() - CWE-787 heap-buffer-overflow WRITE
 *
 * Direct-call ASAN harness. Isolates sample_conv_regsub() (src/sample.c) and drives
 * it with attacker-controlled "subject" bytes (the sample string / e.g. an HTTP
 * header value run through a `regsub()` converter). The regex pattern and the
 * replacement text are fixed operator-configured values (as in a real deployment,
 * where `http-request ... regsub(<match>,<fmt>)` is set in haproxy.cfg and only the
 * traffic content feeding the sample is attacker-controlled) - only the subject is
 * varied across the corpus.
 *
 * Root cause (fixed by commit 3e3b9eebf871510aee36c3a3336faac2f38c9559):
 *   After building the replacement text into a freshly allocated trash chunk
 *   `output`, sample_conv_regsub() computed the copy-length bound against
 *   `output`'s OWN remaining capacity instead of the DESTINATION `trash` buffer's
 *   remaining capacity:
 *       max = output->size - output->data;      // buggy (this file's version)
 *       ...                                       // fix replaces this line with:
 *       max = trash->size - trash->data;         // correct bound
 *   memcpy(trash->area + trash->data, output->area, max) then writes past the end
 *   of `trash` whenever the replacement text is longer than what is actually left
 *   in `trash` (regardless of how much spare capacity `output` itself has left) ->
 *   heap-buffer-overflow WRITE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

/* ---------------------------------------------------------------------------
 * Real HAProxy type/macro definitions, trimmed to exactly what
 * sample_conv_regsub() touches (real names, real semantics).
 * --------------------------------------------------------------------------- */

#define MAX_MATCH      10   /* include/haproxy/defaults.h */
#define ARGF_REG_GLOB  2    /* include/haproxy/arg-t.h    */

/* include/haproxy/buf-t.h */
struct buffer {
	size_t size;                /* buffer size in bytes */
	char  *area;                /* points to <size> bytes */
	size_t data;                /* amount of data after head including wrapping */
	size_t head;                /* start offset of remaining data relative to area */
};

/* include/haproxy/regex-t.h, non-PCRE build variant (plain POSIX regex_t) */
struct my_regex {
	regex_t regex;
};

/* include/haproxy/sample_data-t.h, trimmed union: only the member this
 * function reads (`str`) is kept. */
union sample_value {
	struct buffer str;   /* used for char strings or buffers */
};
struct sample_data {
	int type;                 /* SMP_T_* */
	union sample_value u;     /* sample data */
};

/* include/haproxy/sample-t.h, trimmed: sample_conv_regsub only reads .data */
struct sample {
	struct sample_data data;
};

/* include/haproxy/arg-t.h, trimmed union: only the members this function
 * reads (`reg`, `str`) are kept. */
union arg_data {
	struct my_regex *reg;
	struct buffer str;
};
struct arg {
	unsigned char type_flags; /* type-specific extra flags (eg: case sensitivity for regex), ARGF_* */
	union arg_data data;      /* argument data */
};

/* ---------------------------------------------------------------------------
 * Real callees on the crash path, copied VERBATIM from source_code/src/regex.c
 * (regex_exec_match2's plain-POSIX / non-PCRE branch, since this harness links
 * only against libc/libm - no PCRE dependency).
 * --------------------------------------------------------------------------- */

/* verbatim from src/regex.c (#else branch: no USE_PCRE/USE_PCRE2) */
int regex_exec_match2(const struct my_regex *preg, char *subject, int length,
                      size_t nmatch, regmatch_t pmatch[], int flags) {
	char old_char = subject[length];
	int match;

	flags &= REG_NOTBOL;
	subject[length] = 0;
	match = regexec(&preg->regex, subject, nmatch, pmatch, flags);
	subject[length] = old_char;
	if (match == REG_NOMATCH)
		return 0;
	return 1;
}

/* verbatim from src/regex.c */
int exp_replace(char *dst, unsigned int dst_size, char *src, const char *str, const regmatch_t *matches)
{
	char *old_dst = dst;
	char* dst_end = dst + dst_size;

	while (*str) {
		if (*str == '\\') {
			str++;
			if (!*str)
				return -1;

			if (isdigit((unsigned char)*str)) {
				int len, num;

				num = *str - '0';
				str++;

				if (matches[num].rm_eo > -1 && matches[num].rm_so > -1) {
					len = matches[num].rm_eo - matches[num].rm_so;

					if (dst + len >= dst_end)
						return -1;

					memcpy(dst, src + matches[num].rm_so, len);
					dst += len;
				}

			} else if (*str == 'x') {
				unsigned char hex1, hex2;
				str++;

				if (!*str)
					return -1;

				hex1 = toupper((unsigned char)*str++) - '0';

				if (!*str)
					return -1;

				hex2 = toupper((unsigned char)*str++) - '0';

				if (hex1 > 9) hex1 -= 'A' - '9' - 1;
				if (hex2 > 9) hex2 -= 'A' - '9' - 1;

				if (dst >= dst_end)
					return -1;

				*dst++ = (hex1<<4) + hex2;
			} else {
				if (dst >= dst_end)
					return -1;

				*dst++ = *str++;
			}
		} else {
			if (dst >= dst_end)
				return -1;

			*dst++ = *str++;
		}
	}
	if (dst >= dst_end)
		return -1;

	*dst = '\0';
	return dst - old_dst;
}

/* ---------------------------------------------------------------------------
 * Minimal faithful stubs for the trash-chunk allocator (incidental machinery:
 * real HAProxy backs get_trash_chunk()/alloc_trash_chunk() with a per-thread
 * pool of buffers sized `global.tune.bufsize` (operator-tunable, default
 * 16384). sample_conv_regsub()'s logic only depends on each call handing back
 * a struct buffer with a fixed capacity and data=0, which a plain heap
 * allocation reproduces faithfully; CHUNK_SIZE stands in for a small
 * tune.bufsize so ASAN observes the overflow deterministically.
 * --------------------------------------------------------------------------- */

#define CHUNK_SIZE 64

static struct buffer *chunk_new(void)
{
	struct buffer *b = malloc(sizeof(*b));
	if (!b)
		return NULL;
	b->area = malloc(CHUNK_SIZE);
	if (!b->area) {
		free(b);
		return NULL;
	}
	b->size = CHUNK_SIZE;
	b->data = 0;
	b->head = 0;
	return b;
}

struct buffer *get_trash_chunk(void)
{
	return chunk_new();
}

struct buffer *alloc_trash_chunk(void)
{
	return chunk_new();
}

void free_trash_chunk(struct buffer *chunk)
{
	if (!chunk)
		return;
	free(chunk->area);
	free(chunk);
}

/* =====================================================================
 * TARGET FUNCTION - byte-identical to
 * data_cve/cve_78944823/target/original_function.c
 * ===================================================================== */

static int sample_conv_regsub(const struct arg *arg_p, struct sample *smp, void *private)
{
	char *start, *end;
	struct my_regex *reg = arg_p[0].data.reg;
	regmatch_t pmatch[MAX_MATCH];
	struct buffer *trash = get_trash_chunk();
	struct buffer *output;
	int flag, max;
	int found;

	start = smp->data.u.str.area;
	end = start + smp->data.u.str.data;

	flag = 0;
	while (1) {
		/* check for last round which is used to copy remaining parts
		 * when not running in global replacement mode.
		 */
		found = 0;
		if ((arg_p[0].type_flags & ARGF_REG_GLOB) || !(flag & REG_NOTBOL)) {
			/* Note: we can have start == end on empty strings or at the end */
			found = regex_exec_match2(reg, start, end - start, MAX_MATCH, pmatch, flag);
		}

		if (!found)
			pmatch[0].rm_so = end - start;

		/* copy the heading non-matching part (which may also be the tail if nothing matches) */
		max = trash->size - trash->data;
		if (max && pmatch[0].rm_so > 0) {
			if (max > pmatch[0].rm_so)
				max = pmatch[0].rm_so;
			memcpy(trash->area + trash->data, start, max);
			trash->data += max;
		}

		if (!found)
			break;

		output = alloc_trash_chunk();
		if (!output)
			break;

		output->data = exp_replace(output->area, output->size, start, arg_p[1].data.str.area, pmatch);

		/* replace the matching part */
		max = output->size - output->data;
		if (max) {
			if (max > output->data)
				max = output->data;
			memcpy(trash->area + trash->data,
			       output->area, max);
			trash->data += max;
		}

		free_trash_chunk(output);

		/* stop here if we're done with this string */
		if (start >= end)
			break;

		/* We have a special case for matches of length 0 (eg: "x*y*").
		 * These ones are considered to match in front of a character,
		 * so we have to copy that character and skip to the next one.
		 */
		if (!pmatch[0].rm_eo) {
			if (trash->data < trash->size)
				trash->area[trash->data++] = start[pmatch[0].rm_eo];
			pmatch[0].rm_eo++;
		}

		start += pmatch[0].rm_eo;
		flag |= REG_NOTBOL;
	}

	smp->data.u.str = *trash;
	return 1;
}

/* =====================================================================
 * Driver
 * ===================================================================== */

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <inputfile>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	fseek(f, 0, SEEK_END);
	long fsz = ftell(f);
	if (fsz < 0)
		fsz = 0;
	fseek(f, 0, SEEK_SET);

	/* regex_exec_match2() temporarily NUL-terminates at subject[length]; the
	 * sample string buffer therefore needs >=1 spare writable byte past its
	 * declared length, matching the real precondition ("the <subject> must
	 * have a real length of <length> + 1") and how real HAProxy chunks are
	 * always allocated with slack past their .data length. */
	size_t buflen = (size_t)fsz;
	char *area = malloc(buflen + 1);
	if (!area) {
		fclose(f);
		return 1;
	}
	if (buflen && fread(area, 1, buflen, f) != buflen) {
		fclose(f);
		free(area);
		return 1;
	}
	area[buflen] = '\0';
	fclose(f);

	/* fixed operator-configured regex, e.g. haproxy.cfg:
	 *   http-request replace-value X ^.*$ %[req.hdr(X),regsub(Z,REPLACEMENT_TEXT_OVERFLOW)]
	 * ARGF_REG_GLOB is left unset (no trailing "g" flag) -> single-shot
	 * substitution, matching regsub()'s real non-global default. */
	struct my_regex reg;
	if (regcomp(&reg.regex, "Z", REG_EXTENDED) != 0) {
		free(area);
		return 1;
	}

	static const char replacement[] = "REPLACEMENT_TEXT_OVERFLOW"; /* 25 literal chars, no backrefs */

	struct arg arg_p[2];
	memset(arg_p, 0, sizeof(arg_p));
	arg_p[0].type_flags = 0;   /* no ARGF_REG_GLOB */
	arg_p[0].data.reg = &reg;
	arg_p[1].data.str.area = (char *)replacement;
	arg_p[1].data.str.size = sizeof(replacement) - 1;
	arg_p[1].data.str.data = sizeof(replacement) - 1;

	struct sample smp;
	memset(&smp, 0, sizeof(smp));
	smp.data.u.str.area = area;
	smp.data.u.str.size = buflen;
	smp.data.u.str.data = buflen;

	int rc = sample_conv_regsub(arg_p, &smp, NULL);
	fprintf(stderr, "sample_conv_regsub rc=%d out_len=%zu\n", rc, smp.data.u.str.data);

	regfree(&reg.regex);
	free(area);
	/* smp.data.u.str.area now points at the (possibly leaked) trash chunk
	 * returned by get_trash_chunk() - fine for a single-shot harness. */
	return 0;
}
