void gf_avc_change_vui(AVCConfig *cfg, void *vui) {
    void *bs = NULL;
    u8 sps_data[0x9438];
    u32 sps_data_size = 0;
    u32 idx = 0;
    NALU *nalu = NULL;
    u8 *raw_nalu = NULL;
    u32 raw_nalu_size = 0;
    u32 emulation_bytes_count = 0;
    u32 bits_to_copy = 0;
    u32 bit_val = 0;
    void *bs_out = NULL;

    memset(sps_data, 0, sizeof(sps_data));
    sps_data[0x5800] = 0xFF; // -0x3c58(%rbp) relative to %rbp is offset 0x5800 in the array

    while ((nalu = gf_list_enum(cfg->sps_list, &idx)) != NULL) {
        if (gf_avc_read_sps(nalu->data, nalu->size, sps_data, &sps_data_size, &bits_to_copy) < 0) {
            if (bs) {
                gf_bs_del(bs);
            }
            continue;
        }

        raw_nalu = gf_malloc(nalu->size - 1);
        raw_nalu_size = gf_media_nalu_remove_emulation_bytes(nalu->data + 1, raw_nalu, nalu->size - 1);
        
        bs = gf_bs_new(raw_nalu, raw_nalu_size, 0);
        gf_bs_read_data(bs, raw_nalu, raw_nalu_size);
        gf_bs_seek(bs, 0);
        
        bs_out = gf_bs_new(NULL, 1, 1);

        assert(bits_to_copy >= 8);

        while (bits_to_copy - 8 != 0) {
            bit_val = gf_bs_read_int(bs, 1);
            gf_bs_write_int(bs_out, bit_val, 1);
            bits_to_copy--;
        }

        avc_hevc_vvc_rewrite_vui(vui, bs, bs_out, 0x21);

        while (gf_bs_bits_available(bs)) {
            bit_val = gf_bs_read_int(bs, 1);
            gf_bs_write_int(bs_out, bit_val, 1);
        }

        gf_bs_del(bs);
        bs = NULL;
        gf_free(raw_nalu);

        gf_bs_get_content(bs_out, &raw_nalu, &raw_nalu_size);
        emulation_bytes_count = gf_media_nalu_emulation_bytes_add_count(raw_nalu, raw_nalu_size);

        if (raw_nalu_size + emulation_bytes_count + 1 > nalu->size) {
            nalu->data = gf_realloc(nalu->data, raw_nalu_size + emulation_bytes_count + 1);
        }

        nalu->size = gf_media_nalu_add_emulation_bytes(raw_nalu, nalu->data + 1, raw_nalu_size) + 1;

        gf_bs_del(bs_out);
        gf_free(raw_nalu);
    }
}