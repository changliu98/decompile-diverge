int svc_parse_slice(GF_BitStream *bs, AVCState *avc, AVCSliceInfo *si)
{
    int val;


    gf_bs_read_ue_log_idx3(bs, "first_mb_in_slice", -1, -1, -1);
    si->slice_type = gf_bs_read_ue_log_idx3(bs, "slice_type", -1, -1, -1);
    if (si->slice_type > 9)
        return -1;


    val = gf_bs_read_ue_log_idx3(bs, "pps_id", -1, -1, -1);
    if (val < 0 || val > 255)
        return -1;

    si->pps = &avc->pps[val];
    si->pps->id = val;


    if (!si->pps->slice_group_count)
        return -2;

    si->sps = &avc->sps[si->pps->sps_id + 16];


    if (!si->sps->log2_max_frame_num)
        return -2;

    si->frame_num = gf_bs_read_int(bs, si->sps->log2_max_frame_num);
    si->field_pic_flag = 0;
    if (si->sps->frame_mbs_only_flag == GF_FALSE) {
        si->field_pic_flag = gf_bs_read_int(bs, 1);
        if (si->field_pic_flag)
            si->bottom_field_flag = gf_bs_read_int(bs, 1);
    }


    if (si->nal_unit_type == 5 || si->NalHeader.idr_pic_flag)
        si->idr_pic_id = gf_bs_read_ue_log_idx3(bs, "idr_pic_id", -1, -1, -1);


    if (si->sps->poc_type == 0) {
        si->poc_lsb = gf_bs_read_int(bs, si->sps->log2_max_poc_lsb);
        if (si->pps->pic_order_present && !si->field_pic_flag)
            si->delta_poc_bottom = gf_bs_read_se_log_idx2(bs, "delta_poc_bottom", -1, -1);
    } else if (si->sps->poc_type == 1 && !si->sps->delta_pic_order_always_zero_flag) {
        si->delta_poc[0] = gf_bs_read_se_log_idx2(bs, "delta_poc0", -1, -1);
        if (si->pps->pic_order_present == 1 && !si->field_pic_flag)
            si->delta_poc[1] = gf_bs_read_se_log_idx2(bs, "delta_poc1", -1, -1);
    }


    if (si->pps->redundant_pic_cnt_present)
        si->redundant_pic_cnt = gf_bs_read_ue_log_idx3(bs, "redundant_pic_cnt", -1, -1, -1);

    return 0;
}