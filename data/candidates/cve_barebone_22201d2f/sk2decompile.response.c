OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *p_j2k, opj_tcd_t *p_tcd, OPJ_BYTE *p_data,
                           OPJ_UINT32 *p_data_written, OPJ_UINT32 p_data_size,
                           const opj_image_t *p_image,
                           opj_event_mgr_t *p_manager) {
  assert(p_j2k != 00);
  assert(p_manager != 00);
  assert(p_image != 00);
  opj_write_bytes_LE(p_data, 0xff91, 2);
  p_data += 2;
  p_tcd->m_current_tile_number = p_j2k->m_cp.m_tc.m_current_tile_number;
  p_tcd->m_current_image_number = p_j2k->m_cp.m_tp.m_current_image_number;
  if (p_j2k->m_cp.m_tp.m_current_image_number == 0) {
    p_tcd->m_private_image->m_tccp->m_current_image_index = 0;
  }
  *p_data_written = 0;
  if (!opj_tcd_encode_tile(p_tcd, p_j2k->m_cstr_info, p_data, p_data_written,
                           p_data_size - 4, 0, p_manager)) {
    opj_event_msg(p_manager, 1, "Cannot encode tile\n");
    return 0;
  }
  *p_data_written += 2;
  return 1;
}