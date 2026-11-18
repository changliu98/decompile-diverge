OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *p_j2k,
                           opj_tcd_t *p_tile_coder,
                           OPJ_BYTE *p_data,
                           OPJ_UINT32 *p_data_written,
                           OPJ_UINT32 p_total_data_size,
                           const opj_stream_private_t *p_stream,
                           opj_event_mgr_t *p_manager)
{
    (void)p_stream;

    ((p_j2k != NULL) ? (void)0 : __assert_fail("p_j2k != NULL", "/work/harness.c", 253, "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)"));
    ((p_manager != NULL) ? (void)0 : __assert_fail("p_manager != NULL", "/work/harness.c", 254, "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)"));
    ((p_stream != NULL) ? (void)0 : __assert_fail("p_stream != NULL", "/work/harness.c", 255, "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)"));

    opj_write_bytes_LE(p_data, 0xff93, 2);
    p_data += 2;

    p_tile_coder->tp_num = (p_j2k->m_specific_param).m_decoder.m_state;
    p_tile_coder->cur_tp_num = (p_j2k->m_specific_param).m_encoder.m_current_tile_part_number;

    if ((p_j2k->m_specific_param).m_encoder.m_current_tile_part_number == 0) {
        p_tile_coder->tcd_image->tiles->packno = 0;
    }

    *p_data_written = 0;

    if (!opj_tcd_encode_tile(p_tile_coder,
                             p_j2k->m_current_tile_number,
                             p_data,
                             p_data_written,
                             p_total_data_size - 4,
                             NULL,
                             p_manager)) {
        opj_event_msg(p_manager, 1, "Cannot encode tile\n");
        return 0;
    }

    *p_data_written += 2;

    return 1;
}