/* cve_barebone direct-call harness for cve_bd68ac71 (gpac, CVE-2022-29339)
 * Target: BS_ReadByte (src/utils/bitstream.c) -- FILE-mode ("cache_read") branch.
 * Bug class: CWE-617 Reachable Assertion (NVD: "function BS_ReadByte() ... has a failed
 * assertion, which causes a Denial of Service"; fixed in commit 9ea93a2). See the
 * generator script (scripts/gen_dc_cve_bd68ac71.py) for the full derivation.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/* ---- gpac/setup.h (real names, UNIX branch: stdint-backed) ---- */
typedef uint64_t u64;
typedef int64_t  s64;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint8_t  u8;
typedef int8_t   s8;
#define GFINLINE inline
typedef enum { GF_FALSE = 0, GF_TRUE } Bool;

/* ---- gpac/tools.h: real name GF_Err; minimal stand-in (the real ~20-member enum's
 * values are never read/compared anywhere on this path -- on_block_out, the only
 * struct field of this type, is left NULL and never invoked). ---- */
typedef s32 GF_Err;
#define GF_OK 0

/* ---- gpac/tools.h GF_LOG: real macro name; no-op stand-in. The real body calls
 * gf_log_tool_level_on()/gf_log_lt()/gf_log() -- a whole logging subsystem with zero
 * effect on control flow; whether/where the message is printed does not change
 * BS_ReadByte's crash-relevant behavior. ---- */
#define GF_LOG(_ll, _lm, __args)
#define GF_LOG_ERROR 0
#define GF_LOG_CORE  0

/* ---- gpac/bitstream.h, VERBATIM public enum + opaque typedef ---- */
enum
{
	GF_BITSTREAM_READ = 0,
	GF_BITSTREAM_WRITE,
	GF_BITSTREAM_WRITE_DYN
};
typedef struct __tag_bitstream GF_BitStream;

/* ==== src/utils/bitstream.c, VERBATIM private enum + struct (the exact object
 * BS_ReadByte itself operates on) ==== */
enum
{
	GF_BITSTREAM_FILE_READ = GF_BITSTREAM_WRITE_DYN + 1,
	GF_BITSTREAM_FILE_WRITE,
};

struct __tag_bitstream
{
	/*original stream data*/
	FILE *stream;

	/*or original data*/
	char *original;
	/*the size of our buffer in bytes*/
	u64 size;
	/*current position in BYTES*/
	u64 position;
	/*the byte readen/written*/
	u32 current;
	/*the number of bits in the current byte*/
	u32 nbBits;
	/*the bitstream mode*/
	u32 bsmode;

	void (*EndOfStream)(void *par);
	void *par;


	char *cache_write;
	u32 cache_write_size, buffer_written;

	Bool remove_emul_prevention_byte;
	u32 nb_zeros;

	GF_Err (*on_block_out)(void *cbk, u8 *data, u32 block_size);
	void *usr_data;
	u64 bytes_out;
	u32 prevent_dispatch;

	u64 cookie;

	u8 *cache_read;
	u32 cache_read_size, cache_read_pos, cache_read_alloc;

	void (*on_log)(void *udta, const char *field_name, u32 nb_bits, u64 field_val, s32 idx1, s32 idx2, s32 idx3);
	void *log_udta;

	u32 total_bits_read;
	u32 overflow_state;
};

/* ---- src/utils/os_file.c: for a plain (non-GF_FileIO) FILE*, the real gf_fread/
 * gf_fgetc/gf_feof are EXACTLY these 1-line passthroughs (gf_fileio_check() is false
 * for every FILE* this harness ever creates -- GF_FileIO is gpac's own virtual-
 * filesystem wrapper, an unrelated subsystem never touched here). Not invented: the
 * real fallback path, minus the dead GF_FileIO branch. ---- */
static size_t gf_fread(void *ptr, size_t nbytes, FILE *stream) { return fread(ptr, 1, nbytes, stream); }
static int gf_fgetc(FILE *stream) { return fgetc(stream); }
static int gf_feof(FILE *stream) { return feof(stream); }

/* ---- src/utils/bitstream.c gf_bs_load_byte, VERBATIM. File-private (`static`),
 * called ONLY by BS_ReadByte in the real file -- this IS BS_ReadByte's own crash-path
 * machinery, not an incidental callee. ---- */
static GFINLINE u8 gf_bs_load_byte(GF_BitStream *bs, Bool *is_eos)
{
	u8 res;
	if (bs->cache_read) {
		if (bs->cache_read_pos == bs->cache_read_size) {
			bs->cache_read_size = (u32) gf_fread(bs->cache_read, bs->cache_read_alloc, bs->stream);
			bs->cache_read_pos = 0;
			if (!bs->cache_read_size) {
				*is_eos = GF_TRUE;
				return 0;
			}
		}
		res = bs->cache_read[bs->cache_read_pos];
		bs->cache_read_pos++;
	} else {
		res = gf_fgetc(bs->stream);
	}
	return res;
}

/* ---- incidental callees (real signatures, bitstream.c/bitstream.h) -- both are
 * referenced by BS_ReadByte's verbatim text but NEVER actually invoked by any input
 * this harness constructs: remove_emul_prevention_byte is always GF_FALSE, so the
 * whole `if (bs->remove_emul_prevention_byte) {...}` block (the only caller of
 * gf_bs_seek within BS_ReadByte) never executes; bs->cache_write is always NULL, so
 * `if (bs->cache_write) bs_flush_write_cache(bs);` never executes either. Minimal
 * stubs (never entered) stand in for the real, transitively large implementations. ---- */
