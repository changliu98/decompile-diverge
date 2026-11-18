void BGBBTJ_BC7_EncodeBlock_VecSwapRGBA(byte *v0, byte *v1) {
  int i;
  for (i = 0; i < 4; i++) {
    int t;
    t = v0[i];
    v0[i] = v1[i];
    v1[i] = t;
  }
}