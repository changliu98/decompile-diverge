/* Direct-call crash harness for CVE-2016-1541 (libarchive,
 * zip_read_mac_metadata, archive_read_support_format_zip.c).
 *
 * Real bug (per dataset/cve_2b3ee8c6/io/crafting_report.md + upstream fix
 * commit d0331e8e5b05b475f20b1f3101fe1ad772d7e7e7): zip_read_mac_metadata()
 * reconstructs the AppleDouble ("Mac resource fork") metadata for a ZIP
 * entry from its companion __MACOSX/._<name> central-directory record
 * (`rsrc`). It allocates
 *
 *     metadata = malloc((size_t)rsrc->uncompressed_size);
 *
 * and then, for the "stored" (uncompressed, rsrc->compression == 0) case,
 * copies data into that buffer in a loop bounded by
 *
 *     remaining_bytes = (size_t)rsrc->compressed_size;
 *     ...
 *     memcpy(mp, p, bytes_avail);           -- case 0, no metadata_bytes clamp
 *
 * i.e. bounded by the attacker-controlled *compressed_size* field, NOT by
 * the remaining space in the uncompressed_size-sized destination buffer.
 * Both compressed_size and uncompressed_size come straight from the
 * attacker-controlled ZIP central-directory record, with no relationship
 * enforced between them, so compressed_size > uncompressed_size drives the
 * memcpy() (literally inside zip_read_mac_metadata itself -- not a callee)
 * past the end of `metadata`: a heap-buffer-overflow WRITE (CWE-787). This
 * is exactly the fault upstream's fix adds checks for (compressed_size ==
 * uncompressed_size for the stored case, a 4 MiB cap, and a per-iteration
 * bytes_avail > metadata_bytes clamp before the memcpy).
 *
 * The full fuzz-target PoC (dataset io/input/0) is a complete hand-built
 * ZIP file that reaches this function via bsdtar's real ZIP central-
 * directory parser + local-file-header reader + read-ahead/filter-chain
 * machinery (thousands of lines, entirely unrelated to this bug). This
 * harness calls zip_read_mac_metadata() DIRECTLY, so it supplies a much
 * smaller custom input format that drives exactly the two fields the bug
 * depends on (rsrc->compression, rsrc->uncompressed_size,
 * rsrc->compressed_size) plus the raw "local file data" bytes that
 * __archive_read_ahead() would have handed back from the client stream:
 *
 *   byte[0]      : rsrc->compression        (1 byte)
 *   byte[1..4]   : rsrc->uncompressed_size   (uint32, little-endian)
 *   byte[5..8]   : rsrc->compressed_size     (uint32, little-endian)
 *   byte[9..end] : payload -- the bytes returned by __archive_read_ahead()
 *                  (the resource-fork's local-file data)
 *
 * All of this lives in ONE heap allocation read straight from argv[1] (see
 * main()), so ASAN's heap redzone sits immediately past both the metadata
 * destination buffer (malloc'd BY the target function itself, from
 * attacker-controlled uncompressed_size -- real function logic, untouched)
 * and the source payload.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>   /* ssize_t */

/* ---- ARCHIVE_* result/errno codes, verbatim values from archive.h /
 * archive_platform.h ---- */
#define ARCHIVE_OK                    0   /* archive.h:190 */
#define ARCHIVE_WARN                (-20)  /* archive.h:192 */
#define ARCHIVE_FATAL                (-30) /* archive.h:196 */
#define ARCHIVE_ERRNO_FILE_FORMAT   EINVAL /* archive_platform.h generic fallback */
#define ARCHIVE_ERRNO_MISC           (-1)  /* archive_platform.h:180 */

/* ---- minimal REAL struct defs, real field names/types verbatim from
 * archive_read_private.h / archive_read_support_format_zip.c, trimmed to
 * only the fields zip_read_mac_metadata() itself touches (this is a leaf
 * call: the caller-side filter-bidder/format-table/rb-tree/decryption
 * machinery around these structs is irrelevant to this bug). ---- */

struct archive {
	int _opaque;
};

struct archive_entry {
	int _opaque;   /* never dereferenced by zip_read_mac_metadata, only
	                * passed through to archive_entry_copy_mac_metadata() */
};

struct archive_format_descriptor {           /* archive_read_private.h:196 */
	void *data;
};

struct archive_read {                        /* archive_read_private.h:159 */
	struct archive archive;
	struct archive_format_descriptor *format;
};

struct zip_entry {                           /* archive_read_support_format_zip.c:71 */
	int64_t        local_header_offset;
	int64_t        compressed_size;
	int64_t        uncompressed_size;
	unsigned char  compression;
};

struct zip {                                 /* archive_read_support_format_zip.c:134 */
	char decompress_init;
};

/* ---- fake attacker-controlled "client read window": the bytes the
 * harness hands to __archive_read_ahead(), simulating the archive_read
 * filter chain's buffered client stream. This is harness driver plumbing
 * (NOT part of the bug -- the real filter chain is thousands of lines
 * irrelevant to this fault); it only needs to deliver the same attacker
 * bytes faithfully. ---- */
