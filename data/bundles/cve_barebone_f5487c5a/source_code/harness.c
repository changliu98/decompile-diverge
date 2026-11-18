/* cve_barebone direct-call harness for CVE-2023-34474 (imagemagick)
 * Target: ReplaceXmpValue  (MagickCore/profile.c)
 * Bug class: heap-use-after-free WRITE (CWE-416).
 *
 * ReplaceXmpValue splices a new value into an XMP text blob at [start,end):
 *
 *   length=GetStringInfoLength(profile);
 *   value_length=strlen(value);
 *   new_length=length-(end-start)+value_length;
 *   if (new_length > length) SetStringInfoLength(profile,new_length);   // grow: OK, refetches datum after
 *   datum=(char *) GetStringInfoDatum(profile);
 *   memmove(datum+start+value_length,datum+end,length-end);
 *   memcpy(datum+start,value,value_length);
 *   if (new_length < length) {
 *     SetStringInfoLength(profile,new_length);      // <-- SHRINK: may realloc() the buffer
 *     *(datum+new_length)='\0';                     // <-- BUG: writes through the STALE `datum`
 *   }                                                //     captured *before* this realloc
 *
 * When the replacement value is shorter than the span it replaces, the trailing
 * SetStringInfoLength() shrinks (and, under a real allocator, may relocate) the
 * datum buffer -- but `datum` was cached earlier and is never re-read, so the
 * final `*(datum+new_length)='\0'` writes through a dangling pointer. The fix
 * commit (1061db7f80fdc9ef572ac60b55f408f7bab6e1b0) adds exactly one line:
 * `datum=(char *) GetStringInfoDatum(profile);` right before that write.
 *
 * SetStringInfoLength()'s allocator is libc realloc() (MagickCore/memory.c: the
 * default, non-Windows, non-anonymous-memory acquire/resize handlers are plain
 * malloc/realloc), which under ASan's allocator always services a size-changing
 * realloc as a fresh allocation + copy + poison-old -- so the shrink above
 * reliably relocates and the stale write is a genuine heap-use-after-free.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 *   + harness.flags: -fno-inline   (keeps ReplaceXmpValue a real frame in the
 *     ASAN backtrace instead of being folded into its single call site in main)
 */
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- MagickCore/method-attribute.h, verbatim constants ---- */
#define MagickExport
#define MagickPathExtent    4096       /* always >= max(PATH_MAX,4096) */
#define MagickCoreSignature 0xabacadabUL

/* ---- MagickCore/magick-type.h, verbatim ---- */
typedef enum
{
  MagickFalse = 0,
  MagickTrue = 1
} MagickBooleanType;

/* ---- MagickCore/string_.h, verbatim ---- */
typedef struct _StringInfo
{
  char
    *path;

  unsigned char
    *datum;

  size_t
    length,
    signature;

  char
    *name;
} StringInfo;

/* ---- MagickCore/exception.h: fatal-exception path is never taken by any of
 * our inputs (only reached on OOM); minimal faithful stub. ---- */
#define ResourceLimitFatalError 1
static void ThrowFatalException(const int severity,const char *tag)
{
  (void) severity;
  fprintf(stderr,"ThrowFatalException: %s\n",tag);
  abort();
}

/* ---- MagickCore/memory_.h: HeapOverflowSanityCheckGetSize(), verbatim ---- */
static inline MagickBooleanType HeapOverflowSanityCheckGetSize(
  const size_t count,const size_t quantum,size_t *const extent)
{
  size_t
    length;

  if ((count == 0) || (quantum == 0))
    return(MagickTrue);
  length=count*quantum;
  if (quantum != (length/count))
    {
      errno=ENOMEM;
      return(MagickTrue);
    }
  if (extent != NULL)
    *extent=length;
  return(MagickFalse);
}

/* GetMaxMemoryRequest() (MagickCore/memory.c): the real function lazily reads
 * a "system:max-memory-request" security policy and otherwise defaults to
 * MAGICK_SSIZE_MAX (effectively unlimited). We ship no policy subsystem, so
 * this minimal faithful stub reproduces the no-policy-configured default. */
