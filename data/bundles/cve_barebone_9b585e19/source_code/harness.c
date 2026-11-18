/* cve_barebone direct-call harness for cve_9b585e19 (libarchive)
 * Target: archive_read_format_rar_read_data  (archive_read_support_format_rar.c)
 * Bug class: heap-use-after-free (CWE-416), missing `rar->start_new_table = 1;` after
 * Ppmd7_Free() (fix commit b8592ecba2f9e451e1f5cb7ab6dcee8b8e7b3f60).
 *
 * See the module docstring of scripts/gen_dc_cve_9b585e19.py for the full mechanism
 * and the line-by-line trace of why every non-verbatim stub below is unreachable in
 * every state this harness constructs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

/* ==== archive_ppmd_private.h, lines 16-149 (verbatim: Byte/Int16/UInt16/Int32/UInt32/
 * Int64/UInt64/Bool, IByteIn/IByteOut, CpuArch PPMD_32BIT detection, CPpmd_See/
 * CPpmd_State(+_Ref)/CPpmd_Void_Ref/CPpmd_Byte_Ref, PPMD_* macros). IByteIn/IByteOut's
 * `struct archive_read *a;` / `struct archive_write *a;` fields are legal forward
 * references to pointer-only types here (struct archive_read is defined fully below;
 * struct archive_write is never dereferenced anywhere in this call graph). ==== */
/*** Begin defined in Types.h ***/

#if !defined(ZCONF_H)
typedef unsigned char Byte;
#endif
typedef short Int16;
typedef unsigned short UInt16;

#ifdef _LZMA_UINT32_IS_ULONG
typedef long Int32;
typedef unsigned long UInt32;
#else
typedef int Int32;
typedef unsigned int UInt32;
#endif

#ifdef _SZ_NO_INT_64

/* define _SZ_NO_INT_64, if your compiler doesn't support 64-bit integers.
   NOTES: Some code will work incorrectly in that case! */

typedef long Int64;
typedef unsigned long UInt64;

#else

#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef __int64 Int64;
typedef unsigned __int64 UInt64;
#define UINT64_CONST(n) n
#else
typedef long long int Int64;
typedef unsigned long long int UInt64;
#define UINT64_CONST(n) n ## ULL
#endif

#endif

typedef int Bool;
#define True 1
#define False 0

/* The following interfaces use first parameter as pointer to structure */

typedef struct
{
  struct archive_read *a;
  Byte (*Read)(void *p); /* reads one byte, returns 0 in case of EOF or error */
} IByteIn;

typedef struct
{
  struct archive_write *a;
  void (*Write)(void *p, Byte b);
} IByteOut;

/*** End defined in Types.h ***/
/*** Begin defined in CpuArch.h ***/

#if defined(_M_IX86) || defined(__i386__)
#define MY_CPU_X86
#endif

#if defined(MY_CPU_X86) || defined(_M_ARM)
#define MY_CPU_32BIT
#endif

#ifdef MY_CPU_32BIT
#define PPMD_32BIT
#endif

/*** End defined in CpuArch.h ***/

#define PPMD_INT_BITS 7
#define PPMD_PERIOD_BITS 7
#define PPMD_BIN_SCALE (1 << (PPMD_INT_BITS + PPMD_PERIOD_BITS))

#define PPMD_GET_MEAN_SPEC(summ, shift, round) (((summ) + (1 << ((shift) - (round)))) >> (shift))
#define PPMD_GET_MEAN(summ) PPMD_GET_MEAN_SPEC((summ), PPMD_PERIOD_BITS, 2)
#define PPMD_UPDATE_PROB_0(prob) ((prob) + (1 << PPMD_INT_BITS) - PPMD_GET_MEAN(prob))
#define PPMD_UPDATE_PROB_1(prob) ((prob) - PPMD_GET_MEAN(prob))

#define PPMD_N1 4
#define PPMD_N2 4
#define PPMD_N3 4
#define PPMD_N4 ((128 + 3 - 1 * PPMD_N1 - 2 * PPMD_N2 - 3 * PPMD_N3) / 4)
#define PPMD_NUM_INDEXES (PPMD_N1 + PPMD_N2 + PPMD_N3 + PPMD_N4)

/* SEE-contexts for PPM-contexts with masked symbols */
typedef struct
{
  UInt16 Summ; /* Freq */
  Byte Shift;  /* Speed of Freq change; low Shift is for fast change */
  Byte Count;  /* Count to next change of Shift */
} CPpmd_See;

#define Ppmd_See_Update(p)  if ((p)->Shift < PPMD_PERIOD_BITS && --(p)->Count == 0) \
    { (p)->Summ <<= 1; (p)->Count = (Byte)(3 << (p)->Shift++); }

typedef struct
{
  Byte Symbol;
  Byte Freq;
  UInt16 SuccessorLow;
  UInt16 SuccessorHigh;
} CPpmd_State;

typedef
  #ifdef PPMD_32BIT
    CPpmd_State *
  #else
    UInt32
  #endif
  CPpmd_State_Ref;

typedef
  #ifdef PPMD_32BIT
    void *
  #else
    UInt32
  #endif
  CPpmd_Void_Ref;

typedef
  #ifdef PPMD_32BIT
    Byte *
  #else
    UInt32
  #endif
  CPpmd_Byte_Ref;

#define PPMD_SetAllBitsIn256Bytes(p) \
  { unsigned j; for (j = 0; j < 256 / sizeof(p[0]); j += 8) { \
  p[j+7] = p[j+6] = p[j+5] = p[j+4] = p[j+3] = p[j+2] = p[j+1] = p[j+0] = ~(size_t)0; }}

/* ==== archive_ppmd7_private.h, lines 18-116 (verbatim: CPpmd7_Context(+_Ref)/CPpmd7,
 * IPpmd7_RangeDec/CPpmd7z_RangeDec/CPpmd7z_RangeEnc, the IPpmd7 function-pointer vtable
 * struct). ==== */
#define PPMD7_MIN_ORDER 2
#define PPMD7_MAX_ORDER 64

#define PPMD7_MIN_MEM_SIZE (1 << 11)
#define PPMD7_MAX_MEM_SIZE (0xFFFFFFFFu - 12 * 3)

struct CPpmd7_Context_;

typedef
  #ifdef PPMD_32BIT
    struct CPpmd7_Context_ *
  #else
    UInt32
  #endif
  CPpmd7_Context_Ref;

typedef struct CPpmd7_Context_
{
  UInt16 NumStats;
  UInt16 SummFreq;
  CPpmd_State_Ref Stats;
  CPpmd7_Context_Ref Suffix;
} CPpmd7_Context;

#define Ppmd7Context_OneState(p) ((CPpmd_State *)&(p)->SummFreq)

typedef struct
{
  CPpmd7_Context *MinContext, *MaxContext;
  CPpmd_State *FoundState;
  unsigned OrderFall, InitEsc, PrevSuccess, MaxOrder, HiBitsFlag;
  Int32 RunLength, InitRL; /* must be 32-bit at least */

  UInt32 Size;
  UInt32 GlueCount;
  Byte *Base, *LoUnit, *HiUnit, *Text, *UnitsStart;
  UInt32 AlignOffset;

  Byte Indx2Units[PPMD_NUM_INDEXES];
  Byte Units2Indx[128];
  CPpmd_Void_Ref FreeList[PPMD_NUM_INDEXES];
  Byte NS2Indx[256], NS2BSIndx[256], HB2Flag[256];
  CPpmd_See DummySee, See[25][16];
  UInt16 BinSumm[128][64];
} CPpmd7;

/* ---------- Decode ---------- */

typedef struct
{
  UInt32 (*GetThreshold)(void *p, UInt32 total);
  void (*Decode)(void *p, UInt32 start, UInt32 size);
  UInt32 (*DecodeBit)(void *p, UInt32 size0);
} IPpmd7_RangeDec;

typedef struct
{
  IPpmd7_RangeDec p;
  UInt32 Range;
  UInt32 Code;
  UInt32 Low;
  UInt32 Bottom;
  IByteIn *Stream;
} CPpmd7z_RangeDec;

/* ---------- Encode ---------- */

typedef struct
{
  UInt64 Low;
  UInt32 Range;
  Byte Cache;
  UInt64 CacheSize;
  IByteOut *Stream;
} CPpmd7z_RangeEnc;

typedef struct
{
  /* Base Functions */
  void (*Ppmd7_Construct)(CPpmd7 *p);
  Bool (*Ppmd7_Alloc)(CPpmd7 *p, UInt32 size);
  void (*Ppmd7_Free)(CPpmd7 *p);
  void (*Ppmd7_Init)(CPpmd7 *p, unsigned maxOrder);
  #define Ppmd7_WasAllocated(p) ((p)->Base != NULL)

  /* Decode Functions */
  void (*Ppmd7z_RangeDec_CreateVTable)(CPpmd7z_RangeDec *p);
  void (*PpmdRAR_RangeDec_CreateVTable)(CPpmd7z_RangeDec *p);
  Bool (*Ppmd7z_RangeDec_Init)(CPpmd7z_RangeDec *p);
  Bool (*PpmdRAR_RangeDec_Init)(CPpmd7z_RangeDec *p);
  #define Ppmd7z_RangeDec_IsFinishedOK(p) ((p)->Code == 0)
  int (*Ppmd7_DecodeSymbol)(CPpmd7 *p, IPpmd7_RangeDec *rc);

  /* Encode Functions */
  void (*Ppmd7z_RangeEnc_Init)(CPpmd7z_RangeEnc *p);
  void (*Ppmd7z_RangeEnc_FlushData)(CPpmd7z_RangeEnc *p);

  void (*Ppmd7_EncodeSymbol)(CPpmd7 *p, CPpmd7z_RangeEnc *rc, int symbol);
} IPpmd7;

