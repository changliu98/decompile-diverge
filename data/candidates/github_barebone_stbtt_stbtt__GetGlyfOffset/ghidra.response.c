int stbtt__GetGlyfOffset(stbtt_fontinfo *info,int glyph_index)

{
  int iVar1;
  stbtt_uint16 sVar2;
  stbtt_uint32 sVar3;
  int local_38;
  int g2;
  int g1;
  int glyph_index_local;
  stbtt_fontinfo *info_local;
  int local_c;
  
  if ((info->cff).size == 0) {
    if (glyph_index < info->numGlyphs) {
      if (info->indexToLocFormat < 2) {
        if (info->indexToLocFormat == 0) {
          iVar1 = info->glyf;
          sVar2 = ttUSHORT(info->data + (long)(glyph_index << 1) + (long)info->loca);
          g1 = iVar1 + (uint)sVar2 * 2;
          iVar1 = info->glyf;
          sVar2 = ttUSHORT(info->data + (long)(glyph_index << 1) + (long)info->loca + 2);
          g2 = iVar1 + (uint)sVar2 * 2;
        }
        else {
          iVar1 = info->glyf;
          sVar3 = ttULONG(info->data + (long)(glyph_index << 2) + (long)info->loca);
          g1 = iVar1 + sVar3;
          iVar1 = info->glyf;
          sVar3 = ttULONG(info->data + (long)(glyph_index << 2) + (long)info->loca + 4);
          g2 = iVar1 + sVar3;
        }
        if (g1 == g2) {
          local_38 = -1;
        }
        else {
          local_38 = g1;
        }
        local_c = local_38;
      }
      else {
        local_c = -1;
      }
    }
    else {
      local_c = -1;
    }
    return local_c;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("!info->cff.size","func.c",0x647,
                "int stbtt__GetGlyfOffset(const stbtt_fontinfo *, int)");
}