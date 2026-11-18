/*
 * Direct-call crash harness for CVE-2018-13785 (libpng, integer-overflow ->
 * divide-by-zero, CWE-369 / CWE-190; case.json baseline.cwe is recorded as
 * "CWE-UNKNOWN").
 *
 * Target function: png_check_chunk_length() from pngrutil.c.
 *
 * Real-world trigger site (baseline.dedup_token
 * "png_check_chunk_length--png_read_chunk_header--png_read_info"):
 * png_read_info() -> png_read_chunk_header() reads a chunk's 4-byte length +
 * 4-byte type from the PNG stream and calls
 *   png_check_chunk_length(png_ptr, length);
 * whenever the chunk type is IDAT (chunk_name == png_IDAT), using the
 * already-parsed IHDR fields (png_ptr->width/height/bit_depth/channels/
 * interlaced) that were stashed on png_ptr by an earlier png_set_IHDR() /
 * png_handle_IHDR() call.
 *
 * The bug (baseline.summary "AddressSanitizer: FPE .../pngrutil.c:3172:44
 * in png_check_chunk_length", column 44 is the '/' in
 * "PNG_UINT_32_MAX/row_factor"):
 *
 *   size_t row_factor =
 *      (png_ptr->width * png_ptr->channels * (png_ptr->bit_depth > 8? 2: 1)
 *       + 1 + (png_ptr->interlaced? 6: 0));
 *   if (png_ptr->height > PNG_UINT_32_MAX/row_factor)   <-- divide by zero
 *
 * `width`, `channels`, `bit_depth`, `interlaced` are all `unsigned
 * int`/`unsigned char`-sized operands, so the whole right-hand side of the
 * row_factor assignment is computed in 32-bit unsigned arithmetic (only the
 * FINAL 32-bit result is widened to size_t on assignment). If
 * `width * channels * factor` wraps around to exactly (0xFFFFFFFF - extra)
 * modulo 2^32 -- e.g. channels==3 (RGB), bit_depth<=8 (factor==1),
 * interlaced==0, width==0x55555555 (0x55555555*3 == 0xFFFFFFFF exactly) --
 * then row_factor becomes 0 after the "+1" wraps 0x100000000 down to 0, and
 * the very next line divides PNG_UINT_32_MAX by that zero row_factor ->
 * SIGFPE, which ASAN's signal handler reports as "AddressSanitizer: FPE".
 * This requires chunk_name == png_IDAT (the divide only happens inside the
 * `if (png_ptr->chunk_name == png_IDAT)` block).
 *
 * This harness reproduces the call directly: it reads the attacker-
 * controlled bytes from argv[1] (a file path) into a HEAP buffer (malloc),
 * parses a small fixed record out of that buffer into the fields of a
 * heap-allocated png_struct (mirroring the real png_create_read_struct()
 * heap allocation of png_ptr), and calls png_check_chunk_length() exactly
 * once, exactly as png_read_chunk_header() does.
 *
 * `png_struct` here is a MINIMAL re-declaration (real tag/typedef names
 * from png.h/pngstruct.h) carrying only the fields png_check_chunk_length()
 * actually dereferences: chunk_name, user_chunk_malloc_max, width, height,
 * bit_depth, channels, interlaced. This harness is a fresh, self-contained
 * translation unit (not linked against the rest of libpng), so it does not
 * need the full ~450-field real png_struct layout -- only the real field
 * NAMES and real field TYPES matter for the pasted function body to compile
 * and behave identically to the real struct. PNG_SET_USER_LIMITS_SUPPORTED
 * is defined (matches scripts/pnglibconf.h.prebuilt, the default config
 * used by this project's build) so the same `#ifdef` branch that the real
 * build takes is taken here too.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* ---- minimal real typedefs, from pngconf.h ---- */
typedef unsigned char  png_byte;
typedef unsigned int   png_uint_32;
typedef size_t         png_alloc_size_t;   /* pngconf.h: size_t unless PNG_SMALL_SIZE_T */
typedef const char    *png_const_charp;

/* ---- minimal real struct, from pngstruct.h (struct png_struct_def) ----
 * Only the fields png_check_chunk_length() touches; real names/types. */
struct png_struct_def
{
   png_alloc_size_t user_chunk_malloc_max;
   png_uint_32      width;
   png_uint_32      height;
   png_uint_32      chunk_name;
   png_byte         interlaced;
   png_byte         bit_depth;
   png_byte         channels;
};
typedef struct png_struct_def png_struct;
/* real png.h: `typedef const png_struct * PNG_RESTRICT png_const_structrp;`
 * -- PNG_RESTRICT (a `restrict`/`__restrict` qualifier on some compilers)
 * is an optimizer hint only, dropped here as behaviorally irrelevant. */
