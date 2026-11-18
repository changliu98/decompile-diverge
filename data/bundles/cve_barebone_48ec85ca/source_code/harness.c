/* ============================================================================
 * cve_48ec85ca -- direct-call harness for mupdf `initialise_banding()`
 * (source/tools/muraster.c), CVE-2021-4216 / CWE-369 divide-by-zero.
 *
 * Baseline (case.json): dedup_token
 * "initialise_banding--drawpage--drawrange", summary
 * "UndefinedBehaviorSanitizer: undefined-behavior source/tools/muraster.c:1006:31 in".
 * `initialise_banding` IS the bundle's crash_site/target function, and the
 * faulting instruction is INSIDE its own body (no callee needs embedding):
 *
 *     w = render->ibounds.x1 - render->ibounds.x0;                    // L1004
 *     min_band_mem = (size_t)bpp * w * min_band_height;                // L1005
 *     reps = (int)(max_band_memory / min_band_mem);                    // L1006 <-- crash
 *
 * Root cause: `bpp` is always >=1 (case CS_GRAY:1 / CS_RGB:2 / default
 * CS_CMYK:3) and `min_band_height` is a positive CLI default (32), so the
 * ONLY way `min_band_mem` collapses to exactly 0 is `w == 0`, i.e. a page
 * whose rounded, resolution-scaled integer bounds have `ibounds.x1 ==
 * ibounds.x0` (a degenerate/zero-width raster) -- exactly CVE-2021-4216
 * ("muraster: division by zero when rendering a page with 0 width/height").
 * (Negative `w` does NOT trigger this: `(size_t)bpp * w * min_band_height`
 * promotes the negative `int w` to a huge unsigned `size_t` via the usual
 * arithmetic conversions, so `min_band_mem` becomes enormous, not zero --
 * `reps` truncates to 0 and is then clamped back up to 1. Verified live.)
 *
 * FAITHFULNESS / what is VERBATIM vs. glue:
 *   - initialise_banding() (target/original_function.c): embedded 100%
 *     VERBATIM below, byte-for-byte, no logic/name/signature changes
 *     (including its own `#if GREY_FALLBACK != 0` preprocessor guard).
 *   - Every external symbol the body references (fz_new_pnm_band_writer,
 *     fz_new_pam_band_writer, fz_new_pbm_band_writer, fz_new_pkm_band_writer)
 *     sits STRICTLY AFTER the divide-by-zero line (L1006, triggering inputs
 *     abort there before reaching them) and, for safe inputs that DO reach
 *     them, their return value is only ever STORED into render->bander --
 *     never dereferenced by initialise_banding itself. They are supplied as
 *     trivial, real-signature (source_code/include/mupdf/fitz/write-pixmap.h)
 *     link-only stubs that never fabricate any decode/render behaviour.
 *   - `render_details` below is the REAL struct verbatim (source/tools/
 *     muraster.c), real field names/types/order; `fz_rect`/`fz_irect`/
 *     `fz_matrix` are the REAL structs (include/mupdf/fitz/geometry.h);
 *     `fz_page`/`fz_display_list`/`fz_band_writer`/`fz_context`/`fz_output`
 *     are the REAL opaque typedefs (mupdf headers) -- never dereferenced by
 *     the reachable code, so kept opaque (no fabricated internals).
 *   - `output_cs`/`output_format`/`min_band_height`/`max_band_memory`/`out`
 *     are the REAL file-scope globals `initialise_banding` reads (muraster.c
 *     top-level statics), same real names/types. `min_band_height`(32) and
 *     `max_band_memory` (5081088 = MIN_BAND_HEIGHT * PAPER_WIDTH *
 *     X_RESOLUTION * 4 * 16, muraster.c's own BAND_MEMORY default with no
 *     `-B`/`-M` override) are pinned to the tool's real compiled-in defaults.
 *     `render->num_workers` is pinned to 0, mirroring the frozen corpus's own
 *     real replay recipe (`io/manifest.json: "{tool} -T 0 -r 0 -o
 *     /tmp/o.pgm {input}"` -- `-T 0` sets `num_workers=0`), which also keeps
 *     execution strictly on the L1006 crash site (avoids the function's
 *     UNRELATED second division at L1011-1020, gated by `num_workers>0`).
 *     `GREY_FALLBACK` is pinned to 1: the frozen `target/ghidra.c` shows the
 *     real compiled binary DOES contain the `if (color==0) {...}` fallback
 *     block, i.e. GREY_FALLBACK was nonzero in the real build.
 *   - `output_format`/`output_cs` are driven PER-INPUT from a real
 *     suffix-table pairing (muraster.c's own `suffix_table[]`, mirrored
 *     verbatim below as FMT_TABLE) -- exactly how the real CLI ties them
 *     together from the output filename's suffix, so every (format,cs) pair
 *     used is one the real tool can actually produce.
 *   - main() reads argv[1] into a HEAP buffer (malloc) -- the attacker-
 *     controlled bytes never touch the stack/globals -- and decodes it as
 *     this harness's own compact encoding for the one thing a real PDF's
 *     page geometry actually drives here: `render->ibounds` (x0,x1,y0,y1,
 *     4x little-endian int32) plus one `color` byte and one format-selector
 *     byte (index into FMT_TABLE). There is no PDF/page-layout engine here
 *     because the direct call bypasses drawpage()'s real
 *     `render->ibounds = fz_round_rect(render->tbounds)` computation
 *     entirely, exactly as instructed -- the harness controls the RESULT of
 *     that computation directly, which is what initialise_banding() itself
 *     actually consumes. initialise_banding() is then called exactly ONCE.
 * ============================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---------------------------------------------------------------------- *
 * Minimal REAL mupdf opaque typedefs (include/mupdf/fitz/context.h,
 * document.h, display-list.h, band-writer.h) -- never dereferenced by any
 * code path this harness reaches, so kept intentionally opaque (no
 * fabricated internals).
 * ---------------------------------------------------------------------- */
