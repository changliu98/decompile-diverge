uLong adler32_z(uLong adler,Bytef *buf,z_size_t len)

{
  long lVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  uint n;
  unsigned_long sum2;
  z_size_t len_local;
  Bytef *buf_local;
  uLong adler_local;
  ulong local_10;
  
  sum2 = adler >> 0x10 & 0xffff;
  adler_local = adler & 0xffff;
  if (len == 1) {
    adler_local = *buf + adler_local;
    if (0xfff0 < adler_local) {
      adler_local = adler_local - 0xfff1;
    }
    sum2 = adler_local + sum2;
    if (0xfff0 < sum2) {
      sum2 = sum2 - 0xfff1;
    }
    local_10 = adler_local | sum2 << 0x10;
  }
  else if (buf == (Bytef *)0x0) {
    local_10 = 1;
  }
  else {
    len_local = len;
    buf_local = buf;
    if (len < 0x10) {
      while (len_local != 0) {
        adler_local = *buf_local + adler_local;
        sum2 = adler_local + sum2;
        len_local = len_local - 1;
        buf_local = buf_local + 1;
      }
      if (0xfff0 < adler_local) {
        adler_local = adler_local - 0xfff1;
      }
      local_10 = adler_local | sum2 % 0xfff1 << 0x10;
    }
    else {
      while (0x15af < len_local) {
        len_local = len_local - 0x15b0;
        n = 0x15b;
        do {
          lVar1 = *buf_local + adler_local;
          lVar2 = (ulong)buf_local[1] + lVar1;
          lVar3 = (ulong)buf_local[2] + lVar2;
          lVar4 = (ulong)buf_local[3] + lVar3;
          lVar5 = (ulong)buf_local[4] + lVar4;
          lVar6 = (ulong)buf_local[5] + lVar5;
          lVar7 = (ulong)buf_local[6] + lVar6;
          lVar8 = (ulong)buf_local[7] + lVar7;
          lVar9 = (ulong)buf_local[8] + lVar8;
          lVar10 = (ulong)buf_local[9] + lVar9;
          lVar11 = (ulong)buf_local[10] + lVar10;
          lVar12 = (ulong)buf_local[0xb] + lVar11;
          lVar13 = (ulong)buf_local[0xc] + lVar12;
          lVar14 = (ulong)buf_local[0xd] + lVar13;
          lVar15 = (ulong)buf_local[0xe] + lVar14;
          adler_local = (ulong)buf_local[0xf] + lVar15;
          sum2 = adler_local +
                 lVar15 + lVar14 + lVar13 + lVar12 + lVar11 + lVar10 + lVar9 + lVar8 + lVar7 + lVar6
                                                                                               + 
                                                  lVar5 + lVar4 + lVar3 + lVar2 + lVar1 + sum2;
          buf_local = buf_local + 0x10;
          n = n - 1;
        } while (n != 0);
        adler_local = adler_local % 0xfff1;
        sum2 = sum2 % 0xfff1;
      }
      if (len_local != 0) {
        for (; 0xf < len_local; len_local = len_local - 0x10) {
          lVar1 = *buf_local + adler_local;
          lVar2 = (ulong)buf_local[1] + lVar1;
          lVar3 = (ulong)buf_local[2] + lVar2;
          lVar4 = (ulong)buf_local[3] + lVar3;
          lVar5 = (ulong)buf_local[4] + lVar4;
          lVar6 = (ulong)buf_local[5] + lVar5;
          lVar7 = (ulong)buf_local[6] + lVar6;
          lVar8 = (ulong)buf_local[7] + lVar7;
          lVar9 = (ulong)buf_local[8] + lVar8;
          lVar10 = (ulong)buf_local[9] + lVar9;
          lVar11 = (ulong)buf_local[10] + lVar10;
          lVar12 = (ulong)buf_local[0xb] + lVar11;
          lVar13 = (ulong)buf_local[0xc] + lVar12;
          lVar14 = (ulong)buf_local[0xd] + lVar13;
          lVar15 = (ulong)buf_local[0xe] + lVar14;
          adler_local = (ulong)buf_local[0xf] + lVar15;
          sum2 = adler_local +
                 lVar15 + lVar14 + lVar13 + lVar12 + lVar11 + lVar10 + lVar9 + lVar8 + lVar7 + lVar6
                                                                                               + 
                                                  lVar5 + lVar4 + lVar3 + lVar2 + lVar1 + sum2;
          buf_local = buf_local + 0x10;
        }
        while (len_local != 0) {
          adler_local = *buf_local + adler_local;
          sum2 = adler_local + sum2;
          len_local = len_local - 1;
          buf_local = buf_local + 1;
        }
        adler_local = adler_local % 0xfff1;
        sum2 = sum2 % 0xfff1;
      }
      local_10 = adler_local | sum2 << 0x10;
    }
  }
  return local_10;
}