typedef const png_struct *png_const_structrp;
typedef png_struct       *png_structp;

/* ---- minimal real macros, from png.h / pngpriv.h ---- */
#define PNG_UINT_31_MAX ((png_uint_32)0x7fffffffL)   /* png.h */
#define PNG_UINT_32_MAX ((png_uint_32)(-1))          /* png.h */
/* png.h: `#ifdef PNG_SET_USER_LIMITS_SUPPORTED` guards png_ptr->user_chunk_malloc_max
 * lookup; this is ON by default (scripts/pnglibconf.h.prebuilt) -- keep the
 * same branch the real, default-configured build takes. */
#define PNG_SET_USER_LIMITS_SUPPORTED 1
/* pngpriv.h: #define PNG_U32(b1,b2,b3,b4) (b1<<24|b2<<16|b3<<8|b4) and the
 * chunk-type table entry `#define png_IDAT PNG_U32(73,68,65,84)` ('I','D','A','T'). */
#define PNG_U32(b1,b2,b3,b4) \
   (((png_uint_32)(b1) << 24) | ((png_uint_32)(b2) << 16) | \
    ((png_uint_32)(b3) << 8)  |  (png_uint_32)(b4))
#define png_IDAT PNG_U32(73,68,65,84)
/* pngdebug.h: no-op unless PNG_DEBUG is set (it isn't, by default). */
#define png_debug2(l, m, p1, p2) ((void)0)

/* Stub of the real (non-static, PNGAPI-exported) declaration in png.h:
 *   PNG_EXPORTA(103, void, png_chunk_error, (png_const_structrp png_ptr,
 *       png_const_charp error_message), PNG_NORETURN);
 * png_chunk_error() is fatal/non-returning in the real library (it reports
 * the message and longjmp()s out via png_ptr->jmp_buf_local, which this
 * harness does not model since jmp_buf/setjmp machinery is unrelated to the
 * divide-by-zero mechanism under test -- png_check_chunk_length() never
 * reaches this call on ANY input that also reaches the divide, since the
 * divide/SIGFPE fires first, before this line, whenever it fires at all).
 * A clean, ordinary exit(0) here is exactly as safe/non-crashing as the
 * real "chunk data is too large" error path (a well-formed application
 * error, not a memory-safety bug). */
static void
png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message)
{
   (void)png_ptr;
   fprintf(stderr, "png_chunk_error: %s\n", error_message);
   exit(0);
}

/* discourage inlining so png_check_chunk_length keeps its own ASAN/SIGFPE
 * backtrace frame (declaration only -- the definition below is untouched/
 * verbatim, byte-identical to target/original_function.c) */
void png_check_chunk_length(png_const_structrp png_ptr, const png_uint_32 length)
   __attribute__((noinline));

/* ==== BEGIN verbatim target/original_function.c (byte-for-byte) ==== */
void /* PRIVATE */
png_check_chunk_length(png_const_structrp png_ptr, const png_uint_32 length)
{
   png_alloc_size_t limit = PNG_UINT_31_MAX;

# ifdef PNG_SET_USER_LIMITS_SUPPORTED
   if (png_ptr->user_chunk_malloc_max > 0 &&
       png_ptr->user_chunk_malloc_max < limit)
      limit = png_ptr->user_chunk_malloc_max;
# elif PNG_USER_CHUNK_MALLOC_MAX > 0
   if (PNG_USER_CHUNK_MALLOC_MAX < limit)
      limit = PNG_USER_CHUNK_MALLOC_MAX;
# endif
   if (png_ptr->chunk_name == png_IDAT)
   {
      png_alloc_size_t idat_limit = PNG_UINT_31_MAX;
      size_t row_factor =
         (png_ptr->width * png_ptr->channels * (png_ptr->bit_depth > 8? 2: 1)
          + 1 + (png_ptr->interlaced? 6: 0));
      if (png_ptr->height > PNG_UINT_32_MAX/row_factor)
         idat_limit=PNG_UINT_31_MAX;
      else
         idat_limit = png_ptr->height * row_factor;
      row_factor = row_factor > 32566? 32566 : row_factor;
      idat_limit += 6 + 5*(idat_limit/row_factor+1); /* zlib+deflate overhead */
      idat_limit=idat_limit < PNG_UINT_31_MAX? idat_limit : PNG_UINT_31_MAX;
      limit = limit < idat_limit? idat_limit : limit;
   }

   if (length > limit)
   {
      png_debug2(0," length = %lu, limit = %lu",
         (unsigned long)length,(unsigned long)limit);
      png_chunk_error(png_ptr, "chunk data is too large");
   }
}
/* ==== END verbatim target/original_function.c ==== */

