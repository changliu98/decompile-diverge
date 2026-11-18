/* ============================================================================
 * cve_0a16b471 -- direct-call harness for imageworsener `iwgif_read_image()`
 * (src/imagew-gif.c), vul_commit 8656405, fix_commit ca3356e / CWE-369
 * divide-by-zero.
 *
 * Fix diff (ca3356eb49fee03e2eaf6b6aff826988c1122d93):
 *     rctx->image_width  = (int)iw_get_ui16le(&rctx->rbuf[4]);
 *     rctx->image_height = (int)iw_get_ui16le(&rctx->rbuf[6]);
 *   + if(rctx->image_width<1 || rctx->image_height<1) {
 *   +     iw_set_error(rctx->ctx, "Invalid image dimensions");
 *   +     goto done;
 *   + }
 * i.e. the vulnerable version never rejects image_width==0/image_height==0.
 *
 * Root cause (traced by hand, no callee needs embedding beyond the ones
 * iwgif_read_image() itself already calls transitively):
 *   iwgif_record_pixel() (imagew-gif.c) does
 *       xi = pixnum % rctx->image_width;
 *   unconditionally, with NO zero check.  When image_width==0 this is an
 *   integer division-by-zero (UB / SIGFPE), reached the moment the LZW
 *   decoder emits its first non-clear/non-eoi code
 *   (lzw_process_code -> lzw_emit_code -> iwgif_record_pixel).
 *
 * WHY image_width==0 is reachable at all despite iw_check_image_dimensions()
 * rejecting w<1/h<1: that check runs in iwgif_init_screen() against the
 * SCREEN dimensions (img->width/height), not the per-image dimensions,
 * whenever rctx->include_screen is true --
 *     if(!rctx->include_screen) { screen_width=image_width; ... }
 *     img->width = rctx->screen_width;
 *     if(!iw_check_image_dimensions(rctx->ctx,img->width,img->height)) return 0;
 * -- so when include_screen (the REAL, verified library default: see
 * imagew-api.c iw_create_context(), "ctx->req.include_screen = 1;") is set,
 * the screen dimensions come from the GIF's logical-screen descriptor
 * (parsed earlier, by iwgif_read_screen_descriptor(), before
 * iwgif_read_image() is ever called) and are completely decoupled from the
 * per-image rctx->image_width/height parsed by iwgif_read_image() itself.
 * A screen descriptor with valid nonzero dimensions plus an image descriptor
 * with image_width==0 sails straight through the dimensions check (it never
 * even looks at image_width) and on into the division. This IS the real
 * attack surface: a two-part malicious GIF (valid logical screen descriptor
 * + zero-width/height image descriptor).
 *
 * DIRECT-CALL DESIGN: a real run parses the file header + logical screen
 * descriptor + optional global color table via iwgif_read_file_header() /
 * iwgif_read_screen_descriptor() / iwgif_read_color_table() *before*
 * iwgif_read_image() is reached; those are prior pipeline stages, not part
 * of iwgif_read_image()'s own body, so per the harness brief they are not
 * embedded -- instead the harness pins the rctx fields they would have
 * produced to real, valid, in-range values (screen_width=640,
 * screen_height=480 -- ordinary GIF screen size; include_screen=1 -- the
 * REAL library default cited above; has_transparency=0; page bookkeeping
 * irrelevant to this function). Every byte of ATTACKER input instead drives
 * exactly what iwgif_read_image() itself parses: the raw wire bytes are fed
 * verbatim through iwgif_read()'s callback, so the harness input format is
 * literally the GIF image-descriptor + local-color-table + LZW-minimum-
 * code-size + sub-block stream this function consumes when reading a real
 * file, starting right where iwgif_read_image() starts reading:
 *     [0:2)  image_left    u16le   (attacker)
 *     [2:4)  image_top     u16le   (attacker)
 *     [4:6)  image_width   u16le   (attacker -- 0 is the trigger)
 *     [6:8)  image_height  u16le   (attacker)
 *     [8]    flags byte: bit6=interlaced, bit7=has_local_ct, bits0-2=ct size
 *     [9:.. ] local color table (3*num_entries bytes), iff has_local_ct
 *     [next] root LZW code size (1 byte, must be in [2,11])
 *     [next..] sub-blocks: 1 size byte, then that many data bytes, repeated,
 *              terminated by a size-0 byte.
 *
 * FAITHFULNESS:
 *   - iwgif_read_image() itself: embedded 100% VERBATIM below, byte-for-byte
 *     from target/original_function.c (diffed to confirm), signature and
 *     body untouched. A __attribute__((noinline)) forward declaration is
 *     added immediately BEFORE the verbatim copy (not inside it) purely so
 *     -O1 cannot collapse its frame out of the ASAN/UBSAN symbolized stack.
 *   - Every real callee it transitively calls on the crash path --
 *     iwgif_read, iwgif_read_color_table, iwgif_record_pixel,
 *     iwgif_init_screen, iwgif_make_row_pointers, lzw_init, lzw_clear,
 *     lzw_emit_code, lzw_add_to_dict, lzw_process_code, lzw_process_bytes --
 *     is embedded VERBATIM from src/imagew-gif.c, same names/bodies/order.
 *   - struct iwgifrcontext / struct lzw_tableentry / struct lzwdeccontext:
 *     the REAL structs verbatim (src/imagew-gif.c), all real field
 *     names/types/order, nothing added or removed.
 *   - struct iw_image / struct iw_palette / struct iw_rgba8color /
 *     struct iw_csdescr / struct iw_color / struct iw_iodescr and the
 *     iw_byte / iw_uint16 / IW_IMGTYPE_x / IW_MALLOCFLAG_x typedefs/macros: the
 *     REAL type definitions verbatim from src/imagew.h.
 *   - iw_malloc_ex/iw_malloc/iw_mallocz/iw_malloc_large/iw_free/iw_zeromem/
 *     iw_get_ui16le/iwpvt_default_malloc/iwpvt_default_free: the REAL
 *     implementations verbatim from src/imagew-util.c (the crash-path
 *     allocator/byte-reader utilities iwgif_init_screen/
 *     iwgif_make_row_pointers/iwgif_read_image actually call).
 *   - iw_check_image_dimensions: the REAL implementation verbatim from
 *     src/imagew-api.c -- this is exactly the gate whose screen-vs-image
 *     decoupling is the root cause, so it must be exact, not stubbed.
 *   - struct iw_context: the real opaque handle threaded through everything
 *     above; it is never allocated/freed by iwgif_read_image() itself (the
 *     real owner is iw_read_gif_file(), which this harness does not call),
 *     so only the specific REAL fields the embedded functions dereference
 *     are kept (mallocfn, freefn, userdata, max_malloc, max_width,
 *     max_height, error_flag -- same real names/types as
 *     src/imagew-internals.h), the rest of that ~100-field struct (image
 *     resize/dither/colorspace/output-format state, all unrelated to GIF
 *     decoding) is omitted rather than fabricated.
 *   - iw_set_error/iw_set_errorf: real signatures, minimal bodies (just set
 *     ctx->error_flag once) -- the real versions format a translated
 *     message string via iw_translate()/iw_strlcpy(), machinery that exists
 *     purely for human-readable diagnostics and has no bearing on this
 *     memory-safety bug; incidental, not on the crash path.
 *
 * main() reads argv[1] into a HEAP buffer (malloc(fsz), no padding) and
 * drives it through iwgif_read_image() via the SAME iw_iodescr/read_fn
 * callback contract iwgif_read() itself uses (a plain in-memory cursor
 * reader) -- the attacker bytes are the file bytes, unmodified, exactly the
 * stream iwgif_read_image() would consume when the real library reads a
 * live GIF file at this point in the format.
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- src/imagew.h (verbatim subset of real typedefs/macros) ---- */

