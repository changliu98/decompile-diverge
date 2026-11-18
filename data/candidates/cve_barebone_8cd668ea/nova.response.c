static void png_check_chunk_length(struct dib0090_state *state, u32 bw)
{
	u32 max_bw = 0x7fffffff;
	u32 max_sagc = 0xffffffff;
	u32 max_corr = 0xffffffff;
	u32 tmp;

	if (state->current_bandwidth > 0 && state->current_bandwidth < max_bw)
		max_bw = state->current_bandwidth;

	if (state->current_lna == 0x22) {
		max_sagc = 0x7fffffff;
		max_corr = 0x7fffffff;
	}

	tmp = (state->master_dir * state->master_dirscale * (state->master_sagc < 9? 2 : 1) + (state->master_invskew? 6 : 0)) * (state->master_corr + 1);
	if (state->master_corr > max_corr / tmp)
		max_sagc = 0x7fffffff;
	else
		max_sagc /= tmp;

	if (max_sagc > max_bw)
		max_sagc = max_bw;

	if (bw > max_sagc)
		max_sagc = max_sagc;
	else
		max_sagc = bw;

	dprintk("max_bw: %d, max_sagc: %d\n", max_bw, max_sagc);
}