static void hil_s_from_xy(u32 data, u32 mask, u32 pos, u32 *reg)
{
	u32 neg_mask = 0;
	u32 neg_val = 0;
	u32 val;

	for (pos = pos - 1; pos >= 0; pos--) {
		val = (data & 0x1) << 1 | (mask & 0x1);
		data >>= 1;
		mask >>= 1;

		switch (val) {
		case 0x0:
			break;
		case 0x1:
			*reg |= (1U << pos);
			break;
		case 0x2:
			break;
		case 0x3:
			neg_mask |= 1U << pos;
			neg_val |= 1U << pos;
			break;
		}
	}

	val = *reg;
	val &= ~neg_mask;
	val |= neg_val;
	*reg = val;
}