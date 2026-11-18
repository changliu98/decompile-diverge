/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void quicktake_100_load_raw(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  uchar uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iStack_4c1f0;
  uchar uStack_4c1ec;
  int iStack_4c1e8;
  int iStack_4c1e4;
  uchar uStack_4c1e0;
  int iStack_4c1dc;
  int iStack_4c1cc;
  int iStack_4c1c8;
  int iStack_4c1c4;
  int iStack_4c1c0;
  int iStack_4c1bc;
  int iStack_4c1b8;
  int iStack_4c1b4;
  int val;
  int sharp;
  int col;
  int row;
  int rb;
  uchar pixel [484] [644];
  
  val = 0;
  getbithuff(-1,(unsigned_short *)0x0);
  memset(pixel,0x80,0x4c190);
  for (row = 2; row < (int)(height + 2); row = row + 1) {
    col = row & 1;
    while (uVar8 = col, col = uVar8 + 2, col < (int)(width + 2)) {
      bVar1 = pixel[row + -1][(int)(uVar8 + 1)];
      bVar2 = pixel[row + -1][(int)(uVar8 + 3)];
      bVar3 = pixel[row][(int)uVar8];
      uVar6 = getbithuff(4,(unsigned_short *)0x0);
      iStack_4c1bc = ((int)((uint)bVar1 + (uint)bVar2 * 2 + (uint)bVar3) >> 2) +
                     (int)quicktake_100_load_raw::gstep[uVar6];
      iStack_4c1b4 = iStack_4c1bc;
      if (0xfe < iStack_4c1bc) {
        iStack_4c1b4 = 0xff;
      }
      if (iStack_4c1b4 < 0) {
        iStack_4c1b8 = 0;
      }
      else {
        if (0xfe < iStack_4c1bc) {
          iStack_4c1bc = 0xff;
        }
        iStack_4c1b8 = iStack_4c1bc;
      }
      val = iStack_4c1b8;
      uVar5 = (uchar)iStack_4c1b8;
      pixel[row][col] = uVar5;
      if (col < 4) {
        pixel[row + 1][(int)((row ^ 0xffffffffU) & 1)] = uVar5;
        pixel[row][(int)uVar8] = uVar5;
      }
      if (row == 2) {
        pixel[1][(int)(uVar8 + 5)] = uVar5;
        pixel[1][(int)(uVar8 + 3)] = uVar5;
      }
    }
    pixel[row][col] = (uchar)val;
  }
  for (rb = 0; iVar7 = rb, rb < 2; rb = rb + 1) {
    while (iVar4 = iVar7, row = iVar4 + 2, row < (int)(height + 2)) {
      for (col = 3 - (row & 1U); iVar7 = row, col < (int)(width + 2); col = col + 2) {
        if ((row < 4) || (col < 4)) {
          sharp = 2;
        }
        else {
          iVar7 = (((uint)pixel[iVar4][col] - (uint)pixel[row][col + -2] ^
                   (int)((uint)pixel[iVar4][col] - (uint)pixel[row][col + -2]) >> 0x1f) -
                  ((int)((uint)pixel[iVar4][col] - (uint)pixel[row][col + -2]) >> 0x1f)) +
                  (((uint)pixel[iVar4][col] - (uint)pixel[iVar4][col + -2] ^
                   (int)((uint)pixel[iVar4][col] - (uint)pixel[iVar4][col + -2]) >> 0x1f) -
                  ((int)((uint)pixel[iVar4][col] - (uint)pixel[iVar4][col + -2]) >> 0x1f)) +
                  (((uint)pixel[row][col + -2] - (uint)pixel[iVar4][col + -2] ^
                   (int)((uint)pixel[row][col + -2] - (uint)pixel[iVar4][col + -2]) >> 0x1f) -
                  ((int)((uint)pixel[row][col + -2] - (uint)pixel[iVar4][col + -2]) >> 0x1f));
          if (iVar7 < 4) {
            iStack_4c1c0 = 0;
          }
          else {
            if (iVar7 < 8) {
              iStack_4c1c4 = 1;
            }
            else {
              if (iVar7 < 0x10) {
                iStack_4c1c8 = 2;
              }
              else {
                if (iVar7 < 0x20) {
                  iStack_4c1cc = 3;
                }
                else {
                  iStack_4c1cc = 5;
                  if (iVar7 < 0x30) {
                    iStack_4c1cc = 4;
                  }
                }
                iStack_4c1c8 = iStack_4c1cc;
              }
              iStack_4c1c4 = iStack_4c1c8;
            }
            iStack_4c1c0 = iStack_4c1c4;
          }
          sharp = iStack_4c1c0;
        }
        bVar1 = pixel[iVar4][col];
        bVar2 = pixel[row][col + -2];
        uVar8 = getbithuff(2,(unsigned_short *)0x0);
        iStack_4c1e4 = ((int)((uint)bVar1 + (uint)bVar2) >> 1) +
                       (int)quicktake_100_load_raw::rstep[sharp][uVar8];
        iStack_4c1dc = iStack_4c1e4;
        if (0xfe < iStack_4c1e4) {
          iStack_4c1dc = 0xff;
        }
        if (iStack_4c1dc < 0) {
          uStack_4c1e0 = '\0';
        }
        else {
          if (0xfe < iStack_4c1e4) {
            iStack_4c1e4 = 0xff;
          }
          uStack_4c1e0 = (uchar)iStack_4c1e4;
        }
        pixel[row][col] = uStack_4c1e0;
        if (row < 4) {
          pixel[iVar4][col + 2] = uStack_4c1e0;
        }
        if (col < 4) {
          pixel[iVar4 + 4][col + -2] = uStack_4c1e0;
        }
      }
    }
  }
  for (row = 2; row < (int)(height + 2); row = row + 1) {
    for (col = 3 - (row & 1U); col < (int)(width + 2); col = col + 2) {
      iStack_4c1f0 = ((int)((uint)pixel[row][col + -1] + (uint)pixel[row][col] * 4 +
                           (uint)pixel[row][col + 1]) >> 1) + -0x100;
      iStack_4c1e8 = iStack_4c1f0;
      if (0xfe < iStack_4c1f0) {
        iStack_4c1e8 = 0xff;
      }
      if (iStack_4c1e8 < 0) {
        uStack_4c1ec = '\0';
      }
      else {
        if (0xfe < iStack_4c1f0) {
          iStack_4c1f0 = 0xff;
        }
        uStack_4c1ec = (uchar)iStack_4c1f0;
      }
      pixel[row][col] = uStack_4c1ec;
    }
  }
  for (row = 0; row < (int)(uint)height; row = row + 1) {
    for (col = 0; col < (int)(uint)width; col = col + 1) {
      raw_image[(int)(row * (uint)raw_width + col)] =
           quicktake_100_load_raw::t_curve[pixel[row + 2][col + 2]];
    }
  }
  maximum = 0x3ff;
  return;
}