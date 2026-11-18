void tableset(float x, float y, int z, float *table) {
  table[0] = (y * x) - 0.9999;
  table[1] = z - 1;
}