int opj_j2k_write_sod(struct opj_j2k *p_j2k, struct opj_tcd *p_tcd, unsigned char *p_data, int *p_data_written, int p_total_data_size, void *p_tile_coder, struct opj_stream *p_stream) {
    int l_remaining_data_size;
    int l_ret_code;
    void *l_current_writer = NULL;

    // Assertions
    if (p_j2k == NULL) {
        // __assert_fail("p_j2k", "...", 0xfd, "...");
    }
    if (p_stream == NULL) {
        // __assert_fail("p_stream", "...", 0xfe, "...");
    }
    if (p_tile_coder == NULL) {
        // __assert_fail("p_tile_coder", "...", 0xff, "...");
    }

    // Write SOD marker (0xFF93) in little-endian
    opj_write_bytes_LE(p_data, 0xff93, 2);
    p_data += 2;

    l_remaining_data_size = p_total_data_size - 4;

    // Copy tile number and poc tile part number from j2k to tcd
    p_tcd->m_current_tile_number = p_j2k->m_current_tile_number;
    p_tcd->m_current_poc_tile_part_number = p_j2k->m_current_poc_tile_part_number;

    if (p_j2k->m_current_poc_tile_part_number == 0) {
        // Access nested struct through p_tcd->m_current_tile_part_offset
        int **tile_part_offset_ptr = (int **)p_tcd->m_current_tile_part_offset;
        *(*tile_part_offset_ptr) = 0;
        
        if (l_current_writer != NULL) {
            *((int *)l_current_writer + 2) = 0; // offset 0x8
        }
    }

    *p_data_written = 0;

    l_ret_code = opj_tcd_encode_tile(p_tcd, p_j2k->m_current_tile_number, p_data, p_data_written, l_remaining_data_size, l_current_writer, p_stream);

    if (l_ret_code == 0) {
        opj_event_msg((struct opj_event_mgr *)p_stream, 1, "...");
        return 0;
    } else {
        *p_data_written += 2;
        return 1;
    }
}