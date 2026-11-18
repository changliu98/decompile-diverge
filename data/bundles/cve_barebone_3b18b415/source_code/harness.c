/*
 * Direct-call crash harness for cve_3b18b415 (CVE-2020-35538, libjpeg-turbo
 * jdmerge.c, merged_2v_upsample()). Embeds the vulnerable function VERBATIM
 * plus its real, directly-crashing callee jcopy_sample_rows() (jutils.c) and
 * calls merged_2v_upsample() directly with heap-allocated, attacker-derived
 * arguments -- no dependency on the rest of libjpeg-turbo (no jdapistd.c /
 * jdmainct.c / jpeg_skip_scanlines() machinery).
 *
 * Bug recap (matches baseline dedup_token
 * "jcopy_sample_rows--merged_2v_upsample--process_data_simple_main" / summary
 * "AddressSanitizer: SEGV /work/jutils.c:112:14 in jcopy_sample_rows",
 * CWE-476): merged_2v_upsample() is the "2:1 vertical sampling, may need a
 * spare row" upsampler control routine. When upsample->spare_full is TRUE it
 * hands back the previously-saved spare row via
 *     jcopy_sample_rows(&upsample->spare_row, 0, output_buf + *out_row_ctr,
 *                        0, 1, size);
 * with NO validation that `output_buf` (an application/caller-supplied
 * scanline-pointer array), the specific row pointer at *out_row_ctr, or
 * upsample->spare_row itself are non-NULL. In the real project,
 * jpeg_skip_scanlines() (called when the application skips output rows, a
 * djpeg feature) manipulates the SAME struct fields as the "unmerged"
 * upsampler's private struct, but merged upsampling uses a *different*
 * private layout -- so it corrupts/omits initialization of the merged
 * upsampler's fields, and process_data_simple_main() ends up invoking
 * merged_2v_upsample() with an output_buf (or spare_row) that was never
 * validly set up -> jcopy_sample_rows() dereferences a NULL/near-NULL
 * pointer -> SIGSEGV, entirely inside merged_2v_upsample()'s call to
 * jcopy_sample_rows() (upstream fix commit 9120a247436e84c0b4eea828cb11e8f -
 * "Fix jpeg_skip_scanlines() segfault w/merged upsamp").
 *
 * This harness reproduces the SAME crash shape -- a NULL/near-NULL pointer
 * fed into jcopy_sample_rows() via merged_2v_upsample()'s spare_full==TRUE
 * branch -- directly, without needing jpeg_skip_scanlines()/jdmainct.c: it
 * builds the my_upsampler private struct and the output_buf array by hand
 * and leaves exactly the pointer(s) the real bug leaves unset. Three
 * variants of the SAME root cause are exercised (see the input convention
 * below) for corpus diversity, all landing on the identical call site.
 *
 * `target/original_function.c` is embedded byte-for-byte below (see the
 * VERBATIM markers) -- logic, names, and signature untouched. All type/
 * struct/macro definitions above it are copied from the REAL libjpeg-turbo
 * headers (jmorecfg.h / jpeglib.h / jpegint.h / jinclude.h) using their real
 * names; struct jpeg_decompress_struct is trimmed to just the three fields
 * merged_2v_upsample() actually dereferences (this program is the only user
 * of the type, so there is no cross-TU ABI dependency on the full real
 * layout -- see the comment at its definition).
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * Minimal, faithful subset of the real libjpeg-turbo headers.
 * ============================================================ */

/* ---- jmorecfg.h ---- */
typedef unsigned char JSAMPLE;         /* BITS_IN_JSAMPLE == 8 (default) */
typedef unsigned int  JDIMENSION;
typedef int  boolean;
#define FALSE   0
#define TRUE    1
#define METHODDEF(type)         static type
#define GLOBAL(type)             type

/* ---- jpeglib.h ---- */
typedef JSAMPLE   *JSAMPROW;    /* ptr to one image row of pixel samples. */
typedef JSAMPROW  *JSAMPARRAY;  /* ptr to some rows (a 2-D sample array) */
typedef JSAMPARRAY *JSAMPIMAGE; /* a 3-D sample array: top index is color */

/* J_COLOR_SPACE, verbatim from jpeglib.h (only JCS_RGB and JCS_RGB565 are
 * actually referenced by merged_2v_upsample(), but the real enum is small
 * and kept whole/real rather than truncated). */
typedef enum {
  JCS_UNKNOWN,
  JCS_GRAYSCALE,
  JCS_RGB,
  JCS_YCbCr,
  JCS_CMYK,
  JCS_YCCK,
  JCS_EXT_RGB,
  JCS_EXT_RGBX,
  JCS_EXT_BGR,
  JCS_EXT_BGRX,
  JCS_EXT_XBGR,
  JCS_EXT_XRGB,
  JCS_EXT_RGBA,
  JCS_EXT_BGRA,
  JCS_EXT_ABGR,
  JCS_EXT_ARGB,
  JCS_RGB565
} J_COLOR_SPACE;

