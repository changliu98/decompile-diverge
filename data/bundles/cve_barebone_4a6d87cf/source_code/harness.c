/* cve_barebone direct-call harness for jasper (jasper-software/jasper)
 * Target: jpc_dec_process_sod  (src/libjasper/jpc/jpc_dec.c)
 * Bug class: reachable assertion (CWE-617) at jpc_streamlist_remove():
 *   `assert(streamno < streamlist->numstreams);`
 *
 * Upstream fix (jasper-software/jasper@6d084c53a77762f41bb5310713a5f1872fef55f5,
 * fixes jasper-software/jasper#381) added a missing check IN jpc_dec_process_sod
 * itself before calling jpc_streamlist_remove(dec->pkthdrstreams, 0):
 *
 *     if (jpc_streamlist_numstreams(dec->pkthdrstreams) != 0 &&
 *       !(tile->pkthdrstream = jpc_streamlist_remove(dec->pkthdrstreams, 0))) {
 *
 * Pre-fix, `if (dec->pkthdrstreams)` only tested the pointer for non-NULL, not
 * whether the streamlist actually holds any streams. A PPM-marker-derived
 * pkthdrstreams list with zero entries (dec->pkthdrstreams non-NULL, numstreams
 * == 0) reaches jpc_streamlist_remove(list, 0) whose own assert
 * `streamno < streamlist->numstreams` (0 < 0) fails -> abort(). The reported
 * upstream crash (jasper-software/jasper#381) is exactly this: SIGABRT inside
 * jpc_streamlist_remove, called directly from jpc_dec_process_sod:614.
 *
 * The direct-call harness constructs a jpc_dec_t/jpc_dec_tile_t pair with
 * tile->partno != 0 (so the heavy jpc_dec_cp_isvalid/jpc_dec_cp_prepare/
 * jpc_dec_tileinit tile-init block at the top of jpc_dec_process_sod, which
 * needs a fully-populated coding-parameters object, is skipped -- exactly the
 * ARVO fuzz harness's own "already past the first tile-part" state) and feeds
 * the attacker-controlled input byte straight into pkthdrstreams->numstreams,
 * matching the real trigger condition (an empty PPM stream list) 1:1.
 *
 * Struct layout for jpc_dec_t / jpc_dec_tile_t / jpc_streamlist_t / jpc_ppxstab_t
 * is copied verbatim (real field names/types) from
 * src/libjasper/jpc/jpc_dec.h, TRIMMED to only the fields jpc_dec_process_sod's
 * own body reads/writes (the omitted fields -- tile geometry, tcomps, pi, cp
 * internals, image, cstate, ... -- are never touched by this function; they
 * only matter to the deep tile-init/tile-decode machinery that this input
 * class never reaches). jpc_streamlist_remove is the REAL function body
 * (verbatim from jpc_dec.c) since it is where the crash manifests. All other
 * callees jpc_dec_process_sod can statically reach (jpc_dec_cp_isvalid,
 * jpc_dec_cp_prepare, jpc_dec_tileinit, jas_stream_memopen, jpc_pptstabwrite,
 * jpc_ppxstab_destroy, jas_get_debug_level, jpc_dec_dump, jpc_dec_decodepkts,
 * jpc_dec_tiledecode, jpc_dec_tilefini, jas_stream_tell/seek/getrwcount/getc,
 * jas_logerrorf/jas_logwarnf) are faithful no-op/error-returning stubs: with
 * tile->partno!=0 and tile->pptstab==0 they are provably never invoked before
 * the crash (or, on safe inputs, before jpc_dec_process_sod's own natural
 * `return -1`), so their bodies have zero effect on program behaviour -- they
 * exist only so the whole-function control flow (which the compiler cannot
 * statically prove dead, since it depends on runtime struct fields) links.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/* ---- jas_uchar (jasper/jas_types.h:89) ---- */
#define jas_uchar unsigned char

/* ---- JAS_UNUSED (jasper/jas_compiler.h:145) ---- */
#define JAS_UNUSED(x) ((void) x)

/* ---- JPC_TPHSOT (jpc_dec.c:102) ---- */
#define JPC_TPHSOT 0x0008

/* Opaque types: only ever handled as pointers by jpc_dec_process_sod's own
 * body (never dereferenced through their real fields there). */
typedef struct jas_stream_s jas_stream_t;
typedef struct jpc_ms_s jpc_ms_t;
typedef struct jpc_dec_cp_s jpc_dec_cp_t;

/* ---- jpc_ppxstab_t (jpc_dec.h:108-121), real fields ---- */
typedef struct {
	unsigned numents;
	unsigned maxents;
	void **ents;
} jpc_ppxstab_t;

