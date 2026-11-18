/* Direct-call crash harness for CVE-2019-20912 (libredwg), CWE-127
 * (stack-buffer under-read).
 *
 * Target: bit_write_UMC() in src/bits.c, embedded VERBATIM below together with
 * its real callees (bit_write_RC / bit_chain_alloc / bit_advance_position, also
 * VERBATIM from src/bits.c) so the whole call chain the bug actually executes
 * through is present, with no other project files.
 *
 * Bug (fixed by b84c2cab55948a5ee70860779b2640913e3ee1ed, "encode: protect from
 * stack under-flow"): bit_write_UMC() base-128-encodes `val` into a 5-byte stack
 * array `byte[5]`, scans forward for the first byte (0..3) whose low 7 bits are
 * non-zero, and if that byte's 0x40 bit is set, decrements the index once more
 * ("continuation" heuristic). If the scan already stopped at index 0 AND that
 * byte's 0x40 bit is set, the unconditional `i--;` drives i to -1, and the very
 * next statement `byte[i] &= 0x7f;` reads-then-writes `byte[-1]` -- one byte
 * below the on-stack array (ASAN: stack-buffer-underflow, READ access).
 *
 * Trigering condition (real names, derived from the verbatim logic below): the
 * scan-loop breaks at i==0 iff byte[0]'s low 7 bits are non-zero, i.e. iff any
 * of value bits 28..34 is set; the immediate re-decrement additionally needs
 * byte[0]'s bit 0x40 set, i.e. bit 34 of `val`. Bit 34 of `val` alone implies
 * both (it IS one of bits 28..34, and it maps directly onto byte[0]'s 0x40
 * bit) -- so the single condition "bit 34 of val is set" is necessary and
 * sufficient. In little-endian byte terms: byte index 4 (0-based, the 5th byte
 * of the input) having its 0x04 bit set. This matches the frozen reference PoC
 * (io/input/0 = 00 00 00 00 04 00 00 00 LE = 0x400000000, bit 34 set) and the
 * upstream fix commit's own example (val == 0x400000000).
 *
 * main() reads argv[1] into a HEAP buffer (malloc), safely folds up to its
 * first 8 bytes little-endian into a BITCODE_UMC value (the type every real
 * call site in src/encode.c passes -- e.g. bit_write_UMC(dat, handleoff) --
 * an integer, not a raw attacker pointer), and calls the real, unmodified
 * bit_write_UMC() exactly once with a real Bit_Chain set up the way every
 * real call site sets one up.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal, faithful type/struct/macro defs, REAL names, copied from
 *      source_code/include/dwg.h + source_code/src/bits.h + source_code/src/logging.h
 *      (no logic changes -- these are just the declarations bit_write_UMC's
 *      call chain needs to compile standalone). ---- */

/* dwg.h:145 */
typedef unsigned long BITCODE_UMC;

/* dwg.h ~220 (DWG_VERSION_TYPE enum) */
typedef enum DWG_VERSION_TYPE
{
  R_INVALID,
  R_1_1,
  R_1_2,
  R_1_4,
  R_2_0,
  R_2_1,
  R_2_5,
  R_2_6,
  R_9,
  R_10,
  R_11,
  R_13,
  R_14,
  R_2000,
  R_2004,
  R_2007,
  R_2010,
  R_2013,
  R_2018,
  R_AFTER
} Dwg_Version_Type;

/* bits.h: Structure for DWG-files raw data storage */
typedef struct _bit_chain
{
  unsigned char *chain;
  long unsigned int size;
  long unsigned int byte;
  unsigned char bit;
  FILE *fh;
  Dwg_Version_Type version;
  Dwg_Version_Type from_version;
  unsigned char opts; /* from dwg->opts, see DWG_OPTS_* */
} Bit_Chain;

/* dwg.h: #define DWG_OPTS_LOGLEVEL 0xf */
#define DWG_OPTS_LOGLEVEL 0xf

