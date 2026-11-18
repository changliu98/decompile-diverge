/* cve_barebone harness -- libvips vips_source_read_to_memory integer-truncation
 * heap-buffer-overflow WRITE (CWE-787).
 *
 * Fix (a56feecbe9ed66521d9647ec9fbcd2546eccd7ee) adds, right after the existing g_assert()s
 * and BEFORE g_byte_array_set_size() is called:
 *     if (G_UNLIKELY(source->length > UINT_MAX)) { vips_error(...); return -1; }
 *
 * Root cause (entirely within vips_source_read_to_memory's own body):
 *     g_byte_array_set_size(byte_array, source->length);
 * source->length is a gint64 (signed 64-bit); g_byte_array_set_size()'s real second
 * parameter is `guint` (unsigned 32-bit) -- the gint64 argument is silently narrowed
 * (truncated modulo 2^32) AT THE CALL SITE. A source->length just above UINT_MAX
 * (2^32 + K) allocates a byte_array of only K bytes, but the read loop right below still
 * bounds itself with the FULL, un-truncated 64-bit source->length:
 *     while (read_position < source->length) {
 *         bytes_read = vips_source_read(source, q, VIPS_MAX(4096, source->length - read_position));
 *         ...
 *     }
 * -- so it requests (and, if the source genuinely has that many bytes, WRITES) far more
 * than the K bytes actually allocated at `q`.
 *
 * Isolation: vips_source_read_to_memory() is called directly on a hand-built VipsSource.
 * GByteArray / VIPS_MAX / VIPS_FREEF / VIPS_DEBUG_MSG / g_assert are the real libvips/glib
 * names, reproduced as minimal contract-faithful stubs. vips_source_rewind() and
 * vips_source_read() (the two crash-path callees) are faithful stubs of their documented
 * contract (see vips/iofuncs/source.c doc comments) rather than the full GObject
 * class-vtable dispatch, which is incidental to this bug. vips_source_minimise() is an
 * incidental no-op stub (never reached on the trigger path -- the overflow aborts first).
 *
 * TRIGGER: source->length = 2^32 + K (K small) -> g_byte_array_set_size() truncates the
 *          allocation to K bytes, but the harness's backing "device" genuinely has more
 *          than K bytes on hand -> vips_source_read()'s first call overflows the K-byte
 *          heap chunk.
 * SAFE:    source->length <= UINT_MAX (a normal, real file size) -> no truncation; the
 *          read stub never hands back more than the declared remaining length (exactly
 *          like a real fd -- read(2) can never return more bytes than the file actually
 *          contains, no matter how large a buffer/length you offer it), so the byte_array
 *          is filled exactly, cleanly, never overflowing.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- glib base typedefs (real names, glib/gtypes.h) ---- */
typedef int          gint;
typedef unsigned int guint;
typedef gint         gboolean;
typedef long long    gint64;
#define TRUE  1
#define FALSE 0

/* ---- glib statement-expression brackets (real names, glib/gmacros.h) ---- */
#define G_STMT_START do
#define G_STMT_END while (0)

/* ---- vips/util.h (real, verbatim) ---- */
#define VIPS_MAX(A, B) ((A) > (B) ? (A) : (B))

/* ---- vips/debug.h (real, non-debug-build form -- VIPS_DEBUG not defined) ---- */
#define VIPS_DEBUG_MSG(...) G_STMT_START { ; } G_STMT_END

/* ---- vips/memory.h (real, verbatim) ---- */
#define VIPS_FREEF(F, S) \
	G_STMT_START \
	{ \
		if (S) { \
			(void) (F((S))); \
			(S) = 0; \
		} \
	} \
	G_STMT_END

