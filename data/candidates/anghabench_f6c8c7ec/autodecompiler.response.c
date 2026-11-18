static int
qcom_nandc_calc_ecc_bytes(int width, int strength)
{
 return strength == 4 ? 12 : 16;
}