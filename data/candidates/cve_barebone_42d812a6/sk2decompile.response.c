int MPEG12_ParseSeqHdr(unsigned char *p_buf, unsigned int i_buf,
                       int *pi_progressive, unsigned int *pi_width,
                       unsigned int *pi_height, double *pf_fps,
                       double *pf_bitrate, unsigned int *pi_vbv_delay) {
  unsigned int i;
  unsigned int i_code;
  unsigned int i_bitrate;
  unsigned int i_vbv_delay;
  int i_ret = -1;
  *pi_progressive = 0;
  i_bitrate = 0;
  for (i = 0; i < i_buf - 6; i++) {
    i_code = (p_buf[0] << 24) | (p_buf[1] << 16) | (p_buf[2] << 8) | p_buf[3];
    if (i_code == 0x01B3) {
      p_buf += 4;
      *pi_height = p_buf[0];
      *pi_height <<= 4;
      *pi_height |= (p_buf[1] >> 4) & 0x0F;
      *pi_width = p_buf[1] & 0x0F;
      *pi_width <<= 8;
      *pi_width |= p_buf[2];
      i_vbv_delay = (p_buf[3] >> 4) & 0x0F;
      if (pi_vbv_delay) {
        unsigned int i_delay = 0;
        switch (i_vbv_delay) {
          case 2:
            i_delay = 0x3FFFF;
            break;
          case 3:
            i_delay = 0xFFFFF;
            break;
          case 4:
            i_delay = 0x20005;
            break;
          default:
            *pi_vbv_delay = 0;
            break;
        }
        *pi_vbv_delay = i_delay;
      }
      *pf_fps = mpeg12_fps_tab[p_buf[3] & 0x0F];
      i_bitrate = (p_buf[4] << 10) + (p_buf[5] << 2) + (p_buf[6] >> 6);
      *pf_bitrate = (double)i_bitrate;
      *pf_bitrate *= 400.0;
      i += 11;
      p_buf += 7;
      i_ret = 0;
    } else if (i_ret == 0) {
      if (i_code == 0x01B5) {
        p_buf += 4;
        i += 4;
        if ((p_buf[0] >> 4) == 1) {
          *pi_progressive = 1;
          *pi_width = (*pi_width & 0x0FFF) | ((p_buf[1] & 0x01) << 13) |
                      ((p_buf[2] & 0x80) << 5);
          *pi_height = (*pi_height & 0x0FFF) | ((p_buf[2] & 0x60) << 7);
          i_bitrate |= (((p_buf[3] >> 1) | ((p_buf[2] & 0x1F) << 7)) << 18);
          *pf_bitrate = (double)i_bitrate;
          *pf_bitrate *= 400.0;
        }
        p_buf++;
        i++;
      } else if (i_code == 0x0100) {
        return 0;
      }
    }
    p_buf++;
  }
  return i_ret;
}