/* Direct-call crash harness for file(1) do_bid_note (CVE-2017-1000249, CWE-787).
 *
 * do_bid_note(...) is called (from donote(), src/readelf.c:1090-1093) once
 * per ELF PT_NOTE entry, before the OS/core-note dispatch. When the note's
 * name is "GNU" (namesz==4) and type==NT_GNU_BUILD_ID it does:
 *
 *     uint8_t desc[20];                      // fixed-size STACK buffer, 20 bytes
 *     ...
 *     (void)memcpy(desc, &nbuf[doff], descsz);   // <-- src/readelf.c:527, THE BUG
 *
 * `descsz` is the attacker-controlled ELF note descriptor-size field, and the
 * guard that looks like a bound check --
 *     (descsz >= 4 || descsz <= 20)
 * -- is a tautology (every uint32_t is either >=4 or <=20, generally both),
 * so it never actually rejects anything. descsz is copied into the memcpy
 * with NO real check against sizeof(desc)==20 -- confirmed against
 * case.json's baseline (dedup_token "__asan_memcpy--do_bid_note--donote",
 * bug_class "stack-buffer-overflow", access "WRITE") and VALIDATION.md
 * (both Ghidra and IDA/Hex-Rays keep the unbounded memcpy into desc[20]
 * verbatim). Bug: descsz > sizeof(desc) (20 bytes) -> the memcpy WRITES
 * past the end of the stack-local `desc` -- a stack-buffer-overflow WRITE
 * (CWE-787).
 *
 * This harness embeds do_bid_note() VERBATIM (target/original_function.c,
 * byte-identical logic/names/signature/body) and calls it DIRECTLY from
 * main(), with NO dependency on donote()/the rest of file(1). The source
 * side of the memcpy (nbuf+doff, on the HEAP) is always sized to hold
 * EXACTLY `descsz` real bytes, so the source read is always in-bounds --
 * the ONLY thing that can fault is the fixed-size stack destination
 * `desc`, isolating the CWE-787 WRITE this bundle targets (as opposed to
 * any confounding heap-buffer-overflow READ).
 *
 * Input format: the entire raw input file becomes the note's descriptor
 * payload; the file's OWN LENGTH is used directly as `descsz`. main()
 * builds nbuf on the HEAP as "GNU\0" (4 bytes, zero-padded to a fixed
 * 16-byte doff) ++ <raw file bytes>, and calls
 * do_bid_note(ms=NULL, nbuf, type=NT_GNU_BUILD_ID, swap=0, namesz=4,
 * descsz=<file length>, noff=0, doff=16, &flags=0) ONCE.
 *   - file length > sizeof(desc) (20 bytes)
 *     -> the memcpy overflows `desc` -> stack-buffer-overflow WRITE (CWE-787).
 *   - file length <= 20 -> the memcpy stays within `desc` -> clean.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* ---- minimal REAL type/macro defs, real names, from src/file.h and
 * src/readelf.h ---- */

struct magic_set;   /* opaque: do_bid_note only ever passes `ms` THROUGH to
                      * file_printf(); it never reads or writes any field of
                      * struct magic_set itself. */

/* protected int file_printf(struct magic_set *, const char *, ...) (file.h:448).
 * Real file_printf formats into ms->o's growable output buffer; do_bid_note
 * only ever relies on its RETURN VALUE (-1 == out of memory -> bail, else
 * continue) -- never on any side effect on `ms` -- so a stub that always
 * succeeds (and echoes to stderr for visibility) is faithful to every
 * control-flow path through do_bid_note. */
static int
file_printf(struct magic_set *ms, const char *fmt, ...)
{
	(void)ms;
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
	return 0;
}

/* real macros do_bid_note's body uses, from src/readelf.h (verified via
 * grep: FLAGS_DID_BUILD_ID at readelf.h:317, NT_GNU_BUILD_ID at
 * readelf.h:319). */
#define FLAGS_DID_BUILD_ID		0x010
#define NT_GNU_BUILD_ID			3

/* ---- verbatim target function (dataset/cvf_d1901b12/target/original_function.c,
 * byte-for-byte name/params/body). Upstream src/readelf.c:508 prefixes this
 * with the project's internal-linkage macro `private` (`#define private
 * static`, file.h:88) -- replaced here with plain `static` +
 * `__attribute__((noinline))` (so it keeps its own frame in the ASAN
 * backtrace under -O1, matching target/meta.json's empty return_type, i.e.
 * only the storage-class/linkage prefix was ever stripped by the
 * extraction, never the body); return type/name/params/body are otherwise
 * byte-identical. ---- */
