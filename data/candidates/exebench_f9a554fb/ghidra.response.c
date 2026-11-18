void dlsch_MRC_relay_LLR(short *llr_quant,uint arraySize,short *llr_quant_sum)

{
  uint i;
  short *llr_quant_sum_local;
  uint arraySize_local;
  short *llr_quant_local;
  
  for (i = 0; i < arraySize; i = i + 1) {
    llr_quant_sum[i] = llr_quant_sum[i] + llr_quant[i];
  }
  return;
}