gdImagePtr gdImageCreateFromTgaCtx(gdIOCtxPtr infile) {
  gdImagePtr im;
  tga_data p;
  int i, j;
  int pos = 0;
  int *ptr;
  p = (tga_data)gdMalloc(sizeof(tga_data));
  if (p == NULL) {
    return NULL;
  }
  p->image = NULL;
  p->image_size = 0;
  if (read_header_tga(infile, p) < 0) {
    free_tga(p);
    return NULL;
  }
  if (read_image_tga(infile, p) < 0) {
    free_tga(p);
    return NULL;
  }
  im = gdImageCreateTrueColor(p->width, p->height);
  if (im == NULL) {
    free_tga(p);
    return NULL;
  }
  if (p->alpha) {
    gdImageAlphaBlending(im, 0);
    gdImageSaveAlpha(im, 1);
  }
  for (i = 0; i < p->height; i++) {
    ptr = im->tpixels[i];
    for (j = 0; j < p->width; j++) {
      if (p->pixel_size == 24) {
        *ptr = p->image[pos] + (p->image[pos + 1] << 8) +
               (p->image[pos + 2] << 16);
        pos += 3;
      } else if (p->pixel_size == 32 || p->alpha) {
        *ptr = p->image[pos] + (p->image[pos + 1] << 8) +
               (p->image[pos + 2] << 16) +
               ((127 - (p->image[pos + 3] >> 1)) << 24);
        pos += 4;
      }
      ptr++;
    }
  }
  if (p->flip_vertical && p->flip_horizontal) {
    aes_ctx_free(im);
  } else if (p->flip_vertical) {
    gdImageFlipVertical(im);
  } else if (p->flip_horizontal) {
    gdImageFlipHorizontal(im);
  }
  free_tga(p);
  return im;
}