static int i2s_sf_sclkdiv(int bus_num, u32 *val)
{
	int stat = 0;
	int m_num;

	switch (bus_num) {
	case 0:
		*val |= 0x00800000;
		break;
	case 1:
		*val |= 0x00008000;
		break;
	case 2:
		m_num = bus_num;
		if (m_num % 2) {
			stat = -1;
			break;
		}
		m_num = m_num / 2 - 1;
		if (m_num == 8 || m_num == 9) {
			stat = -1;
			break;
		}
		*val |= ((m_num & 0x7) << 20);
		break;
	default:
		stat = -1;
		break;
	}
	return stat;
}