/* logging.h (trimmed to what bit_advance_position uses) */
#define DWG_LOGLEVEL_NONE 0
#define DWG_LOGLEVEL_ERROR 1
#ifndef DWG_LOGLEVEL
#  define DWG_LOGLEVEL DWG_LOGLEVEL_ERROR
#endif
#define HANDLER fprintf
#define OUTPUT stderr
#define LOG(level, args...)                                                   \
  {                                                                           \
    if (DWG_LOGLEVEL >= DWG_LOGLEVEL_##level)                                 \
      {                                                                       \
        HANDLER (OUTPUT, args);                                               \
      }                                                                       \
  }
#define LOG_ERROR(args...)                                                    \
  {                                                                           \
    if (DWG_LOGLEVEL >= DWG_LOGLEVEL_ERROR)                                   \
      {                                                                       \
        HANDLER (OUTPUT, "ERROR: ");                                          \
        LOG (ERROR, args)                                                     \
        HANDLER (OUTPUT, "\n");                                               \
      }                                                                       \
  }

static unsigned int loglevel;

/* ---- real callees, VERBATIM from source_code/src/bits.c ---- */

/* Advance bits (forward or backward)
 */
void
bit_advance_position (Bit_Chain *dat, long advance)
{
  long endpos = (long)dat->bit + advance;
  if (dat->byte >= dat->size - 1 && endpos > 7)
    {
      // but allow pointing to the very end.
      if (dat->byte != dat->size - 1 || dat->bit != 0)
        {
          loglevel = dat->opts & DWG_OPTS_LOGLEVEL;
          LOG_ERROR ("%s buffer overflow at pos %lu, size %lu, advance by %ld",
                     __FUNCTION__, dat->byte, dat->size, advance)
        }
      dat->byte = dat->size - 1;
      dat->bit = 0;
      return;
    }
  if ((long)dat->byte + (endpos / 8) < 0)
    {
      loglevel = dat->opts & DWG_OPTS_LOGLEVEL;
      LOG_ERROR ("buffer underflow at pos %lu, size %lu, advance by %ld",
                 dat->byte, dat->size, advance)
      dat->byte = 0;
      dat->bit = 0;
      return;
    }
  dat->byte += (endpos >> 3);
  dat->bit = endpos & 7;
}

/*
 * Allocates memory space for bit_chain
 * adds 10 4kB pages.
 */
#define CHAIN_BLOCK 40960
void
bit_chain_alloc (Bit_Chain *dat)
{
  if (dat->size == 0)
    {
      dat->chain = (unsigned char *)calloc (1, CHAIN_BLOCK);
      dat->size = CHAIN_BLOCK;
      dat->byte = 0;
      dat->bit = 0;
    }
  else
    {
      dat->chain
          = (unsigned char *)realloc (dat->chain, dat->size + CHAIN_BLOCK);
      dat->size += CHAIN_BLOCK;
    }
}

/** Write 1 byte (raw char).
 */
void
bit_write_RC (Bit_Chain *dat, unsigned char value)
{
  unsigned char byte;
  unsigned char remainder;

  if (dat->byte >= dat->size - 1)
    bit_chain_alloc (dat);

  if (dat->bit == 0)
    {
      dat->chain[dat->byte] = value;
    }
  else
    {
      byte = dat->chain[dat->byte];
      remainder = byte & (0xff << (8 - dat->bit));
      dat->chain[dat->byte] = remainder | (value >> dat->bit);
      if (dat->byte < dat->size - 1)
        {
          byte = dat->chain[dat->byte + 1];
          remainder = byte & (0xff >> dat->bit);
          dat->chain[dat->byte + 1] = remainder | (value << (8 - dat->bit));
        }
    }

  bit_advance_position (dat, 8);
}

/* ---- TARGET FUNCTION, VERBATIM from target/original_function.c ---- */

/** Write 1 modular char (max 5 bytes, unsigned).
 */
void
bit_write_UMC (Bit_Chain *dat, BITCODE_UMC val)
{
  int i, j;
  int negative;
  unsigned char byte[5];
  BITCODE_UMC mask;
  BITCODE_UMC value;

  value = val;
  mask = 0x0000007f;
  for (i = 4, j = 0; i >= 0; i--, j += 7)
    {
      byte[i] = (unsigned char)((value & mask) >> j);
      byte[i] |= 0x80;
      mask = mask << 7;
    }
  for (i = 0; i < 4; i++)
    if (byte[i] & 0x7f)
      break;

  if (byte[i] & 0x40)
    i--;
  byte[i] &= 0x7f;
  for (j = 4; j >= i; j--)
    bit_write_RC (dat, byte[j]);
}

/* ---- driver ---- */

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <input>\n", argv[0]);
      return 1;
    }
  FILE *f = fopen (argv[1], "rb");
  if (!f)
    {
      perror ("fopen");
      return 1;
    }
  fseek (f, 0, SEEK_END);
  long fsz = ftell (f);
  if (fsz < 0)
    fsz = 0;
  fseek (f, 0, SEEK_SET);

  /* Heap buffer for the raw attacker bytes (required: never stack/global). */
  unsigned char *buf = (unsigned char *)malloc (fsz > 0 ? (size_t)fsz : 1);
  size_t n = fsz > 0 ? fread (buf, 1, (size_t)fsz, f) : 0;
  fclose (f);

  /* Fold up to the first 8 bytes little-endian into the BITCODE_UMC value
   * every real bit_write_UMC() call site passes (an integer, e.g. handleoff /
   * obj->handlestream_size in src/encode.c) -- bounded read, no OOB access on
   * the input buffer itself. */
  unsigned long val = 0;
  size_t take = n < 8 ? n : 8;
  for (size_t k = 0; k < take; k++)
    val |= ((unsigned long)buf[k]) << (8 * k);
  free (buf);

  /* Real Bit_Chain, set up the way every real call site sets one up. */
  Bit_Chain dat;
  memset (&dat, 0, sizeof (dat));
  dat.size = 4096;
  dat.chain = (unsigned char *)calloc (1, dat.size);
  dat.byte = 0;
  dat.bit = 0;
  dat.version = R_2010;
  dat.from_version = R_2010;
  dat.opts = 0;

  bit_write_UMC (&dat, (BITCODE_UMC)val);

  printf ("val=0x%lx wrote=%lu bytes\n", val, dat.byte);
  free (dat.chain);
  return 0;
}