/* ==== struct archive / struct archive_format_descriptor / struct archive_read: real
 * libarchive type NAMES (archive_read_private.h), REDUCED to just the real-named
 * fields archive_read_format_rar_read_data / read_data_compressed actually touch
 * (`a->format->data` and `&a->archive`, the latter only ever passed opaquely to
 * archive_set_error). The real archive_read also embeds ~15 more fields (filter-bidder
 * table, active filter chain, extract state, passphrase callback, ...) -- all
 * unrelated machinery for the container-parsing front end this CVE is not about, and
 * never referenced by the two functions copied verbatim below. ==== */
struct archive {
    int _vb_reserved; /* real struct archive carries ~20 more fields (error string,
                        * vtable, format bookkeeping, ...); nothing in this call graph
                        * dereferences them -- &a->archive is only ever passed opaquely
                        * to archive_set_error(). */
};
struct archive_format_descriptor {
    void *data; /* the only field archive_read_format_rar_read_data/read_data_compressed
                 * read: `(struct rar *)(a->format->data)` */
};
struct archive_read {
    struct archive archive;
    struct archive_format_descriptor *format;
};

#define ARCHIVE_EOF        1   /* archive.h, verbatim */
#define ARCHIVE_OK         0
#define ARCHIVE_WARN     (-20)
#define ARCHIVE_FAILED   (-25)
#define ARCHIVE_FATAL    (-30)
/* archive.h documents these as platform-errno mappings resolved via archive_platform.h
 * (literally "#define ARCHIVE_ERRNO_FILE_FORMAT" with no value in archive.h itself);
 * our own archive_set_error() stub below ignores the value entirely, so any distinct
 * placeholder ints are behaviorally exact. */
#define ARCHIVE_ERRNO_FILE_FORMAT (-1)
#define ARCHIVE_ERRNO_MISC        (-2)
#define ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW -1  /* archive.h, verbatim */

struct archive_string_conv; /* opaque; struct rar only ever holds pointers to it */

/* ==== archive_read_support_format_rar.c size #defines struct rar's lengthtable[]
 * needs (verbatim) + struct huffman_tree_node/huffman_table_entry/huffman_code/lzss/
 * data_block_offsets/struct rar (verbatim, real field names/layout, unedited). ==== */
#define MAINCODE_SIZE      299
#define OFFSETCODE_SIZE    60
#define LOWOFFSETCODE_SIZE 17
#define LENGTHCODE_SIZE    28
#define HUFFMAN_TABLE_SIZE \
  MAINCODE_SIZE + OFFSETCODE_SIZE + LOWOFFSETCODE_SIZE + LENGTHCODE_SIZE

#define MAX_SYMBOL_LENGTH 0xF
#define MAX_SYMBOLS       20


struct huffman_tree_node
{
  int branches[2];
};

struct huffman_table_entry
{
  unsigned int length;
  int value;
};

struct huffman_code
{
  struct huffman_tree_node *tree;
  int numentries;
  int numallocatedentries;
  int minlength;
  int maxlength;
  int tablesize;
  struct huffman_table_entry *table;
};

struct lzss
{
  unsigned char *window;
  int mask;
  int64_t position;
};

struct data_block_offsets
{
  int64_t header_size;
  int64_t start_offset;
  int64_t end_offset;
};

struct rar
{
  /* Entries from main RAR header */
  unsigned main_flags;
  unsigned long file_crc;
  char reserved1[2];
  char reserved2[4];
  char encryptver;

  /* File header entries */
  char compression_method;
  unsigned file_flags;
  int64_t packed_size;
  int64_t unp_size;
  time_t mtime;
  long mnsec;
  mode_t mode;
  char *filename;
  char *filename_save;
  size_t filename_save_size;
  size_t filename_allocated;

  /* File header optional entries */
  char salt[8];
  time_t atime;
  long ansec;
  time_t ctime;
  long cnsec;
  time_t arctime;
  long arcnsec;

  /* Fields to help with tracking decompression of files. */
  int64_t bytes_unconsumed;
  int64_t bytes_remaining;
  int64_t bytes_uncopied;
  int64_t offset;
  int64_t offset_outgoing;
  int64_t offset_seek;
  char valid;
  unsigned int unp_offset;
  unsigned int unp_buffer_size;
  unsigned char *unp_buffer;
  unsigned int dictionary_size;
  char start_new_block;
  char entry_eof;
  unsigned long crc_calculated;
  int found_first_header;
  char has_endarc_header;
  struct data_block_offsets *dbo;
  unsigned int cursor;
  unsigned int nodes;
  char filename_must_match;

  /* LZSS members */
  struct huffman_code maincode;
  struct huffman_code offsetcode;
  struct huffman_code lowoffsetcode;
  struct huffman_code lengthcode;
  unsigned char lengthtable[HUFFMAN_TABLE_SIZE];
  struct lzss lzss;
  char output_last_match;
  unsigned int lastlength;
  unsigned int lastoffset;
  unsigned int oldoffset[4];
  unsigned int lastlowoffset;
  unsigned int numlowoffsetrepeats;
  int64_t filterstart;
  char start_new_table;

  /* PPMd Variant H members */
  char ppmd_valid;
  char ppmd_eod;
  char is_ppmd_block;
  int ppmd_escape;
  CPpmd7 ppmd7_context;
  CPpmd7z_RangeDec range_dec;
  IByteIn bytein;

  /*
   * String conversion object.
   */
  int init_default_conversion;
  struct archive_string_conv *sconv_default;
  struct archive_string_conv *opt_sconv;
  struct archive_string_conv *sconv_utf8;
  struct archive_string_conv *sconv_utf16be;

  /*
   * Bit stream reader.
   */
  struct rar_br {
#define CACHE_TYPE	uint64_t
#define CACHE_BITS	(8 * sizeof(CACHE_TYPE))
    /* Cache buffer. */
    CACHE_TYPE		 cache_buffer;
    /* Indicates how many bits avail in cache_buffer. */
    int			 cache_avail;
    ssize_t		 avail_in;
    const unsigned char *next_in;
  } br;

  /*
   * Custom field to denote that this archive contains encrypted entries
   */
  int has_encrypted_entries;
};


/* Compression Methods (archive_read_support_format_rar.c, verbatim) */
#define COMPRESS_METHOD_STORE   0x30
#define COMPRESS_METHOD_FASTEST 0x31
#define COMPRESS_METHOD_FAST    0x32
#define COMPRESS_METHOD_NORMAL  0x33
#define COMPRESS_METHOD_GOOD    0x34
#define COMPRESS_METHOD_BEST    0x35

/* ---- incidental stand-ins (real signatures, trivial bodies) for everything on the
 * RAR byte-stream/Huffman-table front end. Every one of these is UNREACHABLE in every
 * state this harness constructs (traced in the module docstring): rar->br.next_in is
 * always pre-set non-NULL (skips rar_br_preparation), rar->start_new_table is always 0
 * (skips parse_codes), rar->compression_method is always either COMPRESS_METHOD_GOOD
 * (is_ppmd_block=1, skips read_data_stored and the non-ppmd `expand`/lzss_emit_* path)
 * or an unsupported value (hits the `default:` switch arm before touching any of
 * these), and Ppmd7_DecodeSymbol is engineered to return -2 on its very FIRST call
 * (see below), which returns out of read_data_compressed before it ever reaches
 * copy_from_lzss_window/lzss_emit_* at the bottom of its loop or the crc32 calls
 * inside the (unreached) EOF/CRC branch. They exist only so the verbatim
 * read_data_compressed / archive_read_format_rar_read_data text below links. ---- */
void archive_set_error(struct archive *a, int err, const char *fmt, ...) {
    (void)a; (void)err; (void)fmt;
}
int64_t __archive_read_consume(struct archive_read *a, int64_t request) {
    (void)a; return request;
}
static unsigned long crc32(unsigned long crc, const unsigned char *buf, unsigned int len) {
    (void)buf; return crc + len;
}
static int read_data_stored(struct archive_read *a, const void **buff, size_t *size,
                             int64_t *offset) {
    (void)a; *buff = NULL; *size = 0; *offset = 0; return ARCHIVE_FATAL;
}
static int rar_br_preparation(struct archive_read *a, struct rar_br *br) {
    (void)a; (void)br; return ARCHIVE_FATAL;
}
static int parse_codes(struct archive_read *a) {
    (void)a; return ARCHIVE_FATAL;
}
static int64_t expand(struct archive_read *a, int64_t end) {
    (void)a; return end;
}
static int copy_from_lzss_window(struct archive_read *a, const void **buffer,
                                  int64_t startpos, int length) {
    (void)a; (void)startpos; (void)length; *buffer = NULL; return ARCHIVE_OK;
}
static void lzss_emit_literal(struct rar *rar, uint8_t literal) {
    (void)rar; (void)literal;
}
static void lzss_emit_match(struct rar *rar, int offset, int length) {
    (void)rar; (void)offset; (void)length;
}
static Byte ppmd_read(void *p) {
    (void)p; return 0;
}

