void __cdecl merged_2v_upsample(
        j_decompress_ptr cinfo,
        JSAMPIMAGE input_buf,
        JDIMENSION *in_row_group_ctr,
        JDIMENSION in_row_groups_avail,
        JSAMPARRAY output_buf,
        JDIMENSION *out_row_ctr,
        JDIMENSION out_rows_avail)
{
  JDIMENSION size; // [rsp+8h] [rbp-58h]
  JDIMENSION num_rows; // [rsp+Ch] [rbp-54h]
  JSAMPROW work_ptrs[2]; // [rsp+10h] [rbp-50h] BYREF
  my_upsample_ptr upsample; // [rsp+28h] [rbp-38h]
  JDIMENSION *out_row_ctra; // [rsp+30h] [rbp-30h]
  JSAMPARRAY output_bufa; // [rsp+38h] [rbp-28h]
  JDIMENSION in_row_groups_availa; // [rsp+44h] [rbp-1Ch]
  JDIMENSION *in_row_group_ctra; // [rsp+48h] [rbp-18h]
  JSAMPIMAGE input_bufa; // [rsp+50h] [rbp-10h]
  j_decompress_ptr cinfoa; // [rsp+58h] [rbp-8h]
  JDIMENSION out_rows_availa; // [rsp+70h] [rbp+10h]

  cinfoa = cinfo;
  input_bufa = input_buf;
  in_row_group_ctra = in_row_group_ctr;
  in_row_groups_availa = in_row_groups_avail;
  output_bufa = output_buf;
  out_row_ctra = out_row_ctr;
  upsample = (my_upsample_ptr)cinfo->upsample;
  if ( upsample->spare_full )
  {
    size = upsample->out_row_width;
    if ( cinfoa->out_color_space == JCS_RGB565 )
      size = 2 * cinfoa->output_width;
    jcopy_sample_rows(&upsample->spare_row, 0, &output_bufa[*out_row_ctra], 0, 1, size);
    num_rows = 1;
    upsample->spare_full = 0;
  }
  else
  {
    num_rows = 2;
    if ( upsample->rows_to_go < 2 )
      num_rows = upsample->rows_to_go;
    out_rows_availa = out_rows_avail - *out_row_ctra;
    if ( num_rows > out_rows_availa )
      num_rows = out_rows_availa;
    work_ptrs[0] = output_bufa[*out_row_ctra];
    if ( num_rows <= 1 )
    {
      work_ptrs[1] = upsample->spare_row;
      upsample->spare_full = 1;
    }
    else
    {
      work_ptrs[1] = output_bufa[*out_row_ctra + 1];
    }
    upsample->upmethod(cinfoa, input_bufa, *in_row_group_ctra, work_ptrs);
  }
  *out_row_ctra += num_rows;
  upsample->rows_to_go -= num_rows;
  if ( !upsample->spare_full )
    ++*in_row_group_ctra;
}