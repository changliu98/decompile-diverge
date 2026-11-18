static void sycc420_to_rgb(jpeg_decompress_struct *cinfo) {
  unsigned int x, y, width, height;
  unsigned int depth, row;
  unsigned int half, full;
  int *y0, *u, *v, *r0, *g0, *b0, *y1, *r1, *g1, *b1, *r, *g, *b, *r2, *g2, *b2,
      *r3, *g3, *b3;
  depth = cinfo->comp_info[0].data_precision;
  half = 1 << (depth - 1);
  full = (1 << depth) - 1;
  width = cinfo->comp_info[0].width_in_blocks;
  height = cinfo->comp_info[0].height_in_blocks;
  y0 = cinfo->comp_info[0].component_ptr;
  u = cinfo->comp_info[1].component_ptr;
  v = cinfo->comp_info[2].component_ptr;
  r0 = (int *)malloc(width * height * sizeof(int));
  r = r0;
  g0 = (int *)malloc(width * height * sizeof(int));
  g = g0;
  b0 = (int *)malloc(width * height * sizeof(int));
  b = b0;
  if (!r0 || !g0 || !b0) {
    if (r0) free(r0);
    if (g0) free(g0);
    if (b0) free(b0);
    return;
  }
  for (row = 0; row < height & ~1; row += 2) {
    y1 = y0 + width;
    r1 = r0 + width;
    g1 = g0 + width;
    b1 = b0 + width;
    for (x = 0; x < width & ~1; x += 2) {
      sycc_to_rgb(half, full, *y0, *u, *v, r0, g0, b0);
      y0++;
      r1++;
      g1++;
      b1++;
      sycc_to_rgb(half, full, *y0, *u, *v, r1, g1, b1);
      y0++;
      r1++;
      g1++;
      b1++;
      sycc_to_rgb(half, full, *y1, *u, *v, y1, g1, b1);
      y1++;
      r1++;
      g1++;
      b1++;
      sycc_to_rgb(half, full, *y1, *u, *v, r1, g1, b1);
      y1++;
      r1++;
      g1++;
      b1++;
      u++;
      v++;
    }
    if (x < width) {
      sycc_to_rgb(half, full, *y0, *u, *v, r0, g0, b0);
      y0++;
      r0++;
      g0++;
      b0++;
      sycc_to_rgb(half, full, *y1, *u, *v, y1, g1, b1);
      u++;
      v++;
    }
    y0 += width;
    r0 += width;
    g0 += width;
    b0 += width;
  }
  if (row < height) {
    for (x = 0; x < width & ~1; x += 2) {
      sycc_to_rgb(half, full, *y0, *u, *v, r0, g0, b0);
      y0++;
      r1++;
      g1++;
      b1++;
      sycc_to_rgb(half, full, *y0, *u, *v, r1, g1, b1);
      y0++;
      r1++;
      g1++;
      b1++;
      u++;
      v++;
    }
    if (x < width) {
      sycc_to_rgb(half, full, *y0, *u, *v, r0, g0, b0);
    }
  }
  free(cinfo->comp_info[0].component_ptr);
  cinfo->comp_info[0].component_ptr = r;
  free(cinfo->comp_info[1].component_ptr);
  cinfo->comp_info[1].component_ptr = g;
  free(cinfo->comp_info[2].component_ptr);
  cinfo->comp_info[2].component_ptr = b;
  cinfo->comp_info[1].width_in_blocks = width;
  cinfo->comp_info[1].height_in_blocks = height;
  cinfo->comp_info[2].width_in_blocks = width;
  cinfo->comp_info[2].height_in_blocks = height;
  cinfo->comp_info[1].component_id = cinfo->comp_info[0].component_id;
  cinfo->comp_info[2].component_id = cinfo->comp_info[0].component_id;
  cinfo->comp_info[1].h_samp_factor = cinfo->comp_info[0].h_samp_factor;
  cinfo->comp_info[2].h_samp_factor = cinfo->comp_info[0].h_samp_factor;
}