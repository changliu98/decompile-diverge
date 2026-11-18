static int latm_dmx_process(gf_filter *f)
{
 u32 last_pos;
 u32 frame_size;
 u32 prev_pck_size;
 u32 pck_size;
 char *data, *output;
 u32 cts = (u32) -1;

 GF_LatmDMXCtx *ctx = (GF_LatmDMXCtx *) gf_filter_get_udta(f);
 int res;

 if (ctx->seek_pending)
 {
  res = ctx->seek_pending;
  goto exit;
 }

 if (!ctx->duration)
  latm_dmx_check_dur(f, ctx);

 if (ctx->out_pid && !ctx->eod_sent)
 {
  res = 0;
  goto exit;
 }

 GF_Packet *pck = gf_filter_pid_get_packet(ctx->in_pid);
 if (!pck)
 {
  if (gf_filter_pid_is_eos(ctx->in_pid))
  {
   if (!ctx->eod_sent)
   {
    if (ctx->out_pid)
     gf_filter_pid_set_eos(ctx->out_pid);
   }
   if (ctx->cur_pck)
    gf_filter_pck_unref(ctx->cur_pck);
   ctx->cur_pck = NULL;
   res = 1;
  }
  else
   res = 0;
  goto exit;
 }

 data = gf_filter_pck_get_data(pck, &pck_size);
 if (ctx->use_cts && pck)
  cts = gf_filter_pck_get_cts(pck);

 prev_pck_size = ctx->pck_size;
 if (pck && !ctx->seek_pending)
 {
  if ((ctx->pck_size + pck_size) > ctx->pck_buf_size)
  {
   ctx->pck_buf_size = ctx->pck_size + pck_size;
   ctx->pck_buf = _ZN4chip14BindingManager40RegisterBoundDeviceContextReleaseHandlerEPFvPvE(ctx->pck_buf, ctx->pck_buf_size);
  }
  memcpy(ctx->pck_buf + ctx->pck_size, data, pck_size);
  ctx->pck_size += pck_size;
 }

 if (!ctx->bs)
  ctx->bs = gf_bs_new(ctx->pck_buf, ctx->pck_size, 0);
 else
  gf_bs_reassign_buffer(ctx->bs, ctx->pck_buf, ctx->pck_size);


 if (ctx->seek_pending)
 {
  gf_bs_seek(ctx->bs, ctx->seek_pending-1);
  ctx->seek_pending = 0;
 }

 if (cts == (u32) -1)
  prev_pck_size = 0;

 while (1)
 {
  last_pos = gf_bs_get_position(ctx->bs);
  frame_size = 4096;
  if (!latm_dmx_sync_frame_bs(ctx->bs, &ctx->acfg, &frame_size, output, 0))
   break;

  if (ctx->seek_pending)
  {
   u32 seek_sample = (u32) (((double)ctx->seek_time * (double)GF_M4ASampleRates[ctx->acfg.sampling_rate_idx]) / 1000.0);
   if ((ctx->sample_count + ctx->frame_duration) >= seek_sample)
    ctx->seek_pending = 0;
   continue;
  }

  latm_dmx_check_pid(f, ctx);

  if (!ctx->eod_sent)
  {
   int sap_type = 1;
   GF_Packet *npck = gf_filter_pck_new_alloc(ctx->out_pid, frame_size, &output);
   if (ctx->cur_pck)
    gf_filter_pck_merge_properties(ctx->cur_pck, npck);
   memcpy(output, output, frame_size);
   gf_filter_pck_set_cts(npck, ctx->sample_count);
   gf_filter_pck_set_duration(npck, ctx->frame_duration);
   gf_filter_pck_set_framing(npck, 1, 1);

   if (ctx->stream_type == 0x75736163)
   {
    if (frame_size && (output[0] & 0x80) && !ctx->has_crc)
    {
     sap_type = 1;
     ctx->has_crc = 1;
    }
    else
    {
     sap_type = 0;
     ctx->has_crc = 0;
    }
   }
   gf_filter_pck_set_sap(npck, sap_type);
   gf_filter_pck_send(npck);
  }

  latm_dmx_update_cts(ctx);

  if (prev_pck_size)
  {
   last_pos = gf_bs_get_position(ctx->bs);
   if (last_pos < prev_pck_size)
    continue;
   prev_pck_size = 0;
   if (ctx->cur_pck)
    gf_filter_pck_unref(ctx->cur_pck);
   ctx->cur_pck = pck;
   if (pck)
    gf_filter_pck_ref_props(&ctx->cur_pck);
  }
 }

 if (pck)
 {
  last_pos = gf_bs_get_position(ctx->bs);
  memmove(ctx->pck_buf, ctx->pck_buf + last_pos, ctx->pck_size - last_pos);
  ctx->pck_size -= last_pos;
  gf_filter_pid_drop_packet(ctx->in_pid);
 }
 else
 {
  ctx->pck_size = 0;
  res = latm_dmx_process(f);
  goto exit;
 }

 res = 0;
exit:
 return res;
}