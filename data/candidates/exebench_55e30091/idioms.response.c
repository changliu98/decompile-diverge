void BGBBTJ_BC7_EncodeBlock_VecSwapA(struct card *a, struct card *b)
{
  int t = a->rank;
  a->rank = b->rank;
  b->rank = t;
}