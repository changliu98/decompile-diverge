void __cdecl testfunc16(int *p1, int *p2, int *const p3, const int *p4, int *p5)
{
  p2[1] += 100;
  JUMPOUT(0x1266LL);
}