/*
 * Direct-call ASAN harness for CVE-2016-7538 (ImageMagick), function
 * RemoveICCProfileFromResourceBlock (coders/psd.c).
 *
 * Bug: RemoveICCProfileFromResourceBlock() walks a PSD "image resource block"
 * -- a sequence of "8BIM" chunks, each: 4-byte magic "8BIM", 2-byte id,
 * 2-byte "short_sans" (ignored), 4-byte attacker-controlled `count`. When the
 * chunk id equals 0x040f (the ICC-profile resource id) it splices the chunk's
 * payload out of the buffer:
 *
 *   CopyMagickMemory(q, q+PSDQuantum(count)+12,
 *                     length-(PSDQuantum(count)+12)-(q-datum));
 *   SetStringInfoLength(bim_profile, length-(PSDQuantum(count)+12));
 *
 * `count` is read straight off the wire (PushLongPixel) with NO bound check
 * against the buffer's actual remaining length before it is used to compute
 * both the memcpy source pointer (q+PSDQuantum(count)+12) and the memcpy
 * size (a size_t subtraction that underflows whenever
 * PSDQuantum(count)+12 > length-(q-datum), which is trivial to arrange since
 * `count` is an independent 32-bit field). The fix (commit 82e2049) adds:
 *
 *   if ((q+PSDQuantum(count)+12) < (datum+length-16))
 *
 * around the copy. Without it, a crafted resource block with a legit "8BIM"
 * header, id==0x040f, and an oversized `count` drives CopyMagickMemory (a
 * memmove/memcpy wrapper) with a huge/underflowed length and an
 * out-of-bounds source pointer -> heap-buffer-overflow entirely inside
 * RemoveICCProfileFromResourceBlock's own body.
 *
 * This harness calls RemoveICCProfileFromResourceBlock() DIRECTLY on a
 * StringInfo whose `datum`/`length` are built straight from the input file
 * (heap-allocated, exact size, so ASAN's redzone sits right at the buffer's
 * true end). Everything else needed to run the function standalone is
 * copied from MagickCore, either byte-for-byte (the real callees on the
 * crash path: CopyMagickMemory, LocaleNCompare's glibc-strncasecmp branch,
 * PushLongPixel/PushShortPixel, the PSDQuantum macro) or as a minimal
 * faithful reimplementation for the incidental StringInfo accessors
 * (GetStringInfoLength/GetStringInfoDatum/SetStringInfoLength normally sit
 * on top of ImageMagick's own memory-limit-tracking allocator
 * (AcquireQuantumMemory/ResizeQuantumMemory); here they use plain
 * malloc/realloc with the same read/write semantics -- irrelevant to the
 * bug, which fires inside CopyMagickMemory before SetStringInfoLength is
 * ever reached on the triggering path).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>

/* ---- MagickCore/string_.h (StringInfo, trimmed to the fields this
   function touches) ---- */
typedef struct _StringInfo
{
  char
    *path;

  unsigned char
    *datum;

  size_t
    length,
    signature;
} StringInfo;

/* ---- MagickCore/quantum.h EndianType ---- */
typedef enum
{
  UndefinedEndian,
  LSBEndian,
  MSBEndian
} EndianType;

/* ---- MagickCore/string.c accessors -- minimal faithful reimplementation
   (real allocator swapped for libc malloc/realloc; same semantics) ---- */
static size_t GetStringInfoLength(const StringInfo *string_info)
{
  return string_info->length;
}

static unsigned char *GetStringInfoDatum(const StringInfo *string_info)
{
  return string_info->datum;
}

static void SetStringInfoLength(StringInfo *string_info, const size_t length)
{
  unsigned char *datum = (unsigned char *) realloc(string_info->datum, length + 64);
  if (datum == NULL)
  {
    fprintf(stderr, "SetStringInfoLength: allocation failed\n");
    exit(1);
  }
  string_info->datum = datum;
  string_info->length = length;
}

/* ---- MagickCore/locale.c LocaleNCompare -- this platform (glibc,
   MAGICKCORE_HAVE_STRNCASECMP) takes the strncasecmp branch verbatim ---- */
static int LocaleNCompare(const char *p, const char *q, const size_t length)
{
  if ((p == (char *) NULL) && (q == (char *) NULL))
    return(0);
  if (p == (char *) NULL)
    return(-1);
  if (q == (char *) NULL)
    return(1);
  return(strncasecmp(p,q,length));
}

