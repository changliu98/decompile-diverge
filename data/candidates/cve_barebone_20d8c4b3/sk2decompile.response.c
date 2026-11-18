static int svc_parse_slice(GOP *g, SVCContext *svc, Slice *slice) {
  int pps_id;
  gf_bs_read_ue_log_idx3(g, "first_mb_in_slice", -1, -1, -1);
  slice->slice_type = gf_bs_read_ue_log_idx3(g, "slice_type", -1, -1, -1);
  if (slice->slice_type >= 10) return -1;
  pps_id = gf_bs_read_ue_log_idx3(g, "pps_id", -1, -1, -1);
  if (pps_id >= 256) return -1;
  slice->pps = &g->pps_list[pps_id];
  slice->pps->id = pps_id;
  if (slice->pps->valid == 0) return -2;
  slice->sps = &g->sps_list[slice->pps->sps_id + 16];
  if (slice->sps->log2_ctb_size == 0) return -2;
  slice->ctb_size = gf_bs_read_int(g, slice->sps->log2_ctb_size);
  slice->adaptive_ref_pic_buffering_flag = 0;
  if (slice->sps->seq_scaling_matrix_present == GF_TRUE) {
    slice->adaptive_ref_pic_buffering_flag = gf_bs_read_int(g, 1);
    if (slice->adaptive_ref_pic_buffering_flag)
      slice->diff_pic_scaling_off_flag = gf_bs_read_int(g, 1);
  }
  if (slice->slice_type_code == 5 || slice->idr_flag)
    slice->idr_pic_id = gf_bs_read_ue_log_idx3(g, "idr_pic_id", -1, -1, -1);
  if (slice->sps->poc_type == 0) {
    slice->poc_cycle = gf_bs_read_int(g, slice->sps->log2_max_poc_lsb);
    if (slice->pps->bottom_field_pic_order_in_frame_present_flag &&
        !slice->adaptive_ref_pic_buffering_flag)
      slice->delta_poc_bottom =
          gf_bs_read_se_log_idx2(g, "delta_poc_bottom", -1, -1);
  } else if (slice->sps->poc_type == 1 && !slice->sps->poc_cycle_alt) {
    slice->delta_poc[0] = gf_bs_read_se_log_idx2(g, "delta_poc0", -1, -1);
    if (slice->pps->bottom_field_pic_order_in_frame_present_flag &&
        !slice->adaptive_ref_pic_buffering_flag)
      slice->delta_poc[1] = gf_bs_read_se_log_idx2(g, "delta_poc1", -1, -1);
  }
  if (slice->pps->redundant_pic_cnt)
    slice->redundant_pic_cnt =
        gf_bs_read_ue_log_idx3(g, "redundant_pic_cnt", -1, -1, -1);
  return 0;
}