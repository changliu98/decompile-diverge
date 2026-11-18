#include <string.h>

// Assuming standard GD library types and functions are defined elsewhere
typedef struct { int offset; int size; } t_chunk_info;
typedef struct { /* ... */ } gdIOCtx;
typedef gdIOCtx *gdIOCtxPtr;

int gdGetC(gdIOCtxPtr ctx);
int gdGetWord(int *val, gdIOCtxPtr ctx);
int gdGetInt(int *val, gdIOCtxPtr ctx);
void gdFree(void *ptr);
int overflow2(int a, int b);

// Reconstructed allocator (originally decompiled as chip::BindingManager::...)
void *gdMalloc(size_t size, unsigned int flags);

int __cdecl gd2GetHeader(
        gdIOCtxPtr in,
        int *sx,
        int *sy,
        int *cs_0,
        int *vers,
        int *fmt,
        int *ncx,
        int *ncy,
        t_chunk_info **chunkIdx)
{
  int nc;
  t_chunk_info *cidx;
  char id[5];
  int ch, i;

  // Read the 4-byte magic identifier ("gd2\0")
  for (i = 0; i < 4; ++i)
  {
    ch = gdGetC(in);
    if (ch == -1)
      return 0;
    id[i] = ch;
  }
  id[4] = 0;

  // Validate magic string and read header fields sequentially
  if (strcmp(id, "gd2") != 0)
    return 0;

  if (gdGetWord(vers, in) != 1 || (*vers != 1 && *vers != 2))
    return 0;

  if (!gdGetWord(sx, in) || !gdGetWord(sy, in))
    return 0;

  if (gdGetWord(cs_0, in) != 1 || *cs_0 < 64 || *cs_0 > 4096)
    return 0;

  if (gdGetWord(fmt, in) != 1 || (*fmt != 1 && *fmt != 2 && *fmt != 3 && *fmt != 4))
    return 0;

  if (gdGetWord(ncx, in) != 1 || gdGetWord(ncy, in) != 1)
    return 0;

  // If the format does not contain chunk index data, we are done
  if (*fmt != 2 && *fmt != 4)
    return 1;

  // Allocate and read the chunk index array
  nc = *ncy * *ncx;
  if (overflow2(8, nc) || 8 * nc <= 0)
    return 0;

  cidx = (t_chunk_info *)gdMalloc(8 * nc, 1);
  if (!cidx)
    return 0;

  for (i = 0; i < nc; ++i)
  {
    if (gdGetInt(&cidx[i].offset, in) != 1 || 
        gdGetInt(&cidx[i].size, in) != 1 ||
        cidx[i].offset < 0 || 
        cidx[i].size < 0)
    {
      gdFree(cidx);
      return 0;
    }
  }

  *chunkIdx = cidx;
  return 1;
}