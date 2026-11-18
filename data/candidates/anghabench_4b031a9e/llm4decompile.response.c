int valid_bo_pre_v2(u32 bo_pre)
{
	int ret = 0;

	if ((bo_pre & 0x14) == 0x00)
		ret = 1;
	else if ((bo_pre & 0x14) == 0x04)
		ret = ((bo_pre & 0x02) == 0x00) ? 1 : 0;
	else if ((bo_pre & 0x14) == 0x10)
		ret = ((bo_pre & 0x08) == 0x00) ? 1 : 0;
	else if (bo_pre == 0x14)
		ret = 1;
	else
		ret = 0;

	return ret;
}