/* ==== archive_ppmd7.c, lines 11-1168 (verbatim, complete: Ppmd7_Construct/Alloc/Free/
 * Init/RestartModel/DecodeSymbol, the RAR + 7z range-decoder variants, the encoder
 * half (never called; kept because the real __archive_ppmd7_functions vtable
 * initializer below references its symbols, and this way NOTHING in this file is
 * hand-edited), and the real `const IPpmd7 __archive_ppmd7_functions` vtable
 * archive_read_format_rar_read_data/read_data_compressed dispatch every Ppmd7 call
 * through. ==== */
#ifdef PPMD_32BIT
  #define Ppmd7_GetPtr(p, ptr) (ptr)
  #define Ppmd7_GetContext(p, ptr) (ptr)
  #define Ppmd7_GetStats(p, ctx) ((ctx)->Stats)
#else
  #define Ppmd7_GetPtr(p, offs) ((void *)((p)->Base + (offs)))
  #define Ppmd7_GetContext(p, offs) ((CPpmd7_Context *)Ppmd7_GetPtr((p), (offs)))
  #define Ppmd7_GetStats(p, ctx) ((CPpmd_State *)Ppmd7_GetPtr((p), ((ctx)->Stats)))
#endif

#define Ppmd7_GetBinSumm(p) \
    &p->BinSumm[Ppmd7Context_OneState(p->MinContext)->Freq - 1][p->PrevSuccess + \
    p->NS2BSIndx[Ppmd7_GetContext(p, p->MinContext->Suffix)->NumStats - 1] + \
    (p->HiBitsFlag = p->HB2Flag[p->FoundState->Symbol]) + \
    2 * p->HB2Flag[Ppmd7Context_OneState(p->MinContext)->Symbol] + \
    ((p->RunLength >> 26) & 0x20)]

#define kTopValue (1 << 24)
#define MAX_FREQ 124
#define UNIT_SIZE 12

#define U2B(nu) ((UInt32)(nu) * UNIT_SIZE)
#define U2I(nu) (p->Units2Indx[(nu) - 1])
#define I2U(indx) (p->Indx2Units[indx])

#ifdef PPMD_32BIT
  #define REF(ptr) (ptr)
#else
  #define REF(ptr) ((UInt32)((Byte *)(ptr) - (p)->Base))
#endif

#define STATS_REF(ptr) ((CPpmd_State_Ref)REF(ptr))

#define CTX(ref) ((CPpmd7_Context *)Ppmd7_GetContext(p, ref))
#define STATS(ctx) Ppmd7_GetStats(p, ctx)
#define ONE_STATE(ctx) Ppmd7Context_OneState(ctx)
#define SUFFIX(ctx) CTX((ctx)->Suffix)

static const UInt16 kInitBinEsc[] = { 0x3CDD, 0x1F3F, 0x59BF, 0x48F3, 0x64A1, 0x5ABC, 0x6632, 0x6051};
static const Byte PPMD7_kExpEscape[16] = { 25, 14, 9, 7, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2 };

typedef CPpmd7_Context * CTX_PTR;

struct CPpmd7_Node_;

typedef
  #ifdef PPMD_32BIT
    struct CPpmd7_Node_ *
  #else
    UInt32
  #endif
  CPpmd7_Node_Ref;

typedef struct CPpmd7_Node_
{
  UInt16 Stamp; /* must be at offset 0 as CPpmd7_Context::NumStats. Stamp=0 means free */
  UInt16 NU;
  CPpmd7_Node_Ref Next; /* must be at offset >= 4 */
  CPpmd7_Node_Ref Prev;
} CPpmd7_Node;

#ifdef PPMD_32BIT
  #define NODE(ptr) (ptr)
#else
  #define NODE(offs) ((CPpmd7_Node *)(p->Base + (offs)))
#endif

static void Ppmd7_Update1(CPpmd7 *p);
static void Ppmd7_Update1_0(CPpmd7 *p);
static void Ppmd7_Update2(CPpmd7 *p);
static void Ppmd7_UpdateBin(CPpmd7 *p);
static CPpmd_See *Ppmd7_MakeEscFreq(CPpmd7 *p, unsigned numMasked,
                                    UInt32 *scale);

/* ----------- Base ----------- */

static void Ppmd7_Construct(CPpmd7 *p)
{
  unsigned i, k, m;

  p->Base = 0;

  for (i = 0, k = 0; i < PPMD_NUM_INDEXES; i++)
  {
    unsigned step = (i >= 12 ? 4 : (i >> 2) + 1);
    do { p->Units2Indx[k++] = (Byte)i; } while(--step);
    p->Indx2Units[i] = (Byte)k;
  }

  p->NS2BSIndx[0] = (0 << 1);
  p->NS2BSIndx[1] = (1 << 1);
  memset(p->NS2BSIndx + 2, (2 << 1), 9);
  memset(p->NS2BSIndx + 11, (3 << 1), 256 - 11);

  for (i = 0; i < 3; i++)
    p->NS2Indx[i] = (Byte)i;
  for (m = i, k = 1; i < 256; i++)
  {
    p->NS2Indx[i] = (Byte)m;
    if (--k == 0)
      k = (++m) - 2;
  }

  memset(p->HB2Flag, 0, 0x40);
  memset(p->HB2Flag + 0x40, 8, 0x100 - 0x40);
}

static void Ppmd7_Free(CPpmd7 *p)
{
  free(p->Base);
  p->Size = 0;
  p->Base = 0;
}

static Bool Ppmd7_Alloc(CPpmd7 *p, UInt32 size)
{
  if (p->Base == 0 || p->Size != size)
  {
    /* RestartModel() below assumes that p->Size >= UNIT_SIZE
       (see the calculation of m->MinContext). */
    if (size < UNIT_SIZE) {
      return False;
    }
    Ppmd7_Free(p);
    p->AlignOffset =
      #ifdef PPMD_32BIT
        (4 - size) & 3;
      #else
        4 - (size & 3);
      #endif
    if ((p->Base = (Byte *)malloc(p->AlignOffset + size
        #ifndef PPMD_32BIT
        + UNIT_SIZE
        #endif
        )) == 0)
      return False;
    p->Size = size;
  }
  return True;
}

static void InsertNode(CPpmd7 *p, void *node, unsigned indx)
{
  *((CPpmd_Void_Ref *)node) = p->FreeList[indx];
  p->FreeList[indx] = REF(node);
}

static void *RemoveNode(CPpmd7 *p, unsigned indx)
{
  CPpmd_Void_Ref *node = (CPpmd_Void_Ref *)Ppmd7_GetPtr(p, p->FreeList[indx]);
  p->FreeList[indx] = *node;
  return node;
}

static void SplitBlock(CPpmd7 *p, void *ptr, unsigned oldIndx, unsigned newIndx)
{
  unsigned i, nu = I2U(oldIndx) - I2U(newIndx);
  ptr = (Byte *)ptr + U2B(I2U(newIndx));
  if (I2U(i = U2I(nu)) != nu)
  {
    unsigned k = I2U(--i);
    InsertNode(p, ((Byte *)ptr) + U2B(k), nu - k - 1);
  }
  InsertNode(p, ptr, i);
}

static void GlueFreeBlocks(CPpmd7 *p)
{
  #ifdef PPMD_32BIT
  CPpmd7_Node headItem;
  CPpmd7_Node_Ref head = &headItem;
  #else
  CPpmd7_Node_Ref head = p->AlignOffset + p->Size;
  #endif
  
  CPpmd7_Node_Ref n = head;
  unsigned i;

  p->GlueCount = 255;

  /* create doubly-linked list of free blocks */
  for (i = 0; i < PPMD_NUM_INDEXES; i++)
  {
    UInt16 nu = I2U(i);
    CPpmd7_Node_Ref next = (CPpmd7_Node_Ref)p->FreeList[i];
    p->FreeList[i] = 0;
    while (next != 0)
    {
      CPpmd7_Node *node = NODE(next);
      node->Next = n;
      n = NODE(n)->Prev = next;
      next = *(const CPpmd7_Node_Ref *)node;
      node->Stamp = 0;
      node->NU = (UInt16)nu;
    }
  }
  NODE(head)->Stamp = 1;
  NODE(head)->Next = n;
  NODE(n)->Prev = head;
  if (p->LoUnit != p->HiUnit)
    ((CPpmd7_Node *)p->LoUnit)->Stamp = 1;
  
  /* Glue free blocks */
  while (n != head)
  {
    CPpmd7_Node *node = NODE(n);
    UInt32 nu = (UInt32)node->NU;
    for (;;)
    {
      CPpmd7_Node *node2 = NODE(n) + nu;
      nu += node2->NU;
      if (node2->Stamp != 0 || nu >= 0x10000)
        break;
      NODE(node2->Prev)->Next = node2->Next;
      NODE(node2->Next)->Prev = node2->Prev;
      node->NU = (UInt16)nu;
    }
    n = node->Next;
  }
  
  /* Fill lists of free blocks */
  for (n = NODE(head)->Next; n != head;)
  {
    CPpmd7_Node *node = NODE(n);
    unsigned nu;
    CPpmd7_Node_Ref next = node->Next;
    for (nu = node->NU; nu > 128; nu -= 128, node += 128)
      InsertNode(p, node, PPMD_NUM_INDEXES - 1);
    if (I2U(i = U2I(nu)) != nu)
    {
      unsigned k = I2U(--i);
      InsertNode(p, node + k, nu - k - 1);
    }
    InsertNode(p, node, i);
    n = next;
  }
}