typedef struct fz_context fz_context;
typedef struct fz_output fz_output;
typedef struct fz_page fz_page;
typedef struct fz_display_list fz_display_list;
typedef struct fz_band_writer fz_band_writer;

/* ---- REAL fz_rect / fz_irect / fz_matrix (include/mupdf/fitz/geometry.h),
 * verbatim field names/types/order. ---- */
typedef struct
{
	float x0, y0;
	float x1, y1;
} fz_rect;

typedef struct
{
	int x0, y0;
	int x1, y1;
} fz_irect;

typedef struct
{
	float a, b, c, d, e, f;
} fz_matrix;

/* ---- REAL enums (source/tools/muraster.c) -- verbatim values via C's
 * default sequential enumerator assignment. ---- */
enum {
	OUT_PGM,
	OUT_PPM,
	OUT_PAM,
	OUT_PBM,
	OUT_PKM
};

enum {
	CS_GRAY,
	CS_RGB,
	CS_CMYK
};

/* ---- REAL suffix_table (source/tools/muraster.c) -- mirrored verbatim so
 * every (format,cs) combination this harness picks is one the real CLI can
 * actually produce from an output filename suffix. ---- */
typedef struct { const char *suffix; int format; int cs; } suffix_t;
static const suffix_t FMT_TABLE[] = {
	{ ".pgm", OUT_PGM, CS_GRAY },
	{ ".ppm", OUT_PPM, CS_RGB },
	{ ".pam", OUT_PAM, CS_CMYK },
	{ ".pbm", OUT_PBM, CS_GRAY },
	{ ".pkm", OUT_PKM, CS_CMYK },
};
#define N_FMT_TABLE (sizeof(FMT_TABLE) / sizeof(FMT_TABLE[0]))

/* ---- REAL file-scope statics (source/tools/muraster.c) that
 * initialise_banding() reads, real names/types. `out` is never dereferenced
 * (only passed through as an opaque token to the stub band-writer ctors). ---- */
static fz_output *out = NULL;
static int output_format;
static int output_cs;
static int min_band_height;
static size_t max_band_memory;

/* ---- REAL render_details (source/tools/muraster.c), verbatim struct,
 * every real field, real names/types/order. ---- */
