GF_Err __cdecl latm_dmx_process(GF_Filter *filter)
{
  char *v1; // rax
  GF_BitStream *v2; // rax
  GF_FilterSAPType sap; // [rsp+Ch] [rbp-1064h]
  u32 latm_frame_size; // [rsp+1Ch] [rbp-1054h] BYREF
  u8 latm_buffer[4096]; // [rsp+20h] [rbp-1050h] BYREF
  u64 cts; // [rsp+1020h] [rbp-50h]
  u32 prev_pck_size; // [rsp+1028h] [rbp-48h]
  u32 pck_size; // [rsp+102Ch] [rbp-44h] BYREF
  u8 *output; // [rsp+1030h] [rbp-40h] BYREF
  u8 *data; // [rsp+1038h] [rbp-38h]
  u32 pos; // [rsp+1044h] [rbp-2Ch]
  GF_FilterPacket *dst_pck; // [rsp+1048h] [rbp-28h]
  GF_FilterPacket *pck; // [rsp+1050h] [rbp-20h]
  GF_LATMDmxCtx *ctx; // [rsp+1058h] [rbp-18h]
  GF_Filter *filtera; // [rsp+1060h] [rbp-10h]

  filtera = filter;
  ctx = (GF_LATMDmxCtx *)gf_filter_get_udta(filter);
  cts = -1LL;
  if ( ctx->in_error )
    return ctx->in_error;
  if ( !ctx->duration.num )
    latm_dmx_check_dur(filtera, ctx);
  if ( ctx->opid && ctx->is_playing == GF_FALSE )
    return 0;
  pck = gf_filter_pid_get_packet(ctx->ipid);
  if ( pck )
    goto LABEL_18;
  if ( gf_filter_pid_is_eos(ctx->ipid) == GF_FALSE )
    return 0;
  if ( ctx->latm_buffer_size )
  {
LABEL_18:
    data = (u8 *)gf_filter_pck_get_data(pck, &pck_size);
    if ( ctx->timescale && pck )
      cts = gf_filter_pck_get_cts(pck);
    prev_pck_size = ctx->latm_buffer_size;
    if ( pck && !ctx->resume_from )
    {
      if ( pck_size + ctx->latm_buffer_size > ctx->latm_buffer_alloc )
      {
        ctx->latm_buffer_alloc = pck_size + ctx->latm_buffer_size;
        v1 = (char *)chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(
                       ctx->latm_buffer,
                       ctx->latm_buffer_alloc);
        ctx->latm_buffer = v1;
      }
      memcpy(&ctx->latm_buffer[ctx->latm_buffer_size], data, pck_size);
      ctx->latm_buffer_size += pck_size;
    }
    if ( ctx->bs )
    {
      gf_bs_reassign_buffer(ctx->bs, (const u8 *)ctx->latm_buffer, ctx->latm_buffer_size);
    }
    else
    {
      v2 = gf_bs_new((const u8 *)ctx->latm_buffer, ctx->latm_buffer_size, 0);
      ctx->bs = v2;
    }
    if ( ctx->resume_from )
    {
      gf_bs_seek(ctx->bs, ctx->resume_from - 1);
      ctx->resume_from = 0;
    }
    if ( cts == -1LL )
      prev_pck_size = 0;
    while ( 1 )
    {
      pos = gf_bs_get_position(ctx->bs);
      latm_frame_size = 4096;
      if ( latm_dmx_sync_frame_bs(ctx->bs, &ctx->acfg, &latm_frame_size, latm_buffer, 0LL) == GF_FALSE )
      {
        if ( pck )
        {
          pos = gf_bs_get_position(ctx->bs);
          memmove(ctx->latm_buffer, &ctx->latm_buffer[pos], ctx->latm_buffer_size - pos);
          ctx->latm_buffer_size -= pos;
          gf_filter_pid_drop_packet(ctx->ipid);
          return 0;
        }
        else
        {
          ctx->latm_buffer_size = 0;
          return latm_dmx_process(filtera);
        }
      }
      if ( ctx->in_seek
        && ctx->dts_inc + ctx->cts >= (unsigned int)(int)(ctx->start_range * (double)GF_M4ASampleRates[ctx->sr_idx]) )
      {
        ctx->in_seek = GF_FALSE;
      }
      latm_dmx_check_pid(filtera, ctx);
      if ( ctx->is_playing == GF_FALSE )
      {
        ctx->resume_from = pos + 1;
        return 0;
      }
      if ( ctx->in_seek == GF_FALSE )
        break;
LABEL_50:
      latm_dmx_update_cts(ctx);
      if ( prev_pck_size )
      {
        pos = gf_bs_get_position(ctx->bs);
        if ( prev_pck_size <= pos )
        {
          prev_pck_size = 0;
          if ( ctx->src_pck )
            gf_filter_pck_unref(ctx->src_pck);
          ctx->src_pck = pck;
          if ( pck )
            gf_filter_pck_ref_props(&ctx->src_pck);
        }
      }
    }
    sap = GF_FILTER_SAP_1;
    dst_pck = gf_filter_pck_new_alloc(ctx->opid, latm_frame_size, &output);
    if ( ctx->src_pck )
      gf_filter_pck_merge_properties(ctx->src_pck, dst_pck);
    memcpy(output, latm_buffer, latm_frame_size);
    gf_filter_pck_set_cts(dst_pck, ctx->cts);
    gf_filter_pck_set_duration(dst_pck, ctx->dts_inc);
    gf_filter_pck_set_framing(dst_pck, GF_TRUE, GF_TRUE);
    if ( ctx->acfg.base_object_type == 1970495843 )
    {
      if ( latm_frame_size && (*output & 0x80) != 0 && ctx->prev_sap == GF_FALSE )
      {
        ctx->prev_sap = GF_TRUE;
        gf_filter_pck_set_sap(dst_pck, GF_FILTER_SAP_1);
LABEL_49:
        gf_filter_pck_send(dst_pck);
        goto LABEL_50;
      }
      sap = GF_FILTER_SAP_NONE;
      ctx->prev_sap = GF_FALSE;
    }
    gf_filter_pck_set_sap(dst_pck, sap);
    goto LABEL_49;
  }
  if ( ctx->opid )
    gf_filter_pid_set_eos(ctx->opid);
  if ( ctx->src_pck )
    gf_filter_pck_unref(ctx->src_pck);
  ctx->src_pck = 0LL;
  return 1;
}