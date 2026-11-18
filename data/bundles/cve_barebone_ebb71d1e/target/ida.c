unsigned __int8 *__cdecl DecompressRTF(variableLength *p, int *size)
{
  int v2; // eax
  unsigned int v3; // ecx
  unsigned int v4; // ecx
  unsigned int v5; // ecx
  unsigned __int8 v6; // dl
  unsigned int v7; // ecx
  unsigned int v8; // ecx
  unsigned __int8 v9; // dl
  unsigned int v10; // ecx
  bool v12; // [rsp+Bh] [rbp-65h]
  int v13; // [rsp+Ch] [rbp-64h]
  unsigned int end; // [rsp+10h] [rbp-60h]
  unsigned int lengtha; // [rsp+14h] [rbp-5Ch]
  unsigned int length; // [rsp+14h] [rbp-5Ch]
  unsigned int offseta; // [rsp+18h] [rbp-58h]
  int offsetb; // [rsp+18h] [rbp-58h]
  unsigned int offset; // [rsp+18h] [rbp-58h]
  int flags; // [rsp+1Ch] [rbp-54h]
  int flagCount; // [rsp+20h] [rbp-50h]
  unsigned int magic; // [rsp+24h] [rbp-4Ch]
  unsigned int uncompressedSize; // [rsp+28h] [rbp-48h]
  unsigned int compressedSize; // [rsp+2Ch] [rbp-44h]
  void *comp_Prebuf; // [rsp+30h] [rbp-40h]
  unsigned int out; // [rsp+40h] [rbp-30h]
  unsigned int in; // [rsp+44h] [rbp-2Ch]
  unsigned __int8 *src; // [rsp+48h] [rbp-28h]
  unsigned __int8 *srca; // [rsp+48h] [rbp-28h]
  unsigned __int8 *dst; // [rsp+50h] [rbp-20h]
  unsigned __int8 *dsta; // [rsp+50h] [rbp-20h]
  unsigned __int8 *dstb; // [rsp+50h] [rbp-20h]

  comp_Prebuf = calloc(0xD0uLL, 1uLL);
  if ( !comp_Prebuf )
  {
    printf("Out of Memory at %s : %i\n", "/work/harness.c", 79LL);
    return 0LL;
  }
  memcpy(
    comp_Prebuf,
    "{\\rtf1\\ansi\\mac\\deff0\\deftab720{\\fonttbl;}{\\f0\\fnil \\froman \\fswiss \\fmodern \\fscript \\fdecor MS Sans S"
    "erifSymbolArialTimes New RomanCourier{\\colortbl\\red0\\green0\\blue0\n"
    "\r\\par \\pard\\plain\\f0\\fs20\\b\\i\\u\\tab\\tx",
    0xCFuLL);
  src = p->data;
  if ( p->size < 20 )
  {
    printf("File too small\n");
    return 0LL;
  }
  compressedSize = SwapDWord(src, 4);
  uncompressedSize = SwapDWord(src + 4, 4);
  magic = SwapDWord(src + 8, 4);
  in = 16;
  if ( compressedSize != p->size - 4 )
  {
    printf(" Size Mismatch: %u != %i\n", compressedSize, (unsigned int)(p->size - 4));
    free(comp_Prebuf);
    return 0LL;
  }
  if ( magic == 1095517517 )
  {
    dst = (unsigned __int8 *)calloc(uncompressedSize, 1uLL);
    if ( !dst )
    {
      printf("Out of Memory at %s : %i\n", "/work/harness.c", 108LL);
      return 0LL;
    }
    memcpy(dst, src + 4, uncompressedSize);
LABEL_39:
    free(comp_Prebuf);
    return 0LL;
  }
  if ( magic != 1967544908 )
  {
    printf("Unknown compression type (magic number %x)\n", magic);
    goto LABEL_39;
  }
  flagCount = 0;
  flags = 0;
  if ( 0x7FFFFFFF - uncompressedSize <= 0xCF )
  {
    printf("Corrupted file\n");
    exit(-1);
  }
  dsta = (unsigned __int8 *)calloc(uncompressedSize + 207, 1uLL);
  if ( dsta )
  {
    memcpy(dsta, comp_Prebuf, 0xCFuLL);
    out = 207;
    while ( out < uncompressedSize + 207 )
    {
      v2 = flagCount++;
      if ( v2 % 8 )
      {
        v13 = flags >> 1;
      }
      else
      {
        v3 = in++;
        v13 = src[v3];
      }
      flags = v13;
      if ( (v13 & 1) == 1 )
      {
        offseta = src[in];
        v4 = in + 1;
        in += 2;
        lengtha = src[v4];
        offsetb = (lengtha >> 4) | (16 * offseta);
        length = (lengtha & 0xF) + 2;
        offset = offsetb + (out >> 12 << 12);
        if ( offset >= out )
          offset -= 4096;
        end = length + offset;
        while ( 1 )
        {
          v12 = 0;
          if ( offset < end )
          {
            v12 = 0;
            if ( out < uncompressedSize + 207 )
              v12 = offset < uncompressedSize + 207;
          }
          if ( !v12 )
            break;
          v5 = offset++;
          v6 = dsta[v5];
          v7 = out++;
          dsta[v7] = v6;
        }
      }
      else
      {
        if ( out >= uncompressedSize + 207 || in >= p->size )
        {
          printf("Corrupted stream\n");
          exit(-1);
        }
        v8 = in++;
        v9 = src[v8];
        v10 = out++;
        dsta[v10] = v9;
      }
    }
    srca = dsta;
    dstb = (unsigned __int8 *)calloc(uncompressedSize, 1uLL);
    if ( dstb )
    {
      memcpy(dstb, srca + 207, uncompressedSize);
      free(srca);
      *size = uncompressedSize;
      free(comp_Prebuf);
      return dstb;
    }
    else
    {
      printf("Out of Memory at %s : %i\n", "/work/harness.c", 158LL);
      return 0LL;
    }
  }
  else
  {
    printf("Out of Memory at %s : %i\n", "/work/harness.c", 120LL);
    return 0LL;
  }
}