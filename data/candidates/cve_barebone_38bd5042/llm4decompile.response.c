GF_Err gf_avc_change_vui(GF_AVCConfig *avcc, GF_VUIInfo *vui_info)
{
    u32 i = 0;
    u32 bit_offset;
    AVCState avc;
    memset(&avc, 0, sizeof(AVCState));
    avc.sps_active_idx = -1;

    while (1) {
        GF_AVCConfigSlot *slc = (GF_AVCConfigSlot *)gf_list_enum(avcc->sequenceParameterSets, &i);
        u8 *data;
        u32 size;
        GF_BitStream *bs, *mod;
        u32 flag;

        if (!slc) break;

        data = NULL;

        if (gf_avc_read_sps(slc->data, slc->size, &avc, NULL, &bit_offset) < 0)
            continue;

        data = gf_malloc(slc->size - 1);
        size = gf_media_nalu_remove_emulation_bytes(slc->data + 1, data, slc->size - 1);

        bs = gf_bs_new(data, size, 0);
        gf_bs_read_data(bs, data, size);
        gf_bs_seek(bs, 0);

        mod = gf_bs_new(NULL, 0, 1);

        ((bit_offset >= 8) ? (void)0 : __assert_fail("bit_offset >= 8", "/work/harness.c", 390, "GF_Err gf_avc_change_vui(GF_AVCConfig *, GF_VUIInfo *)"));
        while (bit_offset != 8) {
            flag = gf_bs_read_int(bs, 1);
            gf_bs_write_int(mod, flag, 1);
            bit_offset--;
        }

        avc_hevc_vvc_rewrite_vui(vui_info, bs, mod, 33);

        while (gf_bs_bits_available(bs)) {
            flag = gf_bs_read_int(bs, 1);
            gf_bs_write_int(mod, flag, 1);
        }

        gf_bs_del(bs);
        gf_free(data);

        gf_bs_get_content(mod, &data, &size);

        size = gf_media_nalu_emulation_bytes_add_count(data, size);

        if (slc->size < size + 1) {
            slc->data = gf_realloc(slc->data, size + 1);
        }

        size = gf_media_nalu_add_emulation_bytes(data, slc->data + 1, size);
        slc->size = size + 1;

        gf_bs_del(mod);
        gf_free(data);
    }

    return GF_OK;
}