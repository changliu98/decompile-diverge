static void
upsample2v_merged_rows (j_decompress_ptr cinfo,
   jpeg_component_info * compptr,
   JDIMENSION in_row_group_ctr,
   JDIMENSION in_row_groups_avail,
   JSAMPARRAY output_buf,
   JDIMENSION out_row_ctr,
   JDIMENSION out_rows_avail)
{
  my_upsample_ptr upsample = (my_upsample_ptr) cinfo->upsample;
  unsigned int num_rows, max_rows;
  JSAMPROW rowptr[3];
  JDIMENSION output_cols = upsample->out_row_width;

  if (upsample->need_context_rows) {
    JDIMENSION last_row = upsample->last_row;
    if (cinfo->output_components == 16)
      output_cols = cinfo->output_width << 1;
    jcopy_sample_rows(&upsample->context_rows, 0,
        output_buf + out_row_ctr, 0, 1, output_cols);
    num_rows = 1;
    upsample->need_context_rows = 0;
  } else {
    num_rows = 2;
    if (num_rows > upsample->rows_to_skip)
      num_rows = upsample->rows_to_skip;
    out_rows_avail -= out_row_ctr;
    if (num_rows > out_rows_avail)
      num_rows = out_rows_avail;
    rowptr[0] = output_buf[out_row_ctr];
    if (num_rows > 1) {
      rowptr[1] = output_buf[out_row_ctr + 1];
    } else {
      rowptr[1] = upsample->context_rows;
      upsample->need_context_rows = 1;
    }
    (*upsample->upmethod) (cinfo, compptr,
      in_row_group_ctr, rowptr);
  }

  out_row_ctr += num_rows;
  upsample->rows_to_skip -= num_rows;
  if (! upsample->need_context_rows)
    in_row_group_ctr++;
}