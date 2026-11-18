static int opj_j2k_write_sod(opj_j2k_t *p_j2k, opj_tcd_t *p_tile_coder, void *p_data, unsigned int *p_data_written, unsigned int p_total_data_size, struct opj_stream_private *p_stream, struct opj_event_mgr *p_manager)
{
  unsigned char *p_data_ptr = (opj_uint8 *) p_data;
  if (p_j2k != ((void *)0))
  {
  }
  else
  {
    opj_j2k_error("p_j2k != 00", "/work/harness.c", 253, "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, void *, unsigned int *, unsigned int, struct opj_stream_private *, struct opj_event_mgr *)");
  }
  if (p_manager != ((void *)0))
  {
  }
  else
  {
    opj_j2k_error("p_manager != 00", "/work/harness.c", 254, "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, void *, unsigned int *, unsigned int, struct opj_stream_private *, struct opj_event_mgr *)");
  }
  if (p_stream != ((void *)0))
  {
  }
  else
  {
    opj_j2k_error("p_stream != 00", "/work/harness.c", 255, "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, void *, unsigned int *, unsigned int, struct opj_stream_private *, struct opj_event_mgr *)");
  }
  opj_write_int16(p_data_ptr, 0xff93, sizeof(int16));
  p_data_ptr += sizeof(int16);
  p_tile_coder->tp_num = p_j2k->m_specific_param.m_decoder.m_state.m_num_tile_parts;
  p_tile_coder->cur_tp_num = p_j2k->m_specific_param.m_encoder.m_current_tile_part_number;
  if (p_tile_coder->cur_tp_num == 0)
  {
    p_tile_coder->tcd_image->tiles->packno = 0;
  }
  *p_data_written = 0;
  if (opj_tcd_write_header(p_tile_coder, p_j2k->m_current_tile_number, p_data_ptr, p_data_written, p_total_data_size - sizeof(int16), ((void *)0), p_manager))
  {
    *p_data_written += sizeof(int16);
    return 1;
  }
  else
  {
    opj_j2k_error_mgr(p_manager, 1, "Cannot encode tile\n");
    return 0;
  }
}