struct jpeg_decompress_struct;
typedef struct jpeg_decompress_struct *j_decompress_ptr;

/* ---- jpegint.h ---- */
typedef long JLONG;

struct jpeg_upsampler {
  void (*start_pass) (j_decompress_ptr cinfo);
  void (*upsample) (j_decompress_ptr cinfo, JSAMPIMAGE input_buf,
                    JDIMENSION *in_row_group_ctr,
                    JDIMENSION in_row_groups_avail, JSAMPARRAY output_buf,
                    JDIMENSION *out_row_ctr, JDIMENSION out_rows_avail);
  boolean need_context_rows;    /* TRUE if need rows above & below */
};

/* MINIMAL subset of the real struct jpeg_decompress_struct (jpeglib.h):
 * only the three fields merged_2v_upsample() dereferences
 * (cinfo->upsample, cinfo->out_color_space, cinfo->output_width). Real
 * field names and real types; this program is the sole user of the type
 * (no cross-TU ABI dependency), so the full ~150-field real struct is not
 * required for a byte-identical splice. */
struct jpeg_decompress_struct {
  struct jpeg_upsampler *upsample;
  J_COLOR_SPACE out_color_space; /* colorspace for output */
  JDIMENSION output_width;       /* scaled image width */
};

/* ---- jinclude.h ---- */
#define MEMCOPY(dest, src, size) \
  memcpy((void *)(dest), (const void *)(src), (size_t)(size))

/* ============================================================
 * jdmerge.c: my_upsampler private struct, embedded VERBATIM (it directly
 * precedes merged_2v_upsample() in the real file).
 * ============================================================ */
typedef struct {
  struct jpeg_upsampler pub;    /* public fields */

  /* Pointer to routine to do actual upsampling/conversion of one row group */
  void (*upmethod) (j_decompress_ptr cinfo, JSAMPIMAGE input_buf,
                    JDIMENSION in_row_group_ctr, JSAMPARRAY output_buf);

  /* Private state for YCC->RGB conversion */
  int *Cr_r_tab;                /* => table for Cr to R conversion */
  int *Cb_b_tab;                /* => table for Cb to B conversion */
  JLONG *Cr_g_tab;              /* => table for Cr to G conversion */
  JLONG *Cb_g_tab;              /* => table for Cb to G conversion */

  /* For 2:1 vertical sampling, we produce two output rows at a time.
   * We need a "spare" row buffer to hold the second output row if the
   * application provides just a one-row buffer; we also use the spare
   * to discard the dummy last row if the image height is odd.
   */
  JSAMPROW spare_row;
  boolean spare_full;           /* T if spare buffer is occupied */

  JDIMENSION out_row_width;     /* samples per output row */
  JDIMENSION rows_to_go;        /* counts rows remaining in image */
} my_upsampler;

typedef my_upsampler *my_upsample_ptr;

/* ============================================================
 * jutils.c:jcopy_sample_rows, embedded VERBATIM. This is the real callee --
 * and the real crash site (baseline: jutils.c:112:14) -- that
 * merged_2v_upsample() invokes on its spare_full==TRUE path.
 * ============================================================ */
GLOBAL(void)
jcopy_sample_rows(JSAMPARRAY input_array, int source_row,
                  JSAMPARRAY output_array, int dest_row, int num_rows,
                  JDIMENSION num_cols)
/* Copy some rows of samples from one place to another.
 * num_rows rows are copied from input_array[source_row++]
 * to output_array[dest_row++]; these areas may overlap for duplication.
 * The source and destination arrays must be at least as wide as num_cols.
 */
{
  register JSAMPROW inptr, outptr;
  register size_t count = (size_t)(num_cols * sizeof(JSAMPLE));
  register int row;

  input_array += source_row;
  output_array += dest_row;

  for (row = num_rows; row > 0; row--) {
    inptr = *input_array++;
    outptr = *output_array++;
    MEMCOPY(outptr, inptr, count);
  }
}

/* ============================================================
 * target/original_function.c, embedded VERBATIM.
 * ============================================================ */
METHODDEF(void)
merged_2v_upsample(j_decompress_ptr cinfo, JSAMPIMAGE input_buf,
                   JDIMENSION *in_row_group_ctr,
                   JDIMENSION in_row_groups_avail, JSAMPARRAY output_buf,
                   JDIMENSION *out_row_ctr, JDIMENSION out_rows_avail)