typedef struct render_details
{
	/* Page */
	fz_page *page;

	/* Display list */
	fz_display_list *list;

	/* Raw bounds */
	fz_rect bounds;

	/* Transformed bounds */
	fz_rect tbounds;

	/* Rounded transformed bounds */
	fz_irect ibounds;

	/* Transform matrix */
	fz_matrix ctm;

	/* How many min band heights are we working in? */
	int band_height_multiple;

	/* What colorspace are we working in? (Adjusted for fallback) */
	int colorspace;

	/* What output format? (Adjusted for fallback) */
	int format;

	/* During the course of the rendering, this keeps track of
	 * how many 'min_band_heights' have been safely rendered. */
	int bands_rendered;

	/* The maximum number of workers we'll try to use. This
	 * will start at the maximum value, and may drop to 0
	 * if we have problems with memory. */
	int num_workers;

	/* The band writer to output the page */
	fz_band_writer *bander;

	/* Number of components in image */
	int n;
} render_details;

/* `GREY_FALLBACK`: pinned to 1 -- the frozen target/ghidra.c shows the real
 * compiled binary contains the `if (color==0){...}` fallback block, i.e.
 * this was nonzero in the real build (source/tools/muraster.c defaults it to
 * 1 whenever FZ_PLOTTERS_N or FZ_PLOTTERS_G+{RGB,CMYK} are enabled). */
#define GREY_FALLBACK 1

/* ---------------------------------------------------------------------- *
 * Link-only stubs for every external symbol initialise_banding()'s body
 * references. Real signatures (include/mupdf/fitz/write-pixmap.h). Each is
 * reached ONLY on inputs that do NOT crash (triggering inputs abort at
 * L1006 above, before any of these); the return value is only ever stored
 * into render->bander (never dereferenced by initialise_banding itself), so
 * a NULL-returning stub fabricates no decode/render behaviour.
 * ---------------------------------------------------------------------- */
fz_band_writer *fz_new_pnm_band_writer(fz_context *ctx, fz_output *out_)
{
	(void) ctx; (void) out_;
	return NULL;
}

fz_band_writer *fz_new_pam_band_writer(fz_context *ctx, fz_output *out_)
{
	(void) ctx; (void) out_;
	return NULL;
}

fz_band_writer *fz_new_pbm_band_writer(fz_context *ctx, fz_output *out_)
{
	(void) ctx; (void) out_;
	return NULL;
}

fz_band_writer *fz_new_pkm_band_writer(fz_context *ctx, fz_output *out_)
{
	(void) ctx; (void) out_;
	return NULL;
}

/* ==========================================================================
 * TARGET FUNCTION -- VERBATIM from target/original_function.c, byte-for-
 * byte, no logic/name/signature changes. (noinline forward decl only, so
 * -O1 keeps its own ASAN/UBSAN backtrace frame; the definition below carries
 * no attribute of its own.)
 * ========================================================================== */
static void initialise_banding(fz_context *ctx, render_details *render, int color) __attribute__((noinline));

static void
initialise_banding(fz_context *ctx, render_details *render, int color)
{
	size_t min_band_mem;
	int bpp, h, w, reps;

	render->colorspace = output_cs;
	render->format = output_format;
#if GREY_FALLBACK != 0
	if (color == 0)
	{
		if (render->colorspace == CS_RGB)
		{
			/* Fallback from PPM to PGM */
			render->colorspace = CS_GRAY;
			render->format = OUT_PGM;
		}
		else if (render->colorspace == CS_CMYK)
		{
			render->colorspace = CS_GRAY;
			if (render->format == OUT_PKM)
				render->format = OUT_PBM;
			else
				render->format = OUT_PGM;
		}
	}
#endif

	switch (render->colorspace)
	{
	case CS_GRAY:
		bpp = 1;
		break;
	case CS_RGB:
		bpp = 2;
		break;
	default:
	case CS_CMYK:
		bpp = 3;
		break;
	}

	w = render->ibounds.x1 - render->ibounds.x0;
	min_band_mem = (size_t)bpp * w * min_band_height;
	reps = (int)(max_band_memory / min_band_mem);
	if (reps < 1)
		reps = 1;

	/* Adjust reps to even out the work between threads */
	if (render->num_workers > 0)
	{
		int runs, num_bands;
		h = render->ibounds.y1 - render->ibounds.y0;
		num_bands = (h + min_band_height - 1) / min_band_height;
		/* num_bands = number of min_band_height bands */
		runs = (num_bands + reps-1) / reps;
		/* runs = number of worker runs of reps min_band_height bands */
		runs = ((runs + render->num_workers - 1) / render->num_workers) * render->num_workers;
		/* runs = number of worker runs rounded up to make use of all our threads */
		reps = (num_bands + runs - 1) / runs;
	}

	render->band_height_multiple = reps;
	render->bands_rendered = 0;

	if (output_format == OUT_PGM || output_format == OUT_PPM)
	{
		render->bander = fz_new_pnm_band_writer(ctx, out);
		render->n = output_format == OUT_PGM ? 1 : 3;
	}
	else if (output_format == OUT_PAM)
	{
		render->bander = fz_new_pam_band_writer(ctx, out);
		render->n = 4;
	}
	else if (output_format == OUT_PBM)
	{
		render->bander = fz_new_pbm_band_writer(ctx, out);
		render->n = 1;
	}
	else if (output_format == OUT_PKM)
	{
		render->bander = fz_new_pkm_band_writer(ctx, out);
		render->n = 4;
	}
}