static GF_Err gf_bs_seek(GF_BitStream *bs, u64 offset) { (void) bs; (void) offset; return GF_OK; }
static void bs_flush_write_cache(GF_BitStream *bs) { (void) bs; }

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline + invoked through a volatile function pointer so the abort() keeps its own,
 * dc_batch-visible stack frame (target-in-stack requires "BS_ReadByte" literally in the
 * ASAN/ABRT backtrace). Neither changes a single byte of the pasted function text below. */
__attribute__((noinline))
static u8 BS_ReadByte(GF_BitStream *bs)
{
	Bool is_eos;
	if (bs->bsmode == GF_BITSTREAM_READ) {
		u8 res;
		if (bs->position >= bs->size) {
			if (bs->EndOfStream) bs->EndOfStream(bs->par);
			if (!bs->overflow_state) bs->overflow_state = 1;
			return 0;
		}
		res = bs->original[bs->position++];

		if (bs->remove_emul_prevention_byte) {
			if ((bs->nb_zeros==2) && (res==0x03) && (bs->position<bs->size) && (bs->original[bs->position]<0x04)) {
				bs->nb_zeros = 0;
				res = bs->original[bs->position++];
			}
			if (!res) bs->nb_zeros++;
			else bs->nb_zeros = 0;
		}
		return res;
	}
	if (bs->cache_write)
		bs_flush_write_cache(bs);

	is_eos = gf_feof(bs->stream);

	/*we are in FILE mode, test for end of file*/
	if (!is_eos || bs->cache_read) {
		u8 res;
		Bool loc_eos=GF_FALSE;
		assert(bs->position<=bs->size);
		bs->position++;

		res = gf_bs_load_byte(bs, &loc_eos);
		if (loc_eos) goto bs_eof;

		if (bs->remove_emul_prevention_byte) {
			if ((bs->nb_zeros==2) && (res==0x03) && (bs->position<bs->size)) {
				u8 next = gf_bs_load_byte(bs, &loc_eos);
				if (next < 0x04) {
					bs->nb_zeros = 0;
					res = next;
					bs->position++;
				} else {
					gf_bs_seek(bs, bs->position);
				}
			}
			if (!res) bs->nb_zeros++;
			else bs->nb_zeros = 0;
		}
		return res;
	}

bs_eof:
	if (bs->EndOfStream) {
		bs->EndOfStream(bs->par);
		if (!bs->overflow_state) bs->overflow_state = 1;
	} else {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("[BS] Attempt to overread bitstream\n"));
	}
	assert(bs->position <= 1+bs->size);
	return 0;
}
/* ================= end verbatim ================= */

/* ================= driver =================
 * byte[0] = extra (u8); byte[1..] = content (0..64 bytes, values unused).
 * n_calls = content_len + extra.  extra<=1 -> safe; extra>=2 -> trigger. */
int main(int argc, char **argv)
{
	if (argc < 2) return 0;
	FILE *inf = fopen(argv[1], "rb");
	if (!inf) return 0;
	fseek(inf, 0, SEEK_END);
	long ln = ftell(inf);
	fseek(inf, 0, SEEK_SET);
	if (ln < 0) ln = 0;
	size_t n = (size_t) ln;

	/* HEAP-allocate the raw input (ASAN-guarded). */
	unsigned char *seed = (unsigned char *) malloc(n + 1);
	if (!seed) { fclose(inf); return 0; }
	size_t got = n ? fread(seed, 1, n, inf) : 0;
	fclose(inf);
	seed[got] = 0;

	unsigned char extra = (got > 0) ? seed[0] : 0;
	size_t content_len = (got > 1) ? (got - 1) : 0;
	if (content_len > 64) content_len = 64;   /* keep the underlying "file" small */

	/* Write `content` into a REAL temp file -- this becomes bs->stream, exactly as
	 * gf_bs_from_file() wraps a freshly-opened FILE*. */
	FILE *stream = tmpfile();
	if (!stream) { free(seed); return 0; }
	if (content_len) fwrite(seed + 1, 1, content_len, stream);
	fflush(stream);
	rewind(stream);   /* mirrors gf_bs_from_file's gf_fseek(f, position, SEEK_SET) */

	GF_BitStream bsobj;
	memset(&bsobj, 0, sizeof(bsobj));
	bsobj.bsmode = GF_BITSTREAM_FILE_READ;
	bsobj.stream = stream;
	bsobj.size = (u64) content_len;
	bsobj.position = 0;
	bsobj.EndOfStream = NULL;
	bsobj.par = NULL;
	bsobj.remove_emul_prevention_byte = GF_FALSE;
	bsobj.nb_zeros = 0;
	bsobj.cache_write = NULL;
	bsobj.overflow_state = 0;

	/* gf_bs_from_file's cache setup (mode==GF_BITSTREAM_FILE_READ, core.bs-cache-size>0):
	 * cache_read_pos==cache_read_size==cache_read_alloc "primed" so the FIRST
	 * BS_ReadByte call refills. Sized far above content_len (<=64) so one fread() always
	 * drains the whole temp file in a single shot -- keeps the call-count accounting in
	 * the header comment exact (no multi-refill edge cases). */
	bsobj.cache_read_alloc = 65536;
	bsobj.cache_read = (u8 *) malloc(bsobj.cache_read_alloc);
	if (!bsobj.cache_read) { fclose(stream); free(seed); return 0; }
	bsobj.cache_read_pos = bsobj.cache_read_size = bsobj.cache_read_alloc;

	size_t n_calls = content_len + extra;

	u8 (* volatile fn)(GF_BitStream *) = BS_ReadByte;
	volatile u8 sink = 0;
	for (size_t i = 0; i < n_calls; i++) {
		sink ^= fn(&bsobj);
	}

	free(bsobj.cache_read);
	fclose(stream);
	free(seed);
	(void) sink;
	return 0;
}