#define IW_IMGTYPE_RGB     0x0010
#define IW_IMGTYPE_RGBA    0x0110

#define IW_MALLOCFLAG_ZEROMEM     0x01
#define IW_MALLOCFLAG_NOERRORS    0x02

#define iw_byte     uint8_t
#define iw_uint16   uint16_t
#define iw_int32    int32_t
#define iw_uint32   uint32_t

/* Colorspace descriptor (real struct, src/imagew.h) */
struct iw_csdescr {
	int cstype;
	int srgb_intent;
	double gamma;
};

/* real struct, src/imagew.h */
struct iw_color {
	double c[4];
};

/* An input or output image (real struct, src/imagew.h) */
struct iw_image {
	int imgtype;
	int bit_depth;
	int sampletype;

	int width, height;

	iw_byte *pixels;
	size_t bpr;

	unsigned int orient_transform;

	int native_grayscale;
	int density_code;
	double density_x, density_y;
	int has_colorkey_trns;
	unsigned int colorkey[3];
	int reduced_maxcolors;
	unsigned int maxcolorcode[5];

	int has_bkgdlabel;
	struct iw_color bkgdlabel;

	int rendering_intent;
};

struct iw_rgba8color {
	iw_byte r, g, b, a;
};

struct iw_palette {
	int num_entries;
	struct iw_rgba8color entry[256];
};

