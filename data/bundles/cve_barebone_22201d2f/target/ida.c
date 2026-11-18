OPJ_BOOL __cdecl opj_j2k_write_sod(
        opj_j2k_t *p_j2k,
        opj_tcd_t *p_tile_coder,
        OPJ_BYTE *p_data,
        OPJ_UINT32 *p_data_written,
        OPJ_UINT32 p_total_data_size,
        const opj_stream_private_t *p_stream,
        opj_event_mgr_t *p_manager)
{
  OPJ_BYTE *p_datab; // [rsp+30h] [rbp-20h]

  if ( !p_j2k )
    __assert_fail(
      "p_j2k != 00",
      "/work/harness.c",
      0xFDu,
      "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_privat"
      "e_t *, opj_event_mgr_t *)");
  if ( !p_manager )
    __assert_fail(
      "p_manager != 00",
      "/work/harness.c",
      0xFEu,
      "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_privat"
      "e_t *, opj_event_mgr_t *)");
  if ( !p_stream )
    __assert_fail(
      "p_stream != 00",
      "/work/harness.c",
      0xFFu,
      "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_privat"
      "e_t *, opj_event_mgr_t *)");
  opj_write_bytes_LE(p_data, 0xFF93u, 2u);
  p_datab = p_data + 2;
  p_tile_coder->tp_num = p_j2k->m_specific_param.m_decoder.m_state;
  p_tile_coder->cur_tp_num = p_j2k->m_specific_param.m_encoder.m_current_tile_part_number;
  if ( !p_j2k->m_specific_param.m_encoder.m_current_tile_part_number )
    p_tile_coder->tcd_image->tiles->packno = 0;
  *p_data_written = 0;
  if ( opj_tcd_encode_tile(
         p_tile_coder,
         p_j2k->m_current_tile_number,
         p_datab,
         p_data_written,
         p_total_data_size - 4,
         0LL,
         p_manager) )
  {
    *p_data_written += 2;
    return 1;
  }
  else
  {
    opj_event_msg(p_manager, 1, "Cannot encode tile\n");
    return 0;
  }
}