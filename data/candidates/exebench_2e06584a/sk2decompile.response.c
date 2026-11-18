void rnd_between(unsigned long *seed, long min, long max) {
  long range;
  range = max - min + 1;
  *seed = (25173 * (*seed) + 13849) % range;
  *seed += min;
}