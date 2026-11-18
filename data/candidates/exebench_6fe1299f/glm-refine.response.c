void __cdecl quant_u(float *p_data, int *p_index, float qmin, float qmax, int nlev)
{
  float step = (qmax - qmin) / (float)(nlev - 1);
  float qbnd = qmin + step * 0.5f;
  int i;

  // Find the quantization index by checking which threshold boundary the data exceeds
  for (i = 0; i < nlev - 1 && qbnd <= *p_data; ++i)
    qbnd += step;

  // Reconstruct the quantized value and store the index
  *p_data = qmin + (float)i * step;
  *p_index = i;
}