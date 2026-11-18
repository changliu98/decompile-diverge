s32 svc_parse_slice(GF_BitStream *bs,AVCState *avc,AVCSliceInfo *si)

{
  u32 uVar1;
  s32 sVar2;
  s32 pps_id;
  AVCSliceInfo *si_local;
  AVCState *avc_local;
  GF_BitStream *bs_local;
  s32 local_c;
  
  gf_bs_read_ue_log_idx3(bs,"first_mb_in_slice",-1,-1,-1);
  uVar1 = gf_bs_read_ue_log_idx3(bs,"slice_type",-1,-1,-1);
  si->slice_type = uVar1;
  if (si->slice_type < 10) {
    uVar1 = gf_bs_read_ue_log_idx3(bs,"pps_id",-1,-1,-1);
    if ((int)uVar1 < 0x100) {
      si->pps = avc->pps + (int)uVar1;
      si->pps->id = uVar1;
      if (si->pps->slice_group_count == 0) {
        local_c = -2;
      }
      else {
        si->sps = avc->sps + (si->pps->sps_id + 0x10);
        if (si->sps->log2_max_frame_num == 0) {
          local_c = -2;
        }
        else {
          uVar1 = gf_bs_read_int(bs,si->sps->log2_max_frame_num);
          si->frame_num = uVar1;
          si->field_pic_flag = '\0';
          if (si->sps->frame_mbs_only_flag == GF_FALSE) {
            uVar1 = gf_bs_read_int(bs,1);
            si->field_pic_flag = (u8)uVar1;
            if (si->field_pic_flag != '\0') {
              uVar1 = gf_bs_read_int(bs,1);
              si->bottom_field_flag = (u8)uVar1;
            }
          }
          if ((si->nal_unit_type == '\x05') || ((si->NalHeader).idr_pic_flag != 0)) {
            uVar1 = gf_bs_read_ue_log_idx3(bs,"idr_pic_id",-1,-1,-1);
            si->idr_pic_id = uVar1;
          }
          if (si->sps->poc_type == 0) {
            uVar1 = gf_bs_read_int(bs,si->sps->log2_max_poc_lsb);
            si->poc_lsb = uVar1;
            if ((si->pps->pic_order_present != 0) && (si->field_pic_flag == '\0')) {
              sVar2 = gf_bs_read_se_log_idx2(bs,"delta_poc_bottom",-1,-1);
              si->delta_poc_bottom = sVar2;
            }
          }
          else if ((si->sps->poc_type == 1) && (si->sps->delta_pic_order_always_zero_flag == 0)) {
            sVar2 = gf_bs_read_se_log_idx2(bs,"delta_poc0",-1,-1);
            si->delta_poc[0] = sVar2;
            if ((si->pps->pic_order_present == 1) && (si->field_pic_flag == '\0')) {
              sVar2 = gf_bs_read_se_log_idx2(bs,"delta_poc1",-1,-1);
              si->delta_poc[1] = sVar2;
            }
          }
          if (si->pps->redundant_pic_cnt_present != 0) {
            uVar1 = gf_bs_read_ue_log_idx3(bs,"redundant_pic_cnt",-1,-1,-1);
            si->redundant_pic_cnt = uVar1;
          }
          local_c = 0;
        }
      }
    }
    else {
      local_c = -1;
    }
  }
  else {
    local_c = -1;
  }
  return local_c;
}