static size_t GetMaxMemoryRequest(void)
{
  return (size_t) LONG_MAX;
}

/* AcquireQuantumMemory()/ResizeQuantumMemory() (MagickCore/memory.c): same
 * overflow-checked size computation as the real functions; the real
 * AcquireMagickMemory/ResizeMagickMemory default (non-Windows, non-anonymous-
 * memory) handlers are plain malloc/realloc (memory.c acquire/resize handler
 * table), so we call those directly -- behaviourally identical to the real
 * allocator for every size this harness ever requests, and critically:
 * REAL realloc() semantics (the exact mechanism the CVE depends on). */
static void *AcquireQuantumMemory(const size_t count,const size_t quantum)
{
  size_t
    size;

  if ((HeapOverflowSanityCheckGetSize(count,quantum,&size) != MagickFalse) ||
      (size > GetMaxMemoryRequest()))
    {
      errno=ENOMEM;
      return(NULL);
    }
  return(malloc(size == 0 ? 1UL : size));
}

static void *ResizeQuantumMemory(void *memory,const size_t count,
  const size_t quantum)
{
  size_t
    size;

  if ((HeapOverflowSanityCheckGetSize(count,quantum,&size) != MagickFalse) ||
      (size > GetMaxMemoryRequest()))
    {
      errno=ENOMEM;
      free(memory);
      return(NULL);
    }
  if (memory == (void *) NULL)
    return(malloc(size == 0 ? 1UL : size));
  return(realloc(memory,size == 0 ? 1UL : size));
}

/* ==== MagickCore/string.c, VERBATIM (GetStringInfoDatum / GetStringInfoLength /
 * SetStringInfoLength -- the exact allocator-driving logic ReplaceXmpValue's
 * bug depends on) ==== */
MagickExport unsigned char *GetStringInfoDatum(const StringInfo *string_info)
{
  assert(string_info != (StringInfo *) NULL);
  assert(string_info->signature == MagickCoreSignature);
  return(string_info->datum);
}

MagickExport size_t GetStringInfoLength(const StringInfo *string_info)
{
  assert(string_info != (StringInfo *) NULL);
  assert(string_info->signature == MagickCoreSignature);
  return(string_info->length);
}

