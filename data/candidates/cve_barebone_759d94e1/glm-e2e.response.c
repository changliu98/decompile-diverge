int latm_dmx_process(void *filter) {
    struct ctx *ctx = gf_filter_get_udta(filter);
    u64 cts = (u64)-1;
    int ret = 0;

    if (ctx->abort_reason != 0) {
        return ctx->abort_reason;
    }

    if (ctx->file_size == 0) {
        latm_dmx_check_dur(filter, ctx);
    }

    if (ctx->opid != NULL && ctx->is_playing == 0) {
        return 0;
    }

    void *pck = gf_filter_pid_get_packet(ctx->pid);
    if (pck == NULL) {
        if (gf_filter_pid_is_eos(ctx->pid)) {
            if (ctx->buffer_size == 0) {
                if (ctx->opid) {
                    gf_filter_pid_set_eos(ctx->opid);
                }
                if (ctx->pck_ref) {
                    gf_filter_pck_unref(ctx->pck_ref);
                }
                ctx->pck_ref = NULL;
                return 1;
            }
        } else {
            return 0;
        }
    }

    int pck_size;
    void *pck_data = gf_filter_pck_get_data(pck, &pck_size);

    if (ctx->has_cts && pck != NULL) {
        cts = gf_filter_pck_get_cts(pck);
    }

    u32 remain = ctx->buffer_size;
    if (pck != NULL && ctx->seek_request == 0) {
        if (ctx->buffer_size + pck_size > ctx->max_size) {
            ctx->max_size = ctx->buffer_size + pck_size;
            ctx->buffer = gf_realloc(ctx->buffer, ctx->max_size);
        }
        memcpy(ctx->buffer + ctx->buffer_size, pck_data, pck_size);
        ctx->buffer_size += pck_size;
    }

    if (ctx->bs == NULL) {
        ctx->bs = gf_bs_new(ctx->buffer, ctx->buffer_size, 0);
    } else {
        gf_bs_reassign_buffer(ctx->bs, ctx->buffer, ctx->buffer_size);
    }

    if (ctx->seek_request != 0) {
        gf_bs_seek(ctx->bs, ctx->seek_request - 1);
        ctx->seek_request = 0;
    }

    if (cts == (u64)-1) {
        remain = 0;
    }

    while (1) {
        u32 pos = gf_bs_get_position(ctx->bs);
        int out_size = 0x1000;
        if (!latm_dmx_sync_frame_bs(ctx->bs, ctx, ctx->out_buf, &out_size, 0)) {
            break;
        }

        if (ctx->nb_samples != 0) {
            u64 target_ts = (u64)(ctx->nb_samples * GF_M4ASampleRates[ctx->sample_rate_idx]);
            if (ctx->next_cts + ctx->duration < target_ts) {
                ctx->nb_samples = 0;
            }
        }

        latm_dmx_check_pid(filter, ctx);

        if (ctx->is_playing == 0) {
            ctx->seek_request = pos + 1;
            return 0;
        }

        if (ctx->nb_samples == 0) {
            int sap = 1;
            void *dst_pck = gf_filter_pck_new_alloc(ctx->opid, out_size, &pck_data);
            if (ctx->pck_ref) {
                gf_filter_pck_merge_properties(ctx->pck_ref, dst_pck);
            }
            memcpy(pck_data, ctx->out_buf, out_size);
            gf_filter_pck_set_cts(dst_pck, ctx->next_cts);
            gf_filter_pck_set_duration(dst_pck, ctx->duration);
            gf_filter_pck_set_framing(dst_pck, 1, 1);
            
            if (ctx->stream_type == 0x75736163) { // 'casu' or similar 4CC
                if (out_size && (pck_data[0] & 0x80) && !ctx->crc) {
                    sap = 1;
                    ctx->crc = 1;
                } else {
                    sap = 0;
                    ctx->crc = 0;
                }
            }
            gf_filter_pck_set_sap(dst_pck, sap);
            gf_filter_pck_send(dst_pck);
        }

        latm_dmx_update_cts(ctx);

        if (remain != 0) {
            pos = gf_bs_get_position(ctx->bs);
            if (remain <= pos) {
                remain = 0;
                if (ctx->pck_ref) {
                    gf_filter_pck_unref(ctx->pck_ref);
                }
                ctx->pck_ref = pck;
                if (pck) {
                    gf_filter_pck_ref_props(&ctx->pck_ref);
                }
            }
        }
    }

    if (pck != NULL) {
        pos = gf_bs_get_position(ctx->bs);
        memmove(ctx->buffer, ctx->buffer + pos, ctx->buffer_size - pos);
        ctx->buffer_size -= pos;
        gf_filter_pid_drop_packet(ctx->pid);
    } else {
        ctx->buffer_size = 0;
        return latm_dmx_process(filter);
    }

    return 0;
}