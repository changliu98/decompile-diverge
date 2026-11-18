int ad7192_get_temp_scale(int unipolar)
{
	if (unipolar)
		return 5630; /* 5.630 mV/C */
	else
		return 2815; /* 2.815 mV/C */
}