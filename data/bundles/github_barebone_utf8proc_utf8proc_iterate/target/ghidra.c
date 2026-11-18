utf8proc_ssize_t
utf8proc_iterate(utf8proc_uint8_t *str,utf8proc_ssize_t strlen,utf8proc_int32_t *dst)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  long local_48;
  utf8proc_uint8_t *end;
  utf8proc_int32_t uc;
  utf8proc_int32_t *dst_local;
  utf8proc_ssize_t strlen_local;
  utf8proc_uint8_t *str_local;
  utf8proc_ssize_t local_10;
  
  *dst = -1;
  if (strlen == 0) {
    local_10 = 0;
  }
  else {
    local_48 = strlen;
    if (strlen < 0) {
      local_48 = 4;
    }
    pbVar2 = str + local_48;
    pbVar3 = str + 1;
    uVar1 = (uint)*str;
    if (uVar1 < 0x80) {
      *dst = uVar1;
      local_10 = 1;
    }
    else if (uVar1 - 0xc2 < 0x33) {
      if (uVar1 < 0xe0) {
        if ((pbVar3 < pbVar2) && ((*pbVar3 & 0xc0) == 0x80)) {
          *dst = (uVar1 & 0x1f) << 6 | *pbVar3 & 0x3f;
          local_10 = 2;
        }
        else {
          local_10 = -3;
        }
      }
      else if (uVar1 < 0xf0) {
        if (((str + 2 < pbVar2) && ((*pbVar3 & 0xc0) == 0x80)) && ((str[2] & 0xc0) == 0x80)) {
          if ((uVar1 == 0xed) && (0x9f < *pbVar3)) {
            local_10 = -3;
          }
          else {
            uVar1 = (uVar1 & 0xf) << 0xc | (*pbVar3 & 0x3f) << 6 | str[2] & 0x3f;
            if (uVar1 < 0x800) {
              local_10 = -3;
            }
            else {
              *dst = uVar1;
              local_10 = 3;
            }
          }
        }
        else {
          local_10 = -3;
        }
      }
      else if ((((str + 3 < pbVar2) && ((*pbVar3 & 0xc0) == 0x80)) && ((str[2] & 0xc0) == 0x80)) &&
              ((str[3] & 0xc0) == 0x80)) {
        if (uVar1 == 0xf0) {
          if (*pbVar3 < 0x90) {
            return -3;
          }
        }
        else if ((uVar1 == 0xf4) && (0x8f < *pbVar3)) {
          return -3;
        }
        *dst = (uVar1 & 7) << 0x12 | (*pbVar3 & 0x3f) << 0xc | (str[2] & 0x3f) << 6 | str[3] & 0x3f;
        local_10 = 4;
      }
      else {
        local_10 = -3;
      }
    }
    else {
      local_10 = -3;
    }
  }
  return local_10;
}