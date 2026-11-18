int clear_decompress_subcodecs_data(struct pt_regs *regs, unsigned long addr,
		    unsigned int fsr, unsigned int fir, unsigned int sec,
		    unsigned long fir_reg, unsigned long sec_reg)
{
	unsigned short fir_lo, fir_hi;
	unsigned short sec_lo, sec_hi;
	unsigned short fir_lo_old, fir_hi_old;
	unsigned short sec_lo_old, sec_hi_old;
	unsigned short fir_lo_new, fir_hi_new;
	unsigned short sec_lo_new, sec_hi_new;
	unsigned short fir_lo_tmp, sec_lo_tmp;
	unsigned short fir_hi_tmp, sec_hi_tmp;
	unsigned short fir_lo_old_tmp, sec_lo_old_tmp;
	unsigned short fir_hi_old_tmp, sec_hi_old_tmp;
	unsigned short fir_lo_new_tmp, sec_lo_new_tmp;
	unsigned short fir_hi_new_tmp, sec_hi_new_tmp;
	unsigned short fir_lo_tmp_tmp, sec_lo_tmp_tmp;
	unsigned short fir_hi_tmp_tmp, sec_hi_tmp_tmp;
	unsigned short fir_lo_tmp_tmp_tmp, sec_lo_tmp_tmp_tmp;
	unsigned short fir_hi_tmp_tmp_tmp, sec_hi_tmp_tmp_tmp;
	unsigned short fir_lo_tmp_tmp_tmp_tmp, sec_lo_tmp_tmp_tmp_tmp;
	unsigned short fir_hi_tmp_tmp_tmp_tmp, sec_hi_tmp_tmp_tmp_tmp;
	unsigned short fir_lo_tmp_tmp_tmp_tmp_tmp, sec_lo_tmp_tmp_tmp_tmp_tmp;
	unsigned short fir_hi_tmp_tmp_tmp_tmp_tmp, sec_hi_tmp_tmp_tmp_tmp_tmp;
	unsigned short fir_lo_tmp_tmp_tmp_tmp_tmp_tmp, sec_lo_tmp_tmp_tmp_