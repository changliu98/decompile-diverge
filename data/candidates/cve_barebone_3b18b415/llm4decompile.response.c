void
merged_2v_upsample (j_decompress_ptr cinfo, JSAMPIMAGE input_buf,
      JDIMENSION *in_row_group_ctr, JDIMENSION in_row_groups_avail,
      JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
      JDIMENSION out_rows_avail)
{
  my_upsample_ptr upsample = (my_upsample_ptr) cinfo->upsample;
  register JDIMENSION num_rows;

  if (! upsample->spare_row_valid) {





    num_rows = (upsample->rows_to_go > 2 ? 2 : upsample->rows_to_go);

    if (*out_row_ctr + num_rows > out_rows_avail)
      num_rows = out_rows_avail - *out_row_ctr;


    if (num_rows < 2)
      upsample->spare_row_valid = 1;

    (*cinfo->upsample->upsample) (cinfo, input_buf, in_row_group_ctr,
      in_row_groups_avail, output_buf + *out_row_ctr,
      (JDIMENSION) num_rows);
  } else {





    jcopy_sample_rows((JSAMPARRAY) & upsample->spare_row, 0,
       output_buf + *out_row_ctr, 0,
       1,
       (size_t) ((cinfo->out_color_space == JCS_RGB565) ?
   cinfo->output_width * 2 :
   upsample->out_width_grouped));

    num_rows = 1;
    upsample->spare_row_valid = 0;
  }

  *out_row_ctr += num_rows;
  upsample->rows_to_go -= num_rows;


  if (! upsample->spare_row_valid)
    (*in_row_group_ctr)++;
}