/* ---- MagickCore/memory.c CopyMagickMemory -- verbatim ---- */
static void *CopyMagickMemory(void *destination,const void *source,
  const size_t size)
{
  register const unsigned char
    *p;

  register unsigned char
    *q;

  p=(const unsigned char *) source;
  q=(unsigned char *) destination;
  if (((q+size) < p) || (q > (p+size)))
    switch (size)
    {
      default: return(memcpy(destination,source,size));
      case 8: *q++=(*p++);
      case 7: *q++=(*p++);
      case 6: *q++=(*p++);
      case 5: *q++=(*p++);
      case 4: *q++=(*p++);
      case 3: *q++=(*p++);
      case 2: *q++=(*p++);
      case 1: *q++=(*p++);
      case 0: return(destination);
    }
  return(memmove(destination,source,size));
}

/* ---- MagickCore/quantum-private.h Push{Long,Short}Pixel -- verbatim ---- */
static inline const unsigned char *PushLongPixel(const EndianType endian,
  const unsigned char *pixels,unsigned int *pixel)
{
  register unsigned int
    quantum;

  if (endian == LSBEndian)
    {
      quantum=((unsigned int) *pixels++);
      quantum|=((unsigned int) *pixels++ << 8);
      quantum|=((unsigned int) *pixels++ << 16);
      quantum|=((unsigned int) *pixels++ << 24);
      *pixel=quantum;
      return(pixels);
    }
  quantum=((unsigned int) *pixels++ << 24);
  quantum|=((unsigned int) *pixels++ << 16);
  quantum|=((unsigned int) *pixels++ << 8);
  quantum|=((unsigned int) *pixels++);
  *pixel=quantum;
  return(pixels);
}

static inline const unsigned char *PushShortPixel(const EndianType endian,
  const unsigned char *pixels,unsigned short *pixel)
{
  register unsigned int
    quantum;

  if (endian == LSBEndian)
    {
      quantum=(unsigned int) *pixels++;
      quantum|=(unsigned int) (*pixels++ << 8);
      *pixel=(unsigned short) (quantum & 0xffff);
      return(pixels);
    }
  quantum=(unsigned int) (*pixels++ << 8);
  quantum|=(unsigned int) *pixels++;
  *pixel=(unsigned short) (quantum & 0xffff);
  return(pixels);
}

/* ---- coders/psd.c macro ---- */
#define PSDQuantum(x)  (((ssize_t) (x)+1) & -2)

/* ==== TARGET: byte-for-byte from target/original_function.c ==== */
static void RemoveICCProfileFromResourceBlock(StringInfo *bim_profile)
{
  register const unsigned char
    *p;

  size_t
    length;

  unsigned char
    *datum;

  unsigned int
    count,
    long_sans;

  unsigned short
    id,
    short_sans;

  length=GetStringInfoLength(bim_profile);
  if (length < 16)
    return;
  datum=GetStringInfoDatum(bim_profile);
  for (p=datum; (p >= datum) && (p < (datum+length-16)); )
  {
    register unsigned char
      *q;

    q=(unsigned char *) p;
    if (LocaleNCompare((const char *) p,"8BIM",4) != 0)
      break;
    p=PushLongPixel(MSBEndian,p,&long_sans);
    p=PushShortPixel(MSBEndian,p,&id);
    p=PushShortPixel(MSBEndian,p,&short_sans);
    p=PushLongPixel(MSBEndian,p,&count);
    if (id == 0x0000040f)
      {
        (void) CopyMagickMemory(q,q+PSDQuantum(count)+12,length-
          (PSDQuantum(count)+12)-(q-datum));
        SetStringInfoLength(bim_profile,length-(PSDQuantum(count)+12));
        break;
      }
    p+=count;
    if ((count & 0x01) != 0)
      p++;
  }
}
/* ==== END TARGET ==== */

int main(int argc, char **argv)
{
  StringInfo
    bim_profile;

  FILE
    *f;

  long
    sz;

  unsigned char
    *buf;

  size_t
    n;

  if (argc < 2)
    return 0;
  f=fopen(argv[1],"rb");
  if (f == NULL)
    return 0;
  if (fseek(f,0,SEEK_END) != 0)
  {
    fclose(f);
    return 0;
  }
  sz=ftell(f);
  if (sz < 0)
  {
    fclose(f);
    return 0;
  }
  rewind(f);
  buf=(unsigned char *) malloc((size_t) (sz > 0 ? sz : 1));
  if (buf == NULL)
  {
    fclose(f);
    return 0;
  }
  n=fread(buf,1,(size_t) sz,f);
  fclose(f);

  bim_profile.path=NULL;
  bim_profile.datum=buf;
  bim_profile.length=n;
  bim_profile.signature=0;

  RemoveICCProfileFromResourceBlock(&bim_profile);

  free(bim_profile.datum);
  return 0;
}
