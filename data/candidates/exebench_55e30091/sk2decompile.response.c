void BGBBTJ_BC7_EncodeBlock_VecSwapA(byte *v, byte *v2) {
  int t;
  t = v[3];
  v[3] = v2[3];
  v2[3] = t;
}