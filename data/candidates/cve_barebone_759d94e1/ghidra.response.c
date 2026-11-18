GF_Err latm_dmx_process(GF_Filter *filter)

{
  Bool BVar1;
  char *pcVar2;
  GF_BitStream *pGVar3;
  u64 uVar4;
  ulong uVar5;
  double dVar6;
  GF_FilterSAPType sap;
  u64 nb_samples_at_seek;
  u32 latm_frame_size;
  u8 latm_buffer [4096];
  u64 cts;
  u32 prev_pck_size;
  u32 pck_size;
  u8 *output;
  u8 *data;
  u32 pos;
  GF_FilterPacket *dst_pck;
  GF_FilterPacket *pck;
  GF_LATMDmxCtx *ctx;
  GF_Filter *filter_local;
  GF_Err local_c;
  
  filter_local = filter;
  ctx = gf_filter_get_udta(filter);
  cts = 0xffffffffffffffff;
  if (ctx->in_error == GF_OK) {
    if ((ctx->duration).num == 0) {
      latm_dmx_check_dur(filter_local,ctx);
    }
    if ((ctx->opid == (GF_FilterPid *)0x0) || (ctx->is_playing != GF_FALSE)) {
      pck = gf_filter_pid_get_packet(ctx->ipid);
      if (pck == (GF_FilterPacket *)0x0) {
        BVar1 = gf_filter_pid_is_eos(ctx->ipid);
        if (BVar1 == GF_FALSE) {
          return GF_OK;
        }
        if (ctx->latm_buffer_size == 0) {
          if (ctx->opid != (GF_FilterPid *)0x0) {
            gf_filter_pid_set_eos(ctx->opid);
          }
          if (ctx->src_pck != (GF_FilterPacket *)0x0) {
            gf_filter_pck_unref(ctx->src_pck);
          }
          ctx->src_pck = (GF_FilterPacket *)0x0;
          return GF_EOS;
        }
      }
      data = gf_filter_pck_get_data(pck,&pck_size);
      if ((ctx->timescale != 0) && (pck != (GF_FilterPacket *)0x0)) {
        cts = gf_filter_pck_get_cts(pck);
      }
      prev_pck_size = ctx->latm_buffer_size;
      if ((pck != (GF_FilterPacket *)0x0) && (ctx->resume_from == 0)) {
        if (ctx->latm_buffer_alloc < ctx->latm_buffer_size + pck_size) {
          ctx->latm_buffer_alloc = ctx->latm_buffer_size + pck_size;
          pcVar2 = gf_realloc(ctx->latm_buffer,(ulong)ctx->latm_buffer_alloc);
          ctx->latm_buffer = pcVar2;
        }
        memcpy(ctx->latm_buffer + ctx->latm_buffer_size,data,(ulong)pck_size);
        ctx->latm_buffer_size = pck_size + ctx->latm_buffer_size;
      }
      if (ctx->bs == (GF_BitStream *)0x0) {
        pGVar3 = gf_bs_new((u8 *)ctx->latm_buffer,(ulong)ctx->latm_buffer_size,0);
        ctx->bs = pGVar3;
      }
      else {
        gf_bs_reassign_buffer(ctx->bs,(u8 *)ctx->latm_buffer,(ulong)ctx->latm_buffer_size);
      }
      if (ctx->resume_from != 0) {
        gf_bs_seek(ctx->bs,(ulong)(ctx->resume_from - 1));
        ctx->resume_from = 0;
      }
      if (cts == 0xffffffffffffffff) {
        prev_pck_size = 0;
      }
      while( true ) {
        uVar4 = gf_bs_get_position(ctx->bs);
        pos = (u32)uVar4;
        latm_frame_size = 0x1000;
        BVar1 = latm_dmx_sync_frame_bs(ctx->bs,&ctx->acfg,&latm_frame_size,latm_buffer,(u32 *)0x0);
        if (BVar1 == GF_FALSE) break;
        if ((ctx->in_seek != GF_FALSE) &&
           (dVar6 = ctx->start_range * (double)GF_M4ASampleRates[ctx->sr_idx], uVar5 = (ulong)dVar6,
           (uVar5 | (long)(dVar6 - DAT_00102008) & (long)uVar5 >> 0x3f) <=
           ctx->cts + (ulong)ctx->dts_inc)) {
          ctx->in_seek = GF_FALSE;
        }
        latm_dmx_check_pid(filter_local,ctx);
        if (ctx->is_playing == GF_FALSE) {
          ctx->resume_from = pos + 1;
          return GF_OK;
        }
        if (ctx->in_seek == GF_FALSE) {
          sap = GF_FILTER_SAP_1;
          dst_pck = gf_filter_pck_new_alloc(ctx->opid,latm_frame_size,&output);
          if (ctx->src_pck != (GF_FilterPacket *)0x0) {
            gf_filter_pck_merge_properties(ctx->src_pck,dst_pck);
          }
          memcpy(output,latm_buffer,(ulong)latm_frame_size);
          gf_filter_pck_set_cts(dst_pck,ctx->cts);
          gf_filter_pck_set_duration(dst_pck,ctx->dts_inc);
          gf_filter_pck_set_framing(dst_pck,GF_TRUE,GF_TRUE);
          if ((ctx->acfg).base_object_type == 0x75736163) {
            if (((latm_frame_size == 0) || ((*output & 0x80) == 0)) || (ctx->prev_sap != GF_FALSE))
            {
              sap = GF_FILTER_SAP_NONE;
              ctx->prev_sap = GF_FALSE;
            }
            else {
              sap = GF_FILTER_SAP_1;
              ctx->prev_sap = GF_TRUE;
            }
          }
          gf_filter_pck_set_sap(dst_pck,sap);
          gf_filter_pck_send(dst_pck);
        }
        latm_dmx_update_cts(ctx);
        if (prev_pck_size != 0) {
          uVar4 = gf_bs_get_position(ctx->bs);
          pos = (u32)uVar4;
          if (prev_pck_size <= pos) {
            prev_pck_size = 0;
            if (ctx->src_pck != (GF_FilterPacket *)0x0) {
              gf_filter_pck_unref(ctx->src_pck);
            }
            ctx->src_pck = pck;
            if (pck != (GF_FilterPacket *)0x0) {
              gf_filter_pck_ref_props(&ctx->src_pck);
            }
          }
        }
      }
      if (pck == (GF_FilterPacket *)0x0) {
        ctx->latm_buffer_size = 0;
        local_c = latm_dmx_process(filter_local);
      }
      else {
        uVar4 = gf_bs_get_position(ctx->bs);
        pos = (u32)uVar4;
        memmove(ctx->latm_buffer,ctx->latm_buffer + (uVar4 & 0xffffffff),
                (ulong)(ctx->latm_buffer_size - pos));
        ctx->latm_buffer_size = ctx->latm_buffer_size - pos;
        gf_filter_pid_drop_packet(ctx->ipid);
        local_c = GF_OK;
      }
    }
    else {
      local_c = GF_OK;
    }
  }
  else {
    local_c = ctx->in_error;
  }
  return local_c;
}