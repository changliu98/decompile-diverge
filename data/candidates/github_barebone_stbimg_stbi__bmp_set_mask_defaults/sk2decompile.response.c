static int stbi__bmp_set_mask_defaults(stbi__context *s, int depth) {
  if (depth == 3) return 1;
  if (depth) return 0;
  if (s->depth == 16) {
    s->bmask = 0x7c00;
    s->gmask = 0x03e0;
    s->rmask = 0x001f;
  } else if (s->depth == 32) {
    s->bmask = 0xff0000;
    s->gmask = 0x00ff00;
    s->rmask = 0x0000ff;
    s->amask = 0xff000000;
    s->alpha_index = 0;
  } else {
    s->amask = 0;
    s->rmask = 0;
    s->gmask = 0;
    s->bmask = 0;
  }
  return 1;
}