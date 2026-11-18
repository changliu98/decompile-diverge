void merged_2v_upsample(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION *in_row_group_ctr,
                       JDIMENSION in_row_groups_avail,JSAMPARRAY output_buf,JDIMENSION *out_row_ctr,
                       JDIMENSION out_rows_avail)

{
  jpeg_upsampler *pjVar1;
  JDIMENSION size;
  JDIMENSION num_rows;
  JSAMPROW work_ptrs [2];
  my_upsample_ptr upsample;
  JDIMENSION *out_row_ctr_local;
  JSAMPARRAY output_buf_local;
  JDIMENSION in_row_groups_avail_local;
  JDIMENSION *in_row_group_ctr_local;
  JSAMPIMAGE input_buf_local;
  j_decompress_ptr cinfo_local;
  
  pjVar1 = cinfo->upsample;
  if (*(int *)&pjVar1[3].start_pass == 0) {
    num_rows = 2;
    if (*(uint *)&pjVar1[3].upsample < 2) {
      num_rows = *(JDIMENSION *)&pjVar1[3].upsample;
    }
    if (out_rows_avail - *out_row_ctr < num_rows) {
      num_rows = out_rows_avail - *out_row_ctr;
    }
    if (num_rows < 2) {
      *(undefined4 *)&pjVar1[3].start_pass = 1;
    }
    (*pjVar1[1].start_pass)(cinfo);
  }
  else {
    size = *(JDIMENSION *)((long)&pjVar1[3].start_pass + 4);
    if (cinfo->out_color_space == JCS_RGB565) {
      size = cinfo->output_width << 1;
    }
    jcopy_sample_rows((JSAMPARRAY)&pjVar1[2].need_context_rows,0,output_buf + *out_row_ctr,0,1,size)
    ;
    num_rows = 1;
    *(undefined4 *)&pjVar1[3].start_pass = 0;
  }
  *out_row_ctr = num_rows + *out_row_ctr;
  *(JDIMENSION *)&pjVar1[3].upsample = *(int *)&pjVar1[3].upsample - num_rows;
  if (*(int *)&pjVar1[3].start_pass == 0) {
    *in_row_group_ctr = *in_row_group_ctr + 1;
  }
  return;
}