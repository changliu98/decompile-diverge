void __cdecl id3dmx_flush(
        GF_Filter *filter,
        u8 *id3_buf,
        u32 id3_buf_size,
        GF_FilterPid *audio_pid,
        GF_FilterPid **video_pid_p)
{
    GF_PropertyValue prop_val;
    GF_FilterPacket *dst_pck;
    u8 *out_buffer;
    GF_Err e;
    u32 fsize, pic_size, ftag;
    s32 tag_idx;
    char *sep, *sep_desc;
    char szTag[1024];
    char *buf;
    u32 size;
    u8 ext_hdr[5] = {0}; // Used to track unsynchronization flag and buffer capacity
    char *_buf = NULL;
    GF_BitStream *bs = gf_bs_new(id3_buf, id3_buf_size, 0);

    // Parse ID3v2 Header
    gf_bs_skip_bytes(bs, 3);         // ID3 magic
    gf_bs_read_u8(bs);              // Major version
    gf_bs_read_u8(bs);              // Minor version
    gf_bs_read_int(bs, 1);          // Unsynchronization flag
    ext_hdr[0] = (u8)gf_bs_read_int(bs, 1); // Ext header flag
    gf_bs_read_int(bs, 6);          // Remaining flags

    size = gf_id3_read_size(bs);

    // Iterate over ID3 frames
    while (size)
    {
        if (gf_bs_available(bs) < 0xA)
            break;

        ftag = gf_bs_read_u32(bs);
        fsize = gf_id3_read_size(bs);
        gf_bs_read_u16(bs); // Skip flags
        size -= 10;

        if (!fsize || size < fsize)
            break;

        // Reallocate buffer if needed (capacity stored in ext_hdr[1..4])
        if (*(u32*)&ext_hdr[1] <= fsize)
        {
            // Note: Original decompilation mapped this to a BindingManager symbol due to RTTI confusion
            _buf = (char *)realloc(_buf, fsize + 3);
            *(u32*)&ext_hdr[1] = fsize + 3;
        }

        gf_bs_read_data(bs, (u8 *)_buf + 1, fsize);
        _buf[fsize + 1] = 0;
        _buf[fsize + 2] = 0;
        buf = _buf + 1;

        tag_idx = gf_itags_find_by_id3tag(ftag);

        if (ftag == ID3_TAG_COMM)
        {
            sep = (char *)memchr(buf, 0, fsize);
            if (sep)
            {
                if (!strcasecmp(buf + 1, "comment"))
                {
                    id3dmx_set_string(audio_pid, "comment", (u8 *)sep + 1, GF_FALSE);
                }
                else
                {
                    strcpy(szTag, "tag_");
                    strncat(szTag, buf + 1, 0x3FB);
                    id3dmx_set_string(audio_pid, szTag, (u8 *)sep + 1, GF_TRUE);
                }
            }
        }
        else if (ftag == ID3_TAG_APIC)
        {
            sep = (char *)memchr(buf + 1, 0, fsize - 1);
            sep_desc = (char *)memchr(sep + 2, 0, fsize - 1);
            if (sep_desc)
            {
                pic_size = fsize - ((u32)(sep_desc + 1) - (u32)buf);

                if (video_pid_p)
                {
                    e = gf_filter_pid_raw_new(
                            filter,
                            NULL,
                            NULL,
                            buf + 1,
                            NULL,
                            (const u8 *)sep_desc + 1,
                            pic_size,
                            GF_FALSE,
                            video_pid_p);

                    if (*video_pid_p)
                    {
                        gf_filter_pid_set_name(*video_pid_p, "CoverArt");
                        
                        prop_val.type = GF_PROP_BOOL;
                        prop_val.value.boolean = GF_TRUE;
                        gf_filter_pid_set_property(*video_pid_p, 0x50434F56, &prop_val); // 'PCOV'

                        dst_pck = gf_filter_pck_new_alloc(*video_pid_p, pic_size, &out_buffer);
                        if (dst_pck)
                        {
                            gf_filter_pck_set_framing(dst_pck, GF_TRUE, GF_TRUE);
                            memcpy(out_buffer, sep_desc + 1, pic_size);
                            gf_filter_pck_send(dst_pck);
                        }
                        gf_filter_pid_set_eos(*video_pid_p);
                    }
                }
                else
                {
                    prop_val.type = GF_PROP_DATA;
                    prop_val.value.data.ptr = (u8 *)(sep_desc + 1);
                    prop_val.value.data.size = pic_size;
                    gf_filter_pid_set_property(audio_pid, 0x50434F56, &prop_val); // 'PCOV'
                }
            }
        }
        else if (tag_idx < 0)
        {
            const char *v6 = gf_4cc_to_str(ftag);
            sprintf(szTag, "tag_%s", v6);

            if (HIBYTE(ftag) == 'T') // Text frame
            {
                id3dmx_set_string(audio_pid, szTag, (u8 *)buf + 1, GF_TRUE);
            }
            else
            {
                prop_val.type = GF_PROP_DATA;
                prop_val.value.data.ptr = (u8 *)buf;
                prop_val.value.data.size = fsize;
                gf_filter_pid_set_property_dyn(audio_pid, szTag, &prop_val);
            }
        }
        else
        {
            const char *tag_name = gf_itags_get_name(tag_idx);
            id3dmx_set_string(audio_pid, (char *)tag_name, (u8 *)buf + 1, GF_FALSE);
        }

        size -= fsize;
    }

    // QScopedPointerPodDeleter::cleanup maps directly to gf_bs_del in this context
    gf_bs_del(bs);
    
    if (_buf)
        gf_free(_buf);
}