static void *AllocUnitsRare(CPpmd7 *p, unsigned indx)
{
  unsigned i;
  void *retVal;
  if (p->GlueCount == 0)
  {
    GlueFreeBlocks(p);
    if (p->FreeList[indx] != 0)
      return RemoveNode(p, indx);
  }
  i = indx;
  do
  {
    if (++i == PPMD_NUM_INDEXES)
    {
      UInt32 numBytes = U2B(I2U(indx));
      p->GlueCount--;
      return ((UInt32)(p->UnitsStart - p->Text) > numBytes) ? (p->UnitsStart -= numBytes) : (NULL);
    }
  }
  while (p->FreeList[i] == 0);
  retVal = RemoveNode(p, i);
  SplitBlock(p, retVal, i, indx);
  return retVal;
}

static void *AllocUnits(CPpmd7 *p, unsigned indx)
{
  UInt32 numBytes;
  if (p->FreeList[indx] != 0)
    return RemoveNode(p, indx);
  numBytes = U2B(I2U(indx));
  if (numBytes <= (UInt32)(p->HiUnit - p->LoUnit))
  {
    void *retVal = p->LoUnit;
    p->LoUnit += numBytes;
    return retVal;
  }
  return AllocUnitsRare(p, indx);
}

#define MyMem12Cpy(dest, src, num) \
  { UInt32 *d = (UInt32 *)dest; const UInt32 *s = (const UInt32 *)src; UInt32 n = num; \
    do { d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; s += 3; d += 3; } while(--n); }

static void *ShrinkUnits(CPpmd7 *p, void *oldPtr, unsigned oldNU, unsigned newNU)
{
  unsigned i0 = U2I(oldNU);
  unsigned i1 = U2I(newNU);
  if (i0 == i1)
    return oldPtr;
  if (p->FreeList[i1] != 0)
  {
    void *ptr = RemoveNode(p, i1);
    MyMem12Cpy(ptr, oldPtr, newNU);
    InsertNode(p, oldPtr, i0);
    return ptr;
  }
  SplitBlock(p, oldPtr, i0, i1);
  return oldPtr;
}

#define SUCCESSOR(p) ((CPpmd_Void_Ref)((p)->SuccessorLow | ((UInt32)(p)->SuccessorHigh << 16)))

static void SetSuccessor(CPpmd_State *p, CPpmd_Void_Ref v)
{
  (p)->SuccessorLow = (UInt16)((UInt32)(v) & 0xFFFF);
  (p)->SuccessorHigh = (UInt16)(((UInt32)(v) >> 16) & 0xFFFF);
}

static void RestartModel(CPpmd7 *p)
{
  unsigned i, k, m;

  memset(p->FreeList, 0, sizeof(p->FreeList));
  p->Text = p->Base + p->AlignOffset;
  p->HiUnit = p->Text + p->Size;
  p->LoUnit = p->UnitsStart = p->HiUnit - p->Size / 8 / UNIT_SIZE * 7 * UNIT_SIZE;
  p->GlueCount = 0;

  p->OrderFall = p->MaxOrder;
  p->RunLength = p->InitRL = -(Int32)((p->MaxOrder < 12) ? p->MaxOrder : 12) - 1;
  p->PrevSuccess = 0;

  p->MinContext = p->MaxContext = (CTX_PTR)(p->HiUnit -= UNIT_SIZE); /* AllocContext(p); */
  p->MinContext->Suffix = 0;
  p->MinContext->NumStats = 256;
  p->MinContext->SummFreq = 256 + 1;
  p->FoundState = (CPpmd_State *)p->LoUnit; /* AllocUnits(p, PPMD_NUM_INDEXES - 1); */
  p->LoUnit += U2B(256 / 2);
  p->MinContext->Stats = REF(p->FoundState);
  for (i = 0; i < 256; i++)
  {
    CPpmd_State *s = &p->FoundState[i];
    s->Symbol = (Byte)i;
    s->Freq = 1;
    SetSuccessor(s, 0);
  }

  for (i = 0; i < 128; i++)
    for (k = 0; k < 8; k++)
    {
      UInt16 *dest = p->BinSumm[i] + k;
      UInt16 val = (UInt16)(PPMD_BIN_SCALE - kInitBinEsc[k] / (i + 2));
      for (m = 0; m < 64; m += 8)
        dest[m] = val;
    }
  
  for (i = 0; i < 25; i++)
    for (k = 0; k < 16; k++)
    {
      CPpmd_See *s = &p->See[i][k];
      s->Summ = (UInt16)((5 * i + 10) << (s->Shift = PPMD_PERIOD_BITS - 4));
      s->Count = 4;
    }
}

static void Ppmd7_Init(CPpmd7 *p, unsigned maxOrder)
{
  p->MaxOrder = maxOrder;
  RestartModel(p);
  p->DummySee.Shift = PPMD_PERIOD_BITS;
  p->DummySee.Summ = 0; /* unused */
  p->DummySee.Count = 64; /* unused */
}

static CTX_PTR CreateSuccessors(CPpmd7 *p, Bool skip)
{
  CPpmd_State upState;
  CTX_PTR c = p->MinContext;
  CPpmd_Byte_Ref upBranch = (CPpmd_Byte_Ref)SUCCESSOR(p->FoundState);
  CPpmd_State *ps[PPMD7_MAX_ORDER];
  unsigned numPs = 0;
  
  if (!skip)
    ps[numPs++] = p->FoundState;
  
  while (c->Suffix)
  {
    CPpmd_Void_Ref successor;
    CPpmd_State *s;
    c = SUFFIX(c);
    if (c->NumStats != 1)
    {
      for (s = STATS(c); s->Symbol != p->FoundState->Symbol; s++);
    }
    else
      s = ONE_STATE(c);
    successor = SUCCESSOR(s);
    if (successor != upBranch)
    {
      c = CTX(successor);
      if (numPs == 0)
        return c;
      break;
    }
    ps[numPs++] = s;
  }
  
  upState.Symbol = *(const Byte *)Ppmd7_GetPtr(p, upBranch);
  SetSuccessor(&upState, upBranch + 1);
  
  if (c->NumStats == 1)
    upState.Freq = ONE_STATE(c)->Freq;
  else
  {
    UInt32 cf, s0;
    CPpmd_State *s;
    for (s = STATS(c); s->Symbol != upState.Symbol; s++);
    cf = s->Freq - 1;
    s0 = c->SummFreq - c->NumStats - cf;
    upState.Freq = (Byte)(1 + ((2 * cf <= s0) ? (5 * cf > s0) : ((2 * cf + 3 * s0 - 1) / (2 * s0))));
  }

  while (numPs != 0)
  {
    /* Create Child */
    CTX_PTR c1; /* = AllocContext(p); */
    if (p->HiUnit != p->LoUnit)
      c1 = (CTX_PTR)(p->HiUnit -= UNIT_SIZE);
    else if (p->FreeList[0] != 0)
      c1 = (CTX_PTR)RemoveNode(p, 0);
    else
    {
      c1 = (CTX_PTR)AllocUnitsRare(p, 0);
      if (!c1)
        return NULL;
    }
    c1->NumStats = 1;
    *ONE_STATE(c1) = upState;
    c1->Suffix = REF(c);
    SetSuccessor(ps[--numPs], REF(c1));
    c = c1;
  }
  
  return c;
}

static void SwapStates(CPpmd_State *t1, CPpmd_State *t2)
{
  CPpmd_State tmp = *t1;
  *t1 = *t2;
  *t2 = tmp;
}

