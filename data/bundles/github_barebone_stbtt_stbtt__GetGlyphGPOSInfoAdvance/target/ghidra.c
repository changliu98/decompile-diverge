stbtt_int32 stbtt__GetGlyphGPOSInfoAdvance(stbtt_fontinfo *info,int glyph1,int glyph2)

{
  stbtt_uint16 sVar1;
  stbtt_uint16 sVar2;
  stbtt_uint16 sVar3;
  stbtt_uint16 sVar4;
  stbtt_int16 sVar5;
  stbtt_int32 sVar6;
  int iVar7;
  stbtt_int32 sVar8;
  stbtt_uint8 *psVar9;
  stbtt_uint8 *p;
  stbtt_uint8 *psVar10;
  stbtt_int16 xAdvance_1;
  stbtt_uint8 *class2Records;
  stbtt_uint8 *class1Records;
  stbtt_uint16 class2Count;
  stbtt_uint16 class1Count;
  int glyph2class;
  int glyph1class;
  stbtt_uint16 classDef2Offset;
  stbtt_uint16 classDef1Offset;
  stbtt_uint16 valueFormat2_1;
  stbtt_uint16 valueFormat1_1;
  stbtt_int16 xAdvance;
  stbtt_uint8 *pairValue;
  stbtt_uint16 secondGlyph;
  stbtt_uint8 *pairValueArray;
  stbtt_uint16 pairValueCount;
  stbtt_uint8 *pairValueTable;
  stbtt_uint16 pairPosOffset;
  stbtt_uint16 pairSetCount;
  stbtt_int32 valueRecordPairSizeInBytes;
  stbtt_uint16 valueFormat2;
  stbtt_uint16 valueFormat1;
  int needle;
  int straw;
  stbtt_int32 m;
  stbtt_int32 r;
  stbtt_int32 l;
  stbtt_int32 coverageIndex;
  stbtt_uint16 coverageOffset;
  stbtt_uint16 posFormat;
  stbtt_uint8 *table;
  stbtt_uint16 subtableOffset;
  stbtt_uint8 *subTableOffsets;
  stbtt_uint16 subTableCount;
  stbtt_uint16 lookupType;
  stbtt_uint8 *lookupTable;
  stbtt_uint16 lookupOffset;
  stbtt_int32 sti;
  stbtt_int32 i;
  stbtt_uint8 *data;
  stbtt_uint16 lookupCount;
  stbtt_uint8 *lookupList;
  stbtt_uint16 lookupListOffset;
  int glyph2_local;
  int glyph1_local;
  stbtt_fontinfo *info_local;
  
  if (info->gpos != 0) {
    psVar9 = info->data + info->gpos;
    sVar1 = ttUSHORT(psVar9);
    if ((sVar1 == 1) && (sVar1 = ttUSHORT(psVar9 + 2), sVar1 == 0)) {
      sVar1 = ttUSHORT(psVar9 + 8);
      psVar9 = psVar9 + (int)(uint)sVar1;
      sVar1 = ttUSHORT(psVar9);
      for (i = 0; i < (int)(uint)sVar1; i = i + 1) {
        sVar2 = ttUSHORT(psVar9 + (long)(i << 1) + 2);
        p = psVar9 + (int)(uint)sVar2;
        sVar2 = ttUSHORT(p);
        sVar3 = ttUSHORT(p + 4);
        if (sVar2 == 2) {
          for (sti = 0; sti < (int)(uint)sVar3; sti = sti + 1) {
            sVar2 = ttUSHORT(p + (long)(sti << 1) + 6);
            psVar10 = p + (int)(uint)sVar2;
            sVar2 = ttUSHORT(psVar10);
            sVar4 = ttUSHORT(psVar10 + 2);
            sVar6 = stbtt__GetCoverageIndex(psVar10 + (int)(uint)sVar4,glyph1);
            if (sVar6 != -1) {
              if (sVar2 != 1) {
                if (sVar2 != 2) {
                  return 0;
                }
                sVar1 = ttUSHORT(psVar10 + 4);
                sVar2 = ttUSHORT(psVar10 + 6);
                if ((sVar1 != 4) || (sVar2 != 0)) {
                  return 0;
                }
                sVar1 = ttUSHORT(psVar10 + 8);
                sVar2 = ttUSHORT(psVar10 + 10);
                sVar6 = stbtt__GetGlyphClass(psVar10 + (int)(uint)sVar1,glyph1);
                sVar8 = stbtt__GetGlyphClass(psVar10 + (int)(uint)sVar2,glyph2);
                sVar1 = ttUSHORT(psVar10 + 0xc);
                sVar2 = ttUSHORT(psVar10 + 0xe);
                if ((sVar6 < 0) || ((int)(uint)sVar1 <= sVar6)) {
                  return 0;
                }
                if ((-1 < sVar8) && (sVar8 < (int)(uint)sVar2)) {
                  sVar5 = ttSHORT(psVar10 + (long)(sVar8 << 1) +
                                            (long)(int)(sVar6 * (uint)sVar2 * 2) + 0x10);
                  return (int)sVar5;
                }
                return 0;
              }
              sVar2 = ttUSHORT(psVar10 + 4);
              sVar4 = ttUSHORT(psVar10 + 6);
              if ((sVar2 != 4) || (sVar4 != 0)) {
                return 0;
              }
              sVar2 = ttUSHORT(psVar10 + 8);
              sVar4 = ttUSHORT(psVar10 + (long)(sVar6 << 1) + 10);
              psVar10 = psVar10 + (int)(uint)sVar4;
              sVar4 = ttUSHORT(psVar10);
              if ((int)(uint)sVar2 <= sVar6) {
                return 0;
              }
              r = sVar4 - 1;
              l = 0;
              while (l <= r) {
                iVar7 = l + r >> 1;
                sVar2 = ttUSHORT(psVar10 + (long)(iVar7 * 4) + 2);
                if (glyph2 < (int)(uint)sVar2) {
                  r = iVar7 + -1;
                }
                else {
                  if (glyph2 <= (int)(uint)sVar2) {
                    sVar5 = ttSHORT(psVar10 + (long)(iVar7 * 4) + 2 + 2);
                    return (int)sVar5;
                  }
                  l = iVar7 + 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}