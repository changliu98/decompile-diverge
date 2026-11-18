int read_image(gd_GIF *gif)

{
  uint16_t uVar1;
  int interlace;
  uint8_t fisrz;
  gd_GIF *gif_local;
  int local_c;
  
  gif_local = gif;
  uVar1 = read_num(gif->fd);
  gif_local->fx = uVar1;
  uVar1 = read_num(gif_local->fd);
  gif_local->fy = uVar1;
  if ((gif_local->fx < gif_local->width) && (gif_local->fy < gif_local->height)) {
    uVar1 = read_num(gif_local->fd);
    gif_local->fw = uVar1;
    uVar1 = read_num(gif_local->fd);
    gif_local->fh = uVar1;
    if ((int)(uint)gif_local->fw < (int)((uint)gif_local->width - (uint)gif_local->fx)) {
      uVar1 = gif_local->fw;
    }
    else {
      uVar1 = gif_local->width - gif_local->fx;
    }
    gif_local->fw = uVar1;
    if ((int)(uint)gif_local->fh < (int)((uint)gif_local->height - (uint)gif_local->fy)) {
      uVar1 = gif_local->fh;
    }
    else {
      uVar1 = gif_local->height - gif_local->fy;
    }
    gif_local->fh = uVar1;
    read(gif_local->fd,&fisrz,1);
    if ((fisrz & 0x80) == 0) {
      gif_local->palette = &gif_local->gct;
    }
    else {
      (gif_local->lct).size = 1 << (fisrz & 7) + 1;
      read(gif_local->fd,(gif_local->lct).colors,(long)((gif_local->lct).size * 3));
      gif_local->palette = &gif_local->lct;
    }
    local_c = read_image_data(gif_local,fisrz & 0x40);
  }
  else {
    local_c = -1;
  }
  return local_c;
}