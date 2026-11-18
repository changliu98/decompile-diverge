static int svc_parse_slice(GF_BitStream *s, AVCContext *avctx, H264Slice *sl)
{
    int pps_id;
    int ret;

    gf_bs_read_ue_log_idx3(s, "first_mb_in_slice" , -1, -1);
    sl->type = gf_bs_read_ue_log_idx3(s, "slice_type" , -1, -1);
    if (sl->type > 9) {
        ret = -1;
        goto fail;
    }
    pps_id = gf_bs_read_ue_log_idx3(s, "pps_id" , -1, -1);
    if (pps_id > 255) {
        ret = -1;
        goto fail;
    }
    sl->pps = &avctx->pps[pps_id];
    sl->pps->id = pps_id;
    if (!sl->pps->valid) {
        ret = -2;
        goto fail;
    }

    sl->sp = &avctx->sps[sl->pps->sps_id + 16];
    if (!sl->sp->valid) {
        ret = -2;
        goto fail;
    }

    sl->qp_bd_offset = gf_bs_read_int(s, sl->sp->bit_depth_luma_qp_scale);
    sl->field_pic_flag = 0;
    if (!sl->sp->frame_mbs_only_flag) {
        sl->field_pic_flag = gf_bs_read_int(s, 1);
        if (sl->field_pic_flag) {
            sl->mbaff_frame_flag = gf_bs_read_int(s, 1);
        }
    }
    if (sl->sp->idr_pic_flag || sl->nal_ref_idc) {
        sl->idr_pic_id = gf_bs_read_ue_log_idx3(s, "idr_pic_id" , -1, -1);
    }
    if (!sl->sp->pic_order_cnt_type) {
        sl->pic_order_cnt = gf_bs_read_int(s, sl->sp->pic_order_cnt_bits);
        if (sl->pps->constrained_intra_pred_flag && !sl->field_pic_flag) {
            sl->delta_pic_order_cnt_bottom = gf_bs_read_se_log_idx2(s, "delta_poc_bottom" , -1, -1);
        }
    } else if (sl->sp->pic_order_cnt_type == 1 && !sl->sp->delta_pic_order_always_zero_flag) {
        sl->delta_pic_order_cnt0 = gf_bs_read_se_log_idx2(s, "delta_poc0" , -1, -1);
        if (sl->pps->constrained_intra_pred_flag && !sl->field_pic_flag) {
            sl->delta_pic_order_cnt1 = gf_bs_read_se_log_idx2(s, "delta_poc1" , -1, -1);
        }
    }
    if (sl->pps->redundant_pic_cnt_present_flag) {
        sl->redundant_pic_cnt = gf_bs_read_ue_log_idx3(s, "redundant_pic_cnt" , -1, -1);
    }
    ret = 0;
fail:
    return ret;
}