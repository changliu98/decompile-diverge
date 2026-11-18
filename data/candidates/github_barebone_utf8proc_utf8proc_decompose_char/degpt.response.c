utf8proc_ssize_t
utf8proc_decompose_char
          (utf8proc_int32_t uc,utf8proc_int32_t *dst,utf8proc_ssize_t bufsize,
          utf8proc_option_t options,int *last_boundclass)

{
  short sVar1;
  utf8proc_bool uVar2;
  int iVar3;
  utf8proc_property_t *puVar4;
  utf8proc_ssize_t uVar5;
  utf8proc_bool boundary;
  utf8proc_int32_t hangul_tindex;
  utf8proc_int32_t hangul_sindex;
  utf8proc_propval_t category;
  utf8proc_property_t *property;
  int *last_boundclass_local;
  utf8proc_option_t options_local;
  utf8proc_ssize_t bufsize_local;
  utf8proc_int32_t *dst_local;
  utf8proc_int32_t uc_local;
  utf8proc_ssize_t local_10;
  
  if ((uc < 0) || (0x10ffff < uc)) {
    local_10 = -4;
  }
  else {
    puVar4 = unsafe_get_property(uc);
    sVar1 = puVar4->category;
    iVar3 = uc + -0xac00;
    if ((((options & (UTF8PROC_DECOMPOSE|UTF8PROC_COMPOSE)) == 0) || (iVar3 < 0)) ||
       (0x2ba3 < iVar3)) {
      if (((options & UTF8PROC_REJECTNA) == 0) || (sVar1 != 0)) {
        if (((options & UTF8PROC_IGNORE) == 0) || (puVar4->ignorable == 0)) {
          if (((options & UTF8PROC_STRIPNA) == 0) || (sVar1 != 0)) {
            if ((options & UTF8PROC_LUMP) != 0) {
              if (sVar1 == 0x17) {
                uVar5 = utf8proc_decompose_char
                                  (0x20,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if ((((uc == 0x2018) || (uc == 0x2019)) || (uc == 700)) || (uc == 0x2c8)) {
                uVar5 = utf8proc_decompose_char
                                  (0x27,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if ((sVar1 == 0xd) || (uc == 0x2212)) {
                uVar5 = utf8proc_decompose_char
                                  (0x2d,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if ((uc == 0x2044) || (uc == 0x2215)) {
                uVar5 = utf8proc_decompose_char
                                  (0x2f,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if (uc == 0x2236) {
                uVar5 = utf8proc_decompose_char
                                  (0x3a,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if (((uc == 0x2039) || (uc == 0x2329)) || (uc == 0x3008)) {
                uVar5 = utf8proc_decompose_char
                                  (0x3c,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if (((uc == 0x203a) || (uc == 0x232a)) || (uc == 0x3009)) {
                uVar5 = utf8proc_decompose_char
                                  (0x3e,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if (uc == 0x2216) {
                uVar5 = utf8proc_decompose_char
                                  (0x5c,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if (((uc == 0x2c4) || (uc == 0x2c6)) || ((uc == 0x2038 || (uc == 0x2303)))) {
                uVar5 = utf8proc_decompose_char
                                  (0x5e,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if ((sVar1 == 0xc) || (uc == 0x2cd)) {
                uVar5 = utf8proc_decompose_char
                                  (0x5f,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if (uc == 0x2cb) {
                uVar5 = utf8proc_decompose_char
                                  (0x60,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if (uc == 0x2223) {
                uVar5 = utf8proc_decompose_char
                                  (0x7c,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if (uc == 0x223c) {
                uVar5 = utf8proc_decompose_char
                                  (0x7e,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
              if ((((options & UTF8PROC_NLF2LS) != 0) && ((options & UTF8PROC_NLF2PS) != 0)) &&
                 ((sVar1 == 0x18 || (sVar1 == 0x19)))) {
                uVar5 = utf8proc_decompose_char
                                  (10,dst,bufsize,options & ~UTF8PROC_LUMP,last_boundclass);
                return uVar5;
              }
            }
            if (((options & UTF8PROC_STRIPMARK) == 0) ||
               (((sVar1 != 6 && (sVar1 != 7)) && (sVar1 != 8)))) {
              if (((options & UTF8PROC_CASEFOLD) == 0) || (puVar4->casefold_seqindex == 0xffff)) {
                if (((options & (UTF8PROC_DECOMPOSE|UTF8PROC_COMPOSE)) == 0) ||
                   ((puVar4->decomp_seqindex == 0xffff ||
                    ((puVar4->decomp_type != 0 && ((options & UTF8PROC_COMPAT) == 0)))))) {
                  if (((options & UTF8PROC_CHARBOUND) == 0) ||
                     (uVar2 = grapheme_break_extended
                                        (0,puVar4->boundclass,0,puVar4->indic_conjunct_break,
                                         last_boundclass), !uVar2)) {
                    if (0 < bufsize) {
                      *dst = uc;
                    }
                    local_10 = 1;
                  }
                  else {
                    if (0 < bufsize) {
                      *dst = -1;
                    }
                    if (1 < bufsize) {
                      dst[1] = uc;
                    }
                    local_10 = 2;
                  }
                }
                else {
                  local_10 = seqindex_write_char_decomposed
                                       (puVar4->decomp_seqindex,dst,bufsize,options,last_boundclass)
                  ;
                }
              }
              else {
                local_10 = seqindex_write_char_decomposed
                                     (puVar4->casefold_seqindex,dst,bufsize,options,last_boundclass)
                ;
              }
            }
            else {
              local_10 = 0;
            }
          }
          else {
            local_10 = 0;
          }
        }
        else {
          local_10 = 0;
        }
      }
      else {
        local_10 = -4;
      }
    }
    else {
      if ((0 < bufsize) && (*dst = iVar3 / 0x24c + 0x1100, 1 < bufsize)) {
        dst[1] = (int)((long)((ulong)(uint)((int)((long)iVar3 % 0x24c) >> 0x1f) << 0x20 |
                             (long)iVar3 % 0x24c & 0xffffffffU) / 0x1c) + 0x1161;
      }
      if (iVar3 % 0x1c == 0) {
        local_10 = 2;
      }
      else {
        if (2 < bufsize) {
          dst[2] = iVar3 % 0x1c + 0x11a7;
        }
        local_10 = 3;
      }
    }
  }
  return local_10;
}