HSD_finish_res heatshrink_decoder_finish(heatshrink_decoder *hsd)

{
  uint uVar1;
  heatshrink_decoder *hsd_local;
  HSD_finish_res local_c;
  
  if (hsd == (heatshrink_decoder *)0x0) {
    local_c = HSDR_FINISH_ERROR_NULL;
  }
  else {
    uVar1 = (uint)hsd->state;
    if (uVar1 == 0) {
      local_c = (HSD_finish_res)(hsd->input_size != 0);
    }
    else if (uVar1 == 1) {
      local_c = (HSD_finish_res)(hsd->input_size != 0);
    }
    else if (uVar1 - 2 < 4) {
      local_c = (HSD_finish_res)(hsd->input_size != 0);
    }
    else {
      local_c = HSDR_FINISH_MORE;
    }
  }
  return local_c;
}