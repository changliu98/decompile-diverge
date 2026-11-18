static inline float reson(float input, struct lpc_filter *lpc)
{
  float output = lpc->a[0] * input + lpc->a[1] * lpc->last_output;
  output += lpc->a[2] * lpc->last_last_output;
  lpc->last_last_output = lpc->last_output;
  lpc->last_output = output;
  return output;
}