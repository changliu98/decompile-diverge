/* Direct-call crash harness for CVE-2019-16347 (ngiflib, WritePixels).
 *
 * Real bug (ngiflib.c): WritePixels() copies `n` decoded LZW pixel-index
 * bytes into the image's frame buffer (context->frbuff_p), advancing to the
 * next scanline every `i->width` pixels. For a NON-interlaced image
 * (i->interlaced == 0, context.pass stays 0 for the whole decode) the
 * scanline-wrap switch statement's `case 0:` unconditionally does
 * `context->curY++` with NO check against `p->height` (only the
 * `interlaced` pass 1..4 branches check `curY >= p->height`). So if more
 * pixel bytes are handed to WritePixels than the declared canvas
 * (i->width * i->height) actually holds, WritePixels keeps happily
 * recomputing `context->frbuff_p = p->frbuff.p32 + curY*p->width + posX`
 * past the end of the heap-allocated frame buffer and then WRITES through
 * it -- a heap-buffer-overflow WRITE (CWE-787) entirely inside
 * WritePixels, on the exact line the frozen baseline crashes at
 * (ngiflib.c:213, `*(context->frbuff_p.p32++) = GifIndexToTrueColor(...)`,
 * the true-color / non-indexed branch, reached here via
 * i->gce.transparent_flag=0 and g->mode holding no NGIFLIB_MODE_INDEXED bit).
 *
 * Harness setup: a declared 8x8 true-color canvas -> frame buffer malloc'd
 * to EXACTLY 8*8*sizeof(u32) = 256 bytes (mirrors LoadGif's own
 * `ngiflib_malloc(4*(long)g->height*(long)g->width)`). WritePixels is then
 * called ONCE, directly, with `n` = the raw input file's length (the file
 * bytes themselves become the heap-allocated `pixels` index array -- the
 * ATTACKER DATA lives entirely on the heap, matching the fuzzer's own
 * frame). Because the declared canvas holds exactly 8*8=64 pixels, any
 * n > 64 walks WritePixels straight off the end of the 256-byte frame
 * buffer (first OOB element at n=65); n <= 64 stays fully in-bounds.
 *
 * The 256-entry palette exists purely so GifIndexToTrueColor(palette, v)
 * (v = an arbitrary input byte, u8 range 0..255) can never itself fault --
 * the crash under test must be the frame-buffer WRITE inside WritePixels,
 * not an incidental palette READ.
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/* ---- minimal REAL type defs, verbatim from ngiflib.h (non-__VBCC__ branch) ---- */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

/* ---- real macros, verbatim from ngiflib.h ---- */
#define ngiflib_malloc malloc
#define ngiflib_free free
#define ngiflib_memcpy memcpy
#define ngiflib_memset memset
#define ngiflib_memcmp memcmp
#include <string.h>

#define NGIFLIB_MODE_TRUE_COLOR (0x00)
#define NGIFLIB_MODE_INDEXED    (0x01)
#define NGIFLIB_MODE_FROM_FILE  (0x00)
#define NGIFLIB_MODE_FROM_MEM   (0x02)

/* ---- real struct/union defs, verbatim from ngiflib.h ---- */
/* (NGIFLIB_ENABLE_CALLBACKS and NGIFLIB_INDEXED_ONLY and NGIFLIB_NO_FILE are
 * all left UNDEFINED, exactly as in the project's default (non-embedded)
 * build -- so every struct below matches the header's default-branch shape
 * field-for-field.) */

struct ngiflib_rgb {
	u8 r, g ,b;
};
u32 GifIndexToTrueColor(struct ngiflib_rgb * palette, u8 v);

union ngiflib_pixpointer {
	u8 * p8;
	u32 * p32;
};

/* struct stoquant un Graphic Control Extension */
struct ngiflib_gce {
	u16 delay_time;	/* 1/100 of seconds or 0 */
	u8 transparent_color;
	u8 disposal_method:3;	/* see below */
	u8 user_input_flag:1;	/* User input is : 0 = not expected. 1 = expected. */
	u8 transparent_flag:1;
	u8 gce_present:1;
};

/* struct stoquant les parametres relatifs a une image. */
struct ngiflib_img {
	struct ngiflib_img * next;
	struct ngiflib_gif * parent;
	struct ngiflib_rgb * palette;
	struct ngiflib_gce gce;
	u16 ncolors;
	u16 width;
	u16 height;
	u16 posX;
	u16 posY;
	u8 interlaced;
	u8 sort_flag;		/* is local palette sorted by color frequency ? */
	u8 localpalbits;	/* bits/pixel ! (de 1 a 8) */
	u8 imgbits;	/* bits mini du code LZW (de 2 a 9 ?) */
};