struct iw_context;
struct iw_iodescr;

typedef int (*iw_readfn_type)(struct iw_context *ctx, struct iw_iodescr *iodescr, void *buf, size_t nbytes, size_t *pbytesread);
typedef int (*iw_writefn_type)(struct iw_context *ctx, struct iw_iodescr *iodescr, const void *buf, size_t nbytes);
typedef int (*iw_closefn_type)(struct iw_context *ctx, struct iw_iodescr *iodescr);
typedef int (*iw_getfilesizefn_type)(struct iw_context *ctx, struct iw_iodescr *iodescr, int64_t *pfilesize);
typedef int (*iw_seekfn_type)(struct iw_context *ctx, struct iw_iodescr *iodescr, int64_t offset, int whence);
typedef int (*iw_tellfn_type)(struct iw_context *ctx, struct iw_iodescr *iodescr, int64_t *pfileptr);

/* real struct, src/imagew.h */
struct iw_iodescr {
	void *fp;
	iw_readfn_type read_fn;
	iw_writefn_type write_fn;
	iw_closefn_type close_fn;
	iw_getfilesizefn_type getfilesize_fn;
	iw_seekfn_type seek_fn;
	iw_tellfn_type tell_fn;
};

typedef void* (*iw_mallocfn_type)(void *userdata, unsigned int flags, size_t n);
typedef void (*iw_freefn_type)(void *userdata, void *mem);

/* struct iw_context: the real opaque handle, kept to the specific REAL
 * fields (real names/types, src/imagew-internals.h) that the embedded
 * crash-path functions below actually dereference; the rest of the real
 * ~100-field struct (image pipeline/resize/dither/output-format state) is
 * unrelated to GIF decoding and is omitted, not fabricated. */
struct iw_context {
	iw_mallocfn_type mallocfn;
	iw_freefn_type freefn;
	void *userdata;
	size_t max_malloc;
	int max_width, max_height;
	int error_flag;
};

/* ---- src/imagew-util.c (verbatim) ---- */

void* iwpvt_default_malloc(void *userdata, unsigned int flags, size_t n)
{
	if(flags & IW_MALLOCFLAG_ZEROMEM) {
		return calloc(n,1);
	}
	return malloc(n);
}

void iwpvt_default_free(void *userdata, void *mem)
{
	free(mem);
}

/* iw_set_error/iw_set_errorf: real signatures; the real bodies format a
 * translated diagnostic string via iw_translate()/iw_strlcpy() (pure
 * human-readable-message machinery, incidental to this memory-safety bug,
 * not on the crash path) -- kept to the one real, load-bearing behaviour
 * every caller on the crash path relies on: latch error_flag once. */
static void iw_set_error(struct iw_context *ctx, const char *s)
{
	(void)s;
	if(ctx->error_flag) return;
	ctx->error_flag = 1;
}

static void iw_set_errorf(struct iw_context *ctx, const char *fmt, ...)
{
	(void)fmt;
	if(ctx->error_flag) return;
	ctx->error_flag = 1;
}

static void* iw_malloc_ex(struct iw_context *ctx, unsigned int flags, size_t n)
{
	void *mem;

	if(n>ctx->max_malloc) {
		if(!(flags&IW_MALLOCFLAG_NOERRORS))
			iw_set_error(ctx,"Out of memory");
		return NULL;
	}

	mem = (*ctx->mallocfn)(ctx->userdata,flags,n);

	if(!mem) {
		if(!(flags&IW_MALLOCFLAG_NOERRORS))
			iw_set_error(ctx,"Out of memory");
		return NULL;
	}
	return mem;
}

static void* iw_malloc(struct iw_context *ctx, size_t n)
{
	return iw_malloc_ex(ctx,0,n);
}

static void* iw_mallocz(struct iw_context *ctx, size_t n)
{
	return iw_malloc_ex(ctx,IW_MALLOCFLAG_ZEROMEM,n);
}

static void* iw_malloc_large(struct iw_context *ctx, size_t n1, size_t n2)
{
	if(n1 > ctx->max_malloc/n2) {
		iw_set_error(ctx,"Image too large to process");
		return NULL;
	}
	return iw_malloc_ex(ctx,0,n1*n2);
}

static void iw_free(struct iw_context *ctx, void *mem)
{
	if(!mem) return;
	(*ctx->freefn)(ctx->userdata,mem);
}

