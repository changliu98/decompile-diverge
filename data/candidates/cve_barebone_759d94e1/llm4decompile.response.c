GF_Err latm_dmx_process(GF_Filter *filter)
{
	GF_LATMDmxCtx *ctx = (GF_LATMDmxCtx *)gf_filter_get_udta(filter);
	GF_FilterPacket *pck;
	u8 *data;
	u32 pck_size, prev_pck_size;
	u64 cts = -1;
	u32 pos;
	u8 latm_buffer[4096];
	u32 latm_frame_size;
	u8 *output;
	GF_FilterPacket *dst_pck;
	GF_FilterSAPType sap;

	if (ctx->in_error != GF_OK) return ctx->in_error;

	if (!ctx->duration.num) latm_dmx_check_dur(filter, ctx);

	if (ctx->opid && ctx->is_playing == GF_FALSE) return GF_OK;

	pck = gf_filter_pid_get_packet(ctx->ipid);
	if (!pck && gf_filter_pid_is_eos(ctx->ipid) == GF_FALSE) return GF_OK;

	data = gf_filter_pck_get_data(pck, &pck_size);
	if (ctx->timescale && pck) cts = gf_filter_pck_get_cts(pck);

	prev_pck_size = ctx->latm_buffer_size;
	if (pck && !ctx->resume_from) {
		if (ctx->latm_buffer_size + pck_size > ctx->latm_buffer_alloc) {
			ctx->latm_buffer_alloc = ctx->latm_buffer_size + pck_size;
			ctx->latm_buffer = (u8*)gf_realloc(ctx->latm_buffer, ctx->latm_buffer_alloc);
		}
		memcpy(ctx->latm_buffer + ctx->latm_buffer_size, data, pck_size);
		ctx->latm_buffer_size += pck_size;
	}

	if (!ctx->bs) {
		ctx->bs = gf_bs_new(ctx->latm_buffer, ctx->latm_buffer_size, 0);
	} else {
		gf_bs_reassign_buffer(ctx->bs, ctx->latm_buffer, ctx->latm_buffer_size);
	}

	if (ctx->resume_from) {
		gf_bs_seek(ctx->bs, ctx->resume_from - 1);
		ctx->resume_from = 0;
	}

	if (cts != -1) {
		prev_pck_size = 0;
	}

	while (1) {
		pos = (u32)gf_bs_get_position(ctx->bs);
		latm_frame_size = 4096;
		if (latm_dmx_sync_frame_bs(ctx->bs, &ctx->acfg, &latm_frame_size, latm_buffer, NULL) == GF_FALSE) {
			if (pck) {
				pos = (u32)gf_bs_get_position(ctx->bs);
				memmove(ctx->latm_buffer, ctx->latm_buffer + pos, ctx->latm_buffer_size - pos);
				ctx->latm_buffer_size -= pos;
				gf_filter_pid_drop_packet(ctx->ipid);
				return GF_OK;
			}
			ctx->latm_buffer_size = 0;
			return latm_dmx_process(filter);
		}

		if (ctx->in_seek != GF_FALSE) {
			if (ctx->cts + ctx->dts_inc >= (u64) (ctx->start_range * GF_M4ASampleRates[ctx->sr_idx])) {
				ctx->in_seek = GF_FALSE;