static const unsigned char *g_stream;
static size_t g_stream_len;
static size_t g_stream_pos;

/* ---- stand-ins for libarchive driver/plumbing functions the target
 * calls. None of these participate in the bug -- the overflow WRITE is the
 * memcpy() literally inside zip_read_mac_metadata's own case-0 branch, not
 * inside any callee. Real signatures, from archive_read_private.h /
 * archive.h / archive_entry.h / archive_read_support_format_zip.c. ---- */

int64_t
archive_filter_bytes(struct archive *a, int n)
{
	(void)a; (void)n;
	return (int64_t)g_stream_pos;
}

void
archive_set_error(struct archive *a, int err, const char *fmt, ...)
{
	(void)a; (void)err; (void)fmt;
}

const void *
__archive_read_ahead(struct archive_read *a, size_t min, ssize_t *avail)
{
	size_t rem = g_stream_len - g_stream_pos;
	(void)a; (void)min;
	if (avail)
		*avail = (ssize_t)rem;
	if (rem == 0)
		return NULL;
	return g_stream + g_stream_pos;
}

int64_t
__archive_read_consume(struct archive_read *a, int64_t request)
{
	size_t rem = g_stream_len - g_stream_pos;
	(void)a;
	if (request < 0)
		return -1;
	if ((size_t)request > rem)
		request = (int64_t)rem;
	g_stream_pos += (size_t)request;
	return request;
}

int64_t
__archive_read_seek(struct archive_read *a, int64_t offset, int whence)
{
	(void)a; (void)whence;
	if (offset < 0)
		offset = 0;
	if ((size_t)offset > g_stream_len)
		offset = (int64_t)g_stream_len;
	g_stream_pos = (size_t)offset;
	return offset;
}

/* zip_get_local_file_header_size (archive_read_support_format_zip.c:2746)
 * walks the client stream to size the local-file-header; the target only
 * uses the return value to __archive_read_consume() past it before the
 * metadata payload starts. This harness's input format has no separate
 * local-file-header to skip (byte[9..] IS the payload), so the stand-in
 * returns 0. */
static ssize_t
zip_get_local_file_header_size(struct archive_read *a, size_t extra)
{
	(void)a; (void)extra;
	return 0;
}

/* archive_entry_copy_mac_metadata (archive_entry.h:359): only reached
 * AFTER the metadata copy loop completes without crashing (SAFE inputs);
 * no-op stand-in, real signature. */
void
archive_entry_copy_mac_metadata(struct archive_entry *e, const void *d, size_t s)
{
	(void)e; (void)d; (void)s;
}

/* compression_name (archive_read_support_format_zip.c:373): only used in
 * the unsupported-compression error path, which always returns early
 * (before the vulnerable loop). Real signature, stub body. */
static const char *
compression_name(const int compression)
{
	(void)compression;
	return "unknown";
}

/* ==== target function, VERBATIM from
 * dataset/cve_2b3ee8c6/target/original_function.c (no logic/name/
 * signature/type change) ==== */

static int
zip_read_mac_metadata(struct archive_read *a, struct archive_entry *entry,
    struct zip_entry *rsrc)
{
	struct zip *zip = (struct zip *)a->format->data;
	unsigned char *metadata, *mp;
	int64_t offset = archive_filter_bytes(&a->archive, 0);
	size_t remaining_bytes, metadata_bytes;
	ssize_t hsize;
	int ret = ARCHIVE_OK, eof;

