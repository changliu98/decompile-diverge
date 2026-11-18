static void merged_2v_upsample(j_decompress_ptr cinfo, JSAMPIMAGE output_buf,
                               JDIMENSION *out_row_group_ctr,
                               JDIMENSION out_row_groups_avail,
                               JSAMPARRAY input_buf, JDIMENSION *in_row_ctr,
                               JDIMENSION in_rows_avail) {
  my_upsample_ptr upsample = (my_upsample_ptr)cinfo->upsample;
  JSAMPROW input_rows[2];
  JDIMENSION num_rows;
  JDIMENSION rows_avail;
  if (upsample->first_time) {
    rows_avail = upsample->two_row_goal;
    if (cinfo->process == JPROC_LOSSLESS) rows_avail *= 2;
    jcopy_sample_rows(&upsample->temp_buffer, 0, input_buf[*in_row_ctr], 0, 1,
                      rows_avail);
    num_rows = 1;
    upsample->first_time = 0;
  } else {
    num_rows = 2;
    if (num_rows > upsample->rows_to_go) num_rows = upsample->rows_to_go;
    rows_avail = in_rows_avail - *in_row_ctr;
    if (num_rows > rows_avail) num_rows = rows_avail;
    input_rows[0] = input_buf[*in_row_ctr];
    if (num_rows > 1) {
      input_rows[1] = input_buf[*in_row_ctr + 1];
    } else {
      input_rows[1] = upsample->temp_buffer;
      upsample->first_time = 1;
    }
    (*upsample->upsample_method)(cinfo, output_buf, *out_row_group_ctr,
                                 input_rows);
  }
  *in_row_ctr += num_rows;
  upsample->rows_to_go -= num_rows;
  if (!upsample->first_time) (*out_row_group_ctr)++;
}