static enum GF_Err latm_dmx_process(struct GF_Filter *filter)
{
    struct GF_FilterLATMDmxCtx *ctx = (GF_FilterLATMDmxCtx*)GF_FilterGetContext(filter);
    struct GF_FilterPacket *src_pck;
    struct GF_FilterPacket *dst_pck;
    struct GF_FilterSAPType sap;
    unsigned int size;
    unsigned int prev_size;
    unsigned int pos;
    unsigned int frame_size;
    unsigned char *data;
    unsigned char *output;
    unsigned long long cts = (GF_ULL)(-1);
    if (ctx->in_error != GF_OK)
        return ctx->in_error;
    if (ctx->duration.num == 0)
        GF_FilterLATMDmx_UpdateDuration(filter, ctx);
    if (ctx->opid != 0 && ctx->is_playing == GF_FALSE)
        return GF_OK;
    src_pck = GF_FilterLATMDmx_GetSrcPck(ctx->ipid);
    if (src_pck == ((void *)0))
    {
        if (GF_FilterLATMDmx_AddSrcPck(ctx->ipid) == GF_FALSE)
            return GF_OK;
    }
    if (ctx->latm_buffer_size == 0)
    {
        if (ctx->opid != 0)
            GF_FilterLATMDmx_AddDstPck(ctx->opid);
        if (ctx->src_pck != ((void *)0))
            GF_FilterPacketFree(ctx->src_pck);
        ctx->src_pck = ((void *)0);
        return GF_TRUE;
    }
    if (src_pck != ((void *)0))
    {
        data = GF_FilterPacketGetData(src_pck, &size);
        if (ctx->timescale != 0 && src_pck != ((void *)0))
            cts = GF_FilterLATMDmx_GetCTS(src_pck);
    }
    prev_size = ctx->latm_buffer_size;
    if (src_pck != ((void *)0) && ctx->resume_from == 0)
    {
        if (ctx->latm_buffer_size + size > ctx->latm_buffer_alloc)
        {
            ctx->latm_buffer_alloc = ctx->latm_buffer_size + size;
            ctx->latm_buffer = (unsigned char *)chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(ctx->latm_buffer, ctx->latm_buffer_alloc);
        }
        GF_FilterLATMDmx_Memcpy(&ctx->latm_buffer[ctx->latm_buffer_size], data, size);
        ctx->latm_buffer_size += size;
    }
    if (ctx->bs == ((void *)0))
    {
        ctx->bs = GF_FilterLATMDmx_CreateBitstream(ctx->latm_buffer, ctx->latm_buffer_size, GF_FALSE);
    }
    else
    {
        GF_FilterLATMDmx_AppendBitstream(ctx->bs, ctx->latm_buffer, ctx->latm_buffer_size);
    }
    if (ctx->resume_from != 0)
    {
        GF_FilterLATMDmx_SeekBitstream(ctx->bs, ctx->resume_from - 1);
        ctx->resume_from = 0;
    }
    if (cts == (GF_ULL)(-1))
        prev_size = 0;
    for (;;)
    {
        pos = GF_FilterLATMDmx_GetBitstreamPos(ctx->bs);
        frame_size = (4096);
        if (GF_FilterLATMDmx_ReadFrame(ctx->bs, &ctx->acfg, &frame_size,
                                       ctx->latm_buffer, GF_FALSE) == GF_FALSE)
        {
            if (src_pck != ((void *)0))
            {
                pos = GF_FilterLATMDmx_GetBitstreamPos(ctx->bs);
                GF_FilterLATMDmx_Memcpy(&ctx->latm_buffer[pos], &ctx->latm_buffer[pos],
                                        ctx->latm_buffer_size - pos);
                ctx->latm_buffer_size -= pos;
                GF_FilterLATMDmx_RemoveSrcPck(ctx->ipid);
                return GF_OK;
            }
            else
            {
                ctx->latm_buffer_size = 0;
                return latm_dmx_process(filter);
            }
        }
        if (ctx->in_seek &&
            ctx->dts_inc + ctx->cts >=
            ((double)ctx->start_range * GF_M4ASampleRates[ctx->sr_idx])
            )
        {
            ctx->in_seek = GF_FALSE;
        }
        GF_FilterLATMDmx_UpdateDuration(filter, ctx);
        if (ctx->is_playing == GF_FALSE)
        {
            ctx->resume_from = pos + 1;
            return GF_OK;
        }
        if (ctx->in_seek == GF_FALSE)
            break;
        GF_FilterLATMDmx_UpdateACFG(ctx);
        if (prev_size != 0)
        {
            pos = GF_FilterLATMDmx_GetBitstreamPos(ctx->bs);
            if (pos >= prev_size)
            {
                prev_size = 0;
                if (ctx->src_pck != ((void *)0))
                    GF_FilterPacketFree(ctx->src_pck);
                ctx->src_pck = src_pck;
                if (src_pck != ((void *)0))
                    GF_FilterLATMDmx_AddSrcPck(&ctx->src_pck);
            }
        }
    }
    sap = GF_FILTER_SAP_1;
    dst_pck = GF_FilterLATMDmx_CreateDstPck(ctx->opid, frame_size, &output);
    if (ctx->src_pck != ((void *)0))
        GF_FilterLATMDmx_CopySrcPck(ctx->src_pck, dst_pck);
    GF_FilterLATMDmx_Memcpy(output, ctx->latm_buffer, frame_size);
    GF_FilterLATMDmx_SetDstPckCTS(dst_pck, ctx->cts);
    GF_FilterLATMDmx_SetDstPckDTS(dst_pck, ctx->dts_inc);
    GF_FilterLATMDmx_SetDstPckSize(dst_pck, GF_TRUE, GF_TRUE);
    if (ctx->acfg.base_object_type == (unsigned int)(0x72616d6c))
    {
        if (frame_size != 0 && (output[0] & 0x80) != 0 && ctx->prev_sap == GF_FALSE)
        {
            ctx->prev_sap = GF_TRUE;
            GF_FilterLATMDmx_SetDstPckSAP(dst_pck, sap);
        }
        else
        {
            sap = GF_FILTER_SAP_NONE;
            ctx->prev_sap = GF_FALSE;
        }
    }
    GF_FilterLATMDmx_SetDstPckSAP(dst_pck, sap);
    GF_FilterLATMDmx_SetDstPckSize(dst_pck);
    GF_FilterLATMDmx_AddDstPck(dst_pck);
    return GF_OK;
}