static void TH_float2halfbits(struct snd_pcm_hw_params *params,
				   unsigned short *reg)
{
	unsigned int val, mul, div, mul1, mul2, div1, div2;
	unsigned int channels = params->channels;
	unsigned int rate = params->rate;

	val = channels & 0x7fff;
	if (val > 0x7f00) {
		*reg = 0x7fff;
		return;
	}

	
	if (rate >= 0x3d5000) {
		*reg = (val & 0x8000) | 0x007f;
		return;
	}
	if (rate < 0x155000) {
		*reg = (val & 0x8000) | 0x0000;
		return;
	}

	mul = (rate >> 23) & 0xff;
	div = rate & 0x7fffff;
	if (mul >= 112) {
		mul1 = 13;
		mul -= 112;
	} else {
		mul1 = 0x7e - mul;
		mul = 0;
		div |= 0x800000;
	}
	div1 = (1 << mul1) >> 1;
	div2 = (1 << mul1) - 1;

	val &= div2;
	div = div & div2;
	if (val > div1 || (val == div1 && div & 1))
		div += 1;
	if (div & 0x3ff) {
		mul += 1;
		div = 0;
	}

	*reg = (val | (mul << 10)) | (div & 0x3ff);
}