/* ---- jpc_streamlist_t (jpc_dec.h:124-136), real fields, verbatim ---- */
typedef struct {
	/* The number of streams in this list. */
	unsigned numstreams;
	/* The maximum number of streams that can be accomodated without
	  growing the streams array. */
	unsigned maxstreams;
	/* The streams. */
	jas_stream_t **streams;
} jpc_streamlist_t;

/* ---- jpc_dec_tile_t (jpc_dec.h:478-523), TRIMMED to the fields
 * jpc_dec_process_sod's own body touches: pptstab, pkthdrstream, cp, partno,
 * numparts. (Omitted: state, xstart/ystart/xend/yend, tcomps, realmode, pi --
 * none referenced by jpc_dec_process_sod.) ---- */
typedef struct {
	jpc_ppxstab_t *pptstab;
	jas_stream_t *pkthdrstream;
	jpc_dec_cp_t *cp;
	unsigned partno;
	unsigned numparts;
} jpc_dec_tile_t;

/* ---- jpc_dec_t (jpc_dec.h:557-652), TRIMMED to the fields
 * jpc_dec_process_sod's own body touches: curtile, in, pkthdrstreams,
 * curtileendoff, state. ---- */
typedef struct {
	jpc_dec_tile_t *curtile;
	jas_stream_t *in;
	jpc_streamlist_t *pkthdrstreams;
	long curtileendoff;
	int state;
} jpc_dec_t;

/* ==== Faithful no-op / error-returning stubs for callees jpc_dec_process_sod
 * can statically reach but which this input class provably never invokes
 * before either the crash or the function's own early `return -1`. ==== */
static int jpc_dec_cp_isvalid(const jpc_dec_cp_t *cp) { (void) cp; return 0; }
static int jpc_dec_cp_prepare(jpc_dec_cp_t *cp) { (void) cp; return -1; }
static int jpc_dec_tileinit(jpc_dec_t *dec, jpc_dec_tile_t *tile) { (void) dec; (void) tile; return -1; }
static jas_stream_t *jas_stream_memopen(char *buf, int bufsize) { (void) buf; (void) bufsize; return 0; }
static long jas_stream_tell(jas_stream_t *s) { (void) s; return 0; }
static int jas_stream_seek(jas_stream_t *s, long off, int origin) { (void) s; (void) off; (void) origin; return 0; }
static int jpc_pptstabwrite(jas_stream_t *out, jpc_ppxstab_t *tab) { (void) out; (void) tab; return -1; }
static void jpc_ppxstab_destroy(jpc_ppxstab_t *tab) { (void) tab; }
static int jas_get_debug_level(void) { return 0; }
static void jpc_dec_dump(jpc_dec_t *dec) { (void) dec; }
static int jpc_dec_decodepkts(jpc_dec_t *dec, jas_stream_t *in, jas_stream_t *pin) { (void) dec; (void) in; (void) pin; return -1; }
static void jas_logerrorf(const char *fmt, ...) { (void) fmt; }
static long jas_stream_getrwcount(jas_stream_t *s) { (void) s; return 0; }
static void jas_logwarnf(const char *fmt, ...) { (void) fmt; }
static int jas_stream_getc(jas_stream_t *s) { (void) s; return -1; }
static int jpc_dec_tiledecode(jpc_dec_t *dec, jpc_dec_tile_t *tile) { (void) dec; (void) tile; return -1; }
static void jpc_dec_tilefini(jpc_dec_t *dec, jpc_dec_tile_t *tile) { (void) dec; (void) tile; }

/* ==== VERBATIM from src/libjasper/jpc/jpc_dec.c:2405-2415 (the callee where
 * the crash manifests -- real body, unmodified). ==== */
static jas_stream_t *jpc_streamlist_remove(jpc_streamlist_t *streamlist, unsigned streamno)
{
	assert(streamno < streamlist->numstreams);

	jas_stream_t *stream;
	stream = streamlist->streams[streamno];
	for (unsigned i = streamno + 1; i < streamlist->numstreams; ++i) {
		streamlist->streams[i - 1] = streamlist->streams[i];
	}
	--streamlist->numstreams;
	return stream;
}