static void iw_zeromem(void *mem, size_t n)
{
	memset(mem,0,n);
}

static unsigned int iw_get_ui16le(const iw_byte *b)
{
	return b[0] | (b[1]<<8);
}

/* ---- src/imagew-api.c (verbatim) ----
 * The real gate whose screen-vs-image decoupling is this CVE's root cause;
 * kept exact, not stubbed. */
static int iw_check_image_dimensions(struct iw_context *ctx, int w, int h)
{
	if(w>ctx->max_width || h>ctx->max_height) {
		iw_set_errorf(ctx,"Image dimensions too large (%d\xc3\x97%d)",w,h);
		return 0;
	}

	if(w<1 || h<1) {
		iw_set_errorf(ctx,"Invalid image dimensions (%d\xc3\x97%d)",w,h);
		return 0;
	}

	return 1;
}

/* ============================================================================
 * src/imagew-gif.c (verbatim below this point, down through the end of
 * iwgif_read_image()) -- struct iwgifrcontext + every real function
 * iwgif_read_image() transitively calls on the crash path.
 * ========================================================================== */

struct iwgifrcontext {
	struct iw_iodescr *iodescr;
	struct iw_context *ctx;
	struct iw_image *img;

	struct iw_csdescr csdescr;
	int page; // Page to read. 1=first

	int screen_width, screen_height; // Same as .img->width, .img->height
	int image_width, image_height;
	int image_left, image_top;

	int include_screen; // Do we paint the image onto the "screen", or just extract it?
	int screen_initialized;
	int pages_seen;
	int interlaced;
	int bytes_per_pixel;
	int has_transparency;
	int has_bg_color;
	int bg_color_index;
	int trans_color_index;

	size_t pixels_set; // Number of pixels decoded so far
	size_t total_npixels; // Total number of pixels in the "image" (not the "screen")

	iw_byte **row_pointers;

	struct iw_palette colortable;

	// A buffer used when reading the GIF file.
	// The largest block we need to read is a 256-color palette.
	iw_byte rbuf[768];
};

static int iwgif_read(struct iwgifrcontext *rctx,
		iw_byte *buf, size_t buflen)
{
	int ret;
	size_t bytesread = 0;

	ret = (*rctx->iodescr->read_fn)(rctx->ctx,rctx->iodescr,
		buf,buflen,&bytesread);
	if(!ret || bytesread!=buflen) {
		return 0;
	}
	return 1;
}

// Read a global or local palette into memory.
// ct->num_entries must be set by caller
static int iwgif_read_color_table(struct iwgifrcontext *rctx, struct iw_palette *ct)
{
	int i;
	if(ct->num_entries<1) return 1;

	if(!iwgif_read(rctx,rctx->rbuf,3*ct->num_entries)) return 0;
	for(i=0;i<ct->num_entries;i++) {
		ct->entry[i].r = rctx->rbuf[3*i+0];
		ct->entry[i].g = rctx->rbuf[3*i+1];
		ct->entry[i].b = rctx->rbuf[3*i+2];
	}
	return 1;
}

// Set the (rctx->pixels_set + offset)th pixel in the logical image to the
// color represented by palette entry #coloridx.
static void iwgif_record_pixel(struct iwgifrcontext *rctx, unsigned int coloridx,
		int offset)
{
	struct iw_image *img;
	unsigned int r,g,b,a;
	size_t pixnum;
	size_t xi,yi; // position in image coordinates
	size_t xs,ys; // position in screen coordinates
	iw_byte *ptr;

	img = rctx->img;

	// Figure out which pixel to set.

	pixnum = rctx->pixels_set + offset;
	xi = pixnum%rctx->image_width;
	yi = pixnum/rctx->image_width;
	xs = rctx->image_left + xi;
	ys = rctx->image_top + yi;

	// Make sure the coordinate is within the image, and on the screen.
	if(yi>=(size_t)rctx->image_height) return;
	if(xs>=(size_t)rctx->screen_width) return;
	if(ys>=(size_t)rctx->screen_height) return;

	// Because of how we de-interlace, it's not obvious whether the Y coordinate
	// is on the screen. The easiest way is to check if the row pointer is NULL.
	if(rctx->row_pointers[yi]==NULL) return;

	// Figure out what color to set the pixel to.

	if(coloridx<(unsigned int)rctx->colortable.num_entries) {
		r=rctx->colortable.entry[coloridx].r;
		g=rctx->colortable.entry[coloridx].g;
		b=rctx->colortable.entry[coloridx].b;
		a=rctx->colortable.entry[coloridx].a;
	}
	else {
		return; // Illegal palette index
	}

	// Set the pixel.

	ptr = &rctx->row_pointers[yi][rctx->bytes_per_pixel*xi];
	ptr[0]=r; ptr[1]=g; ptr[2]=b;
	if(img->imgtype==IW_IMGTYPE_RGBA) {
		ptr[3]=a;
	}
}

