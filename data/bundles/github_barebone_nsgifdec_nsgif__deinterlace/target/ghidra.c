_Bool nsgif__deinterlace(uint32_t height,uint32_t *y,uint8_t *step)

{
  uint8_t uVar1;
  uint8_t *step_local;
  uint32_t *y_local;
  uint32_t height_local;
  
  *y = (*step & 0xf) + *y;
  if (*y < height) {
    return true;
  }
  uVar1 = *step;
  if (uVar1 != '\x04') {
    if (uVar1 != '\b') {
      if (uVar1 != '\x18') {
        return false;
      }
      *y = 4;
      *step = '\b';
      if (*y < height) {
        return true;
      }
    }
    *y = 2;
    *step = '\x04';
    if (*y < height) {
      return true;
    }
  }
  *y = 1;
  *step = '\x02';
  if (height <= *y) {
    return false;
  }
  return true;
}