/* ==== VERBATIM from data_cve/cve_4a6d87cf/target/original_function.c ==== */
static int jpc_dec_process_sod(jpc_dec_t *dec, jpc_ms_t *ms)
{
	jpc_dec_tile_t *tile;
	int pos;

	JAS_UNUSED(ms);

	if (!(tile = dec->curtile)) {
		return -1;
	}

	if (!tile->partno) {
		if (!jpc_dec_cp_isvalid(tile->cp)) {
			return -1;
		}
		if (jpc_dec_cp_prepare(tile->cp)) {
			return -1;
		}
		if (jpc_dec_tileinit(dec, tile)) {
			return -1;
		}
	}

	/* Are packet headers stored in the main header or tile-part header? */
	if (dec->pkthdrstreams) {
		/* Get the stream containing the packet header data for this
		  tile-part. */
		if (!(tile->pkthdrstream = jpc_streamlist_remove(dec->pkthdrstreams, 0))) {
			return -1;
		}
	}

	if (tile->pptstab) {
		if (!tile->pkthdrstream) {
			if (!(tile->pkthdrstream = jas_stream_memopen(0, 0))) {
				return -1;
			}
		}
		pos = jas_stream_tell(tile->pkthdrstream);
		jas_stream_seek(tile->pkthdrstream, 0, SEEK_END);
		if (jpc_pptstabwrite(tile->pkthdrstream, tile->pptstab)) {
			return -1;
		}
		jas_stream_seek(tile->pkthdrstream, pos, SEEK_SET);
		jpc_ppxstab_destroy(tile->pptstab);
		tile->pptstab = 0;
	}

	if (jas_get_debug_level() >= 10) {
		jpc_dec_dump(dec);
	}

	if (jpc_dec_decodepkts(dec, (tile->pkthdrstream) ? tile->pkthdrstream :
	  dec->in, dec->in)) {
		jas_logerrorf("jpc_dec_decodepkts failed\n");
		return -1;
	}

	/* Gobble any unconsumed tile data. */
	if (dec->curtileendoff > 0) {
		long curoff;
		uint_fast32_t n;
		curoff = jas_stream_getrwcount(dec->in);
		if (curoff < dec->curtileendoff) {
			n = dec->curtileendoff - curoff;
			jas_logwarnf("warning: ignoring trailing garbage (%lu bytes)\n",
			  (unsigned long) n);

			while (n-- > 0) {
				if (jas_stream_getc(dec->in) == EOF) {
					jas_logerrorf("read error\n");
					return -1;
				}
			}
		} else if (curoff > dec->curtileendoff) {
			jas_logwarnf("warning: not enough tile data (%lu bytes)\n",
			  (unsigned long) curoff - dec->curtileendoff);
		}

	}

	if (tile->numparts > 0 && tile->partno == tile->numparts - 1) {
		if (jpc_dec_tiledecode(dec, tile)) {
			return -1;
		}
		jpc_dec_tilefini(dec, tile);
	}

	dec->curtile = 0;

	/* Increment the expected tile-part number. */
	++tile->partno;

	/* We should expect to encounter a SOT marker segment next. */
	dec->state = JPC_TPHSOT;

	return 0;
}
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocate the input so ASAN guards it. */
	unsigned char *buf = (unsigned char *) malloc((size_t) sz > 0 ? (size_t) sz : 1);
	if (!buf) { fclose(f); return 0; }
	size_t n = fread(buf, 1, (size_t) sz, f);
	fclose(f);

	/* Attacker-controlled byte 0 (0 if the file is empty) selects how many
	 * streams the PPM-derived pkthdrstreams list holds -- this is exactly
	 * the real-world trigger dimension: a crafted JPC codestream whose PPM
	 * marker segments decode (via jpc_ppmstabtostreams(), not reconstructed
	 * here) to a stream count of 0 for the current tile-part. numstreams==0
	 * is the ONLY value that reaches the unguarded jpc_streamlist_remove()
	 * assert; any numstreams>=1 takes the safe, patched-equivalent path. */
	unsigned char sel = (n > 0) ? buf[0] : 0;
	unsigned numstreams = sel % 4; /* 0 => trigger, 1..3 => safe */

	/* Streams array is heap-allocated exactly like the real
	 * jpc_streamlist_create() (maxstreams slots, all zeroed) so an
	 * in-bounds-vs-out-of-bounds access is governed by the SAME allocation
	 * discipline as upstream, not an artifact of this harness. */
	unsigned maxstreams = 8;
	jas_stream_t **streams = (jas_stream_t **) calloc(maxstreams, sizeof(jas_stream_t *));
	if (!streams) { free(buf); return 0; }
	if (numstreams > 0) {
		/* Populate with a benign non-NULL sentinel so the (safe-path)
		 * `!(tile->pkthdrstream = jpc_streamlist_remove(...))` check
		 * takes the non-error branch, same as a real decode with
		 * available packet-header stream data. */
		streams[0] = (jas_stream_t *) (void *) 0x1;
	}

	jpc_streamlist_t pkthdrstreams = { numstreams, maxstreams, streams };

	jpc_dec_tile_t tile;
	memset(&tile, 0, sizeof(tile));
	tile.partno = 1; /* past the first tile-part: skip the tileinit block */

	jpc_dec_t dec;
	memset(&dec, 0, sizeof(dec));
	dec.curtile = &tile;
	dec.pkthdrstreams = &pkthdrstreams;

	jpc_ms_t *ms = 0; /* JAS_UNUSED(ms) in the target -- never dereferenced */

	int rc = jpc_dec_process_sod(&dec, ms);
	fprintf(stderr, "rc=%d numstreams_in=%u\n", rc, numstreams);

	free(buf);
	free(streams);
	return 0;
}