static void UpdateModel(CPpmd7 *p)
{
  CPpmd_Void_Ref successor, fSuccessor = SUCCESSOR(p->FoundState);
  CTX_PTR c;
  unsigned s0, ns;
  
  if (p->FoundState->Freq < MAX_FREQ / 4 && p->MinContext->Suffix != 0)
  {
    c = SUFFIX(p->MinContext);
    
    if (c->NumStats == 1)
    {
      CPpmd_State *s = ONE_STATE(c);
      if (s->Freq < 32)
        s->Freq++;
    }
    else
    {
      CPpmd_State *s = STATS(c);
      if (s->Symbol != p->FoundState->Symbol)
      {
        do { s++; } while (s->Symbol != p->FoundState->Symbol);
        if (s[0].Freq >= s[-1].Freq)
        {
          SwapStates(&s[0], &s[-1]);
          s--;
        }
      }
      if (s->Freq < MAX_FREQ - 9)
      {
        s->Freq += 2;
        c->SummFreq += 2;
      }
    }
  }

  if (p->OrderFall == 0)
  {
    p->MinContext = p->MaxContext = CreateSuccessors(p, True);
    if (p->MinContext == 0)
    {
      RestartModel(p);
      return;
    }
    SetSuccessor(p->FoundState, REF(p->MinContext));
    return;
  }
  
  *p->Text++ = p->FoundState->Symbol;
  successor = REF(p->Text);
  if (p->Text >= p->UnitsStart)
  {
    RestartModel(p);
    return;
  }
  
  if (fSuccessor)
  {
    if (fSuccessor <= successor)
    {
      CTX_PTR cs = CreateSuccessors(p, False);
      if (cs == NULL)
      {
        RestartModel(p);
        return;
      }
      fSuccessor = REF(cs);
    }
    if (--p->OrderFall == 0)
    {
      successor = fSuccessor;
      p->Text -= (p->MaxContext != p->MinContext);
    }
  }
  else
  {
    SetSuccessor(p->FoundState, successor);
    fSuccessor = REF(p->MinContext);
  }
  
  s0 = p->MinContext->SummFreq - (ns = p->MinContext->NumStats) - (p->FoundState->Freq - 1);
  
  for (c = p->MaxContext; c != p->MinContext; c = SUFFIX(c))
  {
    unsigned ns1;
    UInt32 cf, sf;
    if ((ns1 = c->NumStats) != 1)
    {
      if ((ns1 & 1) == 0)
      {
        /* Expand for one UNIT */
        unsigned oldNU = ns1 >> 1;
        unsigned i = U2I(oldNU);
        if (i != U2I(oldNU + 1))
        {
          void *ptr = AllocUnits(p, i + 1);
          void *oldPtr;
          if (!ptr)
          {
            RestartModel(p);
            return;
          }
          oldPtr = STATS(c);
          MyMem12Cpy(ptr, oldPtr, oldNU);
          InsertNode(p, oldPtr, i);
          c->Stats = STATS_REF(ptr);
        }
      }
      c->SummFreq = (UInt16)(c->SummFreq + (2 * ns1 < ns) + 2 * ((4 * ns1 <= ns) & (c->SummFreq <= 8 * ns1)));
    }
    else
    {
      CPpmd_State *s = (CPpmd_State*)AllocUnits(p, 0);
      if (!s)
      {
        RestartModel(p);
        return;
      }
      *s = *ONE_STATE(c);
      c->Stats = REF(s);
      if (s->Freq < MAX_FREQ / 4 - 1)
        s->Freq <<= 1;
      else
        s->Freq = MAX_FREQ - 4;
      c->SummFreq = (UInt16)(s->Freq + p->InitEsc + (ns > 3));
    }
    cf = 2 * (UInt32)p->FoundState->Freq * (c->SummFreq + 6);
    sf = (UInt32)s0 + c->SummFreq;
    if (cf < 6 * sf)
    {
      cf = 1 + (cf > sf) + (cf >= 4 * sf);
      c->SummFreq += 3;
    }
    else
    {
      cf = 4 + (cf >= 9 * sf) + (cf >= 12 * sf) + (cf >= 15 * sf);
      c->SummFreq = (UInt16)(c->SummFreq + cf);
    }
    {
      CPpmd_State *s = STATS(c) + ns1;
      SetSuccessor(s, successor);
      s->Symbol = p->FoundState->Symbol;
      s->Freq = (Byte)cf;
      c->NumStats = (UInt16)(ns1 + 1);
    }
  }
  p->MaxContext = p->MinContext = CTX(fSuccessor);
}
  
static void Rescale(CPpmd7 *p)
{
  unsigned i, adder, sumFreq, escFreq;
  CPpmd_State *stats = STATS(p->MinContext);
  CPpmd_State *s = p->FoundState;
  {
    CPpmd_State tmp = *s;
    for (; s != stats; s--)
      s[0] = s[-1];
    *s = tmp;
  }
  escFreq = p->MinContext->SummFreq - s->Freq;
  s->Freq += 4;
  adder = (p->OrderFall != 0);
  s->Freq = (Byte)((s->Freq + adder) >> 1);
  sumFreq = s->Freq;
  
  i = p->MinContext->NumStats - 1;
  do
  {
    escFreq -= (++s)->Freq;
    s->Freq = (Byte)((s->Freq + adder) >> 1);
    sumFreq += s->Freq;
    if (s[0].Freq > s[-1].Freq)
    {
      CPpmd_State *s1 = s;
      CPpmd_State tmp = *s1;
      do
        s1[0] = s1[-1];
      while (--s1 != stats && tmp.Freq > s1[-1].Freq);
      *s1 = tmp;
    }
  }
  while (--i);
  
  if (s->Freq == 0)
  {
    unsigned numStats = p->MinContext->NumStats;
    unsigned n0, n1;
    do { i++; } while ((--s)->Freq == 0);
    escFreq += i;
    p->MinContext->NumStats = (UInt16)(p->MinContext->NumStats - i);
    if (p->MinContext->NumStats == 1)
    {
      CPpmd_State tmp = *stats;
      do
      {
        tmp.Freq = (Byte)(tmp.Freq - (tmp.Freq >> 1));
        escFreq >>= 1;
      }
      while (escFreq > 1);
      InsertNode(p, stats, U2I(((numStats + 1) >> 1)));
      *(p->FoundState = ONE_STATE(p->MinContext)) = tmp;
      return;
    }
    n0 = (numStats + 1) >> 1;
    n1 = (p->MinContext->NumStats + 1) >> 1;
    if (n0 != n1)
      p->MinContext->Stats = STATS_REF(ShrinkUnits(p, stats, n0, n1));
  }
  p->MinContext->SummFreq = (UInt16)(sumFreq + escFreq - (escFreq >> 1));
  p->FoundState = STATS(p->MinContext);
}

static CPpmd_See *Ppmd7_MakeEscFreq(CPpmd7 *p, unsigned numMasked, UInt32 *escFreq)
{
  CPpmd_See *see;
  unsigned nonMasked = p->MinContext->NumStats - numMasked;
  if (p->MinContext->NumStats != 256)
  {
    see = p->See[p->NS2Indx[nonMasked - 1]] +
        (nonMasked < (unsigned)SUFFIX(p->MinContext)->NumStats - p->MinContext->NumStats) +
        2 * (p->MinContext->SummFreq < 11 * p->MinContext->NumStats) +
        4 * (numMasked > nonMasked) +
        p->HiBitsFlag;
    {
      unsigned r = (see->Summ >> see->Shift);
      see->Summ = (UInt16)(see->Summ - r);
      *escFreq = r + (r == 0);
    }
  }
  else
  {
    see = &p->DummySee;
    *escFreq = 1;
  }
  return see;
}

static void NextContext(CPpmd7 *p)
{
  CTX_PTR c = CTX(SUCCESSOR(p->FoundState));
  if (p->OrderFall == 0 && (Byte *)c > p->Text)
    p->MinContext = p->MaxContext = c;
  else
    UpdateModel(p);
}

static void Ppmd7_Update1(CPpmd7 *p)
{
  CPpmd_State *s = p->FoundState;
  s->Freq += 4;
  p->MinContext->SummFreq += 4;
  if (s[0].Freq > s[-1].Freq)
  {
    SwapStates(&s[0], &s[-1]);
    p->FoundState = --s;
    if (s->Freq > MAX_FREQ)
      Rescale(p);
  }
  NextContext(p);
}

static void Ppmd7_Update1_0(CPpmd7 *p)
{
  p->PrevSuccess = (2 * p->FoundState->Freq > p->MinContext->SummFreq);
  p->RunLength += p->PrevSuccess;
  p->MinContext->SummFreq += 4;
  if ((p->FoundState->Freq += 4) > MAX_FREQ)
    Rescale(p);
  NextContext(p);
}

static void Ppmd7_UpdateBin(CPpmd7 *p)
{
  p->FoundState->Freq = (Byte)(p->FoundState->Freq + (p->FoundState->Freq < 128 ? 1: 0));
  p->PrevSuccess = 1;
  p->RunLength++;
  NextContext(p);
}

static void Ppmd7_Update2(CPpmd7 *p)
{
  p->MinContext->SummFreq += 4;
  if ((p->FoundState->Freq += 4) > MAX_FREQ)
    Rescale(p);
  p->RunLength = p->InitRL;
  UpdateModel(p);
}

/* ---------- Decode ---------- */

static Bool Ppmd_RangeDec_Init(CPpmd7z_RangeDec *p)
{
  unsigned i;
  p->Low = p->Bottom = 0;
  p->Range = 0xFFFFFFFF;
  for (i = 0; i < 4; i++)
    p->Code = (p->Code << 8) | p->Stream->Read((void *)p->Stream);
  return (p->Code < 0xFFFFFFFF);
}

static Bool Ppmd7z_RangeDec_Init(CPpmd7z_RangeDec *p)
{
  if (p->Stream->Read((void *)p->Stream) != 0)
    return False;
  return Ppmd_RangeDec_Init(p);
}

static Bool PpmdRAR_RangeDec_Init(CPpmd7z_RangeDec *p)
{
  if (!Ppmd_RangeDec_Init(p))
    return False;
  p->Bottom = 0x8000;
  return True;
}

