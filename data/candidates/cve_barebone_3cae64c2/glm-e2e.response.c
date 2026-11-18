void id3dmx_flush(void *filter, const void *data, int data_size, void *pid, void **out_pid) {
    void *bs = gf_bs_new(data, data_size, 0);
    void *alloc_ptr = NULL;
    int alloc_size = 0;
    char buffer[0x400]; // Used for string formatting and temporary storage

    gf_bs_skip_bytes(bs, 3);
    gf_bs_read_u8(bs);
    gf_bs_read_u8(bs);
    gf_bs_read_int(bs, 1);
    char flag = (char)gf_bs_read_int(bs, 1);
    gf_bs_read_int(bs, 6);
    int remaining_size = gf_id3_read_size(bs);

    // Empty if-else block corresponding to the branch at 0x19fa-0x1a09
    if (flag == 0) {
        // ...
    } else {
        // ...
    }

    while (remaining_size != 0 && gf_bs_available(bs) >= 10) {
        int tag = gf_bs_read_u32(bs);
        int frame_size = gf_id3_read_size(bs);
        gf_bs_read_u16(bs);
        remaining_size -= 10;

        if (frame_size == 0 || remaining_size < frame_size) {
            break;
        }

        if (alloc_size < frame_size) {
            alloc_ptr = gf_realloc(alloc_ptr, frame_size + 3);
            alloc_size = frame_size + 3;
        }

        gf_bs_read_data(bs, alloc_ptr + 1, frame_size);
        ((char *)alloc_ptr)[frame_size + 1] = 0;
        ((char *)alloc_ptr)[frame_size + 2] = 0;

        char *frame_data = (char *)alloc_ptr + 1;
        int tag_idx = gf_itags_find_by_id3tag(tag);

        if (tag == 0x54585858) { // 'XXX' or similar 4CC
            char *sep = memchr(frame_data, 0, frame_size);
            if (sep != NULL) {
                if (strcasecmp(frame_data + 1, "XXX") == 0) {
                    id3dmx_set_string(pid, "XXX", sep + 1, 0);
                } else {
                    strcpy(buffer, "XXX");
                    strncat(buffer, frame_data + 1, 0x3fb);
                    id3dmx_set_string(pid, buffer, sep + 1, 1);
                }
            }
        } else if (tag == 0x41504943) { // 'CIPA' or similar 4CC
            char *sep1 = memchr(frame_data + 1, 0, frame_size - 1);
            char *sep2 = memchr(sep1 + 2, 0, frame_size - 1);
            if (sep2 != NULL) {
                int pic_size = (sep2 + 1) - frame_data;
                int data_len = frame_size - pic_size;

                if (out_pid != NULL) {
                    int res = gf_filter_pid_raw_new(filter, 0, 0, 0, frame_data + 1, sep2 + 1, data_len, 0, 0, out_pid);
                    if (res == 0 && *out_pid != NULL) {
                        gf_filter_pid_set_name(*out_pid, "ID3 Image");
                        
                        struct GF_PropertyEntry prop;
                        prop.type = 1;
                        gf_filter_pid_set_property(*out_pid, 0x50434f56, &prop); // 'PCOV'
                        
                        void *pck_data;
                        void *pck = gf_filter_pck_new_alloc(*out_pid, data_len, &pck_data);
                        if (pck != NULL) {
                            gf_filter_pck_set_framing(pck, 1, 1);
                            memcpy(pck_data, sep2 + 1, data_len);
                            gf_filter_pck_send(pck);
                        }
                        gf_filter_pid_set_eos(*out_pid);
                    }
                } else {
                    struct GF_PropData prop;
                    prop.type = 0x10;
                    prop.ptr = sep2 + 1;
                    prop.size = data_len;
                    gf_filter_pid_set_property(pid, 0x50434f56, &prop); // 'PCOV'
                }
            }
        } else {
            if (tag_idx >= 0) {
                const char *name = gf_itags_get_name(tag_idx);
                id3dmx_set_string(pid, name, frame_data + 1, 0);
            } else {
                sprintf(buffer, "ID3_%s", gf_4cc_to_str(tag));
                if ((tag >> 24) == 'T') {
                    id3dmx_set_string(pid, buffer, frame_data + 1, 1);
                } else {
                    struct GF_PropData prop;
                    prop.type = 0x10;
                    prop.ptr = frame_data;
                    prop.size = frame_size;
                    gf_filter_pid_set_property_dyn(pid, buffer, &prop);
                }
            }
        }

        remaining_size -= frame_size;
    }

    gf_bs_del(bs);
    if (alloc_ptr != NULL) {
        gf_free(alloc_ptr);
    }
}