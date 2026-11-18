char * gdb_to_rz_profile(char *gdb)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  _Bool _Var5;
  int iVar6;
  RzStrBuf *sb_00;
  ushort **ppuVar7;
  char *pcVar8;
  char *pcVar9;
  undefined *puVar10;
  char *ptr;
  int ret;
  int type_bits;
  int size;
  int offset;
  int rel;
  int number;
  int mmx;
  int system;
  int vector;
  int sse;
  int float_;
  int restore;
  int save;
  int gpr;
  int all;
  char type [16];
  char groups [128];
  char name [16];
  char *gptr1;
  char *gptr;
  char *ptr1;
  RzStrBuf *sb;
  char *gdb_local;
  char *local_10;
  
  if (gdb == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    sb_00 = rz_strbuf_new("");
    if (sb_00 == (RzStrBuf *)0x0) {
      local_10 = (char *)0x0;
    }
    else {
      all = 1;
      gpr = 2;
      save = 4;
      restore = 8;
      float_ = 0x10;
      sse = 0x20;
      vector = 0x40;
      system = 0x80;
      mmx = 0x100;
      ptr = rz_str_trim_head_ro(gdb);
      _Var5 = rz_str_startswith(ptr,"Name");
      if (_Var5) {
        pcVar8 = strchr(ptr,10);
        if (pcVar8 == (char *)0x0) {
          rz_strbuf_free(sb_00);
          return (char *)0x0;
        }
        ptr = pcVar8 + 1;
      }
      while( true ) {
        while (ppuVar7 = __ctype_b_loc(), ((*ppuVar7)[(int)(uint)(byte)*ptr] & 0x2000) != 0) {
          ptr = ptr + 1;
        }
        if (*ptr == '\0') break;
        pcVar8 = strchr(ptr,10);
        if (pcVar8 == (char *)0x0) {
          fprintf(*(FILE **)PTR_stderr_00104ff8,"Could not parse line: %s (missing \\n)\n",ptr);
          rz_strbuf_free(sb_00);
          return (char *)0x0;
        }
        *pcVar8 = '\0';
        iVar6 = __isoc99_sscanf(ptr," %s %d %d %d %d %s %s",name,&number,&rel,&offset,&size,type,
                                groups);
        if (iVar6 < 6) {
          if (*ptr != '*') {
            fprintf(*(FILE **)PTR_stderr_00104ff8,"Could not parse line: %s\n",ptr);
            rz_strbuf_free(sb_00);
            return (char *)0x0;
          }
          ptr = pcVar8 + 1;
        }
        else {
          _Var5 = rz_str_startswith(name,"\'\'");
          if (_Var5) {
            if (pcVar8 == (char *)0x0) break;
            ptr = pcVar8 + 1;
          }
          else if (size == 0) {
            if (pcVar8 == (char *)0x0) break;
            ptr = pcVar8 + 1;
          }
          else {
            bVar2 = false;
            bVar1 = false;
            bVar4 = false;
            if (6 < iVar6) {
              gptr = groups;
              while( true ) {
                pcVar9 = strchr(gptr,0x2c);
                if (pcVar9 != (char *)0x0) {
                  *pcVar9 = '\0';
                }
                _Var5 = rz_str_startswith(gptr,"general");
                if ((((!_Var5) && (_Var5 = rz_str_startswith(gptr,"all"), !_Var5)) &&
                    (_Var5 = rz_str_startswith(gptr,"save"), !_Var5)) &&
                   (_Var5 = rz_str_startswith(gptr,"restore"), !_Var5)) {
                  _Var5 = rz_str_startswith(gptr,"float");
                  if (_Var5) {
                    bVar1 = true;
                  }
                  else {
                    _Var5 = rz_str_startswith(gptr,"sse");
                    if (_Var5) {
                      bVar4 = true;
                    }
                    else {
                      _Var5 = rz_str_startswith(gptr,"mmx");
                      if (_Var5) {
                        bVar2 = true;
                      }
                      else {
                        _Var5 = rz_str_startswith(gptr,"vector");
                        if (!_Var5) {
                          rz_str_startswith(gptr,"system");
                        }
                      }
                    }
                  }
                }
                if (pcVar9 == (char *)0x0) break;
                gptr = pcVar9 + 1;
              }
            }
            if (type[0] == '\0') {
              if (pcVar8 == (char *)0x0) break;
              ptr = pcVar8 + 1;
            }
            else {
              bVar3 = true;
              if ((!bVar2) && (bVar3 = true, !bVar1)) {
                bVar3 = bVar4;
              }
              puVar10 = &DAT_001030d7;
              if (bVar3) {
                puVar10 = &DAT_001030d3;
              }
              rz_strbuf_appendf(sb_00,"%s\t%s\t.%d\t%d\t0\n",puVar10,name,(ulong)(uint)(size << 3),
                                (ulong)(uint)offset);
              if (pcVar8 == (char *)0x0) break;
              ptr = pcVar8 + 1;
            }
          }
        }
      }
      local_10 = rz_strbuf_drain(sb_00);
    }
  }
  return local_10;
}