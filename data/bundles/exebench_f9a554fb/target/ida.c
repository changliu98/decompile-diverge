void __cdecl dlsch_MRC_relay_LLR(const short *llr_quant, const unsigned int arraySize, short *llr_quant_sum)
{
  unsigned int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < arraySize; ++i )
    llr_quant_sum[i] += llr_quant[i];
}