static UInt32 Range_GetThreshold(void *pp, UInt32 total)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  return (p->Code - p->Low) / (p->Range /= total);
}

static void Range_Normalize(CPpmd7z_RangeDec *p)
{
  while (1)
  {
    if((p->Low ^ (p->Low + p->Range)) >= kTopValue)
    {
      if(p->Range >= p->Bottom)
        break;
      else
        p->Range = ((uint32_t)(-(int32_t)p->Low)) & (p->Bottom - 1);
    }
    p->Code = (p->Code << 8) | p->Stream->Read((void *)p->Stream);
    p->Range <<= 8;
    p->Low <<= 8;
  }
}

static void Range_Decode_7z(void *pp, UInt32 start, UInt32 size)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  p->Code -= start * p->Range;
  p->Range *= size;
  Range_Normalize(p);
}

static void Range_Decode_RAR(void *pp, UInt32 start, UInt32 size)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  p->Low += start * p->Range;
  p->Range *= size;
  Range_Normalize(p);
}

static UInt32 Range_DecodeBit_7z(void *pp, UInt32 size0)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  UInt32 newBound = (p->Range >> 14) * size0;
  UInt32 symbol;
  if (p->Code < newBound)
  {
    symbol = 0;
    p->Range = newBound;
  }
  else
  {
    symbol = 1;
    p->Code -= newBound;
    p->Range -= newBound;
  }
  Range_Normalize(p);
  return symbol;
}

static UInt32 Range_DecodeBit_RAR(void *pp, UInt32 size0)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  UInt32 bit, value = p->p.GetThreshold(p, PPMD_BIN_SCALE);
  if(value < size0)
  {
    bit = 0;
    p->p.Decode(p, 0, size0);
  }
  else
  {
    bit = 1;
    p->p.Decode(p, size0, PPMD_BIN_SCALE - size0);
  }
  return bit;
}

static void Ppmd7z_RangeDec_CreateVTable(CPpmd7z_RangeDec *p)
{
  p->p.GetThreshold = Range_GetThreshold;
  p->p.Decode = Range_Decode_7z;
  p->p.DecodeBit = Range_DecodeBit_7z;
}

static void PpmdRAR_RangeDec_CreateVTable(CPpmd7z_RangeDec *p)
{
  p->p.GetThreshold = Range_GetThreshold;
  p->p.Decode = Range_Decode_RAR;
  p->p.DecodeBit = Range_DecodeBit_RAR;
}

#define MASK(sym) ((signed char *)charMask)[sym]

static int Ppmd7_DecodeSymbol(CPpmd7 *p, IPpmd7_RangeDec *rc)
{
  size_t charMask[256 / sizeof(size_t)];
  if (p->MinContext->NumStats != 1)
  {
    CPpmd_State *s = Ppmd7_GetStats(p, p->MinContext);
    unsigned i;
    UInt32 count, hiCnt;
    if ((count = rc->GetThreshold(rc, p->MinContext->SummFreq)) < (hiCnt = s->Freq))
    {
      Byte symbol;
      rc->Decode(rc, 0, s->Freq);
      p->FoundState = s;
      symbol = s->Symbol;
      Ppmd7_Update1_0(p);
      return symbol;
    }
    p->PrevSuccess = 0;
    i = p->MinContext->NumStats - 1;
    do
    {
      if ((hiCnt += (++s)->Freq) > count)
      {
        Byte symbol;
        rc->Decode(rc, hiCnt - s->Freq, s->Freq);
        p->FoundState = s;
        symbol = s->Symbol;
        Ppmd7_Update1(p);
        return symbol;
      }
    }
    while (--i);
    if (count >= p->MinContext->SummFreq)
      return -2;
    p->HiBitsFlag = p->HB2Flag[p->FoundState->Symbol];
    rc->Decode(rc, hiCnt, p->MinContext->SummFreq - hiCnt);
    PPMD_SetAllBitsIn256Bytes(charMask);
    MASK(s->Symbol) = 0;
    i = p->MinContext->NumStats - 1;
    do { MASK((--s)->Symbol) = 0; } while (--i);
  }
  else
  {
    UInt16 *prob = Ppmd7_GetBinSumm(p);
    if (rc->DecodeBit(rc, *prob) == 0)
    {
      Byte symbol;
      *prob = (UInt16)PPMD_UPDATE_PROB_0(*prob);
      symbol = (p->FoundState = Ppmd7Context_OneState(p->MinContext))->Symbol;
      Ppmd7_UpdateBin(p);
      return symbol;
    }
    *prob = (UInt16)PPMD_UPDATE_PROB_1(*prob);
    p->InitEsc = PPMD7_kExpEscape[*prob >> 10];
    PPMD_SetAllBitsIn256Bytes(charMask);
    MASK(Ppmd7Context_OneState(p->MinContext)->Symbol) = 0;
    p->PrevSuccess = 0;
  }
  for (;;)
  {
    CPpmd_State *ps[256], *s;
    UInt32 freqSum, count, hiCnt;
    CPpmd_See *see;
    unsigned i, num, numMasked = p->MinContext->NumStats;
    do
    {
      p->OrderFall++;
      if (!p->MinContext->Suffix)
        return -1;
      p->MinContext = Ppmd7_GetContext(p, p->MinContext->Suffix);
    }
    while (p->MinContext->NumStats == numMasked);
    hiCnt = 0;
    s = Ppmd7_GetStats(p, p->MinContext);
    i = 0;
    num = p->MinContext->NumStats - numMasked;
    do
    {
      int k = (int)(MASK(s->Symbol));
      hiCnt += (s->Freq & k);
      ps[i] = s++;
      i -= k;
    }
    while (i != num);

    see = Ppmd7_MakeEscFreq(p, numMasked, &freqSum);
    freqSum += hiCnt;
    count = rc->GetThreshold(rc, freqSum);

    if (count < hiCnt)
    {
      Byte symbol;
      CPpmd_State **pps = ps;
      for (hiCnt = 0; (hiCnt += (*pps)->Freq) <= count; pps++);
      s = *pps;
      rc->Decode(rc, hiCnt - s->Freq, s->Freq);
      Ppmd_See_Update(see);
      p->FoundState = s;
      symbol = s->Symbol;
      Ppmd7_Update2(p);
      return symbol;
    }
    if (count >= freqSum)
      return -2;
    rc->Decode(rc, hiCnt, freqSum - hiCnt);
    see->Summ = (UInt16)(see->Summ + freqSum);
    do { MASK(ps[--i]->Symbol) = 0; } while (i != 0);
  }
}

/* ---------- Encode ---------- Ppmd7Enc.c */

#define kTopValue (1 << 24)

static void Ppmd7z_RangeEnc_Init(CPpmd7z_RangeEnc *p)
{
  p->Low = 0;
  p->Range = 0xFFFFFFFF;
  p->Cache = 0;
  p->CacheSize = 1;
}

static void RangeEnc_ShiftLow(CPpmd7z_RangeEnc *p)
{
  if ((UInt32)p->Low < (UInt32)0xFF000000 || (unsigned)(p->Low >> 32) != 0)
  {
    Byte temp = p->Cache;
    do
    {
      p->Stream->Write(p->Stream, (Byte)(temp + (Byte)(p->Low >> 32)));
      temp = 0xFF;
    }
    while(--p->CacheSize != 0);
    p->Cache = (Byte)((UInt32)p->Low >> 24);
  }
  p->CacheSize++;
  p->Low = ((UInt32)p->Low << 8) & 0xFFFFFFFF;
}

static void RangeEnc_Encode(CPpmd7z_RangeEnc *p, UInt32 start, UInt32 size, UInt32 total)
{
  p->Low += start * (p->Range /= total);
  p->Range *= size;
  while (p->Range < kTopValue)
  {
    p->Range <<= 8;
    RangeEnc_ShiftLow(p);
  }
}

static void RangeEnc_EncodeBit_0(CPpmd7z_RangeEnc *p, UInt32 size0)
{
  p->Range = (p->Range >> 14) * size0;
  while (p->Range < kTopValue)
  {
    p->Range <<= 8;
    RangeEnc_ShiftLow(p);
  }
}

static void RangeEnc_EncodeBit_1(CPpmd7z_RangeEnc *p, UInt32 size0)
{
  UInt32 newBound = (p->Range >> 14) * size0;
  p->Low += newBound;
  p->Range -= newBound;
  while (p->Range < kTopValue)
  {
    p->Range <<= 8;
    RangeEnc_ShiftLow(p);
  }
}

static void Ppmd7z_RangeEnc_FlushData(CPpmd7z_RangeEnc *p)
{
  unsigned i;
  for (i = 0; i < 5; i++)
    RangeEnc_ShiftLow(p);
}


#define MASK(sym) ((signed char *)charMask)[sym]