/* 2:1 vertical sampling case: may need a spare row. */
{
  my_upsample_ptr upsample = (my_upsample_ptr)cinfo->upsample;
  JSAMPROW work_ptrs[2];
  JDIMENSION num_rows;          /* number of rows returned to caller */

  if (upsample->spare_full) {
    /* If we have a spare row saved from a previous cycle, just return it. */
    JDIMENSION size = upsample->out_row_width;
    if (cinfo->out_color_space == JCS_RGB565)
      size = cinfo->output_width * 2;
    jcopy_sample_rows(&upsample->spare_row, 0, output_buf + *out_row_ctr, 0, 1,
                      size);
    num_rows = 1;
    upsample->spare_full = FALSE;
  } else {
    /* Figure number of rows to return to caller. */
    num_rows = 2;
    /* Not more than the distance to the end of the image. */
    if (num_rows > upsample->rows_to_go)
      num_rows = upsample->rows_to_go;
    /* And not more than what the client can accept: */
    out_rows_avail -= *out_row_ctr;
    if (num_rows > out_rows_avail)
      num_rows = out_rows_avail;
    /* Create output pointer array for upsampler. */
    work_ptrs[0] = output_buf[*out_row_ctr];
    if (num_rows > 1) {
      work_ptrs[1] = output_buf[*out_row_ctr + 1];
    } else {
      work_ptrs[1] = upsample->spare_row;
      upsample->spare_full = TRUE;
    }
    /* Now do the upsampling. */
    (*upsample->upmethod) (cinfo, input_buf, *in_row_group_ctr, work_ptrs);
  }

  /* Adjust counts */
  *out_row_ctr += num_rows;
  upsample->rows_to_go -= num_rows;
  /* When the buffer is emptied, declare this input row group consumed */
  if (!upsample->spare_full)
    (*in_row_group_ctr)++;
}
/* ---- end verbatim ---- */

/* ============================================================
 * main(): reads argv[1] into a HEAP buffer and drives merged_2v_upsample()
 * directly, exactly once, with heap-allocated caller-side state built from
 * the file bytes.
 *
 * Input convention (harness-only -- there is no such marker in a real JPEG
 * stream; a direct-call harness necessarily invents SOME mapping from "a
 * corpus file" to "the arguments the target function actually takes"):
 *
 *   byte0 & 3 == 0 : TRIGGER variant A -- output_buf itself is NULL
 *                    (the exact CVE-2020-35538 mechanism: "NULL pointer
 *                    passed to jcopy_sample_rows"). output_buf + *out_row_ctr
 *                    is then an invalid near-NULL pointer, and
 *                    jcopy_sample_rows's `outptr = *output_array++;`
 *                    dereferences it directly -> SEGV.
 *   byte0 & 3 == 1 : TRIGGER variant B -- output_buf is a real, valid array
 *                    of row pointers, but the ONE row pointer at the target
 *                    index (*out_row_ctr) was never allocated (NULL) --
 *                    jcopy_sample_rows reads the (valid) array slot fine,
 *                    then MEMCOPY() WRITES through outptr==NULL -> SEGV.
 *   byte0 & 3 == 2 : TRIGGER variant C -- the INPUT side is NULL: the spare
 *                    row (upsample->spare_row) was never allocated --
 *                    jcopy_sample_rows's `inptr = *input_array++;` yields
 *                    NULL and MEMCOPY() READS from it -> SEGV.
 *   byte0 & 3 == 3 : SAFE -- everything (output array, target row slot,
 *                    spare row) is validly heap-allocated and correctly
 *                    sized; merged_2v_upsample() completes normally.
 *
 *   byte1        : selects which row-array slot is the "target" index
 *                  (*out_row_ctr), mod 4.
 *   byte2,byte3   : (little-endian) selects out_row_width / the copy size,
 *                  clamped to [1,512] -- purely for corpus diversity; every
 *                  variant above crashes (or stays safe) for ANY width in
 *                  that range.
 *   remaining bytes: fill data for the spare-row heap buffer -- irrelevant
 *                  to whether the crash triggers, present purely so the
 *                  corpus carries varying-length heap-resident attacker
 *                  bytes (as required), mirroring how in the real bug the
 *                  crash is independent of the row's pixel content once the
 *                  vulnerable pointer state is present.
 * ============================================================ */
