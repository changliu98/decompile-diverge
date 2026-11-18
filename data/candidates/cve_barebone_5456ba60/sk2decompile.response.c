static int kwajd_read_headers(struct kwajd_device *kwajd,
                              struct kwajd_drv_data *drv_data,
                              struct kwajd_data *data) {
  unsigned char buf[16];
  unsigned char *p;
  int i;
  long pos;
  int len;
  if (drv_data->read(drv_data, buf, 14) != 14) return 3;
  if ((((buf[0]) << 24) | ((buf[1]) << 16) | ((buf[2]) << 8) | (buf[3])) !=
          0x4b57414b ||
      (((buf[4]) << 24) | ((buf[5]) << 16) | ((buf[6]) << 8) | (buf[7])) !=
          0xeeeeeeee)
    return 7;
  data->width = (((buf[8]) << 8) | (buf[9]));
  data->height = (((buf[10]) << 8) | (buf[11]));
  data->flags = (((buf[12]) << 8) | (buf[13]));
  data->timestamp = 0;
  data->author = NULL;
  data->title = NULL;
  data->title_len = 0;
  if (data->flags & 1) {
    if (drv_data->read(drv_data, buf, 4) != 4) return 3;
    data->timestamp = (((buf[0]) << 24) | ((buf[1]) << 16) | ((buf[2]) << 8) |
                       (buf[3]));
  }
  if ((data->flags & 2) && drv_data->read(drv_data, buf, 2) != 2) return 3;
  if (data->flags & 4) {
    if (drv_data->read(drv_data, buf, 2) != 2) return 3;
    if (drv_data->seek(drv_data, (((buf[0]) << 8) | (buf[1])), 1)) return 5;
  }
  if (data->flags & 24) {
    pos = drv_data->tell(drv_data);
    p = drv_data->alloc(drv_data, 13);
    if (!p) return 6;
    data->author = p;
    if (data->flags & 8) {
      if (drv_data->read(drv_data, buf, 9) != 9) return 3;
      for (i = 0; i < 9; i++) {
        *p = buf[i];
        if (!*p) break;
        p++;
      }
      pos += (i < 9) ? i + 1 : 9;
      if (drv_data->seek(drv_data, pos, 0)) return 5;
    }
    if (data->flags & 16) {
      *p++ = '.';
      if (drv_data->read(drv_data, buf, 4) != 4) return 3;
      for (i = 0; i < 4; i++) {
        *p = buf[i];
        if (!*p) break;
        p++;
      }
      pos += (i < 4) ? i + 1 : 4;
      if (drv_data->seek(drv_data, pos, 0)) return 5;
    }
    *p = 0;
  }
  if (data->flags & 32) {
    if (drv_data->read(drv_data, buf, 2) != 2) return 3;
    len = (((buf[0]) << 8) | (buf[1]));
    data->title = drv_data->alloc(drv_data, len + 1);
    if (!data->title) return 6;
    if (drv_data->read(drv_data, data->title, len) != len) return 3;
    data->title[len] = 0;
    data->title_len = len;
  }
  return 0;
}