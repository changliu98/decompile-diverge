uchar * DecompressRTF(variableLength *p,int *size)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  void *__dest;
  void *pvVar4;
  uchar *puVar5;
  int iVar6;
  ulong uVar7;
  bool bVar8;
  uint local_6c;
  uint end;
  uint length;
  uint offset;
  int flags;
  int flagCount;
  uint magic;
  uint uncompressedSize;
  uint compressedSize;
  variableLength comp_Prebuf;
  uint out;
  uint in;
  uchar *src;
  uchar *dst;
  int *size_local;
  variableLength *p_local;
  
  __dest = calloc(0xd0,1);
  if (__dest == (void *)0x0) {
    printf("Out of Memory at %s : %i\n","/work/harness.c",0x4f);
  }
  else {
    memcpy(__dest,
           "{\\rtf1\\ansi\\mac\\deff0\\deftab720{\\fonttbl;}{\\f0\\fnil \\froman \\fswiss \\fmodern \\fscript \\fdecor MS Sans SerifSymbolArialTimes New RomanCourier{\\colortbl\\red0\\green0\\blue0\n\r\\par \\pard\\plain\\f0\\fs20\\b\\i\\u\\tab\\tx"
           ,0xcf);
    puVar5 = p->data;
    if (p->size < 0x14) {
      printf("File too small\n");
    }
    else {
      uVar1 = SwapDWord(puVar5,4);
      uVar2 = SwapDWord(puVar5 + 4,4);
      uVar3 = SwapDWord(puVar5 + 8,4);
      if (uVar1 == p->size - 4U) {
        if (uVar3 == 0x414c454d) {
          pvVar4 = calloc((ulong)uVar2,1);
          if (pvVar4 == (void *)0x0) {
            printf("Out of Memory at %s : %i\n","/work/harness.c",0x6c);
            return (uchar *)0x0;
          }
          memcpy(pvVar4,puVar5 + 4,(ulong)uVar2);
        }
        else {
          if (uVar3 == 0x75465a4c) {
            flagCount = 0;
            flags = 0;
            if (0x7fffffff - uVar2 < 0xd0) {
              printf("Corrupted file\n");
                    /* WARNING: Subroutine does not return */
              exit(-1);
            }
            pvVar4 = calloc((ulong)(uVar2 + 0xcf),1);
            if (pvVar4 == (void *)0x0) {
              printf("Out of Memory at %s : %i\n","/work/harness.c",0x78);
              return (uchar *)0x0;
            }
            memcpy(pvVar4,__dest,0xcf);
            out = 0xcf;
            in = 0x10;
            while( true ) {
              while( true ) {
                if (uVar2 + 0xcf <= out) {
                  puVar5 = calloc((ulong)uVar2,1);
                  if (puVar5 == (uchar *)0x0) {
                    printf("Out of Memory at %s : %i\n","/work/harness.c",0x9e);
                    return (uchar *)0x0;
                  }
                  memcpy(puVar5,(void *)((long)pvVar4 + 0xcf),(ulong)uVar2);
                  free(pvVar4);
                  *size = uVar2;
                  free(__dest);
                  return puVar5;
                }
                iVar6 = flagCount + 1;
                if (flagCount % 8 == 0) {
                  local_6c = (uint)puVar5[in];
                  in = in + 1;
                }
                else {
                  local_6c = flags >> 1;
                }
                flags = local_6c;
                flagCount = iVar6;
                if ((local_6c & 1) != 1) break;
                uVar1 = in + 1;
                uVar7 = (ulong)in;
                in = in + 2;
                offset = (out & 0xfffff000) +
                         ((uint)puVar5[uVar7] << 4 | (uint)(puVar5[uVar1] >> 4));
                if (out <= offset) {
                  offset = offset - 0x1000;
                }
                uVar1 = offset + (puVar5[uVar1] & 0xf) + 2;
                while( true ) {
                  bVar8 = false;
                  if ((offset < uVar1) && (bVar8 = false, out < uVar2 + 0xcf)) {
                    bVar8 = offset < uVar2 + 0xcf;
                  }
                  if (!bVar8) break;
                  *(undefined1 *)((long)pvVar4 + (ulong)out) =
                       *(undefined1 *)((long)pvVar4 + (ulong)offset);
                  offset = offset + 1;
                  out = out + 1;
                }
              }
              if ((uVar2 + 0xcf <= out) || ((uint)p->size <= in)) break;
              *(uchar *)((long)pvVar4 + (ulong)out) = puVar5[in];
              out = out + 1;
              in = in + 1;
            }
            printf("Corrupted stream\n");
                    /* WARNING: Subroutine does not return */
            exit(-1);
          }
          printf("Unknown compression type (magic number %x)\n",(ulong)uVar3);
        }
        free(__dest);
      }
      else {
        printf(" Size Mismatch: %u != %i\n",(ulong)uVar1,(ulong)(p->size - 4));
        free(__dest);
      }
    }
  }
  return (uchar *)0x0;
}