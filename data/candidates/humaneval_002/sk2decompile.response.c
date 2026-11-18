float _modff(float x) {
  int i;
  i = (int)x;
  x -= i;
  return x;
}