/* ---- input record parsed out of the heap-allocated attacker buffer ----
 * Custom fixed 23-byte big-endian record (this harness's own corpus
 * format -- png_check_chunk_length() is called directly, so there is no
 * PNG file to re-parse; each field maps 1:1 onto a real png_ptr field /
 * the real `length` argument that a genuine png_read_chunk_header() call
 * would have supplied):
 *   [0:4)   chunk_name             (default png_IDAT if truncated)
 *   [4:8)   width
 *   [8:12)  height
 *   [12]    bit_depth
 *   [13]    channels
 *   [14]    interlaced
 *   [15:19) length                 (2nd argument to the target function)
 *   [19:23) user_chunk_malloc_max
 * Missing trailing bytes default to 0 (chunk_name defaults to png_IDAT so
 * short/empty inputs still exercise the vulnerable branch). */
static png_uint_32
rd_u32(const unsigned char *b, size_t n, size_t off, png_uint_32 deflt)
{
   if (off + 4 > n)
      return deflt;
   return ((png_uint_32)b[off] << 24) | ((png_uint_32)b[off+1] << 16) |
          ((png_uint_32)b[off+2] << 8) | (png_uint_32)b[off+3];
}

static png_byte
rd_u8(const unsigned char *b, size_t n, size_t off, png_byte deflt)
{
   if (off >= n)
      return deflt;
   return (png_byte)b[off];
}

int
main(int argc, char **argv)
{
   FILE *f;
   long sz;
   size_t rd;
   unsigned char *raw;   /* heap buffer holding the attacker-controlled
                           * corpus-file bytes */
   png_structp png_ptr;
   png_uint_32 length;

   if (argc < 2)
   {
      fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
      return 1;
   }

   f = fopen(argv[1], "rb");
   if (f == NULL)
   {
      perror("fopen");
      return 1;
   }
   if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
   sz = ftell(f);
   if (sz < 0) { fclose(f); return 1; }
   if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

   /* Attacker-controlled bytes MUST live on the heap: malloc exactly the
    * file size (0 is fine -- malloc(0) still returns a valid, freeable
    * heap pointer) and fread the whole file into it, no over-read. */
   raw = (unsigned char *)malloc((size_t)sz > 0 ? (size_t)sz : 1);
   if (raw == NULL) { fclose(f); return 1; }
   rd = (sz > 0) ? fread(raw, 1, (size_t)sz, f) : 0;
   fclose(f);

   /* png_ptr itself is also heap-allocated, exactly like the real
    * png_create_read_struct() -> malloc(sizeof(png_struct)) the genuine
    * caller performs before png_read_info()/png_read_chunk_header() ever
    * run. */
   png_ptr = (png_structp)malloc(sizeof(png_struct));
   if (png_ptr == NULL) { free(raw); return 1; }
   memset(png_ptr, 0, sizeof(*png_ptr));

   png_ptr->chunk_name             = rd_u32(raw, rd, 0, png_IDAT);
   png_ptr->width                  = rd_u32(raw, rd, 4, 0);
   png_ptr->height                 = rd_u32(raw, rd, 8, 0);
   png_ptr->bit_depth              = rd_u8 (raw, rd, 12, 8);
   png_ptr->channels               = rd_u8 (raw, rd, 13, 1);
   png_ptr->interlaced             = rd_u8 (raw, rd, 14, 0);
   length                          = rd_u32(raw, rd, 15, 0);
   png_ptr->user_chunk_malloc_max  = (png_alloc_size_t)rd_u32(raw, rd, 19, 0);

   /* Exactly the real call site in png_read_chunk_header():
    *   png_check_chunk_length(png_ptr, length);            */
   png_check_chunk_length(png_ptr, length);

   printf("ok chunk_name=%08x width=%u height=%u bit_depth=%u channels=%u "
          "interlaced=%u length=%u\n",
          png_ptr->chunk_name, png_ptr->width, png_ptr->height,
          png_ptr->bit_depth, png_ptr->channels, png_ptr->interlaced,
          length);

   free(png_ptr);
   free(raw);
   return 0;
}
