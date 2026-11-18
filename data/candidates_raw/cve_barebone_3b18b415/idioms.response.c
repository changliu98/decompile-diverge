void my_upsample(struct j_decompress_ptr cinfo, struct JSAMPIMAGE input_buf, long *in_row_group_ctr, long in_row_groups_avail, struct JSAMPARRAY output_buf, long *out_row_ctr, long out_rows_avail)
{
  struct my_upsample_ptr upsample = cinfo->upsample;
  if (upsample->spare_full) {
    long out_row_width = upsample->out_row_width;
    if (cinfo->out_color_space == JCS_RGB565)
      out_row_width *= 2;
    my_copy_row(&upsample->spare_row, 0,
                output_buf[*out_row_ctr],
                0, 1, out_row_width);
    long num_rows = 1;
    upsample->spare_full = 0;
  } else {
    long num_rows = 2;
    if (upsample->rows_to_go < num_rows)
      num_rows = upsample->rows_to_go;
    long out_rows_left = out_rows_avail - *out_row_ctr;
    if (num_rows > out_rows_left)
      num_rows = out_rows_left;
    struct JSAMPROW *out_row_ptrs[2];
    out_row_ptrs[0] = output_buf[*out_row_ctr];
    if (num_rows > 1)
      out_row_ptrs[1] = output_buf[*out_row_ctr + 1];
    else {
      out_row_ptrs[1] = upsample->spare_row;
      upsample->spare_full = 1;
    }
    upsample->upmethod(cinfo, input_buf, *in_row_group_ctr,
                       out_row_ptrs);
  }
  (*out_row_ctr) += num_rows;
  upsample->rows_to_go -= num_rows;
  if (!upsample->spare_full)
    (*in_row_group_ctr)++;
}