struct _gdImage *gdImageCopy(struct _gdImage *src)
{
  int i; int j;
  struct _gdImage *dst;
  if (src->trueColor)
    dst = gdImageCreateTrueColor(src->sx, src->sy);
  else
    dst = gdImageCreate(src->sx, src->sy);
  if (dst == ((void *)0))
    return ((void *)0);
  if (src->trueColor) {
    for (j = 0; j < src->sy; j++)
      for (i = 0; i < src->sx; i++)
        dst->tpixels[j][i] = src->tpixels[j][i];
  }
  else {
    dst->colorsTotal = src->colorsTotal;
    for (i = 0; i < 256; i++) {
      dst->red[i] = src->red[i];
      dst->green[i] = src->green[i];
      dst->blue[i] = src->blue[i];
      dst->alpha[i] = src->alpha[i];
      dst->open[i] = src->open[i];
    }
    for (j = 0; j < src->sy; j++)
      for (i = 0; i < src->sx; i++)
        dst->pixels[j][i] = src->pixels[j][i];
  }
  if (src->styleLength > 0) {
    dst->styleLength = src->styleLength;
    dst->stylePos = src->stylePos;
    for (i = 0; i < src->styleLength; i++)
      dst->style[i] = src->style[i];
  }
  dst->interlace = src->interlace;
  dst->alphaBlendingFlag = src->alphaBlendingFlag;
  dst->saveAlphaFlag = src->saveAlphaFlag;
  dst->AA = src->AA;
  dst->AA_color = src->AA_color;
  dst->AA_dont_blend = src->AA_dont_blend;
  dst->cx1 = src->cx1;
  dst->cy1 = src->cy1;
  dst->cx2 = src->cx2;
  dst->cy2 = src->cy2;
  dst->res_x = src->res_x;
  dst->res_y = src->res_y;
  dst->paletteQuantizationMethod = src->paletteQuantizationMethod;
  dst->paletteQuantizationSpeed = src->paletteQuantizationSpeed;
  dst->paletteQuantizationMinQuality = src->paletteQuantizationMinQuality;
  dst->paletteQuantizationMinQuality = src->paletteQuantizationMinQuality;
  dst->interpolation_id = src->interpolation_id;
  dst->interpolation = src->interpolation;
  if (src->brush != ((void *)0))
    dst->brush = gdImageCopy(src->brush);
  if (src->tile != ((void *)0))
    dst->tile = gdImageCopy(src->tile);
  if (src->style != ((void *)0))
    gdImageSetStyle(dst, src->style, src->styleLength);
  for (i = 0; i < 256; i++) {
    dst->brushColorMap[i] = src->brushColorMap[i];
    dst->tileColorMap[i] = src->tileColorMap[i];
  }
  if (src->polyAllocated > 0) {
    dst->polyAllocated = src->polyAllocated;
    for (i = 0; i < src->polyAllocated; i++)
      dst->polyInts[i] = src->polyInts[i];
  }
  return dst;
}