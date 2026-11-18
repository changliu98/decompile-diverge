s32 __cdecl svc_parse_slice(GF_BitStream *bs, AVCState *avc, AVCSliceInfo *si_0)
{
  signed int pps_id; // [rsp+Ch] [rbp-24h]

  gf_bs_read_ue_log_idx3(bs, "first_mb_in_slice", -1, -1, -1);
  si_0->slice_type = gf_bs_read_ue_log_idx3(bs, "slice_type", -1, -1, -1);
  if ( si_0->slice_type > 9 )
    return -1;
  pps_id = gf_bs_read_ue_log_idx3(bs, "pps_id", -1, -1, -1);
  if ( pps_id > 255 )
    return -1;
  si_0->pps = &avc->pps[pps_id];
  si_0->pps->id = pps_id;
  if ( !si_0->pps->slice_group_count )
    return -2;
  si_0->sps = &avc->sps[si_0->pps->sps_id + 16];
  if ( !si_0->sps->log2_max_frame_num )
    return -2;
  si_0->frame_num = gf_bs_read_int(bs, si_0->sps->log2_max_frame_num);
  si_0->field_pic_flag = 0;
  if ( si_0->sps->frame_mbs_only_flag == GF_FALSE )
  {
    si_0->field_pic_flag = gf_bs_read_int(bs, 1u);
    if ( si_0->field_pic_flag )
      si_0->bottom_field_flag = gf_bs_read_int(bs, 1u);
  }
  if ( si_0->nal_unit_type == 5 || si_0->NalHeader.idr_pic_flag )
    si_0->idr_pic_id = gf_bs_read_ue_log_idx3(bs, "idr_pic_id", -1, -1, -1);
  if ( si_0->sps->poc_type )
  {
    if ( si_0->sps->poc_type == 1 && !si_0->sps->delta_pic_order_always_zero_flag )
    {
      si_0->delta_poc[0] = gf_bs_read_se_log_idx2(bs, "delta_poc0", -1, -1);
      if ( si_0->pps->pic_order_present == 1 && !si_0->field_pic_flag )
        si_0->delta_poc[1] = gf_bs_read_se_log_idx2(bs, "delta_poc1", -1, -1);
    }
  }
  else
  {
    si_0->poc_lsb = gf_bs_read_int(bs, si_0->sps->log2_max_poc_lsb);
    if ( si_0->pps->pic_order_present && !si_0->field_pic_flag )
      si_0->delta_poc_bottom = gf_bs_read_se_log_idx2(bs, "delta_poc_bottom", -1, -1);
  }
  if ( si_0->pps->redundant_pic_cnt_present )
    si_0->redundant_pic_cnt = gf_bs_read_ue_log_idx3(bs, "redundant_pic_cnt", -1, -1, -1);
  return 0;
}