/*
 * Direct-call crash harness for cve_2b123e9d (CVE-2021-30218, samurai util.c,
 * writefile()). Embeds the vulnerable function VERBATIM and calls it directly
 * with a heap-allocated `struct string *` built from argv[1], so ASan catches
 * the exact NULL-pointer dereference this CVE describes, with no dependency
 * on the rest of samurai (build.c/env.c/parse.c).
 *
 * Bug recap (matches baseline dedup_token "writefile--jobstart--build" /
 * summary "AddressSanitizer: SEGV /work/util.c:261:25 in writefile"): in the
 * real project, build.c:jobstart() does
 *     rspfile = edgevar(e, "rspfile", false);
 *     if (rspfile) {
 *         content = edgevar(e, "rspfile_content", true);
 *         if (writefile(rspfile->s, content) < 0)
 *             goto err0;
 *     }
 * `edgevar(e, "rspfile_content", true)` returns NULL whenever the ninja rule
 * defines an `rspfile` variable but never defines (or inherits) an
 * `rspfile_content` variable. writefile() is then called with `s == NULL`
 * and, with NO NULL check, evaluates
 *     fwrite(s->s, 1, s->n, f) != s->n
 * which dereferences `s->n` at address 0 -> SIGSEGV, inside writefile()
 * itself (original_function.c line 13 / source util.c:261, matching the
 * frozen baseline exactly). The fault is entirely local to writefile(): it
 * needs no other samurai machinery, only a NULL `struct string *`.
 *
 * `original_function.c` is embedded byte-for-byte below (see the VERBATIM
 * markers) -- logic, names, and signature untouched.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* ---- minimal, faithful subset of util.h: the exact struct writefile()
 * dereferences, real name/layout, nothing else pulled in. ---- */
struct string {
	size_t n;
	char s[];
};

/* real global referenced by warn()/vwarn() (util.c, declared `extern` there,
 * defined in samu.c) */
const char *argv0 = "samu";

/* ---- util.c verbatim: vwarn/warn, the only callees writefile() makes (on
 * its error paths -- not hit by either the trigger or the safe path here,
 * but real callees so they are embedded verbatim rather than stubbed). ---- */
static void
vwarn(const char *fmt, va_list ap)
{
	fprintf(stderr, "%s: ", argv0);
	vfprintf(stderr, fmt, ap);
	if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
		putc(' ', stderr);
		perror(NULL);
	} else {
		putc('\n', stderr);
	}
}

void
warn(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vwarn(fmt, ap);
	va_end(ap);
}

/* ---- target function, embedded VERBATIM from target/original_function.c ---- */
int
writefile(const char *name, struct string *s)
{
	FILE *f;
	int ret;

	f = fopen(name, "w");
	if (!f) {
		warn("open %s:", name);
		return -1;
	}
	ret = 0;
	if (fwrite(s->s, 1, s->n, f) != s->n || fflush(f) != 0) {
		warn("write %s:", name);
		ret = -1;
	}
	fclose(f);

	return ret;
}
/* ---- end verbatim ---- */

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long len = ftell(f);
	if (len < 0) { fclose(f); return 1; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* REQUIRED: heap buffer for the attacker-controlled bytes, so any
	 * later use of them is via a heap allocation ASan tracks. */
	unsigned char *buf = NULL;
	if (len > 0) {
		buf = malloc((size_t)len);
		if (!buf) { fclose(f); return 1; }
		size_t rd = fread(buf, 1, (size_t)len, f);
		fclose(f);
		if (rd != (size_t)len) { free(buf); return 1; }
	} else {
		fclose(f);
	}

	/* writefile()'s first argument is just a writable path -- it plays no
	 * role in the CVE (the bug is entirely in the second argument), so a
	 * fixed scratch path is faithful to the real call site. */
	const char *outpath = "/tmp/vb_dc_writefile_out";

	/*
	 * Harness-only convention (there is no such marker in the real
	 * ninja/samurai wire format -- direct-call harnesses necessarily
	 * invent SOME mapping from "a corpus file" to "the argument(s) the
	 * target function actually takes"): a NON-EMPTY input whose FIRST
	 * byte is 0x00 selects the crash path, reproducing content==NULL
	 * exactly as edgevar() would produce it for a rule with `rspfile`
	 * but no `rspfile_content`. Because the CVE-2021-30218 crash depends
	 * ONLY on the pointer being NULL (writefile() faults on s->n before
	 * it ever looks at *any* byte of *s), whatever bytes follow the 0x00
	 * marker are irrelevant to the outcome -- they exist purely to give
	 * the corpus files length/byte-pattern variety, mirroring how in the
	 * real bug the crash is independent of the ninja file's other
	 * content once the vulnerable rule shape is present.
	 *
	 * Any OTHER input (including the empty file) builds a real, valid
	 * heap struct string from the file's bytes and writefile() succeeds
	 * (the safe / non-null path, matching a rule that DOES define
	 * rspfile_content).
	 */
	struct string *sp = NULL;
	if (!(len > 0 && buf[0] == 0x00)) {
		size_t n = (len > 0) ? (size_t)len : 0;
		sp = malloc(sizeof(*sp) + n);
		if (!sp) { free(buf); return 1; }
		sp->n = n;
		if (n) memcpy(sp->s, buf, n);
	}

	int r = writefile(outpath, sp);
	printf("writefile returned %d (inlen=%ld, s=%p)\n", r, len, (void *)sp);

	free(sp);
	free(buf);
	remove(outpath);
	return 0;
}