static void Ppmd7_EncodeSymbol(CPpmd7 *p, CPpmd7z_RangeEnc *rc, int symbol)
{
  size_t charMask[256 / sizeof(size_t)];
  if (p->MinContext->NumStats != 1)
  {
    CPpmd_State *s = Ppmd7_GetStats(p, p->MinContext);
    UInt32 sum;
    unsigned i;
    if (s->Symbol == symbol)
    {
      RangeEnc_Encode(rc, 0, s->Freq, p->MinContext->SummFreq);
      p->FoundState = s;
      Ppmd7_Update1_0(p);
      return;
    }
    p->PrevSuccess = 0;
    sum = s->Freq;
    i = p->MinContext->NumStats - 1;
    do
    {
      if ((++s)->Symbol == symbol)
      {
        RangeEnc_Encode(rc, sum, s->Freq, p->MinContext->SummFreq);
        p->FoundState = s;
        Ppmd7_Update1(p);
        return;
      }
      sum += s->Freq;
    }
    while (--i);
    
    p->HiBitsFlag = p->HB2Flag[p->FoundState->Symbol];
    PPMD_SetAllBitsIn256Bytes(charMask);
    MASK(s->Symbol) = 0;
    i = p->MinContext->NumStats - 1;
    do { MASK((--s)->Symbol) = 0; } while (--i);
    RangeEnc_Encode(rc, sum, p->MinContext->SummFreq - sum, p->MinContext->SummFreq);
  }
  else
  {
    UInt16 *prob = Ppmd7_GetBinSumm(p);
    CPpmd_State *s = Ppmd7Context_OneState(p->MinContext);
    if (s->Symbol == symbol)
    {
      RangeEnc_EncodeBit_0(rc, *prob);
      *prob = (UInt16)PPMD_UPDATE_PROB_0(*prob);
      p->FoundState = s;
      Ppmd7_UpdateBin(p);
      return;
    }
    else
    {
      RangeEnc_EncodeBit_1(rc, *prob);
      *prob = (UInt16)PPMD_UPDATE_PROB_1(*prob);
      p->InitEsc = PPMD7_kExpEscape[*prob >> 10];
      PPMD_SetAllBitsIn256Bytes(charMask);
      MASK(s->Symbol) = 0;
      p->PrevSuccess = 0;
    }
  }
  for (;;)
  {
    UInt32 escFreq;
    CPpmd_See *see;
    CPpmd_State *s;
    UInt32 sum;
    unsigned i, numMasked = p->MinContext->NumStats;
    do
    {
      p->OrderFall++;
      if (!p->MinContext->Suffix)
        return; /* EndMarker (symbol = -1) */
      p->MinContext = Ppmd7_GetContext(p, p->MinContext->Suffix);
    }
    while (p->MinContext->NumStats == numMasked);
    
    see = Ppmd7_MakeEscFreq(p, numMasked, &escFreq);
    s = Ppmd7_GetStats(p, p->MinContext);
    sum = 0;
    i = p->MinContext->NumStats;
    do
    {
      int cur = s->Symbol;
      if (cur == symbol)
      {
        UInt32 low = sum;
        CPpmd_State *s1 = s;
        do
        {
          sum += (s->Freq & (int)(MASK(s->Symbol)));
          s++;
        }
        while (--i);
        RangeEnc_Encode(rc, low, s1->Freq, sum + escFreq);
        Ppmd_See_Update(see);
        p->FoundState = s1;
        Ppmd7_Update2(p);
        return;
      }
      sum += (s->Freq & (int)(MASK(cur)));
      MASK(cur) = 0;
      s++;
    }
    while (--i);
    
    RangeEnc_Encode(rc, sum, escFreq, sum + escFreq);
    see->Summ = (UInt16)(see->Summ + sum + escFreq);
  }
}

const IPpmd7 __archive_ppmd7_functions =
{
  &Ppmd7_Construct,
  &Ppmd7_Alloc,
  &Ppmd7_Free,
  &Ppmd7_Init,
  &Ppmd7z_RangeDec_CreateVTable,
  &PpmdRAR_RangeDec_CreateVTable,
  &Ppmd7z_RangeDec_Init,
  &PpmdRAR_RangeDec_Init,
  &Ppmd7_DecodeSymbol,
  &Ppmd7z_RangeEnc_Init,
  &Ppmd7z_RangeEnc_FlushData,
  &Ppmd7_EncodeSymbol
};


/* ==== read_data_compressed, archive_read_support_format_rar.c lines 1860-2056,
 * VERBATIM (real callee on the crash path: this is the function whose
 * `rar->start_new_table` gate + is_ppmd_block dispatch to Ppmd7_DecodeSymbol IS the
 * mechanism). ==== */
static int
read_data_compressed(struct archive_read *a, const void **buff, size_t *size,
               int64_t *offset)
{
  struct rar *rar;
  int64_t start, end, actualend;
  size_t bs;
  int ret = (ARCHIVE_OK), sym, code, lzss_offset, length, i;

  rar = (struct rar *)(a->format->data);

  do {
    if (!rar->valid)
      return (ARCHIVE_FATAL);
    if (rar->ppmd_eod ||
       (rar->dictionary_size && rar->offset >= rar->unp_size))
    {
      if (rar->unp_offset > 0) {
        /*
         * We have unprocessed extracted data. write it out.
         */
        *buff = rar->unp_buffer;
        *size = rar->unp_offset;
        *offset = rar->offset_outgoing;
        rar->offset_outgoing += *size;
        /* Calculate File CRC. */
        rar->crc_calculated = crc32(rar->crc_calculated, *buff,
          (unsigned)*size);
        rar->unp_offset = 0;
        return (ARCHIVE_OK);
      }
      *buff = NULL;
      *size = 0;
      *offset = rar->offset;
      if (rar->file_crc != rar->crc_calculated) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "File CRC error");
        return (ARCHIVE_FATAL);
      }
      rar->entry_eof = 1;
      return (ARCHIVE_EOF);
    }

    if (!rar->is_ppmd_block && rar->dictionary_size && rar->bytes_uncopied > 0)
    {
      if (rar->bytes_uncopied > (rar->unp_buffer_size - rar->unp_offset))
        bs = rar->unp_buffer_size - rar->unp_offset;
      else
        bs = (size_t)rar->bytes_uncopied;
      ret = copy_from_lzss_window(a, buff, rar->offset, (int)bs);
      if (ret != ARCHIVE_OK)
        return (ret);
      rar->offset += bs;
      rar->bytes_uncopied -= bs;
      if (*buff != NULL) {
        rar->unp_offset = 0;
        *size = rar->unp_buffer_size;
        *offset = rar->offset_outgoing;
        rar->offset_outgoing += *size;
        /* Calculate File CRC. */
        rar->crc_calculated = crc32(rar->crc_calculated, *buff,
          (unsigned)*size);
        return (ret);
      }
      continue;
    }

    if (!rar->br.next_in &&
      (ret = rar_br_preparation(a, &(rar->br))) < ARCHIVE_WARN)
      return (ret);
    if (rar->start_new_table && ((ret = parse_codes(a)) < (ARCHIVE_WARN)))
      return (ret);

    if (rar->is_ppmd_block)
    {
      if ((sym = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
        &rar->ppmd7_context, &rar->range_dec.p)) < 0)
      {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "Invalid symbol");
        return (ARCHIVE_FATAL);
      }
      if(sym != rar->ppmd_escape)
      {
        lzss_emit_literal(rar, sym);
        rar->bytes_uncopied++;
      }
      else
      {
        if ((code = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
          &rar->ppmd7_context, &rar->range_dec.p)) < 0)
        {
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                            "Invalid symbol");
          return (ARCHIVE_FATAL);
        }

        switch(code)
        {
          case 0:
            rar->start_new_table = 1;
            return read_data_compressed(a, buff, size, offset);

          case 2:
            rar->ppmd_eod = 1;/* End Of ppmd Data. */
            continue;

          case 3:
            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                              "Parsing filters is unsupported.");
            return (ARCHIVE_FAILED);

          case 4:
            lzss_offset = 0;
            for (i = 2; i >= 0; i--)
            {
              if ((code = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
                &rar->ppmd7_context, &rar->range_dec.p)) < 0)
              {
                archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                                  "Invalid symbol");
                return (ARCHIVE_FATAL);
              }
              lzss_offset |= code << (i * 8);
            }
            if ((length = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
              &rar->ppmd7_context, &rar->range_dec.p)) < 0)
            {
              archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                                "Invalid symbol");
              return (ARCHIVE_FATAL);
            }
            lzss_emit_match(rar, lzss_offset + 2, length + 32);
            rar->bytes_uncopied += length + 32;
            break;

          case 5:
            if ((length = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
              &rar->ppmd7_context, &rar->range_dec.p)) < 0)
            {
              archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                                "Invalid symbol");
              return (ARCHIVE_FATAL);
            }
            lzss_emit_match(rar, 1, length + 4);
            rar->bytes_uncopied += length + 4;
            break;

         default:
           lzss_emit_literal(rar, sym);
           rar->bytes_uncopied++;
        }
      }
    }
    else
    {
      start = rar->offset;
      end = start + rar->dictionary_size;
      rar->filterstart = INT64_MAX;

      if ((actualend = expand(a, end)) < 0)
        return ((int)actualend);

      rar->bytes_uncopied = actualend - start;
      if (rar->bytes_uncopied == 0) {
          /* Broken RAR files cause this case.
          * NOTE: If this case were possible on a normal RAR file
          * we would find out where it was actually bad and
          * what we would do to solve it. */
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                            "Internal error extracting RAR file");
          return (ARCHIVE_FATAL);
      }
    }
    if (rar->bytes_uncopied > (rar->unp_buffer_size - rar->unp_offset))
      bs = rar->unp_buffer_size - rar->unp_offset;
    else
      bs = (size_t)rar->bytes_uncopied;
    ret = copy_from_lzss_window(a, buff, rar->offset, (int)bs);
    if (ret != ARCHIVE_OK)
      return (ret);
    rar->offset += bs;
    rar->bytes_uncopied -= bs;
    /*
     * If *buff is NULL, it means unp_buffer is not full.
     * So we have to continue extracting a RAR file.
     */
  } while (*buff == NULL);

  rar->unp_offset = 0;
  *size = rar->unp_buffer_size;
  *offset = rar->offset_outgoing;
  rar->offset_outgoing += *size;
  /* Calculate File CRC. */
  rar->crc_calculated = crc32(rar->crc_calculated, *buff, (unsigned)*size);
  return ret;
}


