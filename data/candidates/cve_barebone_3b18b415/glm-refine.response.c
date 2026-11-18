void __cdecl merged_2v_upsample(
        j_decompress_ptr cinfo,
        JSAMPIMAGE input_buf,
        JDIMENSION *in_row_group_ctr,
        JDIMENSION in_row_groups_avail,
        JSAMPARRAY output_buf,
        JDIMENSION *out_row_ctr,
        JDIMENSION out_rows_avail)
{
  my_upsample_ptr upsample = (my_upsample_ptr)cinfo->upsample;
  JDIMENSION num_rows;

  if (upsample->spare_full)
  {
    JDIMENSION size = upsample->out_row_width;
    if (cinfo->out_color_space == JCS_RGB565)
      size = 2 * cinfo->output_width;

    jcopy_sample_rows(&upsample->spare_row, 0, &output_buf[*out_row_ctr], 0, 1, size);
    num_rows = 1;
    upsample->spare_full = 0;
  }
  else
  {
    num_rows = (upsample->rows_to_go < 2) ? upsample->rows_to_go : 2;
    JDIMENSION out_rows_availa = out_rows_avail - *out_row_ctr;
    if (num_rows > out_rows_availa)
      num_rows = out_rows_availa;

    JSAMPROW work_ptrs[2];
    work_ptrs[0] = output_buf[*out_row_ctr];
    if (num_rows <= 1)
    {
      work_ptrs[1] = upsample->spare_row;
      upsample->spare_full = 1;
    }
    else
    {
      work_ptrs[1] = output_buf[*out_row_ctr + 1];
    }

    upsample->upmethod(cinfo, input_buf, *in_row_group_ctr, work_ptrs);
  }

  *out_row_ctr += num_rows;
  upsample->rows_to_go -= num_rows;
  if (!upsample->spare_full)
    ++*in_row_group_ctr;
}