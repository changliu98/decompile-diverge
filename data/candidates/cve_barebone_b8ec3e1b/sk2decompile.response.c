static int xpm_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                            AVPacket *avpkt) {
  XPMDecContext *s = avctx->priv_data;
  AVFrame *frame = data;
  const unsigned char *p, *p_end;
  int x, i, width, height, chars_per_pixel, colors, ret, max_colors;
  unsigned char *dst;
  avctx->pix_fmt = AV_PIX_FMT_RGBA;
  p = avpkt->data;
  p_end = avpkt->data + avpkt->size;
  while (memcmp(p, "", 9) && p < p_end - 9) p++;
  if (p >= p_end) {
    av_log(avctx, 16, "missing signature\n");
    return -0x47777779;
  }
  p += mod_strcspn(p, "\"");
  if (sscanf(p, "%d %d %d %d", &width, &height, &chars_per_pixel, &colors) !=
      4) {
    av_log(avctx, 16, "missing image parameters\n");
    return -0x47777779;
  }
  if ((ret = ff_set_dimensions(avctx, width, height)) < 0) return ret;
  if ((ret = ff_get_buffer(avctx, frame, 0)) < 0) return ret;
  if (chars_per_pixel < 1 || chars_per_pixel > 4) {
    av_log(avctx, 16, "unsupported/invalid number of chars per pixel: %d\n",
           chars_per_pixel);
    return -0x47777779;
  }
  max_colors = 1;
  for (i = 0; i < chars_per_pixel; i++) max_colors *= 94;
  if (colors < 1 || colors > max_colors) {
    av_log(avctx, 16, "invalid number of colors: %d\n", colors);
    return -0x47777779;
  }
  av_fast_padded_malloc(&s->palette_size, &s->palette, max_colors * 4);
  if (!s->palette) return -12;
  p += mod_strcspn(p, ",") + 1;
  for (i = 0; i < colors; i++) {
    const unsigned char *color_string;
    unsigned char *color_rgba;
    int color_rgba_len;
    p += mod_strcspn(p, "\"") + 1;
    if (p + chars_per_pixel > p_end) return -0x47777779;
    color_string = p;
    color_rgba = strstr(p + chars_per_pixel, "c ");
    if (!color_rgba) return -0x47777779;
    color_rgba += 2;
    color_rgba_len = strcspn(color_rgba, "\" ");
    ret = ascii2index(color_string, chars_per_pixel);
    if (ret < 0) return ret;
    s->palette[ret] = color_string_to_rgba(color_rgba, color_rgba_len);
    p += mod_strcspn(p, ",") + 1;
  }
  for (i = 0; i < avctx->height; i++) {
    dst = frame->data[i];
    p += mod_strcspn(p, "\"") + 1;
    for (x = 0; x < avctx->width; x++) {
      if (p + chars_per_pixel > p_end) return -0x47777779;
      ret = ascii2index(p, chars_per_pixel);
      if (ret < 0) return ret;
      *dst++ = s->palette[ret];
      p += chars_per_pixel;
    }
    p += mod_strcspn(p, ",") + 1;
  }
  frame->key_frame = 1;
  frame->pict_type = 1;
  *got_frame = 1;
  return avpkt->size;
}