/* ---- glib g_assert (real contract: abort the process if expr is false) ---- */
#define g_assert(expr) \
	G_STMT_START { \
		if (!(expr)) { \
			fprintf(stderr, "assertion failed: %s\n", #expr); \
			abort(); \
		} \
	} G_STMT_END

/* ---- GByteArray (real layout, glib/garray.h: guint8 *data; guint len;) ---- */
typedef struct _GByteArray {
	unsigned char *data;
	guint len;
} GByteArray;

__attribute__((noinline))
static GByteArray *
g_byte_array_new(void)
{
	GByteArray *arr = (GByteArray *) malloc(sizeof(GByteArray));
	arr->data = NULL;
	arr->len = 0;
	return arr;
}

/* Faithful stub of g_byte_array_set_size(GByteArray*, guint) -- REAL prototype; note the
 * `guint` (32-bit) second parameter is exactly what truncates a gint64 source->length
 * argument at the call site inside the target function below. */
__attribute__((noinline))
static GByteArray *
g_byte_array_set_size(GByteArray *array, guint length)
{
	unsigned char *nd = (unsigned char *) realloc(array->data, length ? length : 1);
	if (length > array->len)
		memset(nd + array->len, 0, length - array->len);
	array->data = nd;
	array->len = length;
	return array;
}

__attribute__((noinline))
static void
g_byte_array_unref(GByteArray *array)
{
	if (!array)
		return;
	free(array->data);
	free(array);
}

/* ---- VipsSource (real field names/types, vips/connection.h; the VipsConnection parent +
 * fields vips_source_read_to_memory's own body never touches -- sniff, mmap_*, ... -- are
 * omitted as incidental) ---- */
typedef struct _VipsBlob VipsBlob;   /* opaque; only a pointer is ever touched */

typedef struct _VipsSource {
	gboolean is_pipe;
	gint64 read_position;
	gint64 length;
	const void *data;
	GByteArray *header_bytes;
	VipsBlob *blob;
} VipsSource;

/* ---- harness-controlled "backing device": the bytes vips_source_read()'s real class->read()
 * vfunc would hand back from an actual file/pipe/custom source. ---- */
static unsigned char *g_backing_data = NULL;
static size_t g_backing_size = 0;
static size_t g_backing_pos = 0;

/* Faithful stub of vips_source_rewind(): the real implementation seeks back to the start via
 * vips_source_seek()/vips_source_test_features() and resets the sniff cache -- incidental
 * machinery. Contract preserved: reset the read cursor, return 0 (success). */
__attribute__((noinline))
static int
vips_source_rewind(VipsSource *source)
{
	source->read_position = 0;
	g_backing_pos = 0;
	return 0;
}

/* Faithful stub of vips_source_read(): "Read up to @length bytes from @source and store the
 * bytes in @buffer. Return the number of bytes actually read. If all bytes have been read
 * from the file, return 0." (real doc comment, iofuncs/source.c). Bounded by BOTH how much the
 * source declares remaining (source->length - source->read_position -- the real, un-truncated
 * gint64 field) and how much backing data is physically on hand -- precisely like a real
 * read(2)-backed source, which can never hand back more bytes than the underlying file/pipe
 * actually contains no matter how large a buffer/length you offer it. */
__attribute__((noinline))
static gint64
vips_source_read(VipsSource *source, void *buffer, size_t length)
{
	gint64 remaining_source = source->length - source->read_position;
	size_t remaining_backing;
	size_t avail, n;

	if (remaining_source <= 0)
		return 0;
	remaining_backing = g_backing_size - g_backing_pos;
	avail = (size_t) remaining_source < remaining_backing ? (size_t) remaining_source : remaining_backing;
	n = length < avail ? length : avail;
	if (n == 0)
		return 0;

	memcpy(buffer, g_backing_data + g_backing_pos, n);
	g_backing_pos += n;
	source->read_position += n;
	return (gint64) n;
}

/* Faithful stub of vips_source_minimise(): the real implementation may close a tracked fd once
 * it is safe to -- incidental (never reached on the trigger path; the harness never opens a
 * real descriptor to release). */
__attribute__((noinline))
static void
vips_source_minimise(VipsSource *source)
{
	(void) source;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) ================= */
static int
vips_source_read_to_memory(VipsSource *source)
{
	GByteArray *byte_array;
	gint64 read_position;
	unsigned char *q;

	VIPS_DEBUG_MSG("vips_source_read_to_memory:\n");

	g_assert(!source->is_pipe);
	g_assert(!source->blob);
	g_assert(!source->header_bytes);
	g_assert(source->length >= 0);

	if (vips_source_rewind(source))
		return -1;

	/* We know the length, so we can size the buffer correctly and read
	 * directly to it.
	 */
	byte_array = g_byte_array_new();
	g_byte_array_set_size(byte_array, source->length);

	read_position = 0;
	q = byte_array->data;
	while (read_position < source->length) {
		gint64 bytes_read;

		bytes_read = vips_source_read(source, q,
			VIPS_MAX(4096, source->length - read_position));
		if (bytes_read == -1) {
			VIPS_FREEF(g_byte_array_unref, byte_array);
			return -1;
		}
		if (bytes_read == 0)
			break;

		read_position += bytes_read;
		q += bytes_read;
	}

	/* Steal the byte_array pointer and turn into a memory source.
	 *
	 * We save byte_array in the header_bytes field to get it freed when
	 * we are freed.
	 */
	source->data = byte_array->data;
	source->is_pipe = FALSE;
	source->header_bytes = byte_array;

	vips_source_minimise(source);

	return 0;
}

/* ================= driver ================= */
/* Input layout (all attacker/fuzzer-controlled bytes from argv[1], HEAP-loaded):
 *   [0..8)  declared_length, gint64 little-endian -> becomes source->length
 *   [8..)   backing data -> what vips_source_read()'s stub actually has on hand
 *
 * declared_length > UINT_MAX (2^32 + K, K small) with MORE than K backing bytes on hand ->
 * the g_byte_array_set_size() truncation bug -> heap-buffer-overflow WRITE (CWE-787) inside
 * vips_source_read_to_memory's own read loop.
 * declared_length <= UINT_MAX with backing data that never exceeds it -> no truncation, no
 * overflow -> clean exit.
 */
int
main(int argc, char **argv)
{
	FILE *fp;
	unsigned char *filebuf;
	size_t fsize, nread, hdr;
	gint64 declared_length;
	int i;
	VipsSource source;

	if (argc < 2)
		return 0;
	fp = fopen(argv[1], "rb");
	if (!fp)
		return 0;
	fseek(fp, 0, SEEK_END);
	{
		long ln = ftell(fp);
		fsize = ln > 0 ? (size_t) ln : 0;
	}
	fseek(fp, 0, SEEK_SET);

	filebuf = (unsigned char *) malloc(fsize ? fsize : 1);   /* HEAP input buffer */
	nread = fsize ? fread(filebuf, 1, fsize, fp) : 0;
	fclose(fp);

	if (nread < 8) {
		free(filebuf);
		return 0;
	}

	declared_length = 0;
	for (i = 0; i < 8; i++)
		declared_length |= ((gint64) (unsigned long long) filebuf[i]) << (8 * i);
	if (declared_length < 0)
		declared_length = -(declared_length + 1);   /* keep g_assert(length>=0) satisfied */
	hdr = 8;

	g_backing_size = nread - hdr;
	g_backing_data = (unsigned char *) malloc(g_backing_size ? g_backing_size : 1);
	memcpy(g_backing_data, filebuf + hdr, g_backing_size);
	g_backing_pos = 0;

	memset(&source, 0, sizeof(source));
	source.is_pipe = FALSE;
	source.blob = NULL;
	source.header_bytes = NULL;
	source.data = NULL;
	source.length = declared_length;
	source.read_position = 0;

	/* volatile function pointer: forbid the compiler from inlining
	 * vips_source_read_to_memory into main (dc_batch requires the target function's own
	 * frame in the ASAN crash backtrace). */
	{
		int (*volatile fn)(VipsSource *) = vips_source_read_to_memory;
		fn(&source);
	}

	free(g_backing_data);
	free(filebuf);
	return 0;
}