	switch(rsrc->compression) {
	case 0:  /* No compression. */
#ifdef HAVE_ZLIB_H
	case 8: /* Deflate compression. */
#endif
		break;
	default: /* Unsupported compression. */
		/* Return a warning. */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported ZIP compression method (%s)",
		    compression_name(rsrc->compression));
		/* We can't decompress this entry, but we will
		 * be able to skip() it and try the next entry. */
		return (ARCHIVE_WARN);
	}

	if (rsrc->uncompressed_size > (4 * 1024 * 1024)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Mac metadata is too large: %jd > 4M bytes",
		    (intmax_t)rsrc->uncompressed_size);
		return (ARCHIVE_WARN);
	}

	metadata = malloc((size_t)rsrc->uncompressed_size);
	if (metadata == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for Mac metadata");
		return (ARCHIVE_FATAL);
	}

	if (offset < rsrc->local_header_offset)
		__archive_read_consume(a, rsrc->local_header_offset - offset);
	else if (offset != rsrc->local_header_offset) {
		__archive_read_seek(a, rsrc->local_header_offset, SEEK_SET);
	}

	hsize = zip_get_local_file_header_size(a, 0);
	__archive_read_consume(a, hsize);

	remaining_bytes = (size_t)rsrc->compressed_size;
	metadata_bytes = (size_t)rsrc->uncompressed_size;
	mp = metadata;
	eof = 0;
	while (!eof && remaining_bytes) {
		const unsigned char *p;
		ssize_t bytes_avail;
		size_t bytes_used;

		p = __archive_read_ahead(a, 1, &bytes_avail);
		if (p == NULL) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated ZIP file header");
			ret = ARCHIVE_WARN;
			goto exit_mac_metadata;
		}
		if ((size_t)bytes_avail > remaining_bytes)
			bytes_avail = remaining_bytes;
		switch(rsrc->compression) {
		case 0:  /* No compression. */
			memcpy(mp, p, bytes_avail);
			bytes_used = (size_t)bytes_avail;
			metadata_bytes -= bytes_used;
			mp += bytes_used;
			if (metadata_bytes == 0)
				eof = 1;
			break;
#ifdef HAVE_ZLIB_H
		case 8: /* Deflate compression. */
		{
			int r;

			ret = zip_deflate_init(a, zip);
			if (ret != ARCHIVE_OK)
				goto exit_mac_metadata;
			zip->stream.next_in =
			    (Bytef *)(uintptr_t)(const void *)p;
			zip->stream.avail_in = (uInt)bytes_avail;
			zip->stream.total_in = 0;
			zip->stream.next_out = mp;
			zip->stream.avail_out = (uInt)metadata_bytes;
			zip->stream.total_out = 0;

			r = inflate(&zip->stream, 0);
			switch (r) {
			case Z_OK:
				break;
			case Z_STREAM_END:
				eof = 1;
				break;
			case Z_MEM_ERROR:
				archive_set_error(&a->archive, ENOMEM,
				    "Out of memory for ZIP decompression");
				ret = ARCHIVE_FATAL;
				goto exit_mac_metadata;
			default:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "ZIP decompression failed (%d)", r);
				ret = ARCHIVE_FATAL;
				goto exit_mac_metadata;
			}
			bytes_used = zip->stream.total_in;
			metadata_bytes -= zip->stream.total_out;
			mp += zip->stream.total_out;
			break;
		}
#endif
		default:
			bytes_used = 0;
			break;
		}
		__archive_read_consume(a, bytes_used);
		remaining_bytes -= bytes_used;
	}
	archive_entry_copy_mac_metadata(entry, metadata,
	    (size_t)rsrc->uncompressed_size - metadata_bytes);

exit_mac_metadata:
	__archive_read_seek(a, offset, SEEK_SET);
	zip->decompress_init = 0;
	free(metadata);
	return (ret);
}

/* ==== driver ==== */

int
main(int argc, char **argv)
{
	FILE *fp;
	long fsz;
	unsigned char *raw;
	size_t n;
	struct archive_read areader;
	struct archive_format_descriptor fmt;
	struct archive_entry dummy_entry;
	struct zip zipobj;
	struct zip_entry rsrc;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 64;
	}
	fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 64; }
	if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
	fsz = ftell(fp);
	if (fsz < 0) { fclose(fp); return 64; }
	rewind(fp);

	/* Read the raw input bytes into a HEAP buffer (never stack/global) so
	 * ASAN's heap-redzone machinery is the one in play for every
	 * attacker-controlled byte; the real overflow buffer (`metadata`
	 * inside zip_read_mac_metadata) is a SEPARATE malloc()'d by the
	 * target function itself, from attacker-controlled uncompressed_size
	 * below -- unmodified real function logic. */
	raw = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!raw) { fclose(fp); return 64; }
	n = fread(raw, 1, (size_t)fsz, fp);
	fclose(fp);

	memset(&rsrc, 0, sizeof(rsrc));
	memset(&zipobj, 0, sizeof(zipobj));

	if (n >= 9) {
		rsrc.compression = raw[0];
		rsrc.uncompressed_size = (int64_t)(
		    (uint32_t)raw[1] | ((uint32_t)raw[2] << 8) |
		    ((uint32_t)raw[3] << 16) | ((uint32_t)raw[4] << 24));
		rsrc.compressed_size = (int64_t)(
		    (uint32_t)raw[5] | ((uint32_t)raw[6] << 8) |
		    ((uint32_t)raw[7] << 16) | ((uint32_t)raw[8] << 24));
		g_stream = raw + 9;
		g_stream_len = n - 9;
	} else {
		/* Too short to carry a header: force the function's own
		 * unsupported-compression early-return (safe, no memory
		 * touched). */
		rsrc.compression = 0xFF;
		rsrc.uncompressed_size = 0;
		rsrc.compressed_size = 0;
		g_stream = raw;
		g_stream_len = 0;
	}
	rsrc.local_header_offset = 0;
	g_stream_pos = 0;

	fmt.data = &zipobj;
	memset(&areader, 0, sizeof(areader));
	areader.format = &fmt;
	memset(&dummy_entry, 0, sizeof(dummy_entry));

	(void)zip_read_mac_metadata(&areader, &dummy_entry, &rsrc);

	free(raw);
	return 0;
}
