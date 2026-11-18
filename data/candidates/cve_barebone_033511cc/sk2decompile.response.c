gdImagePtr gdImageClone(gdImagePtr src) {
  gdImagePtr dst;
  int x, y, i;
  if (src->trueColor) {
    dst = gdImageCreateTrueColor(src->sx, src->sy);
  } else {
    dst = gdImageCreate(src->sx, src->sy);
  }
  if (!dst) {
    return NULL;
  }
  if (src->trueColor) {
    for (y = 0; y < src->sy; y++) {
      for (x = 0; x < src->sx; x++) {
        dst->tpixels[y][x] = src->tpixels[y][x];
      }
    }
  } else {
    dst->colorsTotal = src->colorsTotal;
    for (x = 0; x < 256; x++) {
      dst->red[x] = src->red[x];
      dst->green[x] = src->green[x];
      dst->blue[x] = src->blue[x];
      dst->alpha[x] = src->alpha[x];
      dst->alphaBlendFlag[x] = src->alphaBlendFlag[x];
    }
    for (y = 0; y < src->sy; y++) {
      for (x = 0; x < src->sx; x++) {
        dst->pixels[y][x] = src->pixels[y][x];
      }
    }
  }
  if (src->styleLength > 0) {
    dst->styleLength = src->styleLength;
    dst->styleType = src->styleType;
    for (x = 0; x < src->styleLength; x++) {
      dst->style[x] = src->style[x];
    }
  }
  dst->interlace = src->interlace;
  dst->transparent = src->transparent;
  dst->alphaBlendingFlag = src->alphaBlendingFlag;
  dst->saveAlphaFlag = src->saveAlphaFlag;
  dst->alphaSaveFlag = src->alphaSaveFlag;
  dst->alphaBlendFlag = src->alphaBlendFlag;
  dst->alphaTransparency = src->alphaTransparency;
  dst->alphaMask = src->alphaMask;
  dst->blendMode = src->blendMode;
  dst->alphaFactor = src->alphaFactor;
  dst->saveAlphaThreshold = src->saveAlphaThreshold;
  dst->thickness = src->thickness;
  dst->thicknessSet = src->thicknessSet;
  dst->textureBgColor = src->textureBgColor;
  dst->textureFgColor = src->textureFgColor;
  dst->textureAlpha = src->textureAlpha;
  if (src->interpolation_id) {
    dst->interpolation_id = gdImageClone(src->interpolation_id);
  }
  if (src->interpolation_quality) {
    dst->interpolation_quality = gdImageClone(src->interpolation_quality);
  }
  if (src->style) {
    gdImageSetStyle(dst, src->style, src->styleLength);
  }
  for (x = 0; x < 256; x++) {
    dst->open[x] = src->open[x];
    dst->close[x] = src->close[x];
  }
  if (src->num_chunks > 0) {
    dst->num_chunks = src->num_chunks;
    for (i = 0; i < src->num_chunks; i++) {
      dst->chunks[i] = src->chunks[i];
    }
  }
  return dst;
}