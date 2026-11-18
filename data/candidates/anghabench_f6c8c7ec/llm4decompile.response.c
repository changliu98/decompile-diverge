int qcom_nandc_calc_ecc_bytes(int step_size, int strength)
{
	switch (strength) {
	case 4:
		return 12;
	default:
		return 16;
	}
}