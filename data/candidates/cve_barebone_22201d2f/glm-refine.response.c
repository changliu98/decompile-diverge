OPJ_BOOL __cdecl opj_j2k_write_sod(
        opj_j2k_t *p_j2k,
        opj_tcd_t *p_tile_coder,
        OPJ_BYTE *p_data,
        OPJ_UINT32 *p_data_written,
        OPJ_UINT32 p_total_data_size,
        const opj_stream_private_t *p_stream,
        opj_event_mgr_t *p_manager)
{
    OPJ_BYTE *p_datab;

    // Validate arguments
    assert(p_j2k != NULL);
    assert(p_manager != NULL);
    assert(p_stream != NULL);

    // Write the SOD (Start of Data) marker 0xFF93 in little-endian
    opj_write_bytes_LE(p_data, 0xFF93u, 2u);
    p_datab = p_data + 2;

    // Sync tile coder state with j2k encoder/decoder state
    p_tile_coder->tp_num = p_j2k->m_specific_param.m_decoder.m_state;
    p_tile_coder->cur_tp_num = p_j2k->m_specific_param.m_encoder.m_current_tile_part_number;

    // Reset packet number if this is the first tile part
    if (!p_j2k->m_specific_param.m_encoder.m_current_tile_part_number) {
        p_tile_coder->tcd_image->tiles->packno = 0;
    }

    *p_data_written = 0;

    // Encode the tile data (subtract 4 from total data size for the marker and length fields)
    if (opj_tcd_encode_tile(
            p_tile_coder,
            p_j2k->m_current_tile_number,
            p_datab,
            p_data_written,
            p_total_data_size - 4,
            0LL,
            p_manager))
    {
        // Include the 2 bytes of the SOD marker itself in the written count
        *p_data_written += 2;
        return OPJ_TRUE;
    } 
    else 
    {
        opj_event_msg(p_manager, EVT_ERROR, "Cannot encode tile\n");
        return OPJ_FALSE;
    }
}