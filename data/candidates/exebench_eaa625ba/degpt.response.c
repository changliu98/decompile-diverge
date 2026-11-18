int get_char_utf8(uint *x,char *s)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int f;
  int e;
  int d;
  int c;
  int b;
  int a;
  char *s_local;
  uint *x_local;
  uint local_c;
  
  bVar1 = *s;
  uVar3 = (uint)bVar1;
  if ((bVar1 & 0x80) == 0) {
    *x = uVar3;
    local_c = (uint)(uVar3 != 0);
  }
  else if ((bVar1 & 0x40) == 0) {
    *x = 0xffffffff;
    local_c = 0xffffffff;
  }
  else {
    bVar2 = s[1];
    uVar4 = (uint)bVar2;
    if ((uVar4 & 0xc0) == 0x80) {
      if ((bVar1 & 0x20) == 0) {
        if ((bVar1 & 0x1e) == 0) {
          *x = 0xffffffff;
          local_c = 0xffffffff;
        }
        else {
          *x = (uVar3 & 0x1f) << 6 | uVar4 & 0x3f;
          local_c = 2;
        }
      }
      else {
        uVar5 = (uint)(byte)s[2];
        if ((uVar5 & 0xc0) == 0x80) {
          if ((bVar1 & 0x10) == 0) {
            if ((bVar1 & 0xf) == 0 && (bVar2 & 0x20) == 0) {
              *x = 0xffffffff;
              local_c = 0xffffffff;
            }
            else {
              *x = (uVar3 & 0xf) << 0xc | (uVar4 & 0x3f) << 6 | uVar5 & 0x3f;
              local_c = 3;
            }
          }
          else {
            uVar6 = (uint)(byte)s[3];
            if ((uVar6 & 0xc0) == 0x80) {
              if ((bVar1 & 8) == 0) {
                if ((bVar1 & 7) == 0 && (bVar2 & 0x30) == 0) {
                  *x = 0xffffffff;
                  local_c = 0xffffffff;
                }
                else {
                  *x = (uVar3 & 7) << 0x12 | (uVar4 & 0x3f) << 0xc | (uVar5 & 0x3f) << 6 |
                       uVar6 & 0x3f;
                  local_c = 4;
                }
              }
              else {
                uVar7 = (uint)(byte)s[4];
                if ((uVar7 & 0xc0) == 0x80) {
                  if ((bVar1 & 4) == 0) {
                    if ((bVar1 & 3) == 0 && (bVar2 & 0x38) == 0) {
                      *x = 0xffffffff;
                      local_c = 0xffffffff;
                    }
                    else {
                      *x = (uVar3 & 3) << 0x18 | (uVar4 & 0x3f) << 0x12 | (uVar5 & 0x3f) << 0xc |
                           (uVar6 & 0x3f) << 6 | uVar7 & 0x3f;
                      local_c = 5;
                    }
                  }
                  else if (((byte)s[5] & 0xc0) == 0x80) {
                    if ((bVar1 & 2) == 0) {
                      if ((bVar1 & 1) == 0 && (bVar2 & 0x3c) == 0) {
                        *x = 0xffffffff;
                        local_c = 0xffffffff;
                      }
                      else {
                        *x = (uVar3 & 1) << 0x1e | (uVar4 & 0x3f) << 0x18 | (uVar5 & 0x3f) << 0x12 |
                             (uVar6 & 0x3f) << 0xc | (uVar7 & 0x3f) << 6 | (byte)s[5] & 0x3f;
                        local_c = 6;
                      }
                    }
                    else {
                      *x = 0xffffffff;
                      local_c = 0xffffffff;
                    }
                  }
                  else {
                    *x = 0xffffffff;
                    local_c = 0xffffffff;
                  }
                }
                else {
                  *x = 0xffffffff;
                  local_c = 0xffffffff;
                }
              }
            }
            else {
              *x = 0xffffffff;
              local_c = 0xffffffff;
            }
          }
        }
        else {
          *x = 0xffffffff;
          local_c = 0xffffffff;
        }
      }
    }
    else {
      *x = 0xffffffff;
      local_c = 0xffffffff;
    }
  }
  return local_c;
}