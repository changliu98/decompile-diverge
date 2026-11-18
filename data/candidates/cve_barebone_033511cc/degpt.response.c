gdImagePtr gdImageClone(gdImagePtr src)

{
  gdImagePtr pgVar1;
  int x;
  int i;
  gdImagePtr dst;
  gdImagePtr src_local;
  gdImagePtr local_10;
  
  if (src->trueColor == 0) {
    dst = gdImageCreate(src->sx,src->sy);
  }
  else {
    dst = gdImageCreateTrueColor(src->sx,src->sy);
  }
  if (dst == (gdImagePtr)0x0) {
    local_10 = (gdImagePtr)0x0;
  }
  else {
    if (src->trueColor == 0) {
      dst->colorsTotal = src->colorsTotal;
      for (i = 0; i < 0x100; i = i + 1) {
        dst->red[i] = src->red[i];
        dst->green[i] = src->green[i];
        dst->blue[i] = src->blue[i];
        dst->alpha[i] = src->alpha[i];
        dst->open[i] = src->open[i];
      }
      for (i = 0; i < src->sy; i = i + 1) {
        for (x = 0; x < src->sx; x = x + 1) {
          dst->pixels[i][x] = src->pixels[i][x];
        }
      }
    }
    else {
      for (i = 0; i < src->sy; i = i + 1) {
        for (x = 0; x < src->sx; x = x + 1) {
          dst->tpixels[i][x] = src->tpixels[i][x];
        }
      }
    }
    if (0 < src->styleLength) {
      dst->styleLength = src->styleLength;
      dst->stylePos = src->stylePos;
      for (i = 0; i < src->styleLength; i = i + 1) {
        dst->style[i] = src->style[i];
      }
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
    if (src->brush != (gdImageStruct *)0x0) {
      pgVar1 = gdImageClone(src->brush);
      dst->brush = pgVar1;
    }
    if (src->tile != (gdImageStruct *)0x0) {
      pgVar1 = gdImageClone(src->tile);
      dst->tile = pgVar1;
    }
    if (src->style != (int *)0x0) {
      gdImageSetStyle(dst,src->style,src->styleLength);
    }
    for (i = 0; i < 0x100; i = i + 1) {
      dst->brushColorMap[i] = src->brushColorMap[i];
      dst->tileColorMap[i] = src->tileColorMap[i];
    }
    if (0 < src->polyAllocated) {
      dst->polyAllocated = src->polyAllocated;
      for (i = 0; i < src->polyAllocated; i = i + 1) {
        dst->polyInts[i] = src->polyInts[i];
      }
    }
    local_10 = dst;
  }
  return local_10;
}