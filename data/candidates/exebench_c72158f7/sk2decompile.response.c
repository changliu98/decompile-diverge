double rnd(long *seed) {
  *seed = (*seed * 25173 + 13849) % 65536;
  return (double)*seed / 65535.0;
}