////////////////////////////////////////////////////////
//                    LZW decoder
////////////////////////////////////////////////////////

struct lzw_tableentry {
	iw_uint16 parent; // pointer to previous table entry (if not a root code)
	iw_uint16 length;
	iw_byte firstchar;
	iw_byte lastchar;
};

struct lzwdeccontext {
	unsigned int root_codesize;
	unsigned int current_codesize;
	int eoi_flag;
	unsigned int oldcode;
	unsigned int pending_code;
	unsigned int bits_in_pending_code;
	unsigned int num_root_codes;
	int ncodes_since_clear;

	unsigned int clear_code;
	unsigned int eoi_code;
	unsigned int last_code_added;

	unsigned int ct_used; // Number of items used in the code table
	struct lzw_tableentry ct[4096]; // Code table
};

static void lzw_init(struct lzwdeccontext *d, unsigned int root_codesize)
{
	unsigned int i;

	iw_zeromem(d,sizeof(struct lzwdeccontext));

	d->root_codesize = root_codesize;
	d->num_root_codes = 1<<d->root_codesize;
	d->clear_code = d->num_root_codes;
	d->eoi_code = d->num_root_codes+1;
	for(i=0;i<d->num_root_codes;i++) {
		d->ct[i].parent = 0;
		d->ct[i].length = 1;
		d->ct[i].lastchar = (iw_byte)i;
		d->ct[i].firstchar = (iw_byte)i;
	}
}

static void lzw_clear(struct lzwdeccontext *d)
{
	d->ct_used = d->num_root_codes+2;
	d->current_codesize = d->root_codesize+1;
	d->ncodes_since_clear=0;
	d->oldcode=0;
}

// Decode an LZW code to one or more pixels, and record it in the image.
static void lzw_emit_code(struct iwgifrcontext *rctx, struct lzwdeccontext *d,
		unsigned int first_code)
{
	unsigned int code;
	code = first_code;

	// An LZW code may decode to more than one pixel. Note that the pixels for
	// an LZW code are decoded in reverse order (right to left).

	while(1) {
		iwgif_record_pixel(rctx, (unsigned int)d->ct[code].lastchar, (int)(d->ct[code].length-1));
		if(d->ct[code].length<=1) break;
		// The codes are structured as a "forest" (multiple trees).
		// Go to the parent code, which will have a length 1 less than this one.
		code = (unsigned int)d->ct[code].parent;
	}

	// Track the total number of pixels decoded in this image.
	rctx->pixels_set += d->ct[first_code].length;
}

// Add a code to the dictionary.
// Sets d->last_code_added to the position where it was added.
// Returns 1 if successful, 0 if table is full.
static int lzw_add_to_dict(struct lzwdeccontext *d, unsigned int oldcode, iw_byte val)
{
	static const unsigned int last_code_of_size[] = {
		// The first 3 values are unused.
		0,0,0,7,15,31,63,127,255,511,1023,2047,4095
	};
	unsigned int newpos;

	if(d->ct_used>=4096) {
		d->last_code_added = 0;
		return 0;
	}

	newpos = d->ct_used;
	d->ct_used++;

	d->ct[newpos].parent = (iw_uint16)oldcode;
	d->ct[newpos].length = d->ct[oldcode].length + 1;
	d->ct[newpos].firstchar = d->ct[oldcode].firstchar;
	d->ct[newpos].lastchar = val;

	// If we've used the last code of this size, we need to increase the codesize.
	if(newpos == last_code_of_size[d->current_codesize]) {
		if(d->current_codesize<12) {
			d->current_codesize++;
		}
	}

	d->last_code_added = newpos;
	return 1;
}

