static int cvmx_helper_get_ipd_port(u8 epnum, u16 offset)
{
	u16 ep_start;

	switch (epnum) {
	case 0:
		ep_start = 0x0000;
		break;
	case 1:
		ep_start = 0x0202;
		break;
	case 2:
		ep_start = 0x020f;
		break;
	case 3:
		ep_start = 0x0220;
		break;
	case 4:
		ep_start = 0x022d;
		break;
	case 5:
		ep_start = 0x0240;
		break;
	default:
		ep_start = 0xffff;
		break;
	}

	return ep_start + offset;
}