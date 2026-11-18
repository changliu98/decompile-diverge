int cp_unfilter(int w,int h,int bpp,uint8_t *raw)

{
  uint8_t uVar1;
  int iVar2;
  uint8_t *puVar3;
  int y;
  int x;
  uint8_t *prev;
  int len;
  uint8_t *raw_local;
  int bpp_local;
  int h_local;
  int w_local;
  
  iVar2 = w * bpp;
  raw_local = raw;
  if (0 < h) {
    raw_local = raw + 1;
    x = bpp;
    switch(*raw) {
    case '\0':
      break;
    case '\x01':
      for (; x < iVar2; x = x + 1) {
        raw_local[x] = raw_local[x] + raw_local[x - bpp];
      }
      break;
    case '\x02':
      break;
    case '\x03':
      for (; x < iVar2; x = x + 1) {
        raw_local[x] = raw_local[x] + raw_local[x - bpp] / 2;
      }
      break;
    case '\x04':
      for (; x < iVar2; x = x + 1) {
        uVar1 = cp_paeth(raw_local[x - bpp],'\0','\0');
        raw_local[x] = raw_local[x] + uVar1;
      }
      break;
    default:
      return 0;
    }
  }
  prev = raw_local;
  raw_local = raw_local + iVar2;
  for (y = 1; y < h; y = y + 1) {
    puVar3 = raw_local + 1;
    switch(*raw_local) {
    case '\0':
      break;
    case '\x01':
      for (x = 0; x < bpp; x = x + 1) {
        puVar3[x] = puVar3[x];
      }
      for (; x < iVar2; x = x + 1) {
        puVar3[x] = puVar3[x] + puVar3[x - bpp];
      }
      break;
    case '\x02':
      for (x = 0; x < bpp; x = x + 1) {
        puVar3[x] = puVar3[x] + prev[x];
      }
      for (; x < iVar2; x = x + 1) {
        puVar3[x] = puVar3[x] + prev[x];
      }
      break;
    case '\x03':
      for (x = 0; x < bpp; x = x + 1) {
        puVar3[x] = puVar3[x] + prev[x] / 2;
      }
      for (; x < iVar2; x = x + 1) {
        puVar3[x] = puVar3[x] + (char)((ulong)((uint)puVar3[x - bpp] + (uint)prev[x]) / 2);
      }
      break;
    case '\x04':
      for (x = 0; x < bpp; x = x + 1) {
        puVar3[x] = puVar3[x] + prev[x];
      }
      for (; x < iVar2; x = x + 1) {
        uVar1 = cp_paeth(puVar3[x - bpp],prev[x],prev[x - bpp]);
        puVar3[x] = puVar3[x] + uVar1;
      }
      break;
    default:
      return 0;
    }
    raw_local = puVar3 + iVar2;
    prev = puVar3;
  }
  return 1;
}