// Process a single LZW code that was read from the input stream.
static int lzw_process_code(struct iwgifrcontext *rctx, struct lzwdeccontext *d,
		unsigned int code)
{
	if(code==d->eoi_code) {
		d->eoi_flag=1;
		return 1;
	}

	if(code==d->clear_code) {
		lzw_clear(d);
		return 1;
	}

	d->ncodes_since_clear++;

	if(d->ncodes_since_clear==1) {
		// Special case for the first code.
		lzw_emit_code(rctx,d,code);
		d->oldcode = code;
		return 1;
	}

	// Is code in code table?
	if(code < d->ct_used) {
		// Yes, code is in table.
		lzw_emit_code(rctx,d,code);

		// Let k = the first character of the translation of the code.
		// Add <oldcode>k to the dictionary.
		lzw_add_to_dict(d,d->oldcode,d->ct[code].firstchar);
	}
	else {
		// No, code is not in table.
		if(d->oldcode>=d->ct_used) {
			iw_set_error(rctx->ctx,"GIF decoding error");
			return 0;
		}

		// Let k = the first char of the translation of oldcode.
		// Add <oldcode>k to the dictionary.
		if(lzw_add_to_dict(d,d->oldcode,d->ct[d->oldcode].firstchar)) {
			// Write <oldcode>k to the output stream.
			lzw_emit_code(rctx,d,d->last_code_added);
		}
	}
	d->oldcode = code;

	return 1;
}

// Decode as much as possible of the provided LZW-encoded data.
// Any unfinished business is recorded, to be continued the next time
// this function is called.
static int lzw_process_bytes(struct iwgifrcontext *rctx, struct lzwdeccontext *d,
	iw_byte *data, size_t data_size)
{
	size_t i;
	int b;
	int retval=0;

	for(i=0;i<data_size;i++) {
		// Look at the bits one at a time.
		for(b=0;b<8;b++) {
			if(d->eoi_flag) { // Stop if we've seen an EOI (end of image) code.
				retval=1;
				goto done;
			}

			if(data[i]&(1<<b))
				d->pending_code |= 1<<d->bits_in_pending_code;
			d->bits_in_pending_code++;

			// When we get enough bits to form a complete LZW code, process it.
			if(d->bits_in_pending_code >= d->current_codesize) {
				if(!lzw_process_code(rctx,d,d->pending_code)) goto done;
				d->pending_code=0;
				d->bits_in_pending_code=0;
			}
		}
	}
	retval=1;

done:
	return retval;
}

////////////////////////////////////////////////////////

// Allocate and set up the global "screen".
static int iwgif_init_screen(struct iwgifrcontext *rctx)
{
	struct iw_image *img;
	int bg_visible=0;
	int retval=0;

	if(rctx->screen_initialized) return 1;
	rctx->screen_initialized = 1;

	img = rctx->img;

	if(!rctx->include_screen) {
		// If ->include_screen is disabled, pretend the screen is the same size as
		// the GIF image, and pretend the GIF image is positioned at (0,0).
		rctx->screen_width = rctx->image_width;
		rctx->screen_height = rctx->image_height;
		rctx->image_left = 0;
		rctx->image_top = 0;
	}

	img->width = rctx->screen_width;
	img->height = rctx->screen_height;
	if(!iw_check_image_dimensions(rctx->ctx,img->width,img->height)) {
		return 0;
	}

	if(rctx->image_left>0 || rctx->image_top>0 ||
		(rctx->image_left+rctx->image_width < rctx->screen_width) ||
		(rctx->image_top+rctx->image_height < rctx->screen_height) )
	{
		// Image does not cover the entire "screen". We'll make the exposed
		// regions of the screen transparent, so set a flag to let us know we
		// need an image type that supports transparency.
		bg_visible = 1;
	}

	// Allocate IW image
	if(rctx->has_transparency || bg_visible) {
		rctx->bytes_per_pixel=4;
		img->imgtype = IW_IMGTYPE_RGBA;
	}
	else {
		rctx->bytes_per_pixel=3;
		img->imgtype = IW_IMGTYPE_RGB;
	}
	img->bit_depth = 8;
	img->bpr = rctx->bytes_per_pixel * img->width;

	img->pixels = (iw_byte*)iw_malloc_large(rctx->ctx, img->bpr, img->height);
	if(!img->pixels) goto done;

	// Start by clearing the screen to black, or transparent black.
	iw_zeromem(img->pixels,img->bpr*img->height);

	retval=1;
done:
	return retval;
}

