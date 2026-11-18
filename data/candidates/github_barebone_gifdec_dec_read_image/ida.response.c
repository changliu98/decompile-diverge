int __cdecl read_image(gd_GIF *gif)
{
  uint16_t fh; // [rsp+0h] [rbp-20h]
  uint16_t fw; // [rsp+4h] [rbp-1Ch]
  int interlace; // [rsp+8h] [rbp-18h]
  uint8_t fisrz; // [rsp+Fh] [rbp-11h] BYREF
  gd_GIF *gifa; // [rsp+10h] [rbp-10h]

  gifa = gif;
  gif->fx = read_num(gif->fd);
  gifa->fy = read_num(gifa->fd);
  if ( gifa->fx >= (int)gifa->width || gifa->fy >= (int)gifa->height )
    return -1;
  gifa->fw = read_num(gifa->fd);
  gifa->fh = read_num(gifa->fd);
  if ( gifa->fw >= gifa->width - gifa->fx )
    fw = gifa->width - gifa->fx;
  else
    fw = gifa->fw;
  gifa->fw = fw;
  if ( gifa->fh >= gifa->height - gifa->fy )
    fh = gifa->height - gifa->fy;
  else
    fh = gifa->fh;
  gifa->fh = fh;
  read(gifa->fd, &fisrz, 1uLL);
  interlace = fisrz & 0x40;
  if ( (fisrz & 0x80) != 0 )
  {
    gifa->lct.size = 1 << ((fisrz & 7) + 1);
    read(gifa->fd, gifa->lct.colors, 3 * gifa->lct.size);
    gifa->palette = &gifa->lct;
  }
  else
  {
    gifa->palette = &gifa->gct;
  }
  return read_image_data(gifa, interlace);
}