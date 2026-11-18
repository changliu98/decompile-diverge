void * memchr2(void *s,int c1_in,int c2_in,size_t n)

{
  uchar uVar1;
  uchar uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  uchar *char_ptr_1;
  longword longword2;
  longword longword1;
  longword repeated_c2;
  longword repeated_c1;
  longword repeated_one;
  longword *longword_ptr;
  uchar *char_ptr;
  void *void_ptr;
  uchar c2;
  uchar c1;
  size_t n_local;
  int c2_in_local;
  int c1_in_local;
  void *s_local;
  void *local_10;
  
  uVar1 = (uchar)c1_in;
  uVar2 = (uchar)c2_in;
  void_ptr = s;
  n_local = n;
  if ((c1_in & 0xffU) == (c2_in & 0xffU)) {
    local_10 = memchr(s,c1_in & 0xff,n);
  }
  else {
    for (; n_local != 0 && ((ulong)void_ptr & 7) != 0; n_local = n_local - 1) {
      if ((*(uchar *)void_ptr == uVar1) || (*(uchar *)void_ptr == uVar2)) {
        return void_ptr;
      }
      void_ptr = (void *)((long)void_ptr + 1);
    }
    longword_ptr = void_ptr;
    uVar3 = (long)(int)(uint)CONCAT11(uVar1,uVar1) << 0x10 | (long)(int)(uint)CONCAT11(uVar1,uVar1);
    uVar4 = (long)(int)(uint)CONCAT11(uVar2,uVar2) << 0x10 | (long)(int)(uint)CONCAT11(uVar2,uVar2);
    while ((7 < n_local &&
           (uVar5 = *longword_ptr ^ (uVar3 << 0x20 | uVar3),
           uVar6 = *longword_ptr ^ (uVar4 << 0x20 | uVar4),
           ((uVar5 + 0xfefefefefefefeff & (uVar5 ^ 0xffffffffffffffff) |
            uVar6 + 0xfefefefefefefeff & (uVar6 ^ 0xffffffffffffffff)) & 0x8080808080808080) == 0)))
    {
      longword_ptr = longword_ptr + 1;
      n_local = n_local - 8;
    }
    char_ptr_1 = (uchar *)longword_ptr;
    for (; n_local != 0; n_local = n_local - 1) {
      if ((*char_ptr_1 == uVar1) || (*char_ptr_1 == uVar2)) {
        return char_ptr_1;
      }
      char_ptr_1 = char_ptr_1 + 1;
    }
    local_10 = (void *)0x0;
  }
  return local_10;
}