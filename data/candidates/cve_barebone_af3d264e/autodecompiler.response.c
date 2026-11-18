gdImagePtr gdImageCreateFromTgaCtx (FILE * in)
{
 int i, j;
 int pos = 0;
 tgaFilePtr tga = NULL;
 gdImagePtr im = NULL;

 tga = (tgaFilePtr) gdMalloc(sizeof(tgaFile));
 if (!tga) {
  return NULL;
 }
 tga->data = NULL;
 tga->palette = NULL;

 if (read_header_tga(in, tga) < 0) {
  free_tga(tga);
  return NULL;
 }

 if (read_image_tga(in, tga) < 0) {
  free_tga(tga);
  return NULL;
 }

 im = gdImageCreateTrueColor(tga->width, tga->height);
 if (!im) {
  free_tga(tga);
  return NULL;
 }

 if (tga->hdr.alpha_bits != 0) {
  gdImageAlphaBlending(im, 0);
  gdImageSaveAlpha(im, 1);
 }

 j = 0;
 for (i = 0; i < tga->height; ++i) {
  unsigned long *curline = im->tpixels[i];
  for (j = 0; j < tga->width; ++j, ++curline) {
   if (tga->hdr.bits_per_pixel == 24) {
    *curline =
        (tga->data[pos + 2] << 16) +
        (tga->data[pos + 1] << 8) + tga->data[pos];
    pos += 3;
   } else if ((tga->hdr.bits_per_pixel == 32) || (tga->hdr.alpha_bits != 0)) {
    int alpha = tga->data[pos + 3];
    *curline =
        (((0x7f - (alpha >> 1)) << 24) +
         (tga->data[pos + 2] << 16) +
         (tga->data[pos + 1] << 8) + tga->data[pos]);
    pos += 4;
   }
  }
 }

 if ((tga->hdr.flags & 0x20) && (tga->hdr.flags & 0x10)) {
  _D4core8internal2gc4impl6manualQp8ManualGC10__aggrDtorMFZv(im);
 } else if (tga->hdr.flags & 0x20) {
  gdImageFlipVertical(im);
 } else if (tga->hdr.flags & 0x10) {
  gdImageFlipHorizontal(im);
 }

 free_tga(tga);

 return im;
}