// Make an array of pointers into the global screen, which point to the
// start of each row in the local image. This will be useful for
// de-interlacing.
static int iwgif_make_row_pointers(struct iwgifrcontext *rctx)
{
	struct iw_image *img;
	int pass;
	int startrow, rowskip;
	int rowcount;
	int row;

	if(rctx->row_pointers) iw_free(rctx->ctx,rctx->row_pointers);
	rctx->row_pointers = (iw_byte**)iw_malloc(rctx->ctx, sizeof(iw_byte*)*rctx->image_height);
	if(!rctx->row_pointers) return 0;

	img = rctx->img;

	if(rctx->interlaced) {
		// Image is interlaced. Rearrange the row pointers, so that it will be
		// de-interlaced as it is decoded.
		rowcount=0;
		for(pass=1;pass<=4;pass++) {
			if(pass==1) { startrow=0; rowskip=8; }
			else if(pass==2) { startrow=4; rowskip=8; }
			else if(pass==3) { startrow=2; rowskip=4; }
			else { startrow=1; rowskip=2; }

			for(row=startrow;row<rctx->image_height;row+=rowskip) {
				if(rctx->image_top+row < rctx->screen_height) {
					rctx->row_pointers[rowcount] = &img->pixels[(rctx->image_top+row)*img->bpr + (rctx->image_left)*rctx->bytes_per_pixel];
				}
				else {
					rctx->row_pointers[rowcount] = NULL;
				}
				rowcount++;
			}
		}
	}
	else {
		// Image is not interlaced.
		for(row=0;row<rctx->image_height;row++) {
			if(rctx->image_top+row < rctx->screen_height) {
				rctx->row_pointers[row] = &img->pixels[(rctx->image_top+row)*img->bpr + (rctx->image_left)*rctx->bytes_per_pixel];
			}
			else {
				rctx->row_pointers[row] = NULL;
			}
		}
	}
	return 1;
}

/* noinline: forward declaration only, added SO THAT -O1 cannot inline this
 * frame out of the symbolized crash stack; the definition immediately
 * below is the untouched, byte-for-byte verbatim copy of
 * target/original_function.c. */
static int iwgif_read_image(struct iwgifrcontext *rctx) __attribute__((noinline));

static int iwgif_read_image(struct iwgifrcontext *rctx)
{
	int retval=0;
	struct lzwdeccontext d;
	size_t subblocksize;
	int has_local_ct;
	int local_ct_size;

	unsigned int root_codesize;

	// Read image header information
	if(!iwgif_read(rctx,rctx->rbuf,9)) goto done;

	rctx->image_left = (int)iw_get_ui16le(&rctx->rbuf[0]);
	rctx->image_top = (int)iw_get_ui16le(&rctx->rbuf[2]);
	// image_left and _top may be updated in iwgif_init_screen().

	rctx->image_width = (int)iw_get_ui16le(&rctx->rbuf[4]);
	rctx->image_height = (int)iw_get_ui16le(&rctx->rbuf[6]);

	rctx->interlaced = (int)((rctx->rbuf[8]>>6)&0x01);

	has_local_ct = (int)((rctx->rbuf[8]>>7)&0x01);
	if(has_local_ct) {
		local_ct_size = (int)(rctx->rbuf[8]&0x07);
		rctx->colortable.num_entries = 1<<(1+local_ct_size);
	}

	if(has_local_ct) {
		// We only support one image, so we don't need to keep both a global and a
		// local color table. If an image has both, the local table will overwrite
		// the global one.
		if(!iwgif_read_color_table(rctx,&rctx->colortable)) goto done;
	}

	// Make the transparent color transparent.
	if(rctx->has_transparency) {
	    rctx->colortable.entry[rctx->trans_color_index].a = 0;
	}

	// Read LZW code size
	if(!iwgif_read(rctx,rctx->rbuf,1)) goto done;
	root_codesize = (unsigned int)rctx->rbuf[0];

	// The spec does not allow the "minimum code size" to be less than 2.
	// Sizes >=12 are impossible to support.
	// There's no reason for the size to be larger than 8, but the spec
	// does not seem to forbid it.
	if(root_codesize<2 || root_codesize>11) {
		iw_set_error(rctx->ctx,"Invalid LZW minimum code size");
		goto done;
	}

	// The creation of the global "screen" was deferred until now, to wait until
	// we know whether the image has transparency.
	// (And if !rctx->include_screen, to wait until we know the size of the image.)
	if(!iwgif_init_screen(rctx)) goto done;

	rctx->total_npixels = (size_t)rctx->image_width * (size_t)rctx->image_height;

	if(!iwgif_make_row_pointers(rctx)) goto done;

	lzw_init(&d,root_codesize);
	lzw_clear(&d);

	while(1) {
		// Read size of next subblock
		if(!iwgif_read(rctx,rctx->rbuf,1)) goto done;
		subblocksize = (size_t)rctx->rbuf[0];
		if(subblocksize==0) break;

		// Read next subblock
		if(!iwgif_read(rctx,rctx->rbuf,subblocksize)) goto done;
		if(!lzw_process_bytes(rctx,&d,rctx->rbuf,subblocksize)) goto done;

		if(d.eoi_flag) break;

		// Stop if we reached the end of the image. We don't care if we've read an
		// EOI code or not.
		if(rctx->pixels_set >= rctx->total_npixels) break;
	}

	retval=1;

done:
	return retval;
}

