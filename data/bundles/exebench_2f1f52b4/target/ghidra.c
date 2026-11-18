int isLegalUTF8(uchar *source,int length)

{
  byte *pbVar1;
  byte bVar2;
  uchar uVar3;
  uchar *puVar4;
  uchar *srcptr;
  uchar a;
  int length_local;
  uchar *source_local;
  int local_c;
  
  puVar4 = source + length;
  srcptr = puVar4;
  switch(length) {
  case 1:
    goto switchD_001014f1_caseD_1;
  case 2:
    goto switchD_001014f1_caseD_2;
  case 3:
    goto switchD_001014f1_caseD_3;
  case 4:
    srcptr = puVar4 + -1;
    if ((puVar4[-1] < 0x80) || (0xbf < puVar4[-1])) {
      return 0;
    }
switchD_001014f1_caseD_3:
    pbVar1 = srcptr + -1;
    if ((*pbVar1 < 0x80) || (srcptr = srcptr + -1, 0xbf < *pbVar1)) {
      local_c = 0;
    }
    else {
switchD_001014f1_caseD_2:
      bVar2 = srcptr[-1];
      if (bVar2 < 0xc0) {
        uVar3 = *source;
        if (uVar3 == 0xe0) {
          if (bVar2 < 0xa0) {
            return 0;
          }
        }
        else if (uVar3 == 0xf0) {
          if (bVar2 < 0x90) {
            return 0;
          }
        }
        else if (uVar3 == 0xf4) {
          if (0x8f < bVar2) {
            return 0;
          }
        }
        else if (bVar2 < 0x80) {
          return 0;
        }
switchD_001014f1_caseD_1:
        if ((*source < 0x80) || (0xc1 < *source)) {
          if (*source < 0xf5) {
            local_c = 1;
          }
          else {
            local_c = 0;
          }
        }
        else {
          local_c = 0;
        }
      }
      else {
        local_c = 0;
      }
    }
    return local_c;
  default:
    return 0;
  }
}