/* ==========================================================================
 * Harness main()
 *
 * Input encoding (this harness's own, since a direct call bypasses the real
 * PDF page-layout/resolution computation entirely): little-endian --
 *     [0:4)   ibounds.x0   int32
 *     [4:8)   ibounds.x1   int32
 *     [8:12)  ibounds.y0   int32
 *     [12:16) ibounds.y1   int32
 *     [16]    color        uint8 (raw byte; passed to initialise_banding as-is)
 *     [17]    fmt_sel      uint8 (index into FMT_TABLE, mod N_FMT_TABLE)
 * Short/absent fields read as 0. `min_band_height`(32)/`max_band_memory`
 * (5081088)/`render.num_workers`(0) are pinned to the tool's real compiled
 * defaults / real `-T 0` replay recipe (see file header).
 * ========================================================================== */
static int32_t
rd_i32le(const uint8_t *p, size_t n, size_t off)
{
	uint32_t v = 0;
	if (off + 4 <= n) {
		v  =  (uint32_t) p[off];
		v |= ((uint32_t) p[off + 1]) << 8;
		v |= ((uint32_t) p[off + 2]) << 16;
		v |= ((uint32_t) p[off + 3]) << 24;
	}
	return (int32_t) v;
}

int
main(int argc, char **argv)
{
	FILE *f;
	long sz;
	uint8_t *data;
	render_details render;
	int color;
	unsigned fmt_idx;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 1;
	}
	f = fopen(argv[1], "rb");
	if (!f) { perror("fopen"); return 1; }
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	sz = ftell(f);
	if (sz < 0) sz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* HEAP buffer for the attacker-controlled bytes (ASAN redzone directly
	 * past the real bytes) -- never a stack/global buffer. */
	data = (uint8_t *) malloc(sz > 0 ? (size_t) sz : 1);
	if (!data) { fclose(f); return 1; }
	if (sz > 0 && fread(data, 1, (size_t) sz, f) != (size_t) sz) {
		free(data); fclose(f); return 1;
	}
	fclose(f);

	memset(&render, 0, sizeof(render));
	render.ibounds.x0 = rd_i32le(data, (size_t) sz, 0);
	render.ibounds.x1 = rd_i32le(data, (size_t) sz, 4);
	render.ibounds.y0 = rd_i32le(data, (size_t) sz, 8);
	render.ibounds.y1 = rd_i32le(data, (size_t) sz, 12);
	color = (sz > 16) ? (int) data[16] : 1;
	fmt_idx = ((sz > 17) ? (unsigned) data[17] : 0) % N_FMT_TABLE;

	output_format = FMT_TABLE[fmt_idx].format;
	output_cs = FMT_TABLE[fmt_idx].cs;
	min_band_height = 32;                 /* MIN_BAND_HEIGHT default */
	max_band_memory = 5081088;            /* BAND_MEMORY default: 32*8.27f*300*4*16 */
	render.num_workers = 0;               /* real replay recipe's `-T 0` */

	initialise_banding(NULL, &render, color);

	free(data);
	return 0;
}
