static bool nsgif__deinterlace(unsigned int max_burst, unsigned int *burst,
			      unsigned char *burst_size)
{
	bool valid;
	unsigned int tmp;

	
	*burst += *burst_size & 0xf;
	if (*burst < max_burst) {
		valid = true;
	} else {
		tmp = *burst_size;
		switch (tmp) {
		case 0x4:
			*burst = 0x4;
			*burst_size = 0x1;
			if (*burst < max_burst)
				valid = true;
			else
				valid = false;
			break;
		case 0x3:
			*burst = 0x24;
			*burst_size = 0x8;
			if (*burst < max_burst)
				valid = true;
			else
				valid = false;
			break;
		case 0x2:
			*burst = 0x18;
			*burst_size = 0x4;
			if (*burst < max_burst)
				valid = true;
			else
				valid = false;
			break;
		case 0x1:
			*burst = 0x02;
			*burst_size = 0x2;
			if (*burst < max_burst)
				valid = true;
			else
				valid = false;
			break;
		default:
			valid = false;
			break;
		}
	}
	return valid;
}