__attribute__((noinline))
static int
do_bid_note(struct magic_set *ms, unsigned char *nbuf, uint32_t type,
    int swap __attribute__((__unused__)), uint32_t namesz, uint32_t descsz,
    size_t noff, size_t doff, int *flags)
{
	if (namesz == 4 && strcmp((char *)&nbuf[noff], "GNU") == 0 &&
	    type == NT_GNU_BUILD_ID && (descsz >= 4 || descsz <= 20)) {
		uint8_t desc[20];
		const char *btype;
		uint32_t i;
		*flags |= FLAGS_DID_BUILD_ID;
		switch (descsz) {
		case 8:
		    btype = "xxHash";
		    break;
		case 16:
		    btype = "md5/uuid";
		    break;
		case 20:
		    btype = "sha1";
		    break;
		default:
		    btype = "unknown";
		    break;
		}
		if (file_printf(ms, ", BuildID[%s]=", btype) == -1)
			return 1;
		(void)memcpy(desc, &nbuf[doff], descsz);
		for (i = 0; i < descsz; i++)
		    if (file_printf(ms, "%02x", desc[i]) == -1)
			return 1;
		return 1;
	}
	return 0;
}
/* ---- end verbatim target function ---- */

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 64;
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 64; }
	if (fseek(fp, 0, SEEK_END) != 0) { perror("fseek"); fclose(fp); return 64; }
	long flen = ftell(fp);
	if (flen < 0) { perror("ftell"); fclose(fp); return 64; }
	rewind(fp);

	/*
	 * Fixed note-header metadata that routes do_bid_note() into the
	 * vulnerable branch (src/readelf.c:513-514) -- the ONLY attacker
	 * surface left is the raw file bytes, which become the note's
	 * descriptor payload directly:
	 *
	 *   namesz = 4, nbuf[0..4) = "GNU\0"
	 *            -> (namesz==4 && strcmp(&nbuf[noff],"GNU")==0) fires.
	 *   type   = NT_GNU_BUILD_ID -> enters the vulnerable branch.
	 *   doff   = 16 (fixed, byte-aligned padding after the 4-byte name;
	 *            arbitrary but fixed -- real ELF note layout also pads
	 *            name to a word boundary before the descriptor begins).
	 *   descsz = the raw input file's OWN LENGTH.
	 *
	 * nbuf is malloc'd to EXACTLY doff+descsz bytes, so
	 * `nbuf+doff .. nbuf+doff+descsz` (the memcpy's SOURCE range) is
	 * always fully in-bounds: the only thing that can fault is the
	 * memcpy's fixed-size stack DESTINATION `desc` (sizeof == 20 bytes)
	 * -- isolating the CWE-787 stack-buffer-overflow WRITE this bundle
	 * targets from any confounding heap-side READ.
	 *
	 * So: file length > 20 -> memcpy(desc, nbuf+doff, descsz) overflows
	 * `desc` -> stack-buffer-overflow WRITE, do_bid_note on the crashing
	 * stack (CWE-787). File length <= 20 -> the copy stays inside `desc`
	 * -> do_bid_note runs to completion and returns cleanly.
	 */
	size_t descsz = (size_t)flen;
	size_t doff = 16;
	size_t total = doff + descsz;

	unsigned char *nbuf = (unsigned char *)malloc(total > 0 ? total : 1);
	if (!nbuf) { perror("malloc"); fclose(fp); return 64; }
	memset(nbuf, 0, doff);
	memcpy(nbuf, "GNU", 3); /* nbuf[3] stays '\0' from the memset -> "GNU\0" */
	if (descsz > 0) {
		size_t got = fread(nbuf + doff, 1, descsz, fp);
		if (got != descsz) {
			fprintf(stderr, "short read\n");
			fclose(fp);
			free(nbuf);
			return 64;
		}
	}
	fclose(fp);

	struct magic_set *ms = NULL; /* opaque; do_bid_note never dereferences it */
	int flags = 0;

	int rc = do_bid_note(ms, nbuf, (uint32_t)NT_GNU_BUILD_ID,
	    /*swap=*/0, /*namesz=*/4, (uint32_t)descsz, /*noff=*/0, doff,
	    &flags);
	printf("do_bid_note flen=%ld descsz=%zu rc=%d flags=0x%x\n",
	    flen, descsz, rc, flags);

	free(nbuf);
	return 0;
}
