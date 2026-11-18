int avc_get_slice_header(struct GF_BitStream *stream, struct AVCState *avc, struct AVCSliceInfo *si)
{
  int pps_id;
  int i;
  int ret = 0;
  avc_get_bit(stream,"first_mb_in_slice",-1,-1,-1);
  si->slice_type = avc_get_bit(stream,"slice_type",-1,-1,-1);
  if (si->slice_type > 9)
    return -1;
  pps_id = avc_get_bit(stream,"pps_id",-1,-1,-1);
  if (pps_id > 255)
    return -1;
  si->pps = &avc->pps[pps_id];
  si->pps->id = pps_id;
  if (si->pps->slice_group_count == 0)
    return -2;
  si->sps = &avc->sps[si->pps->sps_id + 16];
  if (si->sps->log2_max_frame_num == 0)
    return -2;
  si->frame_num = avc_get_ue(stream,si->sps->log2_max_frame_num);
  si->field_pic_flag = 0;
  if (si->sps->frame_mbs_only_flag == GF_FALSE)
  {
    si->field_pic_flag = avc_get_ue(stream,1);
    if (si->field_pic_flag)
      si->bottom_field_flag = avc_get_ue(stream,1);
  }
  if (si->nal_unit_type == 5 || si->NalHeader.idr_pic_flag)
    si->idr_pic_id = avc_get_bit(stream,"idr_pic_id",-1,-1,-1);
  if (si->sps->poc_type == 0)
  {
    si->poc_lsb = avc_get_ue(stream,si->sps->log2_max_poc_lsb);
    if (si->pps->pic_order_present && !si->field_pic_flag)
      si->delta_poc_bottom = avc_get_se(stream,"delta_poc_bottom",-1,-1);
  }
  else if (si->sps->poc_type == 1 && !si->sps->delta_pic_order_always_zero_flag)
  {
    si->delta_poc[0] = avc_get_se(stream,"delta_poc0",-1,-1);
    if (si->pps->pic_order_present == 1 && !si->field_pic_flag)
      si->delta_poc[1] = avc_get_se(stream,"delta_poc1",-1,-1);
  }
  if (si->pps->redundant_pic_cnt_present)
    si->redundant_pic_cnt = avc_get_bit(stream,"redundant_pic_cnt",-1,-1,-1);
  return ret;
}