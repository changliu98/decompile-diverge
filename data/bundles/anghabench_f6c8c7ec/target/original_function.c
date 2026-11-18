int
qcom_nandc_calc_ecc_bytes(int step_size, int strength)
{
	return strength == 4 ? 12 : 16;
}