/* utilises juste pour la decompression */
struct ngiflib_decode_context {
	union ngiflib_pixpointer frbuff_p;	/* current offset in frame buffer */
	const u8 * srcbyte;
	u16 Xtogo;
	u16 curY;
	u16 lbyte;
	u16 max;	/* maximum value = (1 << nbbit) - 1 */
	u8 pass;	/* current pass of interlaced image decoding */
	u8 restbyte;
	u8 nbbit;	/* bits courants du code LZW */
	u8 restbits;
	u8 byte_buffer[256];	/* for get word */
};

/* struct stoquant les parametres relatifs a un fichier gif */
struct ngiflib_gif {
	struct ngiflib_img * first_img;
	struct ngiflib_img * cur_img;
	struct ngiflib_rgb * palette;
	union {
		FILE * file;
		const u8 * bytes;
	} input;	/* used by GetByte */
	union ngiflib_pixpointer frbuff;	/* frame buffer    */
	FILE * log;		/* to output log   */
	int nimg;
	int netscape_loop_count;	/* from netscape animation extension */
	u16 ncolors;
	u16 width;
	u16 height;
	u8 backgroundindex;
	u8 pixaspectratio;	/* width/height = (pixaspectratio + 15) / 64 */
	u8 imgbits;
	u8 colorresolution;
	u8 sort_flag;
	u8 mode; /* voir avant */
	u8 signature[7];	/* 0 terminated  !=) */
};

/* ---- real callee, verbatim from ngiflib.c (WritePixels' fault-path callee) ---- */

u32 GifIndexToTrueColor(struct ngiflib_rgb * palette, u8 v) {
	return palette[v].b | (palette[v].g << 8) | (palette[v].r << 16);
}


/* ---- target function, VERBATIM from dataset/cve_7f6ff08f/target/original_function.c ---- */

static void WritePixels(struct ngiflib_img * i, struct ngiflib_decode_context * context, const u8 * pixels, u16 n) {
	u16 tocopy;	
	struct ngiflib_gif * p = i->parent;

	while(n > 0) {
		tocopy = (context->Xtogo < n) ? context->Xtogo : n;
		if(!i->gce.transparent_flag) {
#ifndef NGIFLIB_INDEXED_ONLY
			if(p->mode & NGIFLIB_MODE_INDEXED) {
#endif /* NGIFLIB_INDEXED_ONLY */
				ngiflib_memcpy(context->frbuff_p.p8, pixels, tocopy);
				pixels += tocopy;
				context->frbuff_p.p8 += tocopy;
#ifndef NGIFLIB_INDEXED_ONLY
			} else {
				int j;
				for(j = (int)tocopy; j > 0; j--) {
					*(context->frbuff_p.p32++) =
					   GifIndexToTrueColor(i->palette, *pixels++);
				}
			}
#endif /* NGIFLIB_INDEXED_ONLY */
		} else {
			int j;
#ifndef NGIFLIB_INDEXED_ONLY
			if(p->mode & NGIFLIB_MODE_INDEXED) {
#endif /* NGIFLIB_INDEXED_ONLY */
				for(j = (int)tocopy; j > 0; j--) {
					if(*pixels != i->gce.transparent_color) *context->frbuff_p.p8 = *pixels;
					pixels++;
					context->frbuff_p.p8++;
				}
#ifndef NGIFLIB_INDEXED_ONLY
			} else {
				for(j = (int)tocopy; j > 0; j--) {
					if(*pixels != i->gce.transparent_color) {
						*context->frbuff_p.p32 = GifIndexToTrueColor(i->palette, *pixels);
					}
					pixels++;
					context->frbuff_p.p32++;
				}
			}
#endif /* NGIFLIB_INDEXED_ONLY */
		}
		context->Xtogo -= tocopy;
		if(context->Xtogo == 0) {
			#ifdef NGIFLIB_ENABLE_CALLBACKS
			if(p->line_cb) p->line_cb(p, context->line_p, context->curY);
			#endif /* NGIFLIB_ENABLE_CALLBACKS */
			context->Xtogo = i->width;
			switch(context->pass) {
			case 0:
				context->curY++;
				break;
			case 1:	/* 1st pass : every eighth row starting from 0 */
				context->curY += 8;
				if(context->curY >= p->height) {
					context->pass++;
					context->curY = i->posY + 4;
				}
				break;
			case 2:	/* 2nd pass : every eighth row starting from 4 */
				context->curY += 8;
				if(context->curY >= p->height) {
					context->pass++;
					context->curY = i->posY + 2;
				}
				break;
			case 3:	/* 3rd pass : every fourth row starting from 2 */
				context->curY += 4;
				if(context->curY >= p->height) {
					context->pass++;
					context->curY = i->posY + 1;
				}
				break;
			case 4:	/* 4th pass : every odd row */
				context->curY += 2;
				break;
			}
#ifndef NGIFLIB_INDEXED_ONLY
			if(p->mode & NGIFLIB_MODE_INDEXED) {
#endif /* NGIFLIB_INDEXED_ONLY */
				#ifdef NGIFLIB_ENABLE_CALLBACKS
				context->line_p.p8 = p->frbuff.p8 + (u32)context->curY*p->width;
				context->frbuff_p.p8 = context->line_p.p8 + i->posX;
				#else
				context->frbuff_p.p8 = p->frbuff.p8 + (u32)context->curY*p->width + i->posX;
				#endif /* NGIFLIB_ENABLE_CALLBACKS */
#ifndef NGIFLIB_INDEXED_ONLY
			} else {
				#ifdef NGIFLIB_ENABLE_CALLBACKS
				context->line_p.p32 = p->frbuff.p32 + (u32)context->curY*p->width;
				context->frbuff_p.p32 = context->line_p.p32 + i->posX;
				#else
				context->frbuff_p.p32 = p->frbuff.p32 + (u32)context->curY*p->width + i->posX;
				#endif /* NGIFLIB_ENABLE_CALLBACKS */
			}
#endif /* NGIFLIB_INDEXED_ONLY */
		}
		n -= tocopy;
	}
}

