static OPJ_BOOL opj_j2k_write_sod(opj_j2k_t * p_j2k,
                                  opj_tcd_t * p_tile_coder,
                                  OPJ_BYTE * p_data,
                                  OPJ_UINT32 * p_data_size,
                                  OPJ_UINT32 p_total_data_size,
                                  opj_stream_private_t * p_stream,
                                  opj_event_mgr_t * p_manager)
{
  opj_codestream_info_t *cstr_info = NULL;
  OPJ_BOOL ret;
  OPJ_UINT32 len;

  (void) p_j2k;
  (void) p_manager;
  (void) p_stream;

  {if(!(p_j2k != 00)) ___assert_fail("p_j2k != 00","harness.c",253,"OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, opj_stream_private_t *, opj_event_mgr_t *)");};
  {if(!(p_manager != 00)) ___assert_fail("p_manager != 00","harness.c",254,"OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, opj_stream_private_t *, opj_event_mgr_t *)");};
  {if(!(p_stream != 00)) ___assert_fail("p_stream != 00","harness.c",255,"OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, opj_stream_private_t *, opj_event_mgr_t *)");};

  opj_write_bytes_LE(p_data, 0xff93, 2);
  p_data += 2;
  len = p_total_data_size - 4;

  p_tile_coder->tile_index = p_j2k->tile_index;
  p_tile_coder->num_comps = p_j2k->numcomps;

  if (!p_j2k->numcomps) {
    p_tile_coder->tccps[0].tccp->prg = 0;
    if (cstr_info) {
      cstr_info->prog = 0;
    }
  } else {

    *p_data_size = 0;

    if (!opj_tcd_encode_tile(p_tile_coder,
                             p_j2k->tile_index,
                             p_data,
                             p_data_size,
                             len,
                             cstr_info)) {
      opj_event_msg(p_manager, 1, "Cannot encode tile\n");
      return 0;
    }

    *p_data_size += 2;
  }

  ret = 1;

  return ret;
}