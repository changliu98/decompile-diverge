static int func0(u32 *value, const u8 *buffer)
{
	u8 b1, b2, b3, b4;
	u8 sign;
	int i;

	sign = buffer[0];
	if (!(sign & 0x80)) {
		*value = sign;
		i = (sign & 0x40)? 1 : 0;
	} else if (!(sign & 0x40)) {
		*value = 0xffffffff;
		i = -1;
	} else {
		b1 = buffer[1];
		if ((b1 & 0xc0)!= 0x80) {
			*value = 0xffffffff;
			i = -1;
		} else {
			if (!(sign & 0x20)) {
				*value = sign & 0x1f;
				i = 2;
			} else {
				b2 = buffer[2];
				if ((b2 & 0xc0)!= 0x80) {
					*value = 0xffffffff;
					i = -1;
				} else {
					*value |= (b1 & 0x3f) << 6;
					i = 3;
				}
			}
		}
	}

	if (i == 2) {
		b3 = buffer[2];
		if ((b3 & 0xc0)!= 0x80) {
			*value = 0xffffffff;
			i = -1;
		} else {
			*value |= (b2 & 0x3f) << 12;
			i = 4;
		}
	}

	if (i == 3) {
		b4 = buffer[3];
		if ((b4 & 0xc0)!= 0x80) {
			*value = 0xffffffff;
			i = -1;
		} else {
			*value |= (b3 & 0x3f) << 18;
			i = 5;
		}
	}

	if (i == 4) {
		b