MagickExport void SetStringInfoLength(StringInfo *string_info,
  const size_t length)
{
  assert(string_info != (StringInfo *) NULL);
  assert(string_info->signature == MagickCoreSignature);
  if (string_info->length == length)
    return;
  if (~length < MagickPathExtent)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  string_info->length=length;
  if (string_info->datum == (unsigned char *) NULL)
    string_info->datum=(unsigned char *) AcquireQuantumMemory(length+
      MagickPathExtent,sizeof(*string_info->datum));
  else
    string_info->datum=(unsigned char *) ResizeQuantumMemory(string_info->datum,
      length+MagickPathExtent,sizeof(*string_info->datum));
  if (string_info->datum == (unsigned char *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
}
/* ==== end verbatim callees ==== */

/* ==== VERBATIM from data_cve/cve_f5487c5a/target/original_function.c ==== */
static void ReplaceXmpValue(StringInfo *profile,size_t start,size_t end,
  const char *value)
{
  char
    *datum;

  size_t
    length,
    new_length,
    value_length;

  length=GetStringInfoLength(profile);
  value_length=strlen(value);
  new_length=length-(end-start)+value_length;
  if (new_length > length)
    SetStringInfoLength(profile,new_length);
  datum=(char *) GetStringInfoDatum(profile);
  memmove(datum+start+value_length,datum+end,length-end);
  memcpy(datum+start,value,value_length);
  if (new_length < length)
    {
      SetStringInfoLength(profile,new_length);
      *(datum+new_length)='\0';
    }
}
/* ==== end verbatim ==== */

/* Deterministic byte->printable mapping so the derived `value` string never
 * embeds a NUL (which would make strlen(value) disagree with our chosen
 * value_length) and so a short/empty pool still yields a stable fill. */
static unsigned char pool_byte(const unsigned char *pool,size_t pool_len,
  size_t idx)
{
  unsigned char
    b;

  if (pool_len == 0)
    return (unsigned char) ('A' + (idx % 26));
  b=pool[idx % pool_len];
  return (unsigned char) (0x20 + (b % 0x5f));  /* 0x20..0x7e, printable, non-NUL */
}

int main(int argc,char **argv)
{
  FILE
    *fp;

  long
    fsz;

  unsigned char
    *filebuf;

  size_t
    n;

  if (argc < 2)
    {
      fprintf(stderr,"usage: %s <input-file>\n",argv[0]);
      return 0;
    }
  fp=fopen(argv[1],"rb");
  if (fp == NULL)
    return 0;
  if (fseek(fp,0,SEEK_END) != 0)
    { fclose(fp); return 0; }
  fsz=ftell(fp);
  if (fsz < 4)
    { fclose(fp); return 0; }
  if (fseek(fp,0,SEEK_SET) != 0)
    { fclose(fp); return 0; }

  n=(size_t) fsz;
  filebuf=(unsigned char *) malloc(n);   /* HEAP-allocate the whole input, ASAN-guarded */
  if (filebuf == NULL)
    { fclose(fp); return 0; }
  if (fread(filebuf,1,n,fp) != n)
    { fclose(fp); free(filebuf); return 0; }
  fclose(fp);

  {
    unsigned int
      mode;

    size_t
      body_len,
      tag_len,
      max_start,
      start,
      end,
      value_len,
      pool_len,
      i;

    const unsigned char
      *pool;

    StringInfo
      profile;

    char
      *value;

    /* ---- decode ReplaceXmpValue's arguments from the fuzzed bytes ---- */
    mode=filebuf[0] % 3;                    /* 0: shrink(trigger) 1: exact(safe) 2: grow(safe) */
    body_len=16 + (filebuf[1] % 240);       /* [16,255]  -- initial profile datum length */
    tag_len=4 + (filebuf[2] % 12);          /* [4,15]    -- length of the span being replaced */
    max_start=body_len - tag_len;
    start=filebuf[3] % (max_start + 1);     /* [0,max_start] */
    end=start + tag_len;

    pool=filebuf + 4;
    pool_len=(n > 4) ? (n - 4) : 0;

    if (mode == 0)
      value_len=1 + (pool_byte(pool,pool_len,0) % (tag_len - 1));  /* [1,tag_len-1] < tag_len */
    else if (mode == 1)
      value_len=tag_len;                                          /* == tag_len */
    else
      value_len=tag_len + 1 + (pool_byte(pool,pool_len,1) % 16);   /* > tag_len */

    /* profile datum: mirrors AcquireStringInfo(body_len) -- datum sized
     * body_len+MagickPathExtent, contents fully attacker-controlled. */
    memset(&profile,0,sizeof(profile));
    profile.signature=MagickCoreSignature;
    profile.length=body_len;
    profile.datum=(unsigned char *) malloc(body_len + MagickPathExtent);
    if (profile.datum == NULL)
      { free(filebuf); return 0; }
    for (i=0; i < body_len; i++)
      profile.datum[i]=pool_byte(pool,pool_len,2 + i);

    /* replacement value: attacker-controlled, NUL-terminated, exactly value_len
     * printable bytes (never embeds 0x00, so strlen(value)==value_len). */
    value=(char *) malloc(value_len + 1);
    if (value == NULL)
      { free(filebuf); free(profile.datum); return 0; }
    for (i=0; i < value_len; i++)
      value[i]=(char) pool_byte(pool,pool_len,2 + body_len + i);
    value[value_len]='\0';

    ReplaceXmpValue(&profile,start,end,value);

    /* only reached for mode 1/2 (safe): mode 0 aborts inside ReplaceXmpValue */
    free(value);
    free(profile.datum);
  }

  free(filebuf);
  return 0;
}
