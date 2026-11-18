unsigned char fsp_test_invert_cmd(unsigned char reg_val)
{
	switch (reg_val) {
	case 0xe9: case 0xee: case 0xf2: case 0xff:
		/*
		 * The requested value being sent to FSP matched to certain
		 * commands, inverse the given value such that the hardware
		 * wouldn't get confused.
		 */
		return ~reg_val;
	default:
		return reg_val;	/* inversion isn't necessary */
	}
}