/* ==========================================================================
 * Harness main()
 *
 * Reads argv[1] into a HEAP buffer, wires it up as the byte stream
 * iwgif_read()'s callback contract expects (a plain forward-only in-memory
 * cursor -- exactly what a real file-backed iw_iodescr provides), pins the
 * rctx fields that would have been set by the PRIOR pipeline stages
 * (iwgif_read_file_header/iwgif_read_screen_descriptor, not part of
 * iwgif_read_image()'s own body) to real, valid, in-range values, and calls
 * iwgif_read_image() exactly once.
 * ========================================================================== */

struct membuf {
	const iw_byte *data;
	size_t size;
	size_t pos;
};

static int membuf_read_fn(struct iw_context *ctx, struct iw_iodescr *iodescr,
	void *buf, size_t nbytes, size_t *pbytesread)
{
	struct membuf *mb = (struct membuf*)iodescr->fp;
	size_t avail = mb->size - mb->pos;
	size_t n = (nbytes<avail) ? nbytes : avail;
	(void)ctx;
	if(n>0) memcpy(buf, mb->data+mb->pos, n);
	mb->pos += n;
	*pbytesread = n;
	return 1;
}

int main(int argc, char **argv)
{
	FILE *f;
	long sz;
	iw_byte *data;
	struct iw_context ctx;
	struct iw_image img;
	struct iw_iodescr iodescr;
	struct membuf mb;
	struct iwgifrcontext rctx;

	if(argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 1;
	}
	f = fopen(argv[1], "rb");
	if(!f) { perror("fopen"); return 1; }
	if(fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	sz = ftell(f);
	if(sz < 0) sz = 0;
	if(fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* HEAP buffer for the attacker-controlled bytes. */
	data = (iw_byte*)malloc(sz > 0 ? (size_t)sz : 1);
	if(!data) { fclose(f); return 1; }
	if(sz > 0 && fread(data, 1, (size_t)sz, f) != (size_t)sz) {
		free(data); fclose(f); return 1;
	}
	fclose(f);

	/* struct iw_context: real defaults from iw_create_context()
	 * (imagew-api.c): max_malloc=IW_DEFAULT_MAX_MALLOC(2000000000),
	 * max_width=max_height=IW_DEFAULT_MAX_DIMENSION(40000), default
	 * malloc/free wrappers. */
	memset(&ctx, 0, sizeof(ctx));
	ctx.mallocfn = iwpvt_default_malloc;
	ctx.freefn = iwpvt_default_free;
	ctx.userdata = NULL;
	ctx.max_malloc = 2000000000u;
	ctx.max_width = 40000;
	ctx.max_height = 40000;
	ctx.error_flag = 0;

	memset(&img, 0, sizeof(img));

	mb.data = data;
	mb.size = (size_t)sz;
	mb.pos = 0;
	memset(&iodescr, 0, sizeof(iodescr));
	iodescr.fp = &mb;
	iodescr.read_fn = membuf_read_fn;

	memset(&rctx, 0, sizeof(rctx));
	rctx.ctx = &ctx;
	rctx.img = &img;
	rctx.iodescr = &iodescr;
	rctx.page = 1;
	/* Real library default (iw_create_context(): ctx->req.include_screen=1),
	 * decouples the logical-screen dims from the per-image dims -- the
	 * actual attack surface for this CVE. */
	rctx.include_screen = 1;
	rctx.screen_initialized = 0;
	/* Stand-in for a real, valid logical screen descriptor already parsed
	 * by iwgif_read_screen_descriptor() (a prior pipeline stage, not part
	 * of iwgif_read_image()'s own body) -- ordinary GIF screen size. */
	rctx.screen_width = 640;
	rctx.screen_height = 480;
	rctx.has_transparency = 0;

	iwgif_read_image(&rctx);

	if(rctx.row_pointers) iw_free(&ctx, rctx.row_pointers);
	if(img.pixels) iw_free(&ctx, img.pixels);
	free(data);
	return 0;
}
