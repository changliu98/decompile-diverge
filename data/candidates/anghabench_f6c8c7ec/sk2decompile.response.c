static int qcom_nandc_calc_ecc_bytes(int page_size, int ecc_strength) {
  int ecc_bytes;
  if (ecc_strength == 4)
    ecc_bytes = 12;
  else
    ecc_bytes = 16;
  return ecc_bytes;
}