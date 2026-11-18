static void read_quant_matrix_ext(unsigned short *dest,
				   struct atyfb_par *par)
{
	int i;

	if (M64_HAS(par, M64_PLL)) {
		for (i = 0; i < 64; i++) {
			int v = aty_ld_pll(par, 8);
			dest[i] = dest[i + 64] = v;
		}
	} else if (M64_HAS(par, M64_PCGC)) {
		for (i = 0; i < 64; i++) {
			int v = aty_ld_pcg(par, 8);
			dest[i] = dest[i + 64] = v;
		}
	} else if (M64_HAS(par, M64_RGC)) {
		for (i = 0; i < 64; i++) {
			int v = aty_ld_rgc(par, 8);
			dest[i] = dest[i + 64] = v;
		}
	} else if (M64_HAS(par, M64_PCGC)) {
		for (i = 0; i < 64; i++) {
			int v = aty_ld_pcg(par, 8);
			dest[i] = dest[i + 64] = v;
		}
	}
}