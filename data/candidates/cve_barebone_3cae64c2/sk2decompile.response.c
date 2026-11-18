void id3dmx_flush(gf_filter_t *p_filter, unsigned char *p_data,
                  unsigned p_data_len, gf_filter_pid_t *p_pid,
                  gf_filter_pid_t **pp_pid_coverart) {
  gf_bs_t *p_bs = gf_bs_new(p_data, p_data_len, 0);
  unsigned char *p_buffer = NULL;
  unsigned p_buffer_size = 0;
  unsigned i_tag;
  unsigned i_tag_size;
  unsigned i_version;
  unsigned i_size;
  unsigned i_coverart_size;
  unsigned char *p_tag_data;
  unsigned char *p_coverart_data;
  char p_name[1024];
  int i_itag;
  gf_bs_skip_bytes(p_bs, 3);
  gf_bs_read_u8(p_bs);
  gf_bs_read_u8(p_bs);
  gf_bs_read_int(p_bs, 1);
  i_version = gf_bs_read_int(p_bs, 1) & 0xff;
  gf_bs_read_int(p_bs, 6);
  i_size = gf_id3_read_size(p_bs);
  while (i_size && gf_bs_available(p_bs) >= 10) {
    i_tag = gf_bs_read_u32(p_bs);
    i_tag_size = gf_id3_read_size(p_bs);
    gf_bs_read_u16(p_bs);
    i_size -= 10;
    if (i_tag_size == 0 || i_size < i_tag_size) break;
    if (i_tag_size >= p_buffer_size) {
      p_buffer = (unsigned char *)_gf_realloc(p_buffer, i_tag_size + 3);
      p_buffer_size = i_tag_size + 3;
    }
    gf_bs_read_data(p_bs, p_buffer + 1, i_tag_size);
    p_buffer[i_tag_size + 1] = 0;
    p_buffer[i_tag_size + 2] = 0;
    p_tag_data = p_buffer + 1;
    i_itag = gf_itags_find_by_id3tag(i_tag);
    if (i_tag == 0x54414748) {
      p_coverart_data = memchr(p_tag_data, 0, i_tag_size);
      if (p_coverart_data) {
        if (!strcasecmp((char *)p_tag_data + 1, "comment")) {
          id3dmx_set_string(p_pid, "comment", p_coverart_data + 1,
                            GF_FILTER_PID_RAW_STRING);
        } else {
          strcpy(p_name, "tag_");
          strncat(p_name, (char *)p_tag_data + 1, 1024 - 4);
          id3dmx_set_string(p_pid, p_name, p_coverart_data + 1,
                            GF_FILTER_PID_RAW_BINARY);
        }
      }
    } else if (i_tag == 0x41564303) {
      p_coverart_data = memchr(p_tag_data + 1, 0, i_tag_size - 1);
      p_coverart_data++;
      p_coverart_data = memchr(p_coverart_data, 0, i_tag_size - 1);
      if (p_coverart_data) {
        i_coverart_size = p_coverart_data + 1 - p_tag_data;
        i_coverart_size = i_tag_size - i_coverart_size;
        if (pp_pid_coverart) {
          gf_filter_t *p_pck;
          unsigned char *p_pck_data;
          p_pck = gf_filter_pid_raw_new(p_filter, NULL, 0, p_tag_data + 1, 0,
                                        p_coverart_data + 1, i_coverart_size,
                                        GF_FILTER_PID_RAW_STRING,
                                        pp_pid_coverart);
          if (*pp_pid_coverart) {
            gf_filter_pid_property_t prop;
            gf_filter_pid_set_name(*pp_pid_coverart, "CoverArt");
            prop.i_type = GF_FILTER_PID_RAW_BINARY;
            gf_filter_pid_set_property(*pp_pid_coverart, 0x4f4b4156, &prop);
            p_pck = gf_filter_pck_new_alloc(*pp_pid_coverart, i_coverart_size,
                                            &p_pck_data);
            if (p_pck) {
              gf_filter_pck_set_framing(p_pck, GF_FILTER_PID_RAW_BINARY,
                                        GF_FILTER_PID_RAW_BINARY);
              memcpy(p_pck_data, p_coverart_data + 1, i_coverart_size);
              gf_filter_pck_send(p_pck);
            }
            gf_filter_pid_set_eos(*pp_pid_coverart);
          }
        } else {
          gf_filter_pid_property_t prop;
          prop.i_type = GF_FILTER_PID_PROPERTY_BINARY;
          prop.value.p_binary = p_coverart_data + 1;
          prop.value.i_binary = i_coverart_size;
          gf_filter_pid_set_property(p_pid, 0x4f4b4156, &prop);
        }
      }
    } else if (i_itag >= 0) {
      id3dmx_set_string(p_pid, gf_itags_get_name(i_itag), p_tag_data + 1,
                        GF_FILTER_PID_RAW_STRING);
    } else {
      gf_filter_pid_property_t prop;
      sprintf(p_name, "tag_%s", gf_4cc_to_str(i_tag));
      if ((i_tag >> 24) == 'T') {
        id3dmx_set_string(p_pid, p_name, p_tag_data + 1,
                          GF_FILTER_PID_RAW_BINARY);
      } else {
        prop.i_type = GF_FILTER_PID_PROPERTY_BINARY;
        prop.value.p_binary = p_tag_data;
        prop.value.i_binary = i_tag_size;
        gf_filter_pid_set_property_dyn(p_pid, p_name, &prop);
      }
    }
    i_size -= i_tag_size;
  }
  gf_bs_delete(p_bs);
  if (p_buffer) gf_free(p_buffer);
}