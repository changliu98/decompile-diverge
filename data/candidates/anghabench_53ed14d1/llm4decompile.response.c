u32 mv78xx0_mbus_win_cfg_offset(int win)
{
	u32 offset;

	if (win < 8)
		offset = 0x000 + win * 0x10;
	else {
		win -= 8;
		offset = 0x900 + win * 0x10;
	}

	return offset;
}