/* ==== archive_read_format_rar_read_data, VERBATIM from
 * data_cve/cve_9b585e19/target/original_function.c (checked byte-for-byte below). ==== */
static int
archive_read_format_rar_read_data(struct archive_read *a, const void **buff,
                                  size_t *size, int64_t *offset)
{
  struct rar *rar = (struct rar *)(a->format->data);
  int ret;

  if (rar->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
	  rar->has_encrypted_entries = 0;
  }

  if (rar->bytes_unconsumed > 0) {
      /* Consume as much as the decompressor actually used. */
      __archive_read_consume(a, rar->bytes_unconsumed);
      rar->bytes_unconsumed = 0;
  }

  *buff = NULL;
  if (rar->entry_eof || rar->offset_seek >= rar->unp_size) {
    *size = 0;
    *offset = rar->offset;
    if (*offset < rar->unp_size)
      *offset = rar->unp_size;
    return (ARCHIVE_EOF);
  }

  switch (rar->compression_method)
  {
  case COMPRESS_METHOD_STORE:
    ret = read_data_stored(a, buff, size, offset);
    break;

  case COMPRESS_METHOD_FASTEST:
  case COMPRESS_METHOD_FAST:
  case COMPRESS_METHOD_NORMAL:
  case COMPRESS_METHOD_GOOD:
  case COMPRESS_METHOD_BEST:
    ret = read_data_compressed(a, buff, size, offset);
    if (ret != ARCHIVE_OK && ret != ARCHIVE_WARN)
      __archive_ppmd7_functions.Ppmd7_Free(&rar->ppmd7_context);
    break;

  default:
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                      "Unsupported compression method for RAR file.");
    ret = ARCHIVE_FATAL;
    break;
  }
  return (ret);
}
/* ==== end verbatim ==== */

/* Real init order, copied from parse_codes()'s own PPMd-table-start sequence
 * (archive_read_support_format_rar.c ~2116-2145): Ppmd7_Free-before-Construct,
 * bytein wiring, PpmdRAR_RangeDec_CreateVTable, Ppmd7_Construct, dictionary-size-gated
 * Ppmd7_Alloc, Ppmd7_Init. We skip only PpmdRAR_RangeDec_Init (which reads 5 bytes via
 * bytein.Read/rar_br_* -- the RAR bitstream front end this CVE is not about) and
 * instead hand-set range_dec.{Low,Range,Code} directly: Range_GetThreshold (the only
 * range-decoder call Ppmd7_DecodeSymbol's chosen -2 branch makes -- see the module
 * docstring) is pure struct-field arithmetic, no Stream->Read needed to reach it. */
static void vb_ppmd_setup(struct archive_read *a, struct rar *rar,
                           unsigned dict_size, unsigned maxorder) {
    rar->bytein.a = a;
    rar->bytein.Read = &ppmd_read;
    __archive_ppmd7_functions.PpmdRAR_RangeDec_CreateVTable(&rar->range_dec);
    rar->range_dec.Stream = &rar->bytein;
    __archive_ppmd7_functions.Ppmd7_Construct(&rar->ppmd7_context);
    if (!__archive_ppmd7_functions.Ppmd7_Alloc(&rar->ppmd7_context, dict_size)) {
        fprintf(stderr, "vb: Ppmd7_Alloc failed\n");
        exit(0);
    }
    __archive_ppmd7_functions.Ppmd7_Init(&rar->ppmd7_context, maxorder);

    /* RestartModel() deterministically sets MinContext->NumStats=256, SummFreq=257
     * regardless of maxorder/dict_size (verified by reading archive_ppmd7.c) -- read
     * it back live rather than hardcoding, for robustness. */
    UInt32 total = (UInt32)rar->ppmd7_context.MinContext->SummFreq;
    rar->range_dec.Low = 0;
    rar->range_dec.Bottom = 0;
    rar->range_dec.Range = total;          /* Range_GetThreshold does Range/=total -> 1 */
    rar->range_dec.Code = total + 999983u;  /* count = Code/1 >= total -> forces `return -2;` */

    rar->is_ppmd_block = 1;
    rar->ppmd_valid = 1;
    rar->ppmd_eod = 0;
    rar->ppmd_escape = 2;
    rar->compression_method = COMPRESS_METHOD_GOOD;
    rar->start_new_table = 0;   /* mimics "a table is already active" -- the normal
                                  * steady state for every read_data call after the
                                  * first in one PPMd block; this is what the missing
                                  * `rar->start_new_table = 1;` after Ppmd7_Free should
                                  * have flipped back to 1. */
}

static void vb_init_common(struct archive_read *a, struct rar *rar,
                            struct archive_format_descriptor *fmt) {
    memset(a, 0, sizeof(*a));
    memset(rar, 0, sizeof(*rar));
    memset(fmt, 0, sizeof(*fmt));
    fmt->data = rar;
    a->format = fmt;
    rar->valid = 1;
    rar->entry_eof = 0;
    rar->offset = 0;
    rar->offset_seek = 0;
    rar->unp_size = (int64_t)1 << 40;  /* keeps offset_seek(0) < unp_size */
    rar->bytes_unconsumed = 0;
    rar->bytes_uncopied = 0;
    rar->has_encrypted_entries = 0;
    {
        static unsigned char br_dummy[4];
        rar->br.next_in = br_dummy;   /* non-NULL -> skips rar_br_preparation */
        rar->br.avail_in = 0;
        rar->br.cache_avail = 0;
        rar->br.cache_buffer = 0;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the raw input (ASAN-guarded). */
    unsigned char *seed = (unsigned char *)malloc((size_t)sz + 1);
    if (!seed) { fclose(f); return 0; }
    size_t n = sz > 0 ? fread(seed, 1, (size_t)sz, f) : 0;
    fclose(f);
    seed[n] = 0;

    unsigned char mode = n > 0 ? seed[0] : 2;
    unsigned char b1 = n > 1 ? seed[1] : 0x11;
    unsigned char b2 = n > 2 ? seed[2] : 0x22;

    struct archive_read a;
    struct rar rar;
    struct archive_format_descriptor fmt;
    vb_init_common(&a, &rar, &fmt);

    if (mode == 0) {
        /* TRIGGER: construct a real PPMd decode context, force the first call's
         * read_data_compressed to fail via Ppmd7_DecodeSymbol's `return -2;` branch
         * (frees the just-allocated, still-valid ppmd7_context) -- then call again
         * with the SAME rar. start_new_table is still 0 (the bug), so the second call
         * skips parse_codes() and re-enters Ppmd7_DecodeSymbol on the now-freed
         * ppmd7_context: heap-use-after-free READ of p->MinContext. */
        unsigned dict = 16384u + 1024u * (b1 % 32u);
        unsigned order = 2u + (b2 % 15u);
        vb_ppmd_setup(&a, &rar, dict, order);

        const void *buff; size_t size; int64_t offset;
        int rc1 = archive_read_format_rar_read_data(&a, &buff, &size, &offset);
        (void)rc1;
        int rc2 = archive_read_format_rar_read_data(&a, &buff, &size, &offset);
        (void)rc2;
    } else if (mode == 1) {
        /* SAFE: the IDENTICAL construction, called exactly ONCE. Exercises the same
         * real Ppmd7 construct/alloc/init/decode/free path (including the genuine
         * Ppmd7_Free of a validly-allocated context) with no stale second call -> the
         * process exits cleanly. The minimal-diff control for the TRIGGER case above. */
        unsigned dict = 16384u + 1024u * (b1 % 32u);
        unsigned order = 2u + (b2 % 15u);
        vb_ppmd_setup(&a, &rar, dict, order);

        const void *buff; size_t size; int64_t offset;
        int rc = archive_read_format_rar_read_data(&a, &buff, &size, &offset);
        (void)rc;
    } else {
        /* SAFE: unsupported compression method -> the target's own `default:` switch
         * arm (archive_set_error + ARCHIVE_FATAL) -- ppmd7_context is never
         * constructed at all. Exercises the real dispatch switch on a legitimately
         * reachable value outside {STORE,FASTEST,FAST,NORMAL,GOOD,BEST}. */
        rar.compression_method = (char)(0x40 + (b1 & 0x3F));
        const void *buff; size_t size; int64_t offset;
        int rc = archive_read_format_rar_read_data(&a, &buff, &size, &offset);
        (void)rc;
    }

    free(seed);
    return 0;
}
