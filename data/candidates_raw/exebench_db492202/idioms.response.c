void set_table(float sampleRate, float duration, int size, float *table)
{
  table[0] = (int)(sampleRate * duration - .9999);
  table[1] = (size - 1);
}