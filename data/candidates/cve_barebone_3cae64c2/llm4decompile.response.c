void id3dmx_flush(GF_Filter *filter,
                          u8 *id3_buf, u32 id3_buf_size,
                          GF_FilterPid *audio_pid, GF_FilterPid **video_pid_p)
{
    GF_BitStream *bs = gf_bs_new(id3_buf, id3_buf_size, 0);
    u32 size, ftag, fsize;
    char *buf = NULL;
    u32 buf_alloc = 0;
    char szTag[1024];
    char *sep;
    u32 tag_idx;
    GF_PropertyValue p;

    gf_bs_skip_bytes(bs, 3);
    gf_bs_read_u8(bs);
    gf_bs_read_u8(bs);
    gf_bs_read_int(bs, 1);
    gf_bs_read_int(bs, 1);
    gf_bs_read_int(bs, 6);
    size = gf_id3_read_size(bs);

    while (size && (gf_bs_available(bs) >= 10)) {
        ftag = gf_bs_read_u32(bs);
        fsize = gf_id3_read_size(bs);
        gf_bs_read_u16(bs);
        if (!fsize || (fsize > (size - 10))) break;

        if (buf_alloc <= fsize) {
            buf = (char *)gf_realloc(buf, fsize + 3);
            buf_alloc = fsize + 3;
        }
        gf_bs_read_data(bs, (u8 *)buf + 1, fsize);
        buf[fsize+1] = 0;
        buf[fsize+2] = 0;

        tag_idx = gf_itags_find_by_id3tag(ftag);

        if (ftag == ((((u32)'T')<<24) | (((u32)'X')<<16) | (((u32)'X')<<8) | (u32)'X')) {
            sep = strchr(buf + 1, 0);
            if (sep) {
                if (!strcasecmp(buf + 2, "comment")) {
                    id3dmx_set_string(audio_pid, "comment", (u8 *)sep + 1, GF_FALSE);
                } else {
                    strcpy(szTag, "tag_");
                    strncat(szTag, buf + 2, sizeof(szTag) - 5);
                    id3dmx_set_string(audio_pid, szTag, (u8 *)sep + 1, GF_TRUE);
                }
            }
        }
        else if (ftag == ((((u32)'A')<<24) | (((u32)'P')<<16) | (((u32)'I')<<8) | (u32)'C')) {
            u8 *ptr;
            u32 pic_size;
            sep = (char *)memchr(buf + 2, 0, fsize - 1);
            ptr = (u8 *)memchr(sep + 2, 0, fsize - 1);
            if (ptr) {
                pic_size = fsize - (ptr + 1 - (u8 *)buf);
                if (video_pid_p) {
                    GF_Err e;
                    GF_FilterPacket *dst_pck;
                    u8 *out_buffer;
                    e = gf_filter_pid_raw_new(filter, NULL, 0, buf + 2, 0, ptr + 1, pic_size, GF_FALSE, video_pid_p);
                    if (*video_pid_p) {
                        gf_filter_pid_set_name(*video_pid_p, "CoverArt");
                        p.type = GF_PROP_BOOL;
                        p.value.boolean = GF_TRUE;
                        gf_filter_pid_set_property(*video_pid_p, ((((u32)'V')<<24) | (((u32)'O')<<16) | (((u32)'C')<<8) | (u32)'O'), &p);

                        dst_pck = gf_filter_pck_new_alloc(*video_pid_p, pic_size, &out_buffer);
                        if (dst_pck) {
                            gf_filter_pck_set_framing(dst_pck, GF_TRUE, GF_TRUE);
                            memcpy(out_buffer, ptr + 1, pic_size);
                            gf_filter_pck_send(dst_pck);
                        }
                        gf_filter_pid_set_eos(*video_pid_p);
                    }
                } else {
                    p.type = GF_PROP_DATA;
                    p.value.data.ptr = ptr + 1;
                    p.value.data.size = pic_size;
                    gf_filter_pid_set_property(audio_pid, ((((u32)'V')<<24) | (((u32)'O')<<16) | (((u32)'C')<<8) | (u32)'O'), &p);
                }
            }
        }
        else if (tag_idx >= 0) {
            const char *tag_name = gf_itags_get_name(tag_idx);
            id3dmx_set_string(audio_pid, tag_name, (u8 *)buf + 2, GF_FALSE);
        }
        else {
            sprintf(szTag, "tag_%s", gf_4cc_to_str(ftag));
            if ((ftag>>24) == 'T') {
                id3dmx_set_string(audio_pid, szTag, (u8 *)buf + 2, GF_TRUE);
            } else {
                p.type = GF_PROP_DATA;
                p.value.data.size = fsize;
                p.value.data.ptr = (u8 *)buf + 1;
                gf_filter_pid_set_property_dyn(audio_pid, szTag, &p);
            }
        }

        size -= 10 + fsize;
    }

    gf_bs_del(bs);
    if (buf) gf_free(buf);
}