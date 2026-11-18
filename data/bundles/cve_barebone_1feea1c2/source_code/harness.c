/*
 * Direct-call crash harness for CVE-2025-5917 (libarchive, CWE-787).
 *
 * Target function: build_ustar_entry_name() from
 *   libarchive/archive_write_set_format_pax.c
 *
 * Real-world trigger site: archive_write_pax_header() in the same file
 * declares `char ustar_entry_name[256];` on its stack and calls
 *   build_ustar_entry_name(ustar_entry_name, path, path_length, NULL);
 * for a pathname that is too long to fit verbatim into the ustar header
 * and cannot be split at a '/' within the 100/155-char prefix/suffix
 * limits (see archive_write_pax_header(), the `has_non_ASCII` /
 * "Find largest suffix that will fit" branches around lines 987-1024).
 *
 * The bug (fixed upstream in commit 7c02cde37a63580cd1859183fbbd2cf04a89be85,
 * "Fix overflow in build_ustar_entry (#2588)"): the unpatched function uses
 * `suffix_length = 99` and `prefix_end = prefix + 155` without reserving a
 * byte for a trailing '/' that may be appended when the located boundary
 * happens to land exactly on a '/'. When BOTH the prefix and suffix
 * boundaries land on a '/', the writes total 156 + 100 = 256 content bytes,
 * and the subsequent `*p = '\0';` writes one byte past the 256-byte `dest`
 * buffer -> a 1-byte out-of-bounds WRITE (CWE-787).
 *
 * This harness reproduces that call directly: it reads the attacker-
 * controlled pathname from argv[1] into a HEAP buffer (malloc), then calls
 * build_ustar_entry_name() exactly as archive_write_pax_header() does
 * (insert == NULL), writing into a 256-byte `dest` buffer that mirrors the
 * real caller's `ustar_entry_name[256]` stack array. No other libarchive
 * code is needed or used.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- verbatim copy of the target function, unmodified ----
 * Source: libarchive/archive_write_set_format_pax.c, build_ustar_entry_name()
 */
static char *
build_ustar_entry_name(char *dest, const char *src, size_t src_length,
    const char *insert)
{
	const char *prefix, *prefix_end;
	const char *suffix, *suffix_end;
	const char *filename, *filename_end;
	char *p;
	int need_slash = 0; /* Was there a trailing slash? */
	size_t suffix_length = 99;
	size_t insert_length;

	/* Length of additional dir element to be added. */
	if (insert == NULL)
		insert_length = 0;
	else
		/* +2 here allows for '/' before and after the insert. */
		insert_length = strlen(insert) + 2;

	/* Step 0: Quick bailout in a common case. */
	if (src_length < 100 && insert == NULL) {
		strncpy(dest, src, src_length);
		dest[src_length] = '\0';
		return (dest);
	}

	/* Step 1: Locate filename and enforce the length restriction. */
	filename_end = src + src_length;
	/* Remove trailing '/' chars and '/.' pairs. */
	for (;;) {
		if (filename_end > src && filename_end[-1] == '/') {
			filename_end --;
			need_slash = 1; /* Remember to restore trailing '/'. */
			continue;
		}
		if (filename_end > src + 1 && filename_end[-1] == '.'
		    && filename_end[-2] == '/') {
			filename_end -= 2;
			need_slash = 1; /* "foo/." will become "foo/" */
			continue;
		}
		break;
	}
	if (need_slash)
		suffix_length--;
	/* Find start of filename. */
	filename = filename_end - 1;
	while ((filename > src) && (*filename != '/'))
		filename --;
	if ((*filename == '/') && (filename < filename_end - 1))
		filename ++;
	/* Adjust filename_end so that filename + insert fits in 99 chars. */
	suffix_length -= insert_length;
	if (filename_end > filename + suffix_length)
		filename_end = filename + suffix_length;
	/* Calculate max size for "suffix" section (#3 above). */
	suffix_length -= filename_end - filename;

	/* Step 2: Locate the "prefix" section of the dirname, including
	 * trailing '/'. */
	prefix = src;
	prefix_end = prefix + 155;
	if (prefix_end > filename)
		prefix_end = filename;
	while (prefix_end > prefix && *prefix_end != '/')
		prefix_end--;
	if ((prefix_end < filename) && (*prefix_end == '/'))
		prefix_end++;

	/* Step 3: Locate the "suffix" section of the dirname,
	 * including trailing '/'. */
	suffix = prefix_end;
	suffix_end = suffix + suffix_length; /* Enforce limit. */
	if (suffix_end > filename)
		suffix_end = filename;
	if (suffix_end < suffix)
		suffix_end = suffix;
	while (suffix_end > suffix && *suffix_end != '/')
		suffix_end--;
	if ((suffix_end < filename) && (*suffix_end == '/'))
		suffix_end++;

	/* Step 4: Build the new name. */
	/* The OpenBSD strlcpy function is safer, but less portable. */
	/* Rather than maintain two versions, just use the strncpy version. */
	p = dest;
	if (prefix_end > prefix) {
		strncpy(p, prefix, prefix_end - prefix);
		p += prefix_end - prefix;
	}
	if (suffix_end > suffix) {
		strncpy(p, suffix, suffix_end - suffix);
		p += suffix_end - suffix;
	}
	if (insert != NULL) {
		/* Note: assume insert does not have leading or trailing '/' */
		strcpy(p, insert);
		p += strlen(insert);
		*p++ = '/';
	}
	strncpy(p, filename, filename_end - filename);
	p += filename_end - filename;
	if (need_slash)
		*p++ = '/';
	*p = '\0';

	return (dest);
}
/* ---- end verbatim target function ---- */

int
main(int argc, char **argv)
{
	FILE *f;
	long sz;
	size_t rd;
	char *src;   /* heap buffer holding the attacker-controlled pathname */
	char dest[256]; /* mirrors archive_write_pax_header()'s
	                 * `char ustar_entry_name[256];` stack array */

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if (f == NULL) {
		perror("fopen");
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return 1;
	}
	sz = ftell(f);
	if (sz < 0) {
		fclose(f);
		return 1;
	}
	if (fseek(f, 0, SEEK_SET) != 0) {
		fclose(f);
		return 1;
	}

	/* Attacker-controlled pathname bytes MUST live on the heap so ASAN's
	 * redzone catches an overflow of the *source* side too; here the
	 * actual bug overflows `dest`, but src is still heap-allocated per
	 * the harness contract. */
	src = (char *)malloc((size_t)sz + 1);
	if (src == NULL) {
		fclose(f);
		return 1;
	}
	rd = fread(src, 1, (size_t)sz, f);
	fclose(f);
	src[rd] = '\0';

	/* Exactly the real call site:
	 *   build_ustar_entry_name(ustar_entry_name, path, path_length, NULL);
	 * from archive_write_pax_header() in archive_write_set_format_pax.c.
	 */
	build_ustar_entry_name(dest, src, rd, NULL);

	/* Use the result so the call can't be optimized away. */
	printf("result[0]=%02x len=%zu\n", (unsigned char)dest[0], strlen(dest));

	free(src);
	return 0;
}
