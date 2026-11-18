/* cve_barebone direct-call harness for cve_ebb71d1e (ytnef, CVE-2017-6802)
 * Target: DecompressRTF (lib/ytnef.c) -- heap-buffer-overflow READ (CWE-125).
 * See scripts/gen_dc_cve_ebb71d1e.py (this file's generator) for the full writeup.
 * Short version: fix commit 22f8346c8d4f0020a40d9f258fdb3bfc097359cc added
 * `&& (in < p->size)` to the LZFu decompression loop's while-condition. Before the
 * fix, three reads of the compressed source buffer inside the loop -- the per-8
 * flags byte, and the reference "offset"/"length" bytes -- have NO bounds check on
 * `in` at all (only the literal-copy site was already guarded). A stream that runs
 * dry at any of those three sites before the declared output length is reached
 * drives `in` past the end of the caller's buffer -> heap-buffer-overflow READ.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* ---- real types (source_code/lib/tnef-types.h, verbatim) ---- */
#define BYTE unsigned char
#define WORD unsigned short int
#define DWORD unsigned int
#define ULONG unsigned int
#define DDWORD unsigned long long

typedef struct {
  BYTE *data;
  int size;
} variableLength;

/* ---- real macros (source_code/lib/ytnef.c, verbatim source lines) ---- */
#define RTF_PREBUF "{\\rtf1\\ansi\\mac\\deff0\\deftab720{\\fonttbl;}{\\f0\\fnil \\froman \\fswiss \\fmodern \\fscript \\fdecor MS Sans SerifSymbolArialTimes New RomanCourier{\\colortbl\\red0\\green0\\blue0\n\r\\par \\pard\\plain\\f0\\fs20\\b\\i\\u\\tab\\tx"
#define ALLOCCHECK_CHAR(x) { if(!x) { printf("Out of Memory at %s : %i\n", __FILE__, __LINE__); return(NULL); } }

/* ---- real callee SwapDWord (source_code/lib/ytnef.c, verbatim source lines) ---- */
DWORD SwapDWord(BYTE *p, int size) {
  union BYTES2DWORD
  {
      DWORD dword;
      BYTE  bytes[sizeof(DWORD)];
  };
  
  union BYTES2DWORD converter;
  converter.dword = 0;
  int i = 0;  
  int correct = size > sizeof(DWORD) ? sizeof(DWORD) : size;
  
#ifdef WORDS_BIGENDIAN
  for (i = 0; i < correct; ++i)
  {
      converter.bytes[i] = p[correct - i];
  }
#else
  for (i = 0; i < correct; ++i)
  {
      converter.bytes[i] = p[i];
  }
#endif
  
  return converter.dword;
}


/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the ASAN report keeps its own frame (dc_batch requires the target
 * function name in the crash backtrace). */
__attribute__((noinline))
BYTE *DecompressRTF(variableLength *p, int *size) {
  BYTE *dst; // destination for uncompressed bytes
  BYTE *src;
  unsigned int in;
  unsigned int out;
  variableLength comp_Prebuf;
  ULONG compressedSize, uncompressedSize, magic;

  comp_Prebuf.size = strlen(RTF_PREBUF);
  comp_Prebuf.data = calloc(comp_Prebuf.size+1, 1);
  ALLOCCHECK_CHAR(comp_Prebuf.data);
  memcpy(comp_Prebuf.data, RTF_PREBUF, comp_Prebuf.size);

  src = p->data;
  in = 0;

  if (p->size < 20) {
    printf("File too small\n");
    return(NULL);
  }
  compressedSize = (ULONG)SwapDWord((BYTE*)src + in, 4);
  in += 4;
  uncompressedSize = (ULONG)SwapDWord((BYTE*)src + in, 4);
  in += 4;
  magic = SwapDWord((BYTE*)src + in, 4);
  in += 4;
  in += 4;

  // check size excluding the size field itself
  if (compressedSize != p->size - 4) {
    printf(" Size Mismatch: %u != %i\n", compressedSize, p->size - 4);
    free(comp_Prebuf.data);
    return NULL;
  }

  // process the data
  if (magic == 0x414c454d) {
    // magic number that identifies the stream as a uncompressed stream
    dst = calloc(uncompressedSize, 1);
    ALLOCCHECK_CHAR(dst);
    memcpy(dst, src + 4, uncompressedSize);
  } else if (magic == 0x75465a4c) {
    // magic number that identifies the stream as a compressed stream
    int flagCount = 0;
    int flags = 0;
    // Prevent overflow on 32 Bit Systems
    if (comp_Prebuf.size >= INT_MAX - uncompressedSize) {
       printf("Corrupted file\n");
       exit(-1);
    }
    dst = calloc(comp_Prebuf.size + uncompressedSize, 1);
    ALLOCCHECK_CHAR(dst);
    memcpy(dst, comp_Prebuf.data, comp_Prebuf.size);
    out = comp_Prebuf.size;
    while (out < (comp_Prebuf.size + uncompressedSize)) {
      // each flag byte flags 8 literals/references, 1 per bit
      flags = (flagCount++ % 8 == 0) ? src[in++] : flags >> 1;
      if ((flags & 1) == 1) { // each flag bit is 1 for reference, 0 for literal
        unsigned int offset = src[in++];
        unsigned int length = src[in++];
        unsigned int end;
        offset = (offset << 4) | (length >> 4); // the offset relative to block start
        length = (length & 0xF) + 2; // the number of bytes to copy
        // the decompression buffer is supposed to wrap around back
        // to the beginning when the end is reached. we save the
        // need for such a buffer by pointing straight into the data
        // buffer, and simulating this behaviour by modifying the
        // pointers appropriately.
        offset = (out / 4096) * 4096 + offset;
        if (offset >= out) // take from previous block
          offset -= 4096;
        // note: can't use System.arraycopy, because the referenced
        // bytes can cross through the current out position.
        end = offset + length;
        while ((offset < end) && (out < (comp_Prebuf.size + uncompressedSize))
             && (offset < (comp_Prebuf.size + uncompressedSize)))
          dst[out++] = dst[offset++];
      } else { // literal
        if ((out >= (comp_Prebuf.size + uncompressedSize)) ||
            (in >= p->size)) {
          printf("Corrupted stream\n");
          exit(-1);
        }
        dst[out++] = src[in++];
      }
    }
    // copy it back without the prebuffered data
    src = dst;
    dst = calloc(uncompressedSize, 1);
    ALLOCCHECK_CHAR(dst);
    memcpy(dst, src + comp_Prebuf.size, uncompressedSize);
    free(src);
    *size = uncompressedSize;
    free(comp_Prebuf.data);
    return dst;
  } else { // unknown magic number
    printf("Unknown compression type (magic number %x)\n", magic);
  }
  free(comp_Prebuf.data);
  return NULL;
}
/* ================= driver ================= */
int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) return 0;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 0; }
    long sz = ftell(fp);
    if (sz < 0) sz = 0;
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 0; }

    /* HEAP-allocate EXACTLY sz bytes (ASAN-guarded, no slack past the real data) so
     * an off-by-one overread lands exactly on the redzone. */
    BYTE *buf = (BYTE *)malloc(sz > 0 ? (size_t)sz : 1);
    if (!buf) { fclose(fp); return 0; }
    size_t n = sz > 0 ? fread(buf, 1, (size_t)sz, fp) : 0;
    fclose(fp);

    variableLength p;
    p.data = buf;
    p.size = (int)n;

    int outsize = 0;
    BYTE *result = DecompressRTF(&p, &outsize);
    if (result) free(result);
    free(buf);
    return 0;
}