/* ---- driver ---- */

#define CANVAS_W 8
#define CANVAS_H 8

int main(int argc, char **argv) {
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 64; }
	fseek(fp, 0, SEEK_END);
	long flen = ftell(fp);
	if (flen < 0) flen = 0;
	fseek(fp, 0, SEEK_SET);

	/* Read the raw input bytes into a HEAP buffer (never stack/global) -- these
	 * become the attacker-controlled `pixels` index array passed straight to
	 * WritePixels(); its length IS `n`. */
	size_t L = (size_t)flen;
	u8 *pixels = (u8 *)malloc(L ? L : 1);
	if (!pixels) { fclose(fp); return 64; }
	size_t got = L ? fread(pixels, 1, L, fp) : 0;
	fclose(fp);
	(void)got;
	u16 n = (u16)(L > 65535 ? 65535 : L);

	/* Declared canvas: 8x8 true-color, frame buffer malloc'd to EXACTLY its
	 * real size (mirrors LoadGif's ngiflib_malloc(4*height*width)). */
	u32 *frbuff = (u32 *)malloc(sizeof(u32) * CANVAS_W * CANVAS_H);
	if (!frbuff) { free(pixels); return 64; }

	/* Palette sized to cover every possible u8 index -- so
	 * GifIndexToTrueColor() can never itself be the fault site. */
	struct ngiflib_rgb *palette = (struct ngiflib_rgb *)calloc(256, sizeof(struct ngiflib_rgb));
	if (!palette) { free(pixels); free(frbuff); return 64; }

	struct ngiflib_gif g;
	memset(&g, 0, sizeof(g));
	g.mode = NGIFLIB_MODE_TRUE_COLOR; /* truecolor: NOT NGIFLIB_MODE_INDEXED
	                                    -> WritePixels takes the p32 branch,
	                                    same as the frozen baseline crash. */
	g.width = CANVAS_W;
	g.height = CANVAS_H;
	g.frbuff.p32 = frbuff;

	struct ngiflib_img img;
	memset(&img, 0, sizeof(img));
	img.parent = &g;
	img.palette = palette;
	img.width = CANVAS_W;
	img.height = CANVAS_H;
	img.posX = 0;
	img.posY = 0;
	img.interlaced = 0;	/* pass stays 0 for the whole decode -> the curY++
	                        scanline-wrap case that has NO height bound check */
	img.gce.transparent_flag = 0;

	struct ngiflib_decode_context ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.frbuff_p.p32 = frbuff;
	ctx.Xtogo = img.width;
	ctx.curY = img.posY;
	ctx.pass = 0;

	WritePixels(&img, &ctx, pixels, n);

	free(pixels);
	free(frbuff);
	free(palette);
	return 0;
}
