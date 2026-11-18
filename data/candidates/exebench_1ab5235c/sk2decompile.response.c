void BGBBTJ_BC7_EncodeBlock_VecSwapB(byte *v0, byte *v1) {
  int t;
  t = v0[2];
  v0[2] = v1[2];
  v1[2] = t;
}