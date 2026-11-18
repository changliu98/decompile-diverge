void hil_s_from_xy(uint x,uint y,int order,uint *s)

{
  uint uVar1;
  uint row;
  uint state;
  int i;
  uint *s_local;
  int order_local;
  uint y_local;
  uint x_local;
  
  state = 0;
  while (i = order + -1, -1 < i) {
    uVar1 = state << 2 | (x >> ((byte)i & 0x1f) & 1) << 1 | y >> ((byte)i & 0x1f) & 1;
    *s = *s << 2 | 0x361e9cb4 >> (sbyte)(uVar1 << 1) & 3U;
    state = 0x8fe65831U >> (sbyte)(uVar1 << 1) & 3;
    order = i;
  }
  return;
}