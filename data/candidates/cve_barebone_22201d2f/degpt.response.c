OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *j2k_codec, opj_tcd_t *tile_coder, OPJ_BYTE *output_buffer,
                           OPJ_UINT32 *bytes_written, OPJ_UINT32 buffer_size,
                           opj_stream_private_t *stream, opj_event_mgr_t *event_manager)
{
    OPJ_BOOL encode_success;

    // Validate that p_j2k pointer is not null
    if (j2k_codec == (opj_j2k_t *)0x0) {
        __assert_fail("p_j2k != 00", "/work/harness.c", 0xfd,
                      "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)");
    }
    // Validate that p_manager pointer is not null
    if (event_manager == (opj_event_mgr_t *)0x0) {
        __assert_fail("p_manager != 00", "/work/harness.c", 0xfe,
                      "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)");
    }
    // Validate that p_stream pointer is not null
    if (stream == (opj_stream_private_t *)0x0) {
        __assert_fail("p_stream != 00", "/work/harness.c", 0xff,
                      "OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *, OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *)");
    }

    // Write the Start of Data (SOD) marker (0xFF93) to the output buffer
    opj_write_bytes_LE(output_buffer, 0xff93, 2);
    
    // Update tile coder state with current tile part number from decoder state
    tile_coder->tp_num = (j2k_codec->m_specific_param).m_decoder.m_state;
    // Update current tile part number from encoder state
    tile_coder->cur_tp_num = (j2k_codec->m_specific_param).m_encoder.m_current_tile_part_number;
    
    // If this is the first tile part, reset the pack number to 0
    if ((j2k_codec->m_specific_param).m_encoder.m_current_tile_part_number == 0) {
        tile_coder->tcd_image->tiles->packno = 0;
    }
    
    // Initialize the number of bytes written to 0
    *bytes_written = 0;
    
    // Encode the tile data into the output buffer, skipping the 2-byte SOD marker
    encode_success = opj_tcd_encode_tile(tile_coder, j2k_codec->m_current_tile_number, output_buffer + 2, bytes_written,
                                buffer_size - 4, (opj_codestream_info *)0x0, event_manager);
    
    // If encoding was successful, add 2 bytes to the written count (for the SOD marker)
    if (encode_success != 0) {
        *bytes_written = *bytes_written + 2;
    }
    else {
        // Log an error message if tile encoding failed
        opj_event_msg(event_manager, 1, "Cannot encode tile\n");
    }
    
    // Return success status based on encoding result
    return (OPJ_BOOL)(encode_success != 0);
}