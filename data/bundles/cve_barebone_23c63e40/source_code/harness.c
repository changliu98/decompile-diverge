/*
 * Direct-call crash harness for dataset/cve_23c63e40 (CVE-2018-14879, tcpdump,
 * tcpdump.c, function get_next_file).
 *
 * Root cause (matches baseline dedup_token "get_next_file--main--" and
 * baseline.summary "AddressSanitizer: stack-buffer-overflow tcpdump.c:707:6
 * in get_next_file", access=READ, cwe=CWE-125):
 *
 *   ret = fgets(ptr, PATH_MAX, VFile);
 *   if (!ret)
 *       return NULL;
 *   if (ptr[strlen(ptr) - 1] == '\n')      // <-- OOB READ
 *       ptr[strlen(ptr) - 1] = '\0';
 *
 * fgets() null-terminates the bytes it copies, but does NOT stop at an
 * embedded NUL byte -- it stops only at '\n', EOF, or n-1 bytes copied. If
 * the very FIRST byte read from VFile is 0x00, fgets() still copies
 * whatever follows (up to the next '\n'/EOF/limit) into ptr, but because
 * ptr[0] == '\0', strlen(ptr) == 0 regardless of what comes after. strlen()
 * returns size_t (unsigned), so `strlen(ptr) - 1` underflows to SIZE_MAX,
 * and `ptr[SIZE_MAX]` is, under normal two's-complement pointer arithmetic,
 * the very same byte as `ptr[-1]` -- a 1-byte READ immediately BEFORE the
 * destination buffer. This is the well-known "-V file whose first line
 * starts with an embedded NUL byte" bug, CVE-2018-14879.
 *
 * Real caller (tcpdump.c): `char VFileLine[PATH_MAX + 1];` is a plain
 * caller-owned line buffer; `ret = get_next_file(VFile, VFileLine);` is
 * called repeatedly to walk a `-V`-supplied text file of pcap filenames
 * (one per line). VFile itself is a plain fopen()'d byte stream.
 *
 * main() reads argv[1] into a HEAP buffer (malloc), backs the FILE *VFile
 * with an fmemopen() stream over that heap buffer (mirroring the real
 * VFile's plain-byte-stream semantics, just sourced from memory instead of
 * disk), and allocates the destination `ptr` buffer on the HEAP too
 * (malloc(PATH_MAX + 1), mirroring VFileLine's real size and never using a
 * stack/global buffer for the attacker-influenced data) so ASan's HEAP
 * redzone -- not merely stack-array instrumentation -- definitively catches
 * the 1-byte underflow as "heap-buffer-overflow READ of size 1 ... located
 * 1 bytes to the left of a 1025-byte region".
 *
 * get_next_file() itself is embedded byte-for-byte verbatim from
 * target/original_function.c (no logic/name/signature/type changes).
 *
 * io/input/0 (the primary PoC) is byte-identical to the bundle's own frozen
 * dataset/cve_23c63e40/io/input/0 (9 bytes: 0x00 followed by "XXXXXXXX", no
 * trailing newline) -- a leading NUL byte followed by arbitrary filler, the
 * literal CVE-2018-14879 trigger.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

/* ---- target function, embedded byte-for-byte from target/original_function.c ---- */

static char *
get_next_file(FILE *VFile, char *ptr)
{
	char *ret;

	ret = fgets(ptr, PATH_MAX, VFile);
	if (!ret)
		return NULL;

	if (ptr[strlen(ptr) - 1] == '\n')
		ptr[strlen(ptr) - 1] = '\0';

	return ret;
}

/* ---- direct-call driver ---- */

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 64;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) { perror("fopen"); return 64; }
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 64; }
	long fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 64; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 64; }

	unsigned char *buf = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!buf) { fclose(f); return 64; }
	size_t n = fread(buf, 1, (size_t)fsz, f);
	fclose(f);

	/* VFile: a heap-buffer-backed memory stream, matching how the real
	 * VFile is a plain fopen()'d byte stream of the attacker-supplied
	 * -V file list. */
	FILE *VFile = fmemopen(buf, n, "rb");
	if (!VFile) { free(buf); return 64; }

	/* ptr: the real caller's VFileLine[PATH_MAX + 1], heap-allocated
	 * here (never stack/global) so the underflow read is definitively
	 * caught by ASan's heap redzone. */
	char *ptr = (char *)malloc(PATH_MAX + 1);
	if (!ptr) { fclose(VFile); free(buf); return 64; }

	get_next_file(VFile, ptr);

	fclose(VFile);
	free(ptr);
	free(buf);
	return 0;
}
