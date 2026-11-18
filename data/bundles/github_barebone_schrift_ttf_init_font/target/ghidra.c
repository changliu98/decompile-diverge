int init_font(SFT_Font *font)

{
  uint_least16_t uVar1;
  int_least16_t iVar2;
  int iVar3;
  uint_least32_t uVar4;
  uint_fast32_t hhea;
  uint_fast32_t head;
  uint_fast32_t scalerType;
  SFT_Font *font_local;
  int local_c;
  
  font_local = font;
  iVar3 = is_safe_offset(font,0,0xc);
  if (iVar3 == 0) {
    local_c = -1;
  }
  else {
    uVar4 = getu32(font_local,0);
    scalerType = (uint_fast32_t)uVar4;
    if ((scalerType == 0x10000) || (scalerType == 0x74727565)) {
      iVar3 = gettable(font_local,"head",&head);
      if (iVar3 < 0) {
        local_c = -1;
      }
      else {
        iVar3 = is_safe_offset(font_local,head,0x36);
        if (iVar3 == 0) {
          local_c = -1;
        }
        else {
          uVar1 = getu16(font_local,head + 0x12);
          font_local->unitsPerEm = uVar1;
          iVar2 = geti16(font_local,head + 0x32);
          font_local->locaFormat = iVar2;
          iVar3 = gettable(font_local,"hhea",&hhea);
          if (iVar3 < 0) {
            local_c = -1;
          }
          else {
            iVar3 = is_safe_offset(font_local,hhea,0x24);
            if (iVar3 == 0) {
              local_c = -1;
            }
            else {
              uVar1 = getu16(font_local,hhea + 0x22);
              font_local->numLongHmtx = uVar1;
              local_c = 0;
            }
          }
        }
      }
    }
    else {
      local_c = -1;
    }
  }
  return local_c;
}