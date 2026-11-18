/* WARNING: Removing unreachable block (ram,0x00101715) */

OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *p_j2k,opj_tcd_t *p_tile_coder,OPJ_BYTE *p_data,
                          OPJ_UINT32 *p_data_written,OPJ_UINT32 p_total_data_size,
                          opj_stream_private_t *p_stream,opj_event_mgr_t *p_manager)

{
  OPJ_BOOL OVar1;
  OPJ_UINT32 l_remaining_data;
  opj_codestream_info_t *l_cstr_info;
  opj_stream_private_t *p_stream_local;
  OPJ_UINT32 p_total_data_size_local;
  OPJ_UINT32 *p_data_written_local;
  OPJ_BYTE *p_data_local;
  opj_tcd_t *p_tile_coder_local;
  opj_j2k_t *p_j2k_local;
  uint local_c;
  
  if (p_j2k == (opj_j2k_t *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("p_j2k != 00","/work/harness.c",0xfd,
                  "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)"
                 );
  }
  if (p_manager == (opj_event_mgr_t *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("p_manager != 00","/work/harness.c",0xfe,
                  "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)"
                 );
  }
  if (p_stream == (opj_stream_private_t *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("p_stream != 00","/work/harness.c",0xff,
                  "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)"
                 );
  }
  opj_write_bytes_LE(p_data,0xff93,2);
  p_tile_coder->tp_num = (p_j2k->m_specific_param).m_decoder.m_state;
  p_tile_coder->cur_tp_num = (p_j2k->m_specific_param).m_encoder.m_current_tile_part_number;
  if ((p_j2k->m_specific_param).m_encoder.m_current_tile_part_number == 0) {
    p_tile_coder->tcd_image->tiles->packno = 0;
  }
  *p_data_written = 0;
  OVar1 = opj_tcd_encode_tile(p_tile_coder,p_j2k->m_current_tile_number,p_data + 2,p_data_written,
                              p_total_data_size - 4,(opj_codestream_info *)0x0,p_manager);
  if (OVar1 != 0) {
    *p_data_written = *p_data_written + 2;
  }
  else {
    opj_event_msg(p_manager,1,"Cannot encode tile\n");
  }
  local_c = (uint)(OVar1 != 0);
  return local_c;
}