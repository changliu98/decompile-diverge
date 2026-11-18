static int stbi__compute_transparency(stbi__png *p, stbi_uc *background,
                                      int out_n) {
  stbi__uint32 pixel_count = p->s->img_x * p->s->img_y;
  stbi_uc *out = p->out;
  stbi__uint32 i;
  (void)((out_n == 2 || out_n == 4) ||
         (stbi__assert("out_n == 2 || out_n == 4"), 0));
  if (out_n == 2) {
    for (i = 0; i < pixel_count; ++i) {
      out[1] = (out[0] == background[0]) ? 0 : 255;
      out += 2;
    }
  } else {
    for (i = 0; i < pixel_count; ++i) {
      if (out[0] == background[0] && out[1] == background[1] &&
          out[2] == background[2])
        out[3] = 0;
      out += 4;
    }
  }
  return 1;
}