int
main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
    return 1;
  }

  FILE *f = fopen(argv[1], "rb");
  if (!f) { fprintf(stderr, "cannot open %s\n", argv[1]); return 1; }
  if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
  long len = ftell(f);
  if (len < 0) { fclose(f); return 1; }
  if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

  /* REQUIRED: heap buffer for the attacker-controlled bytes. */
  unsigned char *buf = NULL;
  if (len > 0) {
    buf = malloc((size_t)len);
    if (!buf) { fclose(f); return 1; }
    size_t rd = fread(buf, 1, (size_t)len, f);
    fclose(f);
    if (rd != (size_t)len) { free(buf); return 1; }
  } else {
    fclose(f);
  }

  unsigned mode   = (len > 0) ? (buf[0] & 3u) : 3u;
  unsigned idxsel = (len > 1) ? (buf[1] & 3u) : 0u;
  unsigned wsel   = 1u;
  if (len > 3)      wsel = (unsigned)buf[2] | ((unsigned)buf[3] << 8);
  else if (len > 2) wsel = buf[2];
  JDIMENSION width = 1u + (wsel % 512u);   /* out_row_width, always >= 1 */

  const unsigned N_ROWS = 4;               /* capacity of output_buf array */
  if (idxsel >= N_ROWS) idxsel = N_ROWS - 1;

  /* ---- caller-side state, all heap-allocated ---- */
  struct jpeg_decompress_struct cinfo_s;
  memset(&cinfo_s, 0, sizeof(cinfo_s));
  cinfo_s.out_color_space = JCS_RGB;   /* != JCS_RGB565 -> size = out_row_width */
  cinfo_s.output_width = width;

  my_upsampler *ups = calloc(1, sizeof(*ups));
  if (!ups) { free(buf); return 1; }
  ups->spare_full = TRUE;      /* always take the jcopy_sample_rows branch --
                                 * that branch is the ONLY one this CVE's
                                 * crash occurs in. */
  ups->out_row_width = width;
  ups->rows_to_go = 100;       /* unused on this path; a sane placeholder */
  cinfo_s.upsample = &ups->pub;

  /* real spare-row backing buffer, filled from the file's own bytes. */
  unsigned char *spare_backing = malloc((size_t)width);
  if (!spare_backing) { free(ups); free(buf); return 1; }
  const long fill_off = 4;
  for (JDIMENSION i = 0; i < width; i++)
    spare_backing[i] = (len > fill_off + (long)i)
                          ? buf[fill_off + i] : (unsigned char)(i & 0xFF);

  JSAMPROW *out_rows_backing = NULL;
  unsigned char *out_row_data = NULL;
  JSAMPARRAY output_buf = NULL;

  switch (mode) {
  case 0:
    /* Variant A: output_buf itself NULL. */
    output_buf = NULL;
    ups->spare_row = spare_backing;
    break;

  case 1:
    /* Variant B: valid array, but the target slot is NULL. */
    out_rows_backing = calloc(N_ROWS, sizeof(JSAMPROW));
    out_row_data = malloc((size_t)width * N_ROWS);
    if (!out_rows_backing || !out_row_data) {
      free(out_rows_backing); free(out_row_data);
      free(spare_backing); free(ups); free(buf);
      return 1;
    }
    for (unsigned i = 0; i < N_ROWS; i++)
      out_rows_backing[i] = out_row_data + (size_t)i * width;
    out_rows_backing[idxsel] = NULL;      /* the one hole */
    output_buf = out_rows_backing;
    ups->spare_row = spare_backing;
    break;

  case 2:
    /* Variant C: valid output array, but spare_row (input side) NULL. */
    out_rows_backing = calloc(N_ROWS, sizeof(JSAMPROW));
    out_row_data = malloc((size_t)width * N_ROWS);
    if (!out_rows_backing || !out_row_data) {
      free(out_rows_backing); free(out_row_data);
      free(spare_backing); free(ups); free(buf);
      return 1;
    }
    for (unsigned i = 0; i < N_ROWS; i++)
      out_rows_backing[i] = out_row_data + (size_t)i * width;
    output_buf = out_rows_backing;
    ups->spare_row = NULL;
    break;

  default:
    /* mode == 3: SAFE -- everything valid and correctly sized. */
    out_rows_backing = calloc(N_ROWS, sizeof(JSAMPROW));
    out_row_data = malloc((size_t)width * N_ROWS);
    if (!out_rows_backing || !out_row_data) {
      free(out_rows_backing); free(out_row_data);
      free(spare_backing); free(ups); free(buf);
      return 1;
    }
    for (unsigned i = 0; i < N_ROWS; i++)
      out_rows_backing[i] = out_row_data + (size_t)i * width;
    output_buf = out_rows_backing;
    ups->spare_row = spare_backing;
    break;
  }

  JDIMENSION out_row_ctr_val = idxsel;
  JDIMENSION in_row_group_ctr_val = 0;

  merged_2v_upsample(&cinfo_s, NULL, &in_row_group_ctr_val, 0, output_buf,
                      &out_row_ctr_val, 0);

  printf("merged_2v_upsample returned normally "
         "(mode=%u width=%u idx=%u)\n", mode, width, out_row_ctr_val);

  free(out_row_data);
  free(out_rows_backing);
  free(spare_backing);
  free(ups);
  free(buf);
  return 0;
}
