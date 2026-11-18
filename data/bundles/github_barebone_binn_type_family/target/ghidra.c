int type_family(int type)

{
  int type_local;
  int local_c;
  
  if (type == 0) {
    return 0xf1;
  }
  if (((type - 0x20U < 2) || (type - 0x40U < 2)) || (type - 0x60U < 2)) {
LAB_00106d74:
    local_c = 0xf2;
  }
  else {
    if (type != 0x62) {
      if (type - 0x80U < 2) goto LAB_00106d74;
      if (type != 0x82) {
        if (type == 0x83) {
          return 0xf4;
        }
        if (type == 0xa0) {
          return 0xf4;
        }
        if (type - 0xa1U < 4) {
          return 0xf4;
        }
        if (1 < type - 0xa6U) {
          if (type != 0xc0) {
            if (type - 0xe0U < 3) {
              return 0xf7;
            }
            if (type - 0xb001U < 5) {
              return 0xf4;
            }
            if (3 < type - 0xd001U) {
              if (type == 0x80061) {
                return 0xf6;
              }
              return 0;
            }
          }
          return 0xf5;
        }
      }
    }
    local_c = 0xf3;
  }
  return local_c;
}