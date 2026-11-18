void dlsch_MRC_relay_LLR(short *llr_quant, unsigned int arraySize, short *llr_quant_sum)
{
  unsigned int i;
  for (i = 0; i < arraySize; i++)
  {
    llr